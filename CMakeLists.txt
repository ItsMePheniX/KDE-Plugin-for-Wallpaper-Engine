cmake_minimum_required(VERSION 3.22)
project(WallpaperEngineKDE VERSION 0.1.0 LANGUAGES CXX)

# Extra CMake Modules (required for KDE Frameworks discovery)
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

# Enable Qt automoc (required for QQmlExtensionPlugin subclass)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

# Qt 6 dependencies
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Multimedia)

# Attempt to locate KF6 Frameworks (optional at prototype stage)
# If present we link them; otherwise we proceed with pure Qt.
find_package(KF6Package QUIET)
find_package(KF6Plasma QUIET)
find_package(KF6Kirigami QUIET)
find_package(KF6KIO QUIET)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Copy plugin.json to build directory for moc
configure_file(src/plugin.json plugin.json COPYONLY)

add_library(wallpaperengineplugin SHARED
    src/wallpaperenginemodel.cpp
    src/plugin.cpp
)

target_include_directories(wallpaperengineplugin PUBLIC src ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(wallpaperengineplugin PRIVATE Qt6::Core Qt6::Qml Qt6::Quick Qt6::Multimedia)

if (TARGET KF6::Package)
    target_link_libraries(wallpaperengineplugin PRIVATE KF6::Package)
    target_compile_definitions(wallpaperengineplugin PRIVATE HAVE_KF6PACKAGE=1)
endif()
if (TARGET KF6::Plasma)
    target_link_libraries(wallpaperengineplugin PRIVATE KF6::Plasma)
    target_compile_definitions(wallpaperengineplugin PRIVATE HAVE_KF6PLASMA=1)
endif()
if (TARGET KF6::Kirigami)
    target_link_libraries(wallpaperengineplugin PRIVATE KF6::Kirigami)
    target_compile_definitions(wallpaperengineplugin PRIVATE HAVE_KF6KIRIGAMI=1)
endif()
if (TARGET KF6::KIO)
    target_link_libraries(wallpaperengineplugin PRIVATE KF6::KIO)
    target_compile_definitions(wallpaperengineplugin PRIVATE HAVE_KF6KIO=1)
endif()

message(STATUS "KF6 linkage summary: Package=" $<BOOL:TARGET:KF6::Package> 
                " Plasma=" $<BOOL:TARGET:KF6::Plasma> 
                " Kirigami=" $<BOOL:TARGET:KF6::Kirigami> 
                " KIO=" $<BOOL:TARGET:KF6::KIO>)

# QML module install - use system Qt6 QML path
set(QML_MODULE_NAME "WallpaperEngine")
set(QML_MODULE_VERSION 1.0)

# Get Qt6 QML import path
execute_process(
    COMMAND qmake6 -query QT_INSTALL_QML
    OUTPUT_VARIABLE QT_QML_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Install QML module to system path (requires sudo for cmake --install)
set(INSTALL_QML_DIR "${QT_QML_DIR}/${QML_MODULE_NAME}")

install(TARGETS wallpaperengineplugin
        LIBRARY DESTINATION ${INSTALL_QML_DIR})

# Install qmldir so the module can be imported by QML (required)
install(FILES qml/WallpaperEngine/qmldir DESTINATION ${INSTALL_QML_DIR})

# Install package (KPackage structure)
install(DIRECTORY package/ DESTINATION share/plasma/wallpapers/org.kde.wallpaper.wallpaperengine)

# Export for local QML import path when running from build tree
set_target_properties(wallpaperengineplugin PROPERTIES
    QT_QML_MODULE_NAME ${QML_MODULE_NAME}
    QT_QML_MODULE_VERSION ${QML_MODULE_VERSION}
)

message(STATUS "Configured Wallpaper Engine KDE prototype (KF6 optional)")

# ----------------------
# Tests (QtTest)
# ----------------------
include(CTest)
if (BUILD_TESTING)
    find_package(Qt6 REQUIRED COMPONENTS Test)
    add_executable(wallpaperengine_tests
        tests/WeModelTest.cpp
        src/wallpaperenginemodel.cpp
    )
    target_include_directories(wallpaperengine_tests PRIVATE src)
    target_link_libraries(wallpaperengine_tests PRIVATE Qt6::Core Qt6::Test)
    add_test(NAME wallpaperengine_tests COMMAND wallpaperengine_tests)
endif()

# ----------------------
# Uninstall target
# ----------------------
add_custom_target(uninstall
    COMMAND sudo rm -rf ${INSTALL_QML_DIR}
    COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/share/plasma/wallpapers/org.kde.wallpaper.wallpaperengine
    COMMENT "Uninstalling Wallpaper Engine plugin..."
)
