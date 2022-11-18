#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow()
{
    auto menuBar = new QMenuBar(this);
    auto fileMenu = new QMenu("File");

    auto helpMenu = new QMenu("Help");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);
}


MainWindow::~MainWindow()
{

}
