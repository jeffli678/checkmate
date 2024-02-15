#pragma once

#include <cinttypes>
#include <string>
#include <filesystem>
#include <QObject>
#include <QProcess>
#include "ucicommon.h"
using namespace std;

enum PonderInfoType
{
    Info_Depth,
    Info_Seldeptch,
    Info_Multipv,
    Info_Score,
    Info_Nodes,
    Info_Nps,
    Info_Hashfull,
    Info_Tbhits,
    Info_Time,
    Info_Pv,
    Info_Invalid
};

struct PonderInfo
{
    uint64_t depth;
    uint64_t seldepth;
    uint64_t multipv;
    uint64_t score;
    uint64_t nodes;
    uint64_t nps;
    uint64_t hashfull;
    uint64_t tbhits;
    uint64_t time;
    MoveList pv;
};

class Engine: public QObject
{
    Q_OBJECT

private:
    enum EngineStatus
    {
        Inactive,
        Starting,
        Started,
        Ready,
        Thinking,
        Idle,
        Error
    };

    QString m_enginePath;
    QProcess* m_process;
    EngineStatus m_engineStatus = Inactive;

public:
    Engine(const QString& path);
    void SetEnginePath(const QString& path);
    bool Init();
    void Write(const QString& content);
    bool SetUCIOption(const QString& name, const QString& value);
    bool SetUCIOption(const QString& name, uint64_t value);
    void Stop();
    void Quit();
    void SetFen(const QString& fen);
    void Go();
    void Kill();

    void parseInfo(const QString& line);
    MoveList parseMoveList(const QString& line, size_t& bytesConsumed);
    void onReadReady();

signals:
    void newPonderInfo(const PonderInfo& info);
};
