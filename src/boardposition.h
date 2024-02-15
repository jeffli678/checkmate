#include "ucicommon.h"
#include <QString>

struct BoardPosition
{
    std::vector<std::string> redPieces = {" ", "K", "A", "B", "N", "R", "P", "C"};
    std::vector<std::string> blackPieces = {" ", "k", "a", "b", "n", "r", "p", "c"};

    Piece pieces[XIANGQI_BOARD_ROWS][XIANGQI_BOARD_COLUMNS];
    Side movingSide;

    static BoardPosition FromFen(const QString& fen);
    static QString ToFen(const BoardPosition& position);

    bool SetFen(const QString& fen);

    Side getMovingSide() const { return movingSide; }
    std::string dump() const;
};
