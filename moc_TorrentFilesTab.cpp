/****************************************************************************
** Meta object code from reading C++ file 'TorrentFilesTab.h'
**
** Created: Fri Jul 3 23:47:10 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TorrentFilesTab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TorrentFilesTab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_hxd__MyTreeWidget[] = {

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

static const char qt_meta_stringdata_hxd__MyTreeWidget[] = {
    "hxd::MyTreeWidget\0\0deleteSelectedTorrents()\0"
};

const QMetaObject hxd::MyTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_hxd__MyTreeWidget,
      qt_meta_data_hxd__MyTreeWidget, 0 }
};

const QMetaObject *hxd::MyTreeWidget::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::MyTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__MyTreeWidget))
        return static_cast<void*>(const_cast< MyTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int hxd::MyTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
void hxd::MyTreeWidget::deleteSelectedTorrents()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_hxd__TorrentFilesTab[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x0a,
      47,   43,   21,   21, 0x08,
     107,  105,   21,   21, 0x08,
     150,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_hxd__TorrentFilesTab[] = {
    "hxd::TorrentFilesTab\0\0refreshTorrentView()\0"
    ",,,\0torrentFileDownloadFinished(QString,QString,QString,bool)\0"
    ",\0torrentDoubleClicked(QTreeWidgetItem*,int)\0"
    "deleteSelectedTorrents()\0"
};

const QMetaObject hxd::TorrentFilesTab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_hxd__TorrentFilesTab,
      qt_meta_data_hxd__TorrentFilesTab, 0 }
};

const QMetaObject *hxd::TorrentFilesTab::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::TorrentFilesTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__TorrentFilesTab))
        return static_cast<void*>(const_cast< TorrentFilesTab*>(this));
    return QWidget::qt_metacast(_clname);
}

int hxd::TorrentFilesTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshTorrentView(); break;
        case 1: torrentFileDownloadFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: torrentDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: deleteSelectedTorrents(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
