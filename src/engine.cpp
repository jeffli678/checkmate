#include "engine.h"
#include <chrono>
#include <thread>


Engine::Engine(const QString &path): m_enginePath(path)
{

}


bool Engine::Init()
{
    m_process = new QProcess;
    connect(m_process, &QProcess::readyReadStandardOutput, this, &Engine::onReadReady);
    connect(m_process, &QProcess::started, [&](){ m_engineStatus = Started; });
    connect(m_process, &QProcess::errorOccurred, [&](){ m_engineStatus = Error; });

    m_engineStatus = Starting;
    m_process->start(m_enginePath);

    Write("uci\n");
    return true;
}


void Engine::Write(const QString &content)
{
    printf("user: %s", content.toStdString().c_str());
    m_process->write(content.toStdString().c_str());
}


void Engine::onReadReady()
{
    while (m_process->isReadable() && m_process->canReadLine())
    {
        QString line = QString(m_process->readLine());
        if (line.endsWith('\n'))
            line.chop(1);
        if (line.isEmpty())
            continue;
        printf("engine: %s\n", line.toStdString().c_str());
        if (line == "uciok")
        {
            m_engineStatus = Ready;
        }
        else if (line.startsWith("info"))
        {
            // info depth 19 seldepth 27 multipv 1 score cp 31753 nodes 4051383 nps 1131671 hashfull 970 tbhits 0 time 3580 pv b2b9 h9g7 b0c2 b7b5 e0e1 b5c5 a0a2 g7e8 b9b0 c5i5 h2i2 e6e5 c3c4 e5e4 i2i5 i6i5 g0e2

        }

    }
}

void Engine::SetFen(const QString &fen)
{
    Write(QString("position fen " + fen + "\n").toStdString().c_str());
}


void Engine::Go()
{
    Write("go ponder\n");
}


void Engine::Stop()
{
    Write("stop\n");
}
