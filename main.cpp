#include <QApplication>

#include "HXDTorrent.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Welcome to hxdTorrent" << std::endl;

    QApplication app( argc, argv );

    hxd::HXDTorrent hxdTorrent;
    
    return app.exec();
  

}