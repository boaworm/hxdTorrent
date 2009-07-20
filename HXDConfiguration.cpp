#include "HXDConfiguration.h"
#include "HXDTorrent.h"

#include <QDomDocument>
#include <QFile>
#include <QRegExp>

#include <vector>

namespace hxd
{


    HXDConfiguration::HXDConfiguration(HXDTorrent* hxd) : m_hxd(hxd)
    {
        qDebug("Creating HXDConfiguration");
        
        m_qdom = new QDomDocument();
        
        // Try and read an existing configuration file:
        
        QFile file( "hxdTorrent.xml" );
        if( file.open(QIODevice::ReadOnly) )
        {
            if( !m_qdom->setContent( &file ) )
            {
                qWarning("Cannot parse contents in configuration file - generating a default QDom");
                createDefaultQDom();
            }
            else
            {
                QString rssUrl;
                std::vector<QRegExp> regex;
            
                // Validate the produced qdom, if it sucks, generate a new one

                QDomElement root = m_qdom->documentElement();
                
                QDomElement rss = root.firstChildElement();
                if( rss.nodeName() != "rss" )
                {
                    qWarning("Cannot find an rss element - creating new xml for you...");
                    goto generate_new_qdom;
                }
                while( rss.nodeName() == "rss" )
                {
                    rssUrl  = rss.attribute("url");
                    qDebug("Extracted url: " + rssUrl.toLatin1() );
                    // Fetch all regex for this rss url. 
                    
                    QDomElement regexElement  = rss.firstChildElement();
                    while( !regexElement.isNull() )
                    {
                        if( regexElement.nodeName() == "regex" )
                        {
                            QRegExp r( regexElement.attribute("pattern"), Qt::CaseInsensitive, QRegExp::Wildcard );
                            regex.push_back( r );
                        }
                        regexElement = regexElement.nextSiblingElement();
                    }
                    
                    qDebug("Found %i patterns for " + rssUrl.toLatin1(), regex.size() );
                    
                    m_rssMap.insert( std::make_pair( rssUrl, regex ) );
                    rssUrl = "";
                    regex.clear();
                    
                    rss = rss.nextSiblingElement();
                }
                
                // Next element is supposed to be directories 
                if( rss.nodeName() != "directories" )
                {
                    qWarning("RSS nodes were not followed by \"directories\" node. bailing out");
                    goto generate_new_qdom;
                }
                m_torrentFilesDir = rss.attribute("torrentfiles");
                m_downloadDir = rss.attribute("download");
            }
        }
        else
        {
generate_new_qdom:
            qWarning("Cannot find or parse configuration file - generating a default QDom");
            createDefaultQDom();
            // Generate it here...
        }
        
    }

    HXDConfiguration::~HXDConfiguration()
    {
        qDebug("Deleting HXDConfiguration");

        
        delete m_qdom;
    }



    void HXDConfiguration::createDefaultQDom()
    {
        QString xml(""
        "<?xml version='1.0' ?>"
        "<hxdTorrent>"
        "<rss name=\"TV\" url=\"http://rss.thepiratebay.org/205\">"
        "<regex pattern=\"*south*park*\"/>"
        "<regex pattern=\"*grey*anatomy*4*\"/>"
        "<regex pattern=\"*the*unit*\"/>"
        "<regex pattern=\"*las*vegas*\"/>"
        "<regex pattern=\"*private*practice*\"/>"
        "<regex pattern=\"*heroes*2*\"/>"
        "<regex pattern=\"*prison*break*3*\"/>"
        "<regex pattern=\"*house*3*\"/>"
        "<regex pattern=\"*desperate*housewife*\">"
        "</rss>"
        "<rss name=\"Movies\" url=\"http://rss.thepiratebay.org/201\">"
        "<regex pattern=\"*rambo*\"/>"
        "</rss>"
        "<directories torrentfiles=\"/Users/boaworm/Desktop/Torrent/\" download=\"/Volumes/Data/Incoming/\"/>"
        "</hxdTorrent>"
        "");
    
        m_qdom->setContent( xml );
    
    }



} // END NAMESPACE



// EOF
