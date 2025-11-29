# Wallpaper Engine KDE Prototype (WORK IN PROGRESS)

Prototype Plasma 6 wallpaper plugin to load and play Wallpaper Engine *video* wallpapers directly from the Steam workshop directory.

## Features (Milestone 1)
- Scan default Steam workshop path: `~/.local/share/Steam/steamapps/workshop/content/431960/`
- Parse `project.json` for video-type projects (fields: `title`, `author`, `file`, `preview`, `type` must be `video`)
- Present selectable grid in configuration UI
- Play selected video as looping, muted wallpaper (mp4/webm/mov)
- Scale modes: cover / contain / stretch

## Structure
```
CMakeLists.txt
src/
  wallpaperenginemodel.h/.cpp  # List model + parsing
  plugin.cpp                    # QML module registration
package/
  metadata.json                 # KPackage descriptor
  contents/ui/main.qml          # Wallpaper runtime
  contents/ui/config.qml        # Configuration UI
```

## Build & Install
```bash
# Configure and build
mkdir -p build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
cmake --build . -j

# Install (requires sudo for system QML path)
sudo cmake --install .

# Restart plasmashell
killall plasmashell && plasmashell &
```

## Uninstall
```bash
cd build
cmake --build . --target uninstall
```

After install, Plasma should detect the wallpaper under:
`$HOME/.local/share/plasma/wallpapers/org.kde.wallpaper.wallpaperengine`

Select it in the wallpaper configuration dialog; choose a project.

## Notes
- Only video-type projects are listed. Others skipped.
- No copying/import; references workshop directory in place.
- Audio is always muted.
- Future work: multi-monitor support, imports, performance optimizations.

## License
GPL-3.0-or-later (prototype stage).
