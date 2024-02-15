#include "boardposition.h"
#include <QList>

bool BoardPosition::SetFen(const QString &fen)
{
// example: rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w
    QString board;
    auto index = fen.indexOf(' ');
    if (index != -1)
        board = fen.first(index);
    else
        board = fen;

    auto splits = board.split('/');
    if (splits.size() != XIANGQI_BOARD_ROWS)
        return false;

    for (auto i = 0; i < splits.size(); i++)
    {
        QString row = splits[i];
        size_t idx = 0;
        while ((idx < XIANGQI_BOARD_COLUMNS) && !row.isEmpty())
        {
            auto c = row[0].toLatin1();
            switch (c)
            {
            case ' ':
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                size_t n = c - '0';
                for (auto j = 0; j < n; j++)
                {
                    pieces[i][idx + j].side = Invalid;
                    pieces[i][idx + j].type = Empty;
                }
                idx += n;
                break;
            }
            case 'r':
            {
                pieces[i][idx].type = Rook;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'R':
            {
                pieces[i][idx].type = Rook;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'n':
            {
                pieces[i][idx].type = Knight;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'N':
            {
                pieces[i][idx].type = Knight;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'b':
            {
                pieces[i][idx].type = Bishop;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'B':
            {
                pieces[i][idx].type = Bishop;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'a':
            {
                pieces[i][idx].type = Advisor;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'A':
            {
                pieces[i][idx].type = Advisor;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'k':
            {
                pieces[i][idx].type = King;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'K':
            {
                pieces[i][idx].type = King;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'c':
            {
                pieces[i][idx].type = Canon;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'C':
            {
                pieces[i][idx].type = Canon;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            case 'p':
            {
                pieces[i][idx].type = Pawn;
                pieces[i][idx].side = Black;
                idx++;
                break;
            }
            case 'P':
            {
                pieces[i][idx].type = Pawn;
                pieces[i][idx].side = Red;
                idx++;
                break;
            }
            default:
                return false;
            }
            row = row.remove(0, 1);
        }

        if ((idx != XIANGQI_BOARD_COLUMNS) || (!row.isEmpty()))
            return false;
    }
    return true;
}


std::string BoardPosition::DumpBoard() const
{
    std::string result;
    for (auto i = 0; i < XIANGQI_BOARD_ROWS; i++)
    {
        for (auto j = 0; j < XIANGQI_BOARD_COLUMNS; j++)
        {
            auto piece = pieces[i][j];
            if (piece.side == Red)
            {
                result += redPieces[piece.type];
            }
            else if (piece.side == Black)
            {
                result += blackPieces[piece.type];
            }
            else
            {
                result += '_';
            }
        }
        result += '\n';
    }
    return result;
}


std::vector<std::string> BoardPosition::RenderMoveList(const MoveList &moveList) const
{
    std::vector<std::string> result;
    result.reserve(moveList.moves.size());
    for (const auto& move: moveList.moves)
    {
        result.push_back(RenderMove(move));
    }
    return result;
}


std::string BoardPosition::RenderMove(const Move &move) const
{
    std::string result;

    auto start = move.start;
    auto end = move.end;

    auto piece = pieces[start.row][start.column];
    if (piece.side == Red)
    {
        result += redPiecesChs[piece.type];
    }
    else if (piece.side == Black)
    {
        result += blackPiecesChs[piece.type];
    }
    else
    {
        result += '?';
    }

    if (piece.side == Red)
    {
        result += redIntegerName[XIANGQI_BOARD_COLUMNS - 1 - start.column];
    }
    else if (piece.side == Black)
    {
        result += blackIntegerName[start.column];
    }
    else
    {
        result += std::to_string(start.column);
    }

    if (start.row == end.row)
    {
        result += "平";
    }
    else if (piece.side == Red)
    {
        result += ((start.row < end.row) ? "退" : "进");
    }
    else if (piece.side == Black)
    {
        result += ((start.row > end.row) ? "退" : "进");
    }
    else
    {
        result += "?";
    }

    if (start.row == end.row)
    {
        if (piece.side == Red)
        {
            result += redIntegerName[XIANGQI_BOARD_COLUMNS - 1 - end.column];
        }
        else if (piece.side == Black)
        {
            result += blackIntegerName[end.column];
        }
        else
        {
            result += "?";
        }
    }
    else
    {
        if (start.column == end.column)
        {
            auto diff = std::abs(start.row - end.row);
            if (piece.side == Red)
            {
                result += redIntegerName[diff - 1];
            }
            else if (piece.side == Black)
            {
                result += blackIntegerName[diff - 1];
            }
            else
            {
                result += "?";
            }
        }
        else
        {
            if (piece.side == Red)
            {
                result += redIntegerName[XIANGQI_BOARD_COLUMNS - 1 - end.column];
            }
            else if (piece.side == Black)
            {
                result += blackIntegerName[end.column];
            }
            else
            {
                result += "?";
            }
        }
    }

    return result;
}
