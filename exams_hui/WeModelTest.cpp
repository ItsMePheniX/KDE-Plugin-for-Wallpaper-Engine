#include <QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QDir>
#include "wallpaperenginemodel.h"

static void writeFile(const QString &path, const QByteArray &data = QByteArray()) {
    QFile f(path);
    QVERIFY2(f.open(QIODevice::WriteOnly), qPrintable(QString("Failed to write %1").arg(path)));
    if (!data.isEmpty()) QVERIFY(f.write(data) >= 0);
}

class WeModelTest : public QObject {
    Q_OBJECT
private slots:
    void test_validVideoProject_listsOne();
    void test_nonVideoType_skipped();
    void test_missingProjectJson_skipped();
    void test_missingVideoFile_skipped();
    void test_previewDetection_optional();
    void test_realSteamPath();
};

void WeModelTest::test_validVideoProject_listsOne() {
    QTemporaryDir tmp;
    QVERIFY(tmp.isValid());
    QDir root(tmp.path());
    QVERIFY(root.mkdir("12345"));
    const QString projDir = root.absoluteFilePath("12345");

    // minimal project.json
    const QByteArray json = R"({
        "type": "video",
        "title": "Foo",
        "author": "Bar",
        "file": "video.mp4"
    })";
    writeFile(projDir + "/project.json", json);
    // create dummy video file (empty is fine for our existence check)
    writeFile(projDir + "/video.mp4");

    WallpaperEngineModel model;
    model.setRootPath(root.path());
    QCOMPARE(model.rowCount(), 1);
    const auto idx = model.index(0, 0);
    QCOMPARE(model.data(idx, WallpaperEngineModel::TitleRole).toString(), QString("Foo"));
    QCOMPARE(model.data(idx, WallpaperEngineModel::AuthorRole).toString(), QString("Bar"));
    QVERIFY(model.data(idx, WallpaperEngineModel::VideoPathRole).toString().endsWith("video.mp4"));
}

void WeModelTest::test_nonVideoType_skipped() {
    QTemporaryDir tmp;
    QVERIFY(tmp.isValid());
    QDir root(tmp.path());
    QVERIFY(root.mkdir("abc"));
    const QString projDir = root.absoluteFilePath("abc");

    const QByteArray json = R"({
        "type": "scene",
        "title": "Foo"
    })";
    writeFile(projDir + "/project.json", json);

    WallpaperEngineModel model;
    model.setRootPath(root.path());
    QCOMPARE(model.rowCount(), 0);
}

void WeModelTest::test_missingProjectJson_skipped() {
    QTemporaryDir tmp;
    QVERIFY(tmp.isValid());
    QDir root(tmp.path());
    QVERIFY(root.mkdir("nojson"));

    WallpaperEngineModel model;
    model.setRootPath(root.path());
    QCOMPARE(model.rowCount(), 0);
}

void WeModelTest::test_missingVideoFile_skipped() {
    QTemporaryDir tmp;
    QVERIFY(tmp.isValid());
    QDir root(tmp.path());
    QVERIFY(root.mkdir("novideo"));
    const QString projDir = root.absoluteFilePath("novideo");

    const QByteArray json = R"({
        "type": "video",
        "title": "Foo",
        "file": "missing.mp4"
    })";
    writeFile(projDir + "/project.json", json);

    WallpaperEngineModel model;
    model.setRootPath(root.path());
    QCOMPARE(model.rowCount(), 0);
}

void WeModelTest::test_previewDetection_optional() {
    QTemporaryDir tmp;
    QVERIFY(tmp.isValid());
    QDir root(tmp.path());
    QVERIFY(root.mkdir("p"));
    const QString projDir = root.absoluteFilePath("p");

    const QByteArray json = R"({
        "type": "video",
        "title": "Foo",
        "file": "v.webm"
    })";
    writeFile(projDir + "/project.json", json);
    writeFile(projDir + "/v.webm");
    writeFile(projDir + "/preview.png");

    WallpaperEngineModel model;
    model.setRootPath(root.path());
    QCOMPARE(model.rowCount(), 1);
    const auto idx = model.index(0, 0);
    const QString preview = model.data(idx, WallpaperEngineModel::PreviewPathRole).toString();
    QVERIFY(preview.endsWith("preview.png"));
}

void WeModelTest::test_realSteamPath() {
    const QString steamPath = QDir::homePath() + "/.local/share/Steam/steamapps/workshop/content/431960";
    QDir steamDir(steamPath);
    
    if (!steamDir.exists()) {
        QSKIP("Steam workshop path doesn't exist, skipping real path test");
    }
    
    qDebug() << "===== REAL STEAM PATH TEST =====";
    qDebug() << "Testing path:" << steamPath;
    qDebug() << "Path exists:" << steamDir.exists();
    
    WallpaperEngineModel model;
    model.useDefaultSteamPath();
    
    qDebug() << "Model root path:" << model.rootPath();
    qDebug() << "Model pathExists:" << model.pathExists();
    qDebug() << "Model count:" << model.count();
    qDebug() << "Model lastError:" << model.lastError();
    
    QVERIFY2(model.pathExists(), "Steam workshop path should exist");
    QVERIFY2(model.count() > 0, qPrintable(QString("Should find at least one project. Error: %1").arg(model.lastError())));
    
    // Print first 3 projects
    for (int i = 0; i < qMin(3, model.count()); i++) {
        auto idx = model.index(i, 0);
        qDebug() << "Project" << i << ":"
                 << model.data(idx, WallpaperEngineModel::TitleRole).toString()
                 << "by" << model.data(idx, WallpaperEngineModel::AuthorRole).toString();
        qDebug() << "  Video:" << model.data(idx, WallpaperEngineModel::VideoPathRole).toString();
    }
}

QTEST_APPLESS_MAIN(WeModelTest)
#include "WeModelTest.moc"
