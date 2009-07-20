
#include "MainWindow.h"

#include "HXDConfiguration.h"
#include "HXDTorrent.h"
#include "RSSScannerTab.h"
#include "TorrentFilesTab.h"

#include <QTabWidget>
#include <QGridLayout>
#include <QMessageBox>

namespace hxd
{


MainWindow::MainWindow(HXDTorrent* hxd) : QMainWindow(), m_hxd(hxd)
{
    // CREATING
    qDebug("Creating MainWindow");

    this->setGeometry( 200, 200, 800, 600 );

    // Tab widget
    m_tabWidget = new QTabWidget( this );
    this->setCentralWidget( m_tabWidget );
    
    // RSS Scanner
    m_rssScannerTab = new RSSScannerTab( this, hxd, m_hxd->getConfig() );
    m_tabWidget->addTab( m_rssScannerTab, "RSS Scanner" );
    
    // Torrent files
    m_torrentFilesTab = new TorrentFilesTab( this, hxd );
    m_tabWidget->addTab( m_torrentFilesTab, "Torrent files" );
    

    // Placeholders
    QWidget* ph1 = new QWidget( this );
    QWidget* ph2 = new QWidget( this );
    m_tabWidget->addTab( ph1, "Placeholder1" );
    m_tabWidget->addTab( ph2, "Placeholder2" );

    // Connects
    /*
    connect(
        m_hxd,SIGNAL(torrentFileDownloadFinished(const QString& url, const QString& path, const QString& error, const bool ok)),
        this,SLOT(torrentFileDownloadFinished(const QString& url, const QString& path, const QString& error, const bool ok))
    );
    */
    connect(
            m_hxd,SIGNAL(torrentFileDownloadFinished(QString,QString,QString,bool)),
            this,SLOT(torrentFileDownloadFinished(QString,QString,QString,bool))
            );
    connect(
        m_tabWidget,SIGNAL(currentChanged(int)),
        this,SLOT(activeTabChanged(int))
    );
	// connect(
			
   
}

MainWindow::~MainWindow()
{
    // DELETING
    qDebug("Deleting MainWindow");
    
    delete m_tabWidget;
}



// PROTECTED



// PRIVATE

//void MainWindow::torrentFileDownloadFinished(const QString& url, const QString& path, const QString& error, const bool ok)
void MainWindow::torrentFileDownloadFinished(QString url,QString path,QString error,bool ok)
{
    if( ok )
    {
        if( !url.isEmpty() && !path.isEmpty() )
        {
            QString msg("The following torrent file was successfully downloaded:\n");
            msg.append( path );
            msg.append("\n");
    
            QMessageBox::information(this,"Torrent file downloaded!",msg);
        }
        else
        {
            qDebug("Why whas this called?");
        }
    }
    else
    {
        QString msg("Sorry, but I was unable to download the following torrent file for you:\n\n");
        msg.append("URL: ");
        msg.append(url);
        msg.append("\n");
        msg.append("Path: ");
        msg.append(path);
        msg.append("\n\nError message: ");
        msg.append(error);
        QMessageBox::warning(this,"Torrent file download failed!",msg);
    }
}

void MainWindow::activeTabChanged(int index)
{
    QWidget* w = m_tabWidget->widget(index);
    
    TorrentFilesTab* ptr( dynamic_cast<TorrentFilesTab*>(w) );
    
    if( ptr )
    {
        ptr->refreshTorrentView();
    }
}





}