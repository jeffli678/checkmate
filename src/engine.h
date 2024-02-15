#pragma once

#include <cinttypes>
#include <string>
#include <filesystem>
#include <QObject>
#include <QProcess>
#include "ucicommon.h"
using namespace std;

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
    bool SetUCIOption(const QString& name, const QString& value);
    bool SetUCIOption(const QString& name, uint64_t value);
    void Stop();
    void Quit();
    void SetFen(const QString& fen);
    void Go();
    void Kill();

    void onReadReady();

signals:
    void onNewInfo();
};
