
#include "RSSScannerTab.h"
#include "HXDConfiguration.h"
#include "HXDTorrent.h"

#include <QFont>
#include <QLabel>
#include <QListWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include <QMessageBox>
#include <QToolTip>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QRegExp>
#include <QDebug>

namespace hxd
{

MyListWidget::MyListWidget(QWidget* parent) : QListWidget(parent)
{
    qDebug("Creating a MyListWidget");
}
void MyListWidget::keyPressEvent(QKeyEvent* event)
{
    // Do something
    if( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete )
    {
        emit deleteSelectedTorrents();
    }
    else
    {
        QListWidget::keyPressEvent(event);
    }
}

BandwidthUsageWidget::BandwidthUsageWidget(QWidget* parent) : QWidget(parent)
{
	QHBoxLayout* mainLayout = new QHBoxLayout( this );
	
	m_megabytesLabel = new QLabel("0",this);
	m_hoursLabel = new QLabel("0",this);
	m_averageLabel = new QLabel("0",this);
	m_leftToCapLabel = new QLabel("0",this);
	
	mainLayout->addWidget( new QLabel("Transferred",this) );
	mainLayout->addWidget( m_megabytesLabel );
	mainLayout->addWidget( new QLabel("MB over ",this) );
	mainLayout->addWidget( m_hoursLabel );
	mainLayout->addWidget( new QLabel("hours. Average per day:",this) );
	mainLayout->addWidget( m_averageLabel );
	mainLayout->addWidget( new QLabel("MB. You have",this) );
	mainLayout->addWidget( m_leftToCapLabel );
	mainLayout->addWidget( new QLabel("MB left until cap",this) );
	mainLayout->addItem(new QSpacerItem(1,1,QSizePolicy::MinimumExpanding,QSizePolicy::Maximum));
}

void BandwidthUsageWidget::updateBandwidthUsage(unsigned int hours, unsigned int megabytes)
{

	qDebug() << "Hours = " << hours << ", megabytes = " << megabytes;

	m_megabytesLabel->setText( QString::number(megabytes) );
	m_hoursLabel->setText( QString::number(hours) );
	
	double d = hours / 24.0;
	
	unsigned int avg = megabytes / d;  
	
	unsigned int maxAllowed = 42 * hours;
	int leftUntilCap = maxAllowed - megabytes;
	
	if( avg < 1000 )
	{
		m_averageLabel->setText("<font color=\"green\">" +  QString::number(avg) + "</font>" );
	}
	else if( avg < 1300 )
	{
		m_averageLabel->setText("<font color=\"orange\">" +  QString::number(avg) + "</font>" );
	}
	else
	{
		m_averageLabel->setText("<font color=\"red\">" +  QString::number(avg) + "</font>" );
	}
	
	m_leftToCapLabel->setText( QString::number( leftUntilCap ) );
}


RSSScannerTab::RSSScannerTab(QWidget* parent, HXDTorrent* hxd, HXDConfiguration* config) 
: QWidget(parent), m_hxd(hxd), m_config(config)
{
    qDebug("Creating RSSScannerTab");
    
    QGridLayout* layout = new QGridLayout( this );
    
    QLabel* titleLabel = new QLabel( "List of recent torrents", this );
    layout->addWidget( titleLabel, 1, 1 );
    
    m_torrentListWidget = new MyListWidget( this );
    m_torrentListWidget->setSortingEnabled( true );
    m_torrentListWidget->setSelectionMode( QAbstractItemView::ContiguousSelection );
    layout->addWidget( m_torrentListWidget, 2, 1 );
    
    // Tree in which we show the rss URLs and their respective regexps
    QLabel* treeLabel = new QLabel( "RSS Feeds and matching patterns", this );
    layout->addWidget( treeLabel, 1, 2 );
    m_rssTreeWidget = new QTreeWidget( this );
    layout->addWidget( m_rssTreeWidget, 2, 2 );
	
	m_bandwidthWidget = new BandwidthUsageWidget(this);
	layout->addWidget( m_bandwidthWidget, 3,1,1,2 );
	
    // And populate the tree.
    HXDConfiguration::RSSMap map( m_config->getRSSMap() );
    HXDConfiguration::RSSMap::iterator it = map.begin();
    for(;it!=map.end();++it)
    {
        QTreeWidgetItem* rssUrl = new QTreeWidgetItem( m_rssTreeWidget );
        rssUrl->setText( 0, it->first );
        for(unsigned int i=0;i<it->second.size();++i)
        {
            QTreeWidgetItem* pattern = new QTreeWidgetItem( rssUrl );
            pattern->setText( 0, it->second[i].pattern() );
        }
        m_rssTreeWidget->addTopLevelItem( rssUrl );
        m_rssTreeWidget->expandItem( rssUrl );
    }
    
    // CONNECT STUFF
    connect(
            hxd,SIGNAL(newTorrentAvailable()),
            this,SLOT(refreshTorrents())
            );
    
    connect(
            m_torrentListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(listWidgetDoubleClicked(QListWidgetItem*))
            );
    
    connect(
            m_torrentListWidget,SIGNAL(deleteSelectedTorrents()),
            this,SLOT(deleteSelectedTorrents())
            );
    connect(
            hxd,SIGNAL(markExistingTorrentsAsOld()),
            this,SLOT(markExistingTorrentsAsOld())
            );
    connect(
            hxd,SIGNAL(torrentAlreadyExists(QString)),
            this,SLOT(markTorrentAsCurrentlyListed(QString))
            );
	connect(
			hxd,SIGNAL( dataTransferStatsUpdated(unsigned int,unsigned int)),
			m_bandwidthWidget,SLOT(updateBandwidthUsage(unsigned int, unsigned int))
			);
}

RSSScannerTab::~RSSScannerTab()
{
    qDebug("Deleting RSSScannerTab");
    delete m_torrentListWidget;
    delete m_rssTreeWidget;
}


void RSSScannerTab::refreshTorrents()
{
    // do something!
    qDebug(" Refreshing torrents list" );
                                         
    HXDTorrent::TorrentMap* map( m_hxd->getTorrentMap() );
                                         
    HXDTorrent::TorrentMap::const_iterator it( map->begin() );
    HXDTorrent::TorrentMap::const_iterator itEnd( map->end() );
    
    before_removal:
    for(int i=0;i<m_torrentListWidget->count();++i)
    {
        // See if we should purge any widgets. 
        if( itEnd == map->find( m_torrentListWidget->item(i)->text() ) )
        {
            // Remove widget. 
            delete m_torrentListWidget->takeItem(i);
            goto before_removal;
        }
    }
    bool found;
    
   
    for(;it!=itEnd;++it)
    {
        found = false;
        for(int i=0;i<m_torrentListWidget->count();++i)
        {
            if( it->first == m_torrentListWidget->item(i)->text() )
            {
                found = true;
                
                // m_torrentListWidget->item(i)->setFont( f );
                break;
            }
        }
        if( !found )
        {
            // Insert it
            m_torrentListWidget->addItem( it->first );
        }
    }
}

void RSSScannerTab::listWidgetDoubleClicked(QListWidgetItem* item)
{
    qDebug("Clicked widget : " + item->text().toLatin1() );
    
    int reply = QMessageBox::question( this, 
                                       "Download this torrent?",
                                       "Do you want to download this torrent ?",
                                       QMessageBox::Ok,
                                       QMessageBox::Cancel);
    if( reply == QMessageBox::Ok )
    {
        qDebug("Download torrent!");

        QList<QListWidgetItem*> list( m_torrentListWidget->selectedItems() );
        for( int i=0;i<list.size();++i)
        {
            if( !m_hxd->downloadTorrent( list[i]->text() ) )
            {   
                QMessageBox::warning( this,
                "Cannot find torrent",
                "Sorry, but I cannot find that torrent :-(",
                                      QMessageBox::Ok);
            }
        }
    }
    else
    {
        qDebug("Don't download torrent");
    }
    
    
}

void RSSScannerTab::deleteSelectedTorrents()
{
    bool deleted = false;
    qDebug("OK, delete all the selected ones...");
    QList<QListWidgetItem*> list( m_torrentListWidget->selectedItems() );
    for( int i=0;i<list.size();++i)
    {
        m_torrentListWidget->removeItemWidget( list[i] );
        
        HXDTorrent::TorrentMap* map( m_hxd->getTorrentMap() );
        
        HXDTorrent::TorrentMap::iterator it( map->begin() );
        it = map->find( list[i]->text() );
        if( it != map->end() )
        {
            map->erase( it );
            deleted = true;
        }
    }
    if( deleted )
        refreshTorrents();
}

void RSSScannerTab::markExistingTorrentsAsOld()
{
    qDebug("Enter - marking existing torrents as old");
    QFont f;

    QList<QListWidgetItem*> list( m_torrentListWidget->findItems("*", Qt::MatchWildcard ) );
    qDebug("Size of list = %i", list.size());
    for( int i=0;i<list.size();++i)
    {
        qDebug("setting font to italic for: " + list[i]->text().toLatin1() );
        f = list[i]->font();
        f.setItalic( true );
        list[i]->setFont( f );
    }
}


void RSSScannerTab::markTorrentAsCurrentlyListed(QString name)
{
    qDebug("Marking a torrent as currently listed in RSS feed: " + name.toLatin1() );
    QFont f;

    QList<QListWidgetItem*> list( m_torrentListWidget->findItems(name, Qt::MatchExactly ) );
    qDebug("list.size() = %i", list.size());
    for(int i=0;i<list.size();++i)
    {
        f = list[i]->font();
        f.setItalic( false );
        list[i]->setFont( f );
    }

}




}