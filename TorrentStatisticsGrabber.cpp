#include "TorrentStatisticsGrabber.h"

#include "HXDTorrent.h"
#include "HXDEvents.h"

#include <QApplication>
#include <QStringList>

#include <iostream>

namespace hxd
{
    
TorrentStatisticsGrabber::TorrentStatisticsGrabber(HXDTorrent* hxd) : m_stop(false), m_hxd(hxd)
{
        qDebug( "Creating an TorrentStatisticsGrabber object" ); 
}

TorrentStatisticsGrabber::~TorrentStatisticsGrabber()
{
    qDebug( "Deleting an TorrentStatisticsGrabber object" ); 
}

void TorrentStatisticsGrabber::stop()
{
    m_stop = true;
}

int TorrentStatisticsGrabber::curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer)
{
    int result = 0;
    if( buffer != NULL )
    {
        // qDebug(" size = %i, nmemb = %i",size,nmemb);
            
        buffer->append(data,size*nmemb);
        result = size*nmemb;
    }
    return result;
}

// PROTECTED

void TorrentStatisticsGrabber::run()
{
    sleep( 10 );
    qDebug("Launching torrent stats grabber");
    std::string url;
    
    QStringList list;
    QStringList::const_iterator it;
    
    while( !m_stop )
    {
        // Danger area, but i don't care right now :)
        HXDTorrent::TorrentMap* map( m_hxd->getTorrentMap() );
        HXDTorrent::TorrentMap::const_iterator mapIt( map->begin() );
        for(;mapIt!=map->end();++mapIt)
        {
            list.push_back( mapIt->second.link );
        }
        // End of danger area.

        // Will be populated incrementally
        StatisticsScanFinished* ssf = new StatisticsScanFinished();
    
        for(it=list.begin();it!=list.end();++it)
        {
            m_buffer.clear();
            // qDebug("m_buffer.max_size() = %i", m_buffer.max_size());
            // m_buffer.resize(10000);
            CURL* curl;
            curl = curl_easy_init();
            url = it->toStdString();
            memcpy(m_urlBuffer,url.c_str(), url.length());
            m_urlBuffer[url.length()] = 0;
            // qDebug(" m_urlBuffer = %s", m_urlBuffer );
            curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, m_errorBuffer);
            curl_easy_setopt(curl,CURLOPT_URL, m_urlBuffer );
            curl_easy_setopt(curl,CURLOPT_HEADER, 0 );
            curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1 );
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, curlWriter );
            curl_easy_setopt(curl,CURLOPT_WRITEDATA, &m_buffer );
            curl_easy_setopt(curl,CURLOPT_NOPROGRESS, 1 );
            curl_easy_setopt(curl,CURLOPT_BUFFERSIZE, 20000 );

            qDebug("Performing curl_easy_perform()");
            m_result = curl_easy_perform( curl );
            qDebug("Done fetching data");
            curl_easy_cleanup(curl);

            if( m_result == CURLE_OK )
            {
                qDebug("CURLE_OK!");
                // OK Figure out how to parse this shit...
                
                // <dt>Distributšrer:</dt><dd>5901</dd>
                // <dt>Reciprokšrer:</dt><dd>7277</dd>
                                
                QString data = QString::fromUtf8( m_buffer.c_str() );
                
                qDebug("ALL DATA\n\n" + data.toLatin1() );
                qDebug("");
                
                QStringList tmpList;
                QRegExp seeders("<dt>Distribut.rer:<\/dt>*<dd>(\\d+)<\/dd>" );
                if( seeders.indexIn( data ) > -1 )
                {
                    qDebug("SEEDERS = " + seeders.cap( 1 ).toLatin1() );
                }
                else
                {
                    qDebug("found no distributšrer...");
                }
                seeders.setPattern("<dt>Deilendur:<\/dt>*<dd>(\\d+)<\/dd>");
                if( seeders.indexIn( data ) > -1 )
                {
                    qDebug("SEEDERS = " + seeders.cap( 1 ).toLatin1() );
                }
                else
                {
                    qDebug("found no icelanders either...");
                }
                
                           
                QRegExp leechers;
                
                
                // QString all( m_buffer );
                // QStringList chubby( all.split( QRegExp("
            }
            else
            {
                qWarning("ERROR: Failed to retrieve HTML from URL: " + it->toLatin1() );
                qWarning("REASON: [%i] %s ",m_result, m_errorBuffer);
            }
        }
        
        QApplication::postEvent(m_hxd,ssf);
        // Sleep 10 minutes
        qDebug("Sleeping 10 minutes");
        sleep(  10 * 60 );
        
    }
    
}















} // END NAMESPACE