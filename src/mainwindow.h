#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include "engine.h"
#include "boardposition.h"

#define DEFAULT_FEN "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w"

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QTextEdit *m_fenInput, *m_movesInfo;
    QPushButton *m_analyzeButton, *m_stopButton;

    BoardPosition m_position;

    Engine* m_engine;
    void InitEngine();

    void StartAnalysis();
    void StopAnalysis();
    void onNewPonderInfo(const PonderInfo& info);

public:
    explicit MainWindow();
    ~MainWindow();
};