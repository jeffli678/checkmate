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

//    if (!m_process->waitForStarted())
//    {
//        auto error = m_process->error();
//        printf("failed to start: %d\n", error);
//        return false;
//    }

    // THis needs better portability
//    if (!m_process->waitForReadyRead())
//    {
//        auto error = m_process->error();
//        printf("failed to wait for read: %d\n", error);
//        return false;
//    }
//    auto array = m_process->readLine();

//    size_t attempts = 0;
//    while (attempts < 100)
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        if (m_engineStatus == Error)
//            return false;
//        else if (m_engineStatus == Started)
//            m_process->write("uci\n");
//        attempts++;
//    }
    m_process->write("uci\n");

//    auto attempts = 0;
//    while (attempts < 100)
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        if (m_engineStatus == Error)
//            return false;
//        else if (m_engineStatus == Ready)
//            return true;
//        attempts++;
//    }
//    return false;

//    if (!m_process->waitForBytesWritten())
//    {
//        auto error = m_process->error();
//        printf("failed to write: %d\n", error);
//        return false;
//    }

//    if (!m_process->waitForReadyRead())
//    {
//        auto error = m_process->error();
//        printf("failed to wait for read: %d\n", error);
//        return false;
//    }
//
//    while (true)
//    {
//        auto array = m_process->readLine();
//        if (array.startsWith("uciok"))
//            break;
//    }
    return true;
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
        printf("%s\n", line.toStdString().c_str());
        if (line == "uciok")
        {
            m_engineStatus = Ready;
        }
        else if (line.startsWith("info"))
        {

        }

    }
}

void Engine::SetFen(const QString &fen)
{
    m_process->write(QString("position fen " + fen + "\n").toStdString().c_str());
//    if (!m_process->waitForBytesWritten())
//    {
//        auto error = m_process->error();
//        printf("failed to write: %d\n", error);
//    }
}


void Engine::Go()
{
    m_process->write("go ponder\n");
//    if (!m_process->waitForBytesWritten())
//    {
//        auto error = m_process->error();
//        printf("failed to write: %d\n", error);
//    }
}


void Engine::Stop()
{
    m_process->write("stop\n");
}
