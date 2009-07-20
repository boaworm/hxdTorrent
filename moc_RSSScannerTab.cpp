/****************************************************************************
** Meta object code from reading C++ file 'RSSScannerTab.h'
**
** Created: Fri Jul 3 23:47:07 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RSSScannerTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RSSScannerTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_hxd__MyListWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_hxd__MyListWidget[] = {
    "hxd::MyListWidget\0\0deleteSelectedTorrents()\0"
};

const QMetaObject hxd::MyListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_hxd__MyListWidget,
      qt_meta_data_hxd__MyListWidget, 0 }
};

const QMetaObject *hxd::MyListWidget::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::MyListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__MyListWidget))
        return static_cast<void*>(const_cast< MyListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int hxd::MyListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deleteSelectedTorrents(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void hxd::MyListWidget::deleteSelectedTorrents()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_hxd__BandwidthUsageWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      43,   27,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_hxd__BandwidthUsageWidget[] = {
    "hxd::BandwidthUsageWidget\0\0hours,megabytes\0"
    "updateBandwidthUsage(uint,uint)\0"
};

const QMetaObject hxd::BandwidthUsageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_hxd__BandwidthUsageWidget,
      qt_meta_data_hxd__BandwidthUsageWidget, 0 }
};

const QMetaObject *hxd::BandwidthUsageWidget::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::BandwidthUsageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__BandwidthUsageWidget))
        return static_cast<void*>(const_cast< BandwidthUsageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int hxd::BandwidthUsageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateBandwidthUsage((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_hxd__RSSScannerTab[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      43,   38,   19,   19, 0x08,
      85,   19,   19,   19, 0x08,
     110,   19,   19,   19, 0x08,
     138,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_hxd__RSSScannerTab[] = {
    "hxd::RSSScannerTab\0\0refreshTorrents()\0"
    "item\0listWidgetDoubleClicked(QListWidgetItem*)\0"
    "deleteSelectedTorrents()\0"
    "markExistingTorrentsAsOld()\0"
    "markTorrentAsCurrentlyListed(QString)\0"
};

const QMetaObject hxd::RSSScannerTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_hxd__RSSScannerTab,
      qt_meta_data_hxd__RSSScannerTab, 0 }
};

const QMetaObject *hxd::RSSScannerTab::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::RSSScannerTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__RSSScannerTab))
        return static_cast<void*>(const_cast< RSSScannerTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int hxd::RSSScannerTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshTorrents(); break;
        case 1: listWidgetDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: deleteSelectedTorrents(); break;
        case 3: markExistingTorrentsAsOld(); break;
        case 4: markTorrentAsCurrentlyListed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
