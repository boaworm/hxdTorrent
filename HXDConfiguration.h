
#ifndef HXDConfiguration_h
#define HXDConfiguration_h

#include <map>
#include <vector>
#include <QRegExp>
#include <QString>

class QDomDocument;

namespace hxd
{
class HXDTorrent;

class HXDConfiguration
{
public:
    HXDConfiguration(HXDTorrent* hxd);
    ~HXDConfiguration();

    typedef std::map< QString, std::vector<QRegExp> > RSSMap;
    const QString& getDownloadDir()
    {
        return m_downloadDir;
    }
    const QString& getTorrentFilesDir()
    {
        return m_torrentFilesDir;
    }
    const RSSMap& getRSSMap()
    {
        return m_rssMap;
    }


    
protected:

private:
    HXDTorrent* m_hxd;
    QDomDocument* m_qdom;
    RSSMap m_rssMap;
    QString m_torrentFilesDir;
    QString m_downloadDir;

    void createDefaultQDom();
};


















}

#endif