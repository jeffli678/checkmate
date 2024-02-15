#pragma once

#include <cstdio>
#include <cinttypes>

constexpr size_t XIANGQI_BOARD_ROWS = 10;
constexpr size_t XIANGQI_BOARD_COLUMNS = 9;

enum Side
{
    Invalid,
    Red,
    Black
};


enum PieceType
{
    InvalidPiece,
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
    Piece(): type(InvalidPiece), side(Invalid) {}
    Piece(PieceType t, Side s): type(t), side(s) {}
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
