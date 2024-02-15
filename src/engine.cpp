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

    Write("uci");
    return true;
}


void Engine::Write(const QString &content)
{
    printf("user: %s\n", content.toStdString().c_str());
    m_process->write((content +'\n').toStdString().c_str());
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
            parseInfo(line.remove(0, 5));
        }
    }
}


MoveList Engine::parseMoveList(const QString &line, size_t &bytesConsumed)
{
    MoveList result;
    auto lineToParse = line;

    while (!lineToParse.isEmpty())
    {
        auto move = lineToParse.remove(0, 4);
        if (move.size() != 4)
            return result;

        PiecePosition start, end;

        QChar c = move[0].toLower();
        if (!((c >= 'a') && (c <= 'i')))
            return result;
        start.column = c.toLatin1() - 'a';

        bool ok;
        uint64_t value = move.mid(1, 1).toULongLong(&ok, 10);
        if (!ok)
            return result;

        if (!((value >= 0) && (value <= 9)))
            return result;
        start.row = 9 - value;

        c = move[2].toLower();
        if (!((c >= 'a') && (c <= 'i')))
            return result;
        end.column = c.toLatin1() - 'a';

        value = move.mid(3, 1).toULongLong(&ok, 10);
        if (!ok)
            return result;

        if (!((value >= 0) && (value <= 9)))
            return result;
        start.row = 9 - value;

        result.moves.push_back({start, end});
        lineToParse.remove(0, 1);
    }

    return result;
}


void Engine::parseInfo(const QString &line)
{
    // info depth 19 seldepth 27 multipv 1 score cp 31753 nodes 4051383 nps 1131671 hashfull 970 tbhits 0 time 3580 \
    // pv b2b9 h9g7 b0c2 b7b5 e0e1 b5c5 a0a2 g7e8 b9b0 c5i5 h2i2 e6e5 c3c4 e5e4 i2i5 i6i5 g0e2
    auto lineToParse = line.trimmed();
    PonderInfo info;
    PonderInfoType type = Info_Invalid;

    uint64_t value;
    MoveList pv;

    QStringList keywords = {
        "depth",
        "seldepth",
        "multipv",
        "score cp",
        "nodes",
        "nps",
        "hashfull",
        "tbhits",
        "time",
        "pv",
    };
    QString token;

    while (!lineToParse.isEmpty())
    {
        for (size_t i = 0; i < keywords.size(); i++)
        {
            token = keywords[i];
            if (lineToParse.startsWith(token))
            {
                type = PonderInfoType(i);
                break;
            }
        }

        if (type == Info_Invalid)
        {
            return;
        }
        else if (type == Info_Pv)
        {
            lineToParse.remove(0, token.size() + 1);
            size_t n;
            pv = parseMoveList(lineToParse, n);
            lineToParse = "";
        }
        else
        {
            lineToParse.remove(0, token.size() + 1);
            auto index = lineToParse.indexOf(' ', 0);
            if (index == -1)
                return;
            bool ok;
            value = lineToParse.first(index).toULongLong(&ok, 10);
            if (!ok)
                return;
            lineToParse.remove(0, index + 1);
        }

        switch (type)
        {
        case Info_Depth:
            info.depth = value;
            break;
        case Info_Seldeptch:
            info.seldepth = value;
            break;
        case Info_Multipv:
            info.multipv = value;
            break;
        case Info_Score:
            info.score = value;
            break;
        case Info_Nodes:
            info.nodes = value;
            break;
        case Info_Nps:
            info.multipv = value;
            break;
        case Info_Hashfull:
            info.score = value;
            break;
        case Info_Tbhits:
            info.nodes = value;
            break;
        case Info_Time:
            info.multipv = value;
            break;
        case Info_Pv:
            info.pv = pv;
            break;
        default:
            break;
        }
    }

    // emit signal
    emit newPonderInfo(info);
}


void Engine::SetFen(const QString &fen)
{
    Write(QString("position fen " + fen).toStdString().c_str());
}


void Engine::Go()
{
    Write("go ponder");
}


void Engine::Stop()
{
    Write("stop");
}
