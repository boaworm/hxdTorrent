#include "RSSScanner.h"

#include "HXDEvents.h"

#include <QApplication>
#include <QDomDocument>
#include <QObject>

namespace hxd
{
    
RSSScanner::RSSScanner(QObject* parent) : m_stop(false), m_parent(parent)
{
        qDebug( "Creating an RSSScanner object" ); 
}

RSSScanner::~RSSScanner()
{
    qDebug( "Deleting an RSSScanner object" ); 
}

void RSSScanner::addScannerTarget( const QString& url, const std::vector<QRegExp>& regex )
{
    m_rssMap.insert( std::make_pair(url, regex) );
}

void RSSScanner::stop()
{
    m_stop = true;
}

int RSSScanner::curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer)
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

void RSSScanner::run()
{
    std::string url;
    HXDConfiguration::RSSMap::iterator rssIt; 
    while( !m_stop )
    {
        // Tag existing ones as "old"
        TorrentScanBegun* tsb = new TorrentScanBegun();
        QApplication::postEvent(m_parent,tsb);
        
    
        for(rssIt=m_rssMap.begin();rssIt!=m_rssMap.end();++rssIt)
        {
            m_buffer.clear();
            // qDebug("m_buffer.max_size() = %i", m_buffer.max_size());
            // m_buffer.resize(10000);
            CURL* curl;
            curl = curl_easy_init();
            url = rssIt->first.toStdString();
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
            
            m_result = curl_easy_perform( curl );
            curl_easy_cleanup(curl);

            if( m_result == CURLE_OK )
            {
                // WOHO!
                QDomDocument dom;
                
                // qDebug("BUFFER = \n\n%s\n\n", m_buffer.c_str() );
                
                QString qstr( m_buffer.c_str() );              
                if( dom.setContent( qstr, true ) )
                {
                    // Parsing OK
                    QDomNode rss = dom.firstChild();
                    rss = rss.nextSibling();
                    QDomNode channel = rss.firstChild();
                    if( channel.nodeName() == "channel" )
                    {
                        // Found the channel node
                        // Loop over "item" nodes.
                        QDomNode item = channel.firstChild();
                        while( item != channel.lastChild() )
                        {
                            if( item.nodeName() == "item" )
                            {   
                                // qDebug("Found an item node");
                                // Located an item node
                                // From this node we should extract two children
                                // title - some description
                                // link - http://path.to/file.torrent
                                QDomNode n = item.firstChild();
                                
                                QString title;
                                QString link;
                                
                                QDomElement e;
                                
                                e = item.firstChildElement("title");
                                if( !e.isNull() )
                                    title = e.text();
                                e = item.firstChildElement("link");
                                if( !e.isNull() )
                                    link = e.text();
                                
                                if( !title.isEmpty() && !link.isEmpty() )
                                {
                                    // Got it!
                                    // See if it matches the regex 
                                    for(unsigned int i=0;i<rssIt->second.size();++i)
                                    {
                                        if( rssIt->second[i].exactMatch( title ) )
                                        {
                                            /*
                                            qDebug("MATCHED Regex!");
                                            qDebug(" title = " + title.toLatin1() );
                                            qDebug(" link  = " + link.toLatin1() );
                                            */
                                            NewTorrentFound* ntf = new NewTorrentFound(title,link);
                                            QApplication::postEvent(m_parent,ntf);
                                            
                                        }
                                    }
                                }
                            }
                            item = item.nextSibling();
                        }
                    }
                }
                else
                {
                    qWarning("ERROR, failed to create QDom (and parse incoming XML)");
                }
            }
            else
            {
                qWarning("ERROR: Failed to retrieve RSS from URL: " + rssIt->first.toLatin1() );
                qWarning("REASON: [%i] %s ",m_result, m_errorBuffer);
            }
            
            // qDebug("Done processing " + rssIt->first.toLatin1() );
        }
        TorrentScanFinished* tsf = new TorrentScanFinished();
        QApplication::postEvent(m_parent,tsf);
        // Sleep 10 minutes
        sleep(  10 * 60 );
    }
    
}



















} // END NAMESPACE