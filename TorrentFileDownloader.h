
#ifndef TorrentFileDownloader_h
#define TorrentFileDownloader_h


#include <QString>
#include <QThread>

#include "curl/curl.h"

class QObject;

namespace hxd
{
    
    class TorrentFileDownloader : public QThread
{
public:
    TorrentFileDownloader(QObject* parent, 
                          const QString& url, 
                          const QString& path,
                          const int id);
    ~TorrentFileDownloader();
    
protected:
        void run();
    
private:
        QObject* m_parent;
    QString m_url;
    QString m_path;
    QString m_error;
    int m_id;
    
    // Curl stuff
    CURLcode m_result;
    char m_errorBuffer[256];
    char m_urlBuffer[4096];
    std::string m_buffer;
    
    static int curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer);
};


#endif










}