#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow()
{
    setWindowTitle("Checkmate");

    auto menuBar = new QMenuBar(this);
    auto fileMenu = new QMenu("File");
    auto newAction = new QAction("New...");
    fileMenu->addAction(newAction);

    auto helpMenu = new QMenu("Help");
    auto aboutAction = new QAction("About");
    helpMenu->addAction(aboutAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);

    setMenuBar(menuBar);
}


MainWindow::~MainWindow()
{

}
