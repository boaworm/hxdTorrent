
#ifndef HXDEvents_h
#define HXDEvents_h

#include <QEvent>
#include <QString>
#include <vector>

namespace hxd
{

enum EventID
{
	NewTorrentFoundID = QEvent::User,
	TorrentScanBegunID,
	TorrentScanFinishedID,
	RouterScanFinishedID,
	TorrentFileDownloadFinishedID,
	TorrentDownloadFinishedID,
	StatisticsScanFinishedID
};

class NewTorrentFound : public QEvent
{
    public:
        NewTorrentFound( const QString& title, const QString& link );

        const QString& getTitle();
        const QString& getLink();

    private:
        QString m_title;
        QString m_link;
}; 

class TorrentScanBegun : public QEvent
{
    public:
        TorrentScanBegun();
};
 
class TorrentScanFinished : public QEvent
{
    public:
        TorrentScanFinished();
}; 

class RouterScanFinished : public QEvent
{
	public:
		RouterScanFinished(unsigned int hours, unsigned int megabytes);
		
		unsigned int getHours() const;
		unsigned int getMegabytes() const;
		
	private:
		unsigned int m_hours;
		unsigned int m_megabytes;
};

class TorrentFileDownloadFinished : public QEvent
{
    public:
    TorrentFileDownloadFinished(const QString& url, 
                                const QString& path, 
                                const QString& error, 
                                const bool ok, 
                                const int id);
    
        const QString& getUrl();
        const QString& getPath();
        const QString& getError();
        const bool ok();
        const int getID();
    
    private:
        QString m_url;
        QString m_path;
        QString m_error;
        bool m_ok;
        int m_id;
};

class TorrentDownloadFinished : public QEvent
{
    public:
    TorrentDownloadFinished(const QString& url, 
                            const QString& path,
                            const QString& error, 
                            const bool ok, 
                            const int id);
    
        const QString& getUrl();
        const QString& getPath();
        const QString& getError();
        const bool ok();
        const int getID();
    
    private:
        QString m_url;
        QString m_path;
        QString m_error;
        bool m_ok;
        int m_id;
};

class StatisticsScanFinished: public QEvent
{
    public:
        struct TorrentStatistics
        {
            QString torrent;
            unsigned int seeders;
            unsigned int leechers;
        };
        typedef std::vector<TorrentStatistics> StatisticsVector;
        
        void addStatistics(const TorrentStatistics& stats);
        StatisticsVector getStatistics() const;
        
    StatisticsScanFinished();
    
    private:
        StatisticsVector m_statsVec;
};


}

#endif