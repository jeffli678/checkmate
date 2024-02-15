#pragma once

#include <cstdio>
#include <cinttypes>
#include <vector>
#include <string>

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
    Empty,
    King,
    Advisor,
    Bishop,
    Knight,
    Rook,
    Pawn,
    Canon,
};


struct Piece
{
    PieceType type;
    Side side;
    Piece(): type(Empty), side(Invalid) {}
    Piece(PieceType t, Side s): type(t), side(s) {}
};


struct PiecePosition
{
    uint8_t row;
    uint8_t column;
};


struct Move
{
    PiecePosition start, end;
};


struct MoveList
{
    std::vector<Move> moves;
};
