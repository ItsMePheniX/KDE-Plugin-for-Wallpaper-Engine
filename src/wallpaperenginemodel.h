#pragma once
#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

class WallpaperEngineProject {
public:
    QString projectPath; // directory path
    QString title;
    QString author;
    QString type; // expect "video"
    QString videoFile; // absolute path
    QString previewFile; // absolute path (optional)
};

class WallpaperEngineModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(bool pathExists READ pathExists NOTIFY rootPathChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles { TitleRole = Qt::UserRole + 1, AuthorRole, VideoPathRole, PreviewPathRole, ProjectPathRole };
    Q_ENUM(Roles)

    explicit WallpaperEngineModel(QObject *parent = nullptr);
    Q_INVOKABLE void useDefaultSteamPath();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

    QString rootPath() const { return m_rootPath; }
    void setRootPath(const QString &path);

    Q_INVOKABLE void reload();

    QString lastError() const { return m_lastError; }
    bool pathExists() const { return QDir(m_rootPath).exists(); }
    int count() const { return m_projects.size(); }

signals:
    void rootPathChanged();
    void lastErrorChanged();
    void countChanged();

private:
    QString m_rootPath;
    QVector<WallpaperEngineProject> m_projects;
    QString m_lastError;
    void scan();
    bool loadProject(const QString &dirPath, WallpaperEngineProject &out);
};
