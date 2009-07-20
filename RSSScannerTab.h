
#ifndef RSSScannerTab_h
#define RSSScannerTab_h

#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QWidget>


class QListWidgetItem;
class QKeyEvent;
class QTreeWidget;



namespace hxd
{
class HXDConfiguration;
class HXDTorrent;

class MyListWidget : public QListWidget
{
    Q_OBJECT
    public:
        MyListWidget(QWidget* parent = 0);
        
    signals:
        void deleteSelectedTorrents();
    
    protected:
        void keyPressEvent(QKeyEvent* event);

};
 
class BandwidthUsageWidget: public QWidget
{
	Q_OBJECT
	public:
		BandwidthUsageWidget(QWidget* parent = 0);
	
	public slots:
		void updateBandwidthUsage(unsigned int hours, unsigned int megabytes);

	private:
		QLabel* m_hoursLabel;
		QLabel* m_megabytesLabel;
		QLabel* m_averageLabel;
		QLabel* m_leftToCapLabel;
};

class RSSScannerTab : public QWidget
{
    Q_OBJECT
    public:
        RSSScannerTab(QWidget* parent, HXDTorrent* hxd, HXDConfiguration* config);
        ~RSSScannerTab();

    public slots:
        void refreshTorrents();

    protected:
    
    private:
        MyListWidget* m_torrentListWidget;
        HXDTorrent* m_hxd;
        QTreeWidget* m_rssTreeWidget;
        HXDConfiguration* m_config;
		BandwidthUsageWidget* m_bandwidthWidget;
		
    private slots:
        void listWidgetDoubleClicked(QListWidgetItem* item);
        void deleteSelectedTorrents();
        void markExistingTorrentsAsOld();
        void markTorrentAsCurrentlyListed(QString);

};








}

#endif 