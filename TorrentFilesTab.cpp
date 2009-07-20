
#include "TorrentFilesTab.h"

#include "HXDConfiguration.h"
#include "HXDTorrent.h"

#include <QDir>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>

#define QT_TREEWIDGET_TOPLEVEL_TYPE 1001

namespace hxd
{

MyTreeWidget::MyTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    qDebug("Creating a MyTreeWidget");
}
void MyTreeWidget::keyPressEvent(QKeyEvent* event)
{
    // Do something
    if( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete )
    {
        emit deleteSelectedTorrents();
        qDebug("Delete the selected torrents!");
    }
    else
    {
        QTreeWidget::keyPressEvent(event);
    }
}





TorrentFilesTab::TorrentFilesTab(QWidget* parent, HXDTorrent* hxd)
: QWidget(parent), m_hxd(hxd)
{
    qDebug("Creating TorrentFilesTab");
    
    QGridLayout* layout = new QGridLayout( this );
    
    m_dir.setPath( hxd->getConfig()->getTorrentFilesDir() );
    if( !m_dir.exists() )
    {
        qWarning("OOPS, torrent dir did not exist, trying to create it");
        // Create it!
        QStringList list( m_dir.path().split('/') );
        
        m_dir.cdUp();
        m_dir.mkdir( list.last() );
        
    }
    qDebug("Torrent dir set to : " + m_dir.path().toLatin1() );
    
    m_treeWidget = new MyTreeWidget( this );
    layout->addWidget( m_treeWidget, 1, 1 );
    
    
    
    
    torrentFileDownloadFinished("","","",true);
                
    
    connect(
            m_hxd,SIGNAL(torrentFileDownloadFinished(QString,QString,QString,bool)),
            this,SLOT(torrentFileDownloadFinished(QString,QString,QString,bool))
            );
    connect(
        m_treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
        this,SLOT(torrentDoubleClicked(QTreeWidgetItem*,int))
    );
    connect(
        m_treeWidget,SIGNAL(deleteSelectedTorrents()),
        this,SLOT(deleteSelectedTorrents())
        );

    
}

TorrentFilesTab::~TorrentFilesTab()
{
    qDebug("Deeleting TorrentFilesTab");
    delete m_treeWidget;
}

void TorrentFilesTab::refreshTorrentView()
{
    torrentFileDownloadFinished("","","",ok);
}

// PROTECTED


// PRIVATE


void TorrentFilesTab::torrentFileDownloadFinished(QString,QString,QString,bool ok)
{
    if( ok )
    {
        // qDebug("Refreshing the torrent file view");
        
        // A new torrent has arrived, refresh the view we have.
        QStringList filter;
        filter.push_back("*.torrent");
        QStringList torrents = m_dir.entryList( filter, QDir::Files | QDir::Readable | QDir::NoSymLinks, QDir::Name );
    
        // qDebug("Found %i torrent files", torrents.size());

        QList<QTreeWidgetItem*> itemList( m_treeWidget->findItems("*",Qt::MatchWildcard) );
        for(int i=0;i<itemList.count();++i)
        {
            // If parent is m_treeWidget AND name is not in the torrents list, remove it. 
            if( itemList[i]->type() == QT_TREEWIDGET_TOPLEVEL_TYPE )
            {
                // TOP Level item.
                bool found = false;
                for(int j=0;j<torrents.count();++j)
                {
                    if( itemList[i]->text( 0 ) == torrents[j] )
                    {
                        // Found it!
                        found = true;
                    }
                }
                if(!found)
                {
                    // Purge it!
                    delete itemList[i];
                }
            }
        }
        
        
        // Now that no GUI components exist for non-existant torrents, add new torrents.
        itemList = m_treeWidget->findItems("*",Qt::MatchWildcard);
        
        for(int i=0;i<torrents.count();++i)
        {
            bool found = false;
            // qDebug("Matching " + torrents[i].toLatin1() );
            for(int j=0;j<itemList.count();++j)
            {
                // qDebug(" --- with " + itemList[j]->text( 0 ).toLatin1() );
                if( itemList[j]->type() == QT_TREEWIDGET_TOPLEVEL_TYPE &&
                    itemList[j]->text( 0 ) == torrents[i] )
                {
                    found = true;
                    break;
                }
            }
            if( !found )
            {
                // Add it!
                QTreeWidgetItem* item = new QTreeWidgetItem( m_treeWidget, QT_TREEWIDGET_TOPLEVEL_TYPE );
                item->setText( 0, torrents[i] );
            }
        }


        
    
    }
    else
    {
        // qDebug("Not OK!");
    }
}



void TorrentFilesTab::torrentDoubleClicked(QTreeWidgetItem* item,int)
{
    qDebug("Someone doubleclicked an item");
    
    if( item->childCount() == 0 )
    {
        qDebug("Clicked on a child-node - ignoring");
        return;
    }
    
    QString msg("You are about to start downloading the following torrent\n\n");
    msg.append( item->text( 0 ) );
    msg.append("\n\n");
    int ret = QMessageBox::question(
        this,
        "Start downloading?",
        msg,
        QMessageBox::Ok,
        QMessageBox::Cancel
    );
    
    if( ret == QMessageBox::Ok )
    {
        qDebug("Time to start leeching!");
        
        m_hxd->beginDownloading( item->text( 0 ) );
    }
    
}


void TorrentFilesTab::deleteSelectedTorrents()
{
    QList<QTreeWidgetItem*> widgetList( m_treeWidget->selectedItems() );
    QList<QTreeWidgetItem*>::iterator it( widgetList.begin() );
    for(;it!=widgetList.end();++it)
    {
        if( (*it)->type() == QT_TREEWIDGET_TOPLEVEL_TYPE )
        {
            QString filepath = m_hxd->getConfig()->getTorrentFilesDir();
            filepath.append("/");
            filepath.append( (*it)->text( 0 ) );
            
            QFile f( filepath );
            if( f.exists() )
            {
                if( !f.remove() )
                {
                    qWarning("OOPS failed to remove the file");
                }
                else
                {
                    delete *it;
                    continue;
                }
            }
        }
    }
}






}