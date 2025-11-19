#pragma once
#include <QQmlExtensionPlugin>

class WallpaperEnginePlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid FILE "plugin.json")
public:
    void registerTypes(const char *uri) override;
};
