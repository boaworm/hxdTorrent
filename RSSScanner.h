#ifndef RSSScanner_h
#define RSSScanner_h

#include "HXDConfiguration.h"

#include <string>

#include <QMutex>
#include <QThread>

#include "curl/curl.h"

class QObject;

namespace hxd
{

class RSSScanner : public QThread
{
    public:
        RSSScanner(QObject* parent);
        ~RSSScanner();
        
        void addScannerTarget( const QString& url, const std::vector<QRegExp>& regex );
        void stop();
    
    protected:
        void run();
        
    private:        
            HXDConfiguration::RSSMap m_rssMap;
    
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