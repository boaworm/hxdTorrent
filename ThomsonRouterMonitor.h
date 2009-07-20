#ifndef ThomsonRouterMonitor_h
#define ThomsonRouterMonitor_h

#include "HXDConfiguration.h"

#include <string>

#include <QMutex>
#include <QThread>

#include "curl/curl.h"

class QObject;

namespace hxd
{

class ThomsonRouterMonitor : public QThread
{
    public:
        ThomsonRouterMonitor(QObject* parent);
        ~ThomsonRouterMonitor();
        void stop();
    
    protected:
        void run();
        
    private:        
        bool m_stop;
        QMutex m_urlMutex;
        QObject* m_parent;

        // Curl stuff
        CURLcode m_result;
        char m_errorBuffer[256];
        char m_urlBuffer[4096];
        std::string m_buffer;


        static int curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer);
};


} // END NAMESPACE

#endif