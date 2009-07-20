/*
 *  HXDTorrent.h
 *  hxdTorrent
 *
 *  Created by Henrik Thorburn on 10/4/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HXDTorrent_h
#define HXDTorrent_h
 
#include <QCustomEvent>

#include <Carbon/Carbon.h>

#include <QFile>
#include <QObject>
#include <QString>

#include <map>


namespace hxd
{
class HXDConfiguration;
class MainWindow;
class RSSScanner;
class TorrentDownloader;
class TorrentFileDownloader;
class TorrentStatisticsGrabber;
class ThomsonRouterMonitor;

class HXDTorrent : public QObject
{
    Q_OBJECT

    public:
    
        struct TorrentStatus
        {
            QString link;
            unsigned int seeders;
            unsigned int leechers;
        };
        typedef std::map<QString, TorrentStatus> TorrentMap;

        HXDTorrent();
        ~HXDTorrent();
        
        TorrentMap* getTorrentMap();
        bool downloadTorrent(const QString& url);
        HXDConfiguration* getConfig()
        {
            return m_config;
        }
        void beginDownloading(const QString& torrent);
        
    protected:
        void customEvent(QEvent* event);
    
    signals:
        void newTorrentAvailable();
        void torrentAlreadyExists(QString);
        void torrentFileDownloadFinished(QString,QString,QString,bool);
        void markExistingTorrentsAsOld();
		void dataTransferStatsUpdated(unsigned int,unsigned int);
    
    private:
        RSSScanner* m_rssScanner;
        TorrentMap m_torrents;
        MainWindow* m_mainWindow;
        HXDConfiguration* m_config;
        TorrentStatisticsGrabber* m_statsGrabber;
		ThomsonRouterMonitor* m_routerMonitor;
        
        typedef std::map<int,TorrentFileDownloader*> TorrentFileDownloaderMap;
        TorrentFileDownloaderMap m_torrentFileDownloaders;

        typedef std::map<int,TorrentDownloader*> TorrentDownloaderMap;
        TorrentDownloaderMap m_torrentDownloaders;

};


}

#endif
