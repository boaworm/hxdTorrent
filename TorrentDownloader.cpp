
#include "TorrentDownloader.h"

#include "HXDEvents.h"

#include <QApplication>
#include <QFile>

// Stuff stolen from torrent example 

namespace hxd
{
    
TorrentDownloader::TorrentDownloader(
                                                QObject* parent, 
                                                const QString& url, 
                                                const QString& path, 
                                                const int id) 
    : m_parent(parent), m_url(url), m_path(path), m_id(id)
{
        qDebug("Creating a TorrentDownloader");
}

TorrentDownloader::~TorrentDownloader()
{
    qDebug("Deleting a TorrentDownloader");
}

// Protected

void TorrentDownloader::run()
{
    // Run method
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    qDebug("TorrentDownloader::run()");
    
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
    
    */
    
    bool ok;
    
post_event:
        TorrentDownloadFinished* tdf = new TorrentDownloadFinished(m_url,m_path,m_error,ok,m_id);
    QApplication::postEvent(m_parent,tdf);
}








}