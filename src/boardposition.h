#include "ucicommon.h"
#include <QString>

struct BoardPosition
{
    std::vector<std::string> redPieces = {" ", "K", "A", "B", "N", "R", "P", "C"};
    std::vector<std::string> blackPieces = {" ", "k", "a", "b", "n", "r", "p", "c"};

    std::vector<std::string> redPiecesChs = {" ", "帅", "仕", "相", "马", "车", "兵", "炮"};
    std::vector<std::string> blackPiecesChs = {" ", "将", "士", "象", "马", "车", "卒", "炮"};

    std::vector<std::string> redIntegerName = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};
    std::vector<std::string> blackIntegerName = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

    Piece pieces[XIANGQI_BOARD_ROWS][XIANGQI_BOARD_COLUMNS];
    Side movingSide;

    static BoardPosition FromFen(const QString& fen);
    static QString ToFen(const BoardPosition& position);

    bool SetFen(const QString& fen);

    Side GetMovingSide() const { return movingSide; }
    std::string DumpBoard() const;
    std::vector<std::string> RenderMoveList(const MoveList& moveList);
    std::string RenderMove(const Move& move) const;
    void CommitMove(const Move& move);
};
