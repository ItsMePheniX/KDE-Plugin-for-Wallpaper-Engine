/****************************************************************************
** Meta object code from reading C++ file 'wallpaperenginemodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/wallpaperenginemodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wallpaperenginemodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20WallpaperEngineModelE_t {};
} // unnamed namespace

template <> constexpr inline auto WallpaperEngineModel::qt_create_metaobjectdata<qt_meta_tag_ZN20WallpaperEngineModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WallpaperEngineModel",
        "rootPathChanged",
        "",
        "lastErrorChanged",
        "countChanged",
        "useDefaultSteamPath",
        "reload",
        "rootPath",
        "lastError",
        "pathExists",
        "count",
        "Roles",
        "TitleRole",
        "AuthorRole",
        "VideoPathRole",
        "PreviewPathRole",
        "ProjectPathRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'rootPathChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastErrorChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'countChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'useDefaultSteamPath'
        QtMocHelpers::MethodData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'rootPath'
        QtMocHelpers::PropertyData<QString>(7, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'lastError'
        QtMocHelpers::PropertyData<QString>(8, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
        // property 'pathExists'
        QtMocHelpers::PropertyData<bool>(9, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'count'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Roles'
        QtMocHelpers::EnumData<enum Roles>(11, 11, QMC::EnumFlags{}).add({
            {   12, Roles::TitleRole },
            {   13, Roles::AuthorRole },
            {   14, Roles::VideoPathRole },
            {   15, Roles::PreviewPathRole },
            {   16, Roles::ProjectPathRole },
        }),
    };
    return QtMocHelpers::metaObjectData<WallpaperEngineModel, qt_meta_tag_ZN20WallpaperEngineModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WallpaperEngineModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20WallpaperEngineModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20WallpaperEngineModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20WallpaperEngineModelE_t>.metaTypes,
    nullptr
} };

void WallpaperEngineModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WallpaperEngineModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rootPathChanged(); break;
        case 1: _t->lastErrorChanged(); break;
        case 2: _t->countChanged(); break;
        case 3: _t->useDefaultSteamPath(); break;
        case 4: _t->reload(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WallpaperEngineModel::*)()>(_a, &WallpaperEngineModel::rootPathChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WallpaperEngineModel::*)()>(_a, &WallpaperEngineModel::lastErrorChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WallpaperEngineModel::*)()>(_a, &WallpaperEngineModel::countChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->rootPath(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->lastError(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->pathExists(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->count(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRootPath(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *WallpaperEngineModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WallpaperEngineModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20WallpaperEngineModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int WallpaperEngineModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WallpaperEngineModel::rootPathChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WallpaperEngineModel::lastErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WallpaperEngineModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
