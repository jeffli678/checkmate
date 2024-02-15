#include "ucicommon.h"
#include <QString>

struct BoardPosition
{
    Piece pieces[XIANGQI_BOARD_ROWS][XIANGQI_BOARD_COLUMNS];
    Side movingSide;

//    QList<PiecePosition> pieces;
//    Side movingSide;

    static BoardPosition FromFen(const QString& fen);
    static QString ToFen(const BoardPosition& position);

    void SetFen(const QString& fen);

    Side getMovingSide() const { return movingSide; }
};
