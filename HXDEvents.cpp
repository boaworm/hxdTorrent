
#include "HXDEvents.h"




namespace hxd
{


NewTorrentFound::NewTorrentFound(const QString& title, const QString& link)
	: QEvent( (QEvent::Type)NewTorrentFoundID), m_title(title), m_link(link)
{}
    
    const QString& NewTorrentFound::getTitle()
{
        return m_title;
}
const QString&  NewTorrentFound::getLink()
{
    return m_link;
}

TorrentScanBegun::TorrentScanBegun() : QEvent((QEvent::Type)TorrentScanBegunID)
{
    //
}
TorrentScanFinished::TorrentScanFinished() : QEvent((QEvent::Type)TorrentScanFinishedID)
{
    // 
}

TorrentFileDownloadFinished::TorrentFileDownloadFinished(
                                                         const QString& url, 
                                                         const QString& path, 
                                                         const QString& error,
                                                         const bool ok,
                                                         const int id)
: QEvent((QEvent::Type)TorrentFileDownloadFinishedID), m_url(url), m_path(path), m_error(error), m_ok(ok), m_id(id)
{}

const QString& TorrentFileDownloadFinished::getUrl()
{
    return m_url;
}
const QString& TorrentFileDownloadFinished::getPath()
{
    return m_path;
}
const bool TorrentFileDownloadFinished::ok()
{
    return m_ok;
}
const QString& TorrentFileDownloadFinished::getError()
{
    return m_error;
}
const int TorrentFileDownloadFinished::getID()
{
    return m_id;
}




TorrentDownloadFinished::TorrentDownloadFinished(
                                                         const QString& url, 
                                                         const QString& path, 
                                                         const QString& error,
                                                         const bool ok,
                                                         const int id)
: QEvent((QEvent::Type)TorrentDownloadFinishedID), m_url(url), m_path(path), m_error(error), m_ok(ok), m_id(id)
{}

const QString& TorrentDownloadFinished::getUrl()
{
    return m_url;
}
const QString& TorrentDownloadFinished::getPath()
{
    return m_path;
}
const bool TorrentDownloadFinished::ok()
{
    return m_ok;
}
const QString& TorrentDownloadFinished::getError()
{
    return m_error;
}
const int TorrentDownloadFinished::getID()
{
    return m_id;
}




StatisticsScanFinished::StatisticsScanFinished() : QEvent((QEvent::Type)StatisticsScanFinishedID)
{}

void StatisticsScanFinished::addStatistics(const TorrentStatistics& stats)
{
    m_statsVec.push_back( stats );
}
StatisticsScanFinished::StatisticsVector StatisticsScanFinished::getStatistics() const
{
    return m_statsVec;
}


RouterScanFinished::RouterScanFinished(unsigned int hours, unsigned int megabytes)
: QEvent((QEvent::Type)RouterScanFinishedID), m_hours(hours), m_megabytes(megabytes)
{}

unsigned int RouterScanFinished::getHours() const
{
	return m_hours;
}
unsigned int RouterScanFinished::getMegabytes() const
{
	return m_megabytes;
}





}