#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>


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

    auto* widget = new QWidget;
    auto* layout = new QVBoxLayout;
    m_fenInput = new QTextEdit(DEFAULT_FEN);
    layout->addWidget(m_fenInput);

    m_analyzeButton = new QPushButton("Analyze");
    layout->addWidget(m_analyzeButton);
    connect(m_analyzeButton, &QPushButton::clicked, this, &MainWindow::StartAnalysis);

    m_stopButton = new QPushButton("Stop");
    layout->addWidget(m_stopButton);
    connect(m_stopButton, &QPushButton::clicked, this, &MainWindow::StopAnalysis);

    m_movesInfo = new QTextEdit("");
    layout->addWidget(m_movesInfo);

    widget->setLayout(layout);
    setCentralWidget(widget);

    InitEngine();
}


void MainWindow::InitEngine()
{
    auto default_engine = "/Users/jeff/checkmate/engines/pikafish/macos/pikafish";
    m_engine = new Engine(default_engine);
    if (!m_engine->Init())
    {
        printf("failed to init engine\n");
        return;
    }
//    m_engine->SetFen(DEFAULT_FEN);
//    m_engine->Go();
//    connect(m_engine, &Engine::onNewInfo, this)
}


void MainWindow::StartAnalysis()
{
    m_engine->SetFen(m_fenInput->toPlainText());
    m_engine->Go();
}


void MainWindow::StopAnalysis()
{
    m_engine->Stop();
}


MainWindow::~MainWindow()
{

}
