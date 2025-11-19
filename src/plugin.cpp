#include "plugin.h"
#include <qqml.h>
#include "wallpaperenginemodel.h"

void WallpaperEnginePlugin::registerTypes(const char *uri) {
    qmlRegisterType<WallpaperEngineModel>(uri, 1, 0, "WallpaperEngineModel");
}


