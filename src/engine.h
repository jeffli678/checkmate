#pragma once

#include <cinttypes>
#include <string>
#include <filesystem>
#include <QObject>
#include "ucicommon.h"
using namespace std;

class Engine: public QObject
{
    Q_OBJECT

private:
    QString m_enginePath;

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

signals:
    void onAnalysisUpdate();
};
