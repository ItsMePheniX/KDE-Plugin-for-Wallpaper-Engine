#include "wallpaperenginemodel.h"
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QDirIterator>
#include <QDebug>

static bool isVideoFile(const QString &file) {
    QString lower = file.toLower();
    return lower.endsWith(".mp4") || lower.endsWith(".webm") || lower.endsWith(".mov") || lower.endsWith(".mkv");
}

WallpaperEngineModel::WallpaperEngineModel(QObject *parent) : QAbstractListModel(parent) {
}

void WallpaperEngineModel::useDefaultSteamPath() {
    setRootPath(QStringLiteral("/home/AadityaA/.local/share/Steam/steamapps/workshop/content/431960"));
}

int WallpaperEngineModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_projects.size();
}

QVariant WallpaperEngineModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_projects.size()) return {};
    const auto &p = m_projects.at(index.row());
    switch (role) {
        case TitleRole: return p.title;
        case AuthorRole: return p.author;
        case VideoPathRole: return p.videoFile;
        case PreviewPathRole: return p.previewFile;
        case ProjectPathRole: return p.projectPath;
        default: return {};
    }
}

QHash<int,QByteArray> WallpaperEngineModel::roleNames() const {
    return {
        { TitleRole, "title" },
        { AuthorRole, "author" },
        { VideoPathRole, "videoPath" },
        { PreviewPathRole, "previewPath" },
        { ProjectPathRole, "projectPath" }
    };
}

void WallpaperEngineModel::setRootPath(const QString &path) {
    if (m_rootPath == path) return;
    m_rootPath = path;
    emit rootPathChanged();
    reload();
}

void WallpaperEngineModel::reload() {
    beginResetModel();
    m_projects.clear();
    m_lastError.clear();
    qDebug() << "[WallpaperEngineModel] Reloading root path:" << m_rootPath;
    scan();
    endResetModel();
    emit lastErrorChanged();
    emit countChanged();
}

void WallpaperEngineModel::scan() {
    if (m_rootPath.isEmpty()) return;
    QDir root(m_rootPath);
    if (!root.exists()) {
        m_lastError = QStringLiteral("Path does not exist");
        qDebug() << "[WallpaperEngineModel] Root path does not exist:" << m_rootPath;
        return;
    }

    const auto entries = root.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if (entries.isEmpty()) {
        m_lastError = QStringLiteral("No subdirectories found");
    }
    for (const QString &dirName : entries) {
        const QString dirPath = root.absoluteFilePath(dirName);
        WallpaperEngineProject proj;
        if (loadProject(dirPath, proj)) {
            m_projects.push_back(proj);
            qDebug() << "[WallpaperEngineModel] Accepted project" << dirName << "video:" << proj.videoFile;
        } else {
            qDebug() << "[WallpaperEngineModel] Skipped directory" << dirName << "(no playable video)";
        }
    }
    if (m_projects.isEmpty() && m_lastError.isEmpty()) {
        m_lastError = QStringLiteral("No video projects (type=video with playable file) found");
        qDebug() << "[WallpaperEngineModel] No video projects found under" << m_rootPath;
    }
    qDebug() << "[WallpaperEngineModel] scan complete. Projects:" << m_projects.size();
}

static QString findVideoRecursive(const QString &dirPath) {
    QDirIterator it(dirPath, QStringList() << "*.mp4" << "*.webm" << "*.mov" << "*.mkv",
                    QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString f = it.next();
        if (QFileInfo::exists(f)) return f;
    }
    return {};
}

bool WallpaperEngineModel::loadProject(const QString &dirPath, WallpaperEngineProject &out) {
    QFileInfo info(dirPath);
    if (!info.isDir()) return false;
    QString jsonPath = dirPath + "/project.json";
    QFile jsonFile(jsonPath);
    QJsonObject obj;
    QString type;
    if (jsonFile.open(QIODevice::ReadOnly)) {
        QByteArray data = jsonFile.readAll();
        QJsonParseError err; QJsonDocument doc = QJsonDocument::fromJson(data, &err);
        if (err.error == QJsonParseError::NoError && doc.isObject()) {
            obj = doc.object();
            type = obj.value("type").toString();
        }
        jsonFile.close();
    }
    // Accept if type is "video" or not specified (fallback by probing files). Reject if explicitly non-video.
    bool explicitNonVideo = (!type.isEmpty() && type.compare("video", Qt::CaseInsensitive) != 0);

    out.projectPath = dirPath;
    out.type = type;
    out.title = obj.value("title").toString(info.fileName());
    out.author = obj.value("author").toString();

    // Determine video file: either explicit field or first matching video in dir
    QString videoRelative = obj.value("file").toString();
    if (!videoRelative.isEmpty()) {
        QString candidate = dirPath + "/" + videoRelative;
        if (QFileInfo::exists(candidate) && isVideoFile(candidate)) {
            out.videoFile = candidate;
        }
    }
    if (out.videoFile.isEmpty()) {
        // Fallback: recursive scan for first supported video file anywhere inside project
        out.videoFile = findVideoRecursive(dirPath);
    }
    if (out.videoFile.isEmpty()) {
        // If no playable video was found, reject project
        return false;
    }
    // If root declared a different type (e.g. "color") but we found a video, still accept.

    // Preview
    QString previewRel = obj.value("preview").toString();
    if (!previewRel.isEmpty()) {
        QString previewCandidate = dirPath + "/" + previewRel;
        if (QFileInfo::exists(previewCandidate)) {
            out.previewFile = previewCandidate;
        }
    }
    if (out.previewFile.isEmpty()) {
        // common names
        QStringList candidates = {"preview.png","preview.jpg","preview.jpeg","thumb.png","thumb.jpg"};
        for (const QString &c : candidates) {
            QString full = dirPath + "/" + c;
            if (QFileInfo::exists(full)) { out.previewFile = full; break; }
        }
    }
    return true;
}
