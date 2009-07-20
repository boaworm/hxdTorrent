SOURCES 	=	main.cpp \
			RSSScanner.cpp \
			RSSScannerTab.cpp \
			HXDTorrent.cpp \
			HXDEvents.cpp \
			MainWindow.cpp \
			ThomsonRouterMonitor.cpp \
			TorrentFileDownloader.cpp \
			TorrentDownloader.cpp \
			TorrentFilesTab.cpp \
			TorrentStatisticsGrabber.cpp \
			HXDConfiguration.cpp

HEADERS		=	RSSScanner.h \
			RSSScannerTab.h \
			HXDTorrent.h \
			HXDEvents.h \
			MainWindow.h \
			ThomsonRouterMonitor.h \
			TorrentFileDownloader.h \
			TorrentDownloader.h \
			TorrentFilesTab.h \
			TorrentStatisticsGrabber.h \
			HXDConfiguration.h

TARGET		= 	hxdTorrent

CONFIG 		+=	qt debug thread 

QT		+= 	xml

LIBS 		+= 	-lcurl -L/opt/local/lib -lboost_date_time

INCLUDEPATH 	+= 	/opt/local/include/
