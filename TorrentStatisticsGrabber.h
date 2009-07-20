#ifndef TorrentStatisticsGrabber_h
#define TorrentStatisticsGrabber_h

#include <string>

#include <QMutex>
#include <QThread>

#include "curl/curl.h"

class QObject;

namespace hxd
{
class HXDTorrent;

class TorrentStatisticsGrabber : public QThread
{
    public:
        TorrentStatisticsGrabber(HXDTorrent* hxd);
        ~TorrentStatisticsGrabber();
        
        void stop();
    
    protected:
        void run();
        
    private:        
        bool m_stop;
        // QMutex m_urlMutex;
        HXDTorrent* m_hxd;


        // Curl stuff
        CURLcode m_result;
        char m_errorBuffer[256];
        char m_urlBuffer[4096];
        std::string m_buffer;

        

        static int curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer);


};


} // END NAMESPACE

#endif