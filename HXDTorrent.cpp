/*
 *  HXDTorrent.cpp
 *  hxdTorrent
 *
 *  Created by Henrik Thorburn on 10/4/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "HXDConfiguration.h"
#include "HXDEvents.h"
#include "HXDTorrent.h"
#include "MainWindow.h"
#include "RSSScanner.h"
#include "ThomsonRouterMonitor.h"
#include "TorrentDownloader.h"
#include "TorrentFileDownloader.h"
#include "TorrentStatisticsGrabber.h"


namespace hxd
{

HXDTorrent::HXDTorrent()
{
    qDebug("Creating HXDTorrent");

    // Create config object and load config
    m_config = new HXDConfiguration( this );

    // Create main window
    m_mainWindow = new MainWindow( this );
    m_mainWindow->show();
    
    
    // Create an rss scanner
    m_rssScanner = new RSSScanner( this );
    
	// Create the router scanner
	m_routerMonitor = new ThomsonRouterMonitor( this );
	
    HXDConfiguration::RSSMap::const_iterator it = m_config->getRSSMap().begin();
    HXDConfiguration::RSSMap::const_iterator itEnd = m_config->getRSSMap().end();
    
    for(;it!=itEnd;++it)
    {
        m_rssScanner->addScannerTarget( it->first, it->second );
    }
    
    m_rssScanner->start();
   	m_routerMonitor->start();

    m_statsGrabber = new TorrentStatisticsGrabber( this );
    m_statsGrabber->start();
    
}

HXDTorrent::~HXDTorrent()
{
    qDebug("Deleting HXDTorrent");
    
    delete m_mainWindow;
    
    // Wait for torrent file downloader threads to finish. 
    for(unsigned int i=0;i<m_torrentFileDownloaders.size();++i)
    {
        qWarning("Waiting for torrent downloader to finish");
        m_torrentFileDownloaders[i]->wait();
        delete m_torrentFileDownloaders[i];
    }
    delete m_config;
    
    // Should do some cleanup of rss scanner
    
    // Should do some cleanup of stats grabber
}

HXDTorrent::TorrentMap* HXDTorrent::getTorrentMap()
{
    return &m_torrents;
}

bool HXDTorrent::downloadTorrent(const QString& name)
{
    // Spawn a new TorrentFileDownloader with URL
    int id = 0;
    while( m_torrentFileDownloaders.end() != m_torrentFileDownloaders.find( id ) )
    {
        ++id;
    }
    // Id is now unique.
    
    // Find the URL and figure out a good filename
    TorrentMap::iterator it = m_torrents.find( name );
    if( it == m_torrents.end() )
    {
        return false;
    }
    
    
    QString url = it->second.link;
    QString filepath;
    
    QStringList list( url.split('/') );
    filepath = m_config->getTorrentFilesDir() + list.back();
    
    
    TorrentFileDownloader* tfd = new TorrentFileDownloader(this,url,filepath,id);
    m_torrentFileDownloaders.insert( std::make_pair(id,tfd) );
    tfd->start();
    
    return true;
}


void HXDTorrent::beginDownloading(const QString& torrent)
{
    qDebug("Time to begin downloading : " + torrent.toLatin1());
    
    
}


// PROTECTED

void HXDTorrent::customEvent(QEvent* event)
{   
	switch( event->type() )
	{    
    case NewTorrentFoundID:
    {
        // A new torrent was discovered!
		NewTorrentFound* ntf( dynamic_cast<NewTorrentFound*>(event) );
        try
        {
            TorrentMap::iterator it = m_torrents.find( ntf->getTitle() );
            if( it == m_torrents.end() )
            {
                qDebug("Trying to insert torrent: " + ntf->getTitle().toLatin1() );
                TorrentStatus ts;
                ts.link = ntf->getLink();
                ts.leechers = 0;
                ts.seeders = 0;
                m_torrents.insert( std::make_pair( ntf->getTitle(), ts ) );
                qDebug("Insert OK, emitting newTorrentsAvailable() signal");
                emit newTorrentAvailable();
            }
            else
            {
                qDebug("Emitting torrentAlreadyExists() " + ntf->getTitle().toLatin1() );
                emit torrentAlreadyExists( ntf->getTitle() );
            }
        }
        catch(...)
        {
            // Ignore, we already knew of this one
            qDebug("Insert failed, emitting torrentAlreadyExists() " + ntf->getTitle().toLatin1() );
            emit torrentAlreadyExists( ntf->getTitle() );
        }
    }
	break;
	case TorrentFileDownloadFinishedID:
    {
		TorrentFileDownloadFinished* tfdf( dynamic_cast<TorrentFileDownloadFinished*> (event) );
		QString url = tfdf->getUrl();
        QString path = tfdf->getPath();
        QString error = tfdf->getError();
        bool ok = tfdf->ok();
        int id = tfdf->getID();
    
        // A thread finished downloading a torrent file for us.
        
        TorrentFileDownloaderMap::iterator it = m_torrentFileDownloaders.find( id );
        if( it != m_torrentFileDownloaders.end() )
        {
            it->second->wait();
            delete it->second;
            m_torrentFileDownloaders.erase( it );
        }

        emit torrentFileDownloadFinished(url,path,error,ok);
	}
	break;
	case TorrentDownloadFinishedID:
    {
        // A thread finished downloading a torrent for us.
		TorrentDownloadFinished* tdf( dynamic_cast<TorrentDownloadFinished*> (event) );
        
        TorrentDownloaderMap::iterator it = m_torrentDownloaders.find( tdf->getID() );
        if( it != m_torrentDownloaders.end() )
        {
            it->second->wait();
            delete it->second;
            m_torrentDownloaders.erase( it );
        }
    }
	break;
	case TorrentScanBegunID:
    {
        qDebug("received a TorrentScanBegun event, emitting signal");
        // Notify the RSSScannerTab that all events should be "cold/blue"
        emit markExistingTorrentsAsOld();
    }
    break;
	
    // PROBABLY POINTLESS EVENT...
    case TorrentScanFinishedID:
    {
        // This will trigger a reload in the GUI components. 
        emit torrentFileDownloadFinished("","","",true);
    }
    break;
    case StatisticsScanFinishedID: // * ssf( dynamic_cast<StatisticsScanFinished*>(event) );
    {
		StatisticsScanFinished* ssf( dynamic_cast<StatisticsScanFinished*>(event) );
        qDebug("--- Received a StatisticsScanFinished event --- ");
        StatisticsScanFinished::StatisticsVector vec( ssf->getStatistics() );
        StatisticsScanFinished::StatisticsVector::const_iterator it( vec.begin() );
        for(;it!=vec.end();++it)
        {
            qDebug("Torrent stats: " + it->torrent.toLatin1());
            qDebug("Seeders : %i", it->seeders);
            qDebug("Leechers : %i", it->leechers);
        }
    }
	break;
	case RouterScanFinishedID:
	{
		RouterScanFinished* rsf( dynamic_cast<RouterScanFinished*>(event) );
		emit dataTransferStatsUpdated( rsf->getHours(), rsf->getMegabytes() );
	}
	break;
	default:
	{
		qDebug("Received an unexpected event, ignoring it");
	}
	} // end switch

}






}