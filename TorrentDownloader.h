
#ifndef TorrentDownloader_h
#define TorrentDownloader_h


#include <QString>
#include <QThread>

class QObject;

namespace hxd
{
    
    class TorrentDownloader : public QThread
{
public:
    TorrentDownloader(QObject* parent, 
                          const QString& url, 
                          const QString& path,
                          const int id);
    ~TorrentDownloader();
    
protected:
        void run();
    
private:
    QObject* m_parent;
    QString m_url;
    QString m_path;
    QString m_error;
    int m_id;
    
};


#endif










}