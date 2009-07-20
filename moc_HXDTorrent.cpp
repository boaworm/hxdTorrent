/****************************************************************************
** Meta object code from reading C++ file 'HXDTorrent.h'
**
** Created: Fri Jul 3 23:47:08 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "HXDTorrent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HXDTorrent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_hxd__HXDTorrent[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      39,   16,   16,   16, 0x05,
      73,   69,   16,   16, 0x05,
     131,   16,   16,   16, 0x05,
     161,  159,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_hxd__HXDTorrent[] = {
    "hxd::HXDTorrent\0\0newTorrentAvailable()\0"
    "torrentAlreadyExists(QString)\0,,,\0"
    "torrentFileDownloadFinished(QString,QString,QString,bool)\0"
    "markExistingTorrentsAsOld()\0,\0"
    "dataTransferStatsUpdated(uint,uint)\0"
};

const QMetaObject hxd::HXDTorrent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_hxd__HXDTorrent,
      qt_meta_data_hxd__HXDTorrent, 0 }
};

const QMetaObject *hxd::HXDTorrent::metaObject() const
{
    return &staticMetaObject;
}

void *hxd::HXDTorrent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hxd__HXDTorrent))
        return static_cast<void*>(const_cast< HXDTorrent*>(this));
    return QObject::qt_metacast(_clname);
}

int hxd::HXDTorrent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newTorrentAvailable(); break;
        case 1: torrentAlreadyExists((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: torrentFileDownloadFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 3: markExistingTorrentsAsOld(); break;
        case 4: dataTransferStatsUpdated((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void hxd::HXDTorrent::newTorrentAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void hxd::HXDTorrent::torrentAlreadyExists(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void hxd::HXDTorrent::torrentFileDownloadFinished(QString _t1, QString _t2, QString _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void hxd::HXDTorrent::markExistingTorrentsAsOld()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void hxd::HXDTorrent::dataTransferStatsUpdated(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
