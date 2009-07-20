
#ifndef TorrentFilesTab_h
#define TorrentFilesTab_h

#include <QWidget>
#include <QDir>
#include <QTreeWidget>


#include <map>


class QTreeWidgetItem;
class QKeyEvent;

namespace hxd
{
class HXDTorrent;

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
    public:
        MyTreeWidget(QWidget* parent = 0);
        
    signals:
        void deleteSelectedTorrents();
    
    protected:
        void keyPressEvent(QKeyEvent* event);
};



class TorrentFilesTab : public QWidget
{
    Q_OBJECT
    public:
        TorrentFilesTab(QWidget* parent, HXDTorrent* hxd);
        ~TorrentFilesTab();
    
    public slots:
        void refreshTorrentView();
    
protected:
        
private:
    HXDTorrent* m_hxd;
    QDir m_dir;
    MyTreeWidget* m_treeWidget;
    
private slots:
        void torrentFileDownloadFinished(QString, 
                                         QString, 
                                         QString, 
                                         bool);
        void torrentDoubleClicked(QTreeWidgetItem*,int);
        void deleteSelectedTorrents();
};















}


#endif