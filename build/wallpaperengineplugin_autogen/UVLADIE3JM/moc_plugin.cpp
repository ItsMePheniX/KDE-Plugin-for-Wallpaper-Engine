/****************************************************************************
** Meta object code from reading C++ file 'plugin.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/plugin.h"
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN21WallpaperEnginePluginE_t {};
} // unnamed namespace

template <> constexpr inline auto WallpaperEnginePlugin::qt_create_metaobjectdata<qt_meta_tag_ZN21WallpaperEnginePluginE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WallpaperEnginePlugin"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WallpaperEnginePlugin, qt_meta_tag_ZN21WallpaperEnginePluginE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WallpaperEnginePlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QQmlExtensionPlugin::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21WallpaperEnginePluginE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21WallpaperEnginePluginE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21WallpaperEnginePluginE_t>.metaTypes,
    nullptr
} };

void WallpaperEnginePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WallpaperEnginePlugin *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *WallpaperEnginePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WallpaperEnginePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21WallpaperEnginePluginE_t>.strings))
        return static_cast<void*>(this);
    return QQmlExtensionPlugin::qt_metacast(_clname);
}

int WallpaperEnginePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQmlExtensionPlugin::qt_metacall(_c, _id, _a);
    return _id;
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_WallpaperEnginePlugin[] = {
    0xbf, 
    // "IID"
    0x02,  0x78,  0x2c,  'o',  'r',  'g',  '.',  'q', 
    't',  '-',  'p',  'r',  'o',  'j',  'e',  'c', 
    't',  '.',  'Q',  't',  '.',  'Q',  'Q',  'm', 
    'l',  'E',  'x',  't',  'e',  'n',  's',  'i', 
    'o',  'n',  'I',  'n',  't',  'e',  'r',  'f', 
    'a',  'c',  'e',  '/',  '1',  '.',  '0', 
    // "className"
    0x03,  0x75,  'W',  'a',  'l',  'l',  'p',  'a', 
    'p',  'e',  'r',  'E',  'n',  'g',  'i',  'n', 
    'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa2,  0x64,  'K',  'e',  'y',  's',  0x81, 
    0x6f,  'W',  'a',  'l',  'l',  'p',  'a',  'p', 
    'e',  'r',  'E',  'n',  'g',  'i',  'n',  'e', 
    0x69,  'c',  'l',  'a',  's',  's',  'N',  'a', 
    'm',  'e',  0x75,  'W',  'a',  'l',  'l',  'p', 
    'a',  'p',  'e',  'r',  'E',  'n',  'g',  'i', 
    'n',  'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(WallpaperEnginePlugin, WallpaperEnginePlugin, qt_pluginMetaDataV2_WallpaperEnginePlugin)
#else
QT_PLUGIN_METADATA_SECTION
Q_CONSTINIT static constexpr unsigned char qt_pluginMetaData_WallpaperEnginePlugin[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x2c,  'o',  'r',  'g',  '.',  'q', 
    't',  '-',  'p',  'r',  'o',  'j',  'e',  'c', 
    't',  '.',  'Q',  't',  '.',  'Q',  'Q',  'm', 
    'l',  'E',  'x',  't',  'e',  'n',  's',  'i', 
    'o',  'n',  'I',  'n',  't',  'e',  'r',  'f', 
    'a',  'c',  'e',  '/',  '1',  '.',  '0', 
    // "className"
    0x03,  0x75,  'W',  'a',  'l',  'l',  'p',  'a', 
    'p',  'e',  'r',  'E',  'n',  'g',  'i',  'n', 
    'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa2,  0x64,  'K',  'e',  'y',  's',  0x81, 
    0x6f,  'W',  'a',  'l',  'l',  'p',  'a',  'p', 
    'e',  'r',  'E',  'n',  'g',  'i',  'n',  'e', 
    0x69,  'c',  'l',  'a',  's',  's',  'N',  'a', 
    'm',  'e',  0x75,  'W',  'a',  'l',  'l',  'p', 
    'a',  'p',  'e',  'r',  'E',  'n',  'g',  'i', 
    'n',  'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(WallpaperEnginePlugin, WallpaperEnginePlugin)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
