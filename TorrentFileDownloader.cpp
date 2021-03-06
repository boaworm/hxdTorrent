
#include "TorrentFileDownloader.h"

#include "HXDEvents.h"

#include <QApplication>
#include <QFile>

namespace hxd
{
    
TorrentFileDownloader::TorrentFileDownloader(
                                                QObject* parent, 
                                                const QString& url, 
                                                const QString& path, 
                                                const int id) 
    : m_parent(parent), m_url(url), m_path(path), m_id(id)
{
        qDebug("Creating a TorrentFileDownloader");
}

TorrentFileDownloader::~TorrentFileDownloader()
{
    qDebug("Deleting a TorrentFileDownloader");
}

// Protected

void TorrentFileDownloader::run()
{
    // Run method
    qDebug("TorrentFileDownloader::run()");
    
    CURL* curl;
    curl = curl_easy_init();
    std::string url = m_url.toStdString();
    memcpy(m_urlBuffer,url.c_str(), url.length());
    m_urlBuffer[url.length()] = 0;
    // qDebug(" m_urlBuffer = %s", m_urlBuffer );
    curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, m_errorBuffer);
    curl_easy_setopt(curl,CURLOPT_URL, m_urlBuffer );
    curl_easy_setopt(curl,CURLOPT_HEADER, 0 );
    curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1 );
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, curlWriter );
    curl_easy_setopt(curl,CURLOPT_WRITEDATA, &m_buffer );
    
    m_result = curl_easy_perform( curl );
    curl_easy_cleanup(curl);
    
    bool ok = false;
    if( m_result == CURLE_OK )
    {
        // Write the data to a file
        QFile file( m_path );
        if( file.exists() )
        {
            qWarning("File already exists - bailing out");
            m_error = "File exists - will not overwrite";
            goto post_event;
        }
        if( !file.open( QIODevice::ReadWrite ) || !file.isWritable() )
        {
            qWarning("Cannot open file for read/write - bailing out");
            m_error = "Cannot open file read/write";
            goto post_event;
        }
        file.write( m_buffer.c_str(), m_buffer.size() );
        
        ok = true;
    }
    
post_event:

    TorrentFileDownloadFinished* tfdf = new TorrentFileDownloadFinished(
                                                                            m_url,
                                                                            m_path,
                                                                            m_error,
                                                                            ok,
                                                                            m_id);
    QApplication::postEvent(m_parent,tfdf);
}





int TorrentFileDownloader::curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer)
{
    int result = 0;
    if( buffer != NULL )
    {
        buffer->append(data,size*nmemb);
        result = size*nmemb;
    }
    return result;
}












}