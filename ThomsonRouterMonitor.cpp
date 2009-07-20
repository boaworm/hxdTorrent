#include "ThomsonRouterMonitor.h"

#include "HXDEvents.h"

#include <QApplication>
#include <QDomDocument>
#include <QObject>
#include <QStringList>

#include <QDebug>

namespace hxd
{
    
	ThomsonRouterMonitor::ThomsonRouterMonitor(QObject* parent) : m_stop(false), m_parent(parent)
	{
        qDebug( "Creating a ThomsonRouterMonitor object" ); 
	}
	
	ThomsonRouterMonitor::~ThomsonRouterMonitor()
	{
		qDebug( "Deleting a ThomsonRouterMonitor object" ); 
	}
	
	void ThomsonRouterMonitor::stop()
	{
		m_stop = true;
	}
	
	int ThomsonRouterMonitor::curlWriter(char* data, size_t size, size_t nmemb, std::string* buffer)
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
	
	void ThomsonRouterMonitor::run()
	{
		
		std::string internetUrl = "http://192.168.1.254/cgi/b/is/_pppoe_/ov/?be=0&l0=1&l1=1&name=Internet";
		std::string portalUrl = "http://192.168.1.254/cgi/b/is/_bridge_/ov/?be=0&l0=1&l1=1&name=Portal";
		while( !m_stop )
		{
			// Tag existing ones as "old"
			TorrentScanBegun* tsb = new TorrentScanBegun();
			QApplication::postEvent(m_parent,tsb);
			
			unsigned int totalHours(0);
			unsigned int totalMegabytes(0);
			
			m_buffer.clear();
			CURL* curl;
			curl = curl_easy_init();
			memcpy(m_urlBuffer,internetUrl.c_str(), internetUrl.length());
			m_urlBuffer[internetUrl.length()] = 0;
			curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, m_errorBuffer);
			curl_easy_setopt(curl,CURLOPT_URL, m_urlBuffer );
			curl_easy_setopt(curl,CURLOPT_HEADER, 0 );
			curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1 );
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, curlWriter );
			curl_easy_setopt(curl,CURLOPT_WRITEDATA, &m_buffer );
			curl_easy_setopt(curl,CURLOPT_NOPROGRESS, 1 );
			curl_easy_setopt(curl,CURLOPT_BUFFERSIZE, 20000 );
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
			curl_easy_setopt(curl,CURLOPT_USERPWD,"user:pass");
			
			m_result = curl_easy_perform( curl );
			curl_easy_cleanup(curl);
			
			if( m_result == CURLE_OK )
			{
				QString sentUnit;
				QString receivedUnit;
				QString sentAmount;
				QString receivedAmount;
				
				QString string( QString::fromStdString(m_buffer) );
				// qDebug() << "BUFFER = " << string;
				
				// "Data Transferred (Sent/Received) [MB/MB]"
				
				QRegExp rx;
				rx.setCaseSensitivity( Qt::CaseSensitive );
				rx.setPatternSyntax( QRegExp::RegExp2 );
				rx.setPattern("Data Transferred \\(Sent\\/Received\\) .(..).(..)");
				rx.indexIn( string );
				
				QStringList capturedTexts = rx.capturedTexts();
				sentUnit = capturedTexts[1];
				receivedUnit = capturedTexts[2];
				
				rx.setPattern("\\]:\\<\\/td.*>(\\d+).*\\/\\s(\\d+)");
				rx.indexIn( string );
				capturedTexts = rx.capturedTexts();
				
				sentAmount = capturedTexts[1];
				receivedAmount = capturedTexts[2];
				// "Data Transferred (Sent/Received) [MB/MB]"
				
				qDebug() << "Received " << receivedAmount << " " << receivedUnit;
				qDebug() << "Sent " << sentAmount << " " << sentUnit;
				
				if( receivedUnit == "MB" )
				{
					totalMegabytes += receivedAmount.toUInt();
				}
				else if( receivedUnit == "GB" )
				{
					totalMegabytes += (1024 * receivedAmount.toUInt());
				}
				else if( receivedUnit == "TB" )
				{
					totalMegabytes += (1024*1024* receivedAmount.toUInt());
				}
				
				if( sentUnit == "MB" )
				{
					totalMegabytes += sentAmount.toUInt();
				}
				else if( sentUnit == "GB" )
				{
					totalMegabytes += (1024 * sentAmount.toUInt());
				}
				else if( sentUnit == "TB" )
				{
					totalMegabytes += (1024*1024* sentAmount.toUInt());
				}
				
				qDebug() << "Total MB transfer: " << totalMegabytes;
			}
			else
			{
				qWarning("ERROR: Failed to retrieve RSS from URL: " );
				qWarning("REASON: [%i] %s ",m_result, m_errorBuffer);
			}
			
			
			curl = curl_easy_init();
			memcpy(m_urlBuffer,portalUrl.c_str(), portalUrl.length());
			m_urlBuffer[portalUrl.length()] = 0;
			
			curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, m_errorBuffer);
			curl_easy_setopt(curl,CURLOPT_URL, m_urlBuffer );
			curl_easy_setopt(curl,CURLOPT_HEADER, 0 );
			curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1 );
			curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, curlWriter );
			curl_easy_setopt(curl,CURLOPT_WRITEDATA, &m_buffer );
			curl_easy_setopt(curl,CURLOPT_NOPROGRESS, 1 );
			curl_easy_setopt(curl,CURLOPT_BUFFERSIZE, 20000 );
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
			curl_easy_setopt(curl,CURLOPT_USERPWD,"admin:admin");
			
			m_result = curl_easy_perform( curl );
			curl_easy_cleanup(curl);
			
			if( m_result == CURLE_OK )
			{
				// <td colspan='3'>0 days, 17:54:29</td>
				QString string( QString::fromStdString(m_buffer) );
				// qDebug() << "\n\n\n" << string << "\n\n\n";
				QStringList capturedTexts;
				
				QRegExp rx;
				rx.setCaseSensitivity( Qt::CaseSensitive );
				rx.setPatternSyntax( QRegExp::RegExp2 );
				rx.setPattern("Bridge.*Uptime:<\/td><td colspan=\'3\'>(\\d+)\\sday.*,\\s(\\d+):(\\d+):");
				rx.indexIn( string );
				capturedTexts = rx.capturedTexts();
				
				qDebug() << capturedTexts[1] << " days, " 
				<< capturedTexts[2] << " hours, " << 
				capturedTexts[3] << " minutes";
				
				totalHours = capturedTexts[2].toUInt();
				totalHours += capturedTexts[1].toUInt() * 24;
				
				qDebug() << "Total runtime: " << totalHours << " hours";
			}
			else
			{
				qWarning("ERROR: Failed to retrieve RSS from URL: " );
				qWarning("REASON: [%i] %s ",m_result, m_errorBuffer);
			}
			
			RouterScanFinished* rsf = new RouterScanFinished(totalHours,totalMegabytes);
			QApplication::postEvent(m_parent,rsf);
			
			// Sleep 10 minutes
			sleep(  10 * 60 );
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
} // END NAMESPACE
