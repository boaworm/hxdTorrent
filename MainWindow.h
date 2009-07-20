
#ifndef MainWindow_h
#define MainWindow_h

#include <QMainWindow>

class QTabWidget;

namespace hxd
{
class HXDTorrent;
class RSSScannerTab;
class TorrentFilesTab;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        MainWindow(HXDTorrent* hxd);
        ~MainWindow();
        
    protected:
    
    private:
        HXDTorrent* m_hxd;
        QTabWidget* m_tabWidget;
        RSSScannerTab* m_rssScannerTab;
        TorrentFilesTab* m_torrentFilesTab;

    private slots:
        void torrentFileDownloadFinished(QString, 
                                         QString, 
                                         QString, 
                                         bool);
        void activeTabChanged(int);
    
};




}

#endif