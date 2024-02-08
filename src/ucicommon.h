#pragma once

enum Side
{
    RedSide,
    BlackSide
};


enum PieceType
{
    King,
    Advisor,
    Bishop,
    Knight,
    Rook,
    Pawn,
    Canon
};


struct Piece
{
    PieceType type;
    Side side;
};


struct PiecePosition
{
    uint8_t row;
    uint8_t column;
};


struct Move
{
    Piece piece;
    PiecePosition start, end;
};


struct BoardPosition
{
    QList<PiecePosition> pieces;
    Side movingSide;

    static BoardPosition FromFen(const QString& fen);
    static QString ToFen(const BoardPosition& position);

    void SetFen(const QString& fen);

    Side getMovingSide() const;
};
