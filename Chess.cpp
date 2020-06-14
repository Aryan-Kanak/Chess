// This code was written by Aryan Kanak

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// square structure
struct Square
{
    int rank;
    int file;
};

// forward declaration
class Piece;
bool validSquare(int rank, int file, bool pieceColour, Piece* board[8][8]);
bool isCheck(Piece* oppSide, Square square, Piece* board[8][8]);

// piece class
class Piece
{
private:
public:
    Square position;
    string pieceType;
    bool colour; // true is white and false is black
    vector <Square> moves;
    bool captured;
    bool castle;
    bool en_passant;
    Piece(string pieceName, bool pieceColour, Square currPosition, Piece* (&board)[8][8])
    {
        pieceType = pieceName;
        colour = pieceColour;
        position = currPosition;
        board[currPosition.rank][currPosition.file] = this;
        captured = false;
        if (pieceType == "king" || pieceType == "rook")
        {
            castle = true;
        }
        else
        {
            castle = false;
        }
        en_passant = false;
    }
    // find all possible moves
    void findMoves(Piece* board[8][8], Piece* oppSide = NULL)
    {
        moves.clear();
        if (!captured)
        {
            // knight
            if (pieceType == "knight")
            {
                if (validSquare(position.rank + 2, position.file - 1, colour, board))
                {
                    moves.push_back({ position.rank + 2, position.file - 1 });
                }
                if (validSquare(position.rank + 2, position.file + 1, colour, board))
                {
                    moves.push_back({ position.rank + 2, position.file + 1 });
                }
                if (validSquare(position.rank + 1, position.file - 2, colour, board))
                {
                    moves.push_back({ position.rank + 1, position.file - 2 });
                }
                if (validSquare(position.rank + 1, position.file + 2, colour, board))
                {
                    moves.push_back({ position.rank + 1, position.file + 2 });
                }
                if (validSquare(position.rank - 2, position.file - 1, colour, board))
                {
                    moves.push_back({ position.rank - 2, position.file - 1 });
                }
                if (validSquare(position.rank - 2, position.file + 1, colour, board))
                {
                    moves.push_back({ position.rank - 2, position.file + 1 });
                }
                if (validSquare(position.rank - 1, position.file - 2, colour, board))
                {
                    moves.push_back({ position.rank - 1, position.file - 2 });
                }
                if (validSquare(position.rank - 1, position.file + 2, colour, board))
                {
                    moves.push_back({ position.rank - 1, position.file + 2 });
                }
            }
            // king
            else if (pieceType == "king")
            {
                if (validSquare(position.rank + 1, position.file, colour, board))
                {
                    moves.push_back({ position.rank + 1, position.file });
                }
                if (validSquare(position.rank + 1, position.file + 1, colour, board))
                {
                    moves.push_back({ position.rank + 1, position.file + 1 });
                }
                if (validSquare(position.rank, position.file + 1, colour, board))
                {
                    moves.push_back({ position.rank, position.file + 1 });
                }
                if (validSquare(position.rank - 1, position.file + 1, colour, board))
                {
                    moves.push_back({ position.rank - 1, position.file + 1 });
                }
                if (validSquare(position.rank - 1, position.file, colour, board))
                {
                    moves.push_back({ position.rank - 1, position.file });
                }
                if (validSquare(position.rank - 1, position.file - 1, colour, board))
                {
                    moves.push_back({ position.rank - 1, position.file - 1 });
                }
                if (validSquare(position.rank, position.file - 1, colour, board))
                {
                    moves.push_back({ position.rank, position.file - 1 });
                }
                if (validSquare(position.rank + 1, position.file - 1, colour, board))
                {
                    moves.push_back({ position.rank + 1, position.file - 1 });
                }
                // castling
                if (castle == true)
                {
                    if (!isCheck(oppSide, position, board))
                    {
                        // kingside castling
                        if (board[position.rank][position.file + 1] == NULL && board[position.rank][position.file + 2] == NULL && board[position.rank][position.file + 3] != NULL)
                        {
                            if (board[position.rank][position.file + 3]->pieceType == "rook" && board[position.rank][position.file + 3]->castle == true && !isCheck(oppSide, { position.rank, position.file + 1 }, board) && !isCheck(oppSide, { position.rank, position.file + 2 }, board))
                            {
                                moves.push_back({ position.rank, position.file + 2 });
                            }
                        }
                        // queenside castling
                        if (board[position.rank][position.file - 1] == NULL && board[position.rank][position.file - 2] == NULL && board[position.rank][position.file - 3] == NULL && board[position.rank][position.file - 4] != NULL)
                        {
                            if (board[position.rank][position.file - 4]->pieceType == "rook" && board[position.rank][position.file - 4]->castle == true && !isCheck(oppSide, { position.rank, position.file - 1 }, board) && !isCheck(oppSide, { position.rank, position.file - 2 }, board))
                            {
                                moves.push_back({ position.rank, position.file - 2 });
                            }
                        }
                    }
                }
            }
            // queen
            else if (pieceType == "queen")
            {
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file });
                        if (board[position.rank + i][position.file] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file + i });
                        if (board[position.rank + i][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank, position.file + i });
                        if (board[position.rank][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file + i });
                        if (board[position.rank - i][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file });
                        if (board[position.rank - i][position.file] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file - i });
                        if (board[position.rank - i][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank, position.file - i });
                        if (board[position.rank][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file - i });
                        if (board[position.rank + i][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // rook
            else if (pieceType == "rook")
            {
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file });
                        if (board[position.rank + i][position.file] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank, position.file + i });
                        if (board[position.rank][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file });
                        if (board[position.rank - i][position.file] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank, position.file - i });
                        if (board[position.rank][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // bishop
            else if (pieceType == "bishop")
            {
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file + i });
                        if (board[position.rank + i][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file + i, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file + i });
                        if (board[position.rank - i][position.file + i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank - i, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank - i, position.file - i });
                        if (board[position.rank - i][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                for (int i = 1; ; i++)
                {
                    if (validSquare(position.rank + i, position.file - i, colour, board))
                    {
                        moves.push_back({ position.rank + i, position.file - i });
                        if (board[position.rank + i][position.file - i] != NULL)
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // pawn
            else if (pieceType == "pawn")
            {
                // white pawn
                if (colour == true)
                {
                    // move up one square
                    if (validSquare(position.rank + 1, position.file, colour, board) && board[position.rank + 1][position.file] == NULL)
                    {
                        moves.push_back({ position.rank + 1, position.file });
                        // move up two squares
                        if (validSquare(3, position.file, colour, board) && board[3][position.file] == NULL && position.rank == 1)
                        {
                            moves.push_back({ 3, position.file });
                        }
                    }
                    // capturing a piece
                    if (validSquare(position.rank + 1, position.file - 1, colour, board) && board[position.rank + 1][position.file - 1] != NULL)
                    {
                        moves.push_back({ position.rank + 1, position.file - 1 });
                    }
                    if (validSquare(position.rank + 1, position.file + 1, colour, board) && board[position.rank + 1][position.file + 1] != NULL)
                    {
                        moves.push_back({ position.rank + 1, position.file + 1 });
                    }
                    // en passant
                    if (validSquare(position.rank, position.file - 1, colour, board) && board[position.rank][position.file - 1] != NULL)
                    {
                        if (board[position.rank][position.file - 1]->en_passant == true)
                        {
                            moves.push_back({ position.rank + 1, position.file - 1 });
                        }
                    }
                    if (validSquare(position.rank, position.file + 1, colour, board) && board[position.rank][position.file + 1] != NULL)
                    {
                        if (board[position.rank][position.file + 1]->en_passant == true)
                        {
                            moves.push_back({ position.rank + 1, position.file + 1 });
                        }
                    }
                }
                // black pawn
                if (colour == false)
                {
                    // move up one square
                    if (validSquare(position.rank - 1, position.file, colour, board) && board[position.rank - 1][position.file] == NULL)
                    {
                        moves.push_back({ position.rank - 1, position.file });
                        // move up two squares
                        if (validSquare(4, position.file, colour, board) && board[4][position.file] == NULL && position.rank == 6)
                        {
                            moves.push_back({ 4, position.file });
                        }
                    }
                    // capturing a piece
                    if (validSquare(position.rank - 1, position.file - 1, colour, board) && board[position.rank - 1][position.file - 1] != NULL)
                    {
                        moves.push_back({ position.rank - 1, position.file - 1 });
                    }
                    if (validSquare(position.rank - 1, position.file + 1, colour, board) && board[position.rank - 1][position.file + 1] != NULL)
                    {
                        moves.push_back({ position.rank - 1, position.file + 1 });
                    }
                    // en passant
                    if (validSquare(position.rank, position.file - 1, colour, board) && board[position.rank][position.file - 1] != NULL)
                    {
                        if (board[position.rank][position.file - 1]->en_passant == true)
                        {
                            moves.push_back({ position.rank - 1, position.file - 1 });
                        }
                    }
                    if (validSquare(position.rank, position.file + 1, colour, board) && board[position.rank][position.file + 1] != NULL)
                    {
                        if (board[position.rank][position.file + 1]->en_passant == true)
                        {
                            moves.push_back({ position.rank - 1, position.file + 1 });
                        }
                    }
                }
            }
        }
    }
    // move piece
    bool move(Piece* (&board)[8][8], int newRank, int newFile, bool override)
    {
        if (override)
        {
            if (board[newRank][newFile] != NULL)
            {
                board[newRank][newFile]->captured = true;
            }
            board[position.rank][position.file] = NULL;
            board[newRank][newFile] = NULL;
            position = { newRank, newFile };
            board[newRank][newFile] = this;
            findMoves(board);
            return true;
        }
        else if (!override)
        {
            for (int i = 0; i < moves.size(); i++)
            {
                if (moves[i].rank == newRank && moves[i].file == newFile)
                {
                    if (board[newRank][newFile] != NULL)
                    {
                        board[newRank][newFile]->captured = true;
                    }
                    // castling
                    if (castle == true)
                    {
                        // kingside
                        if (pieceType == "king" && newFile == position.file + 2)
                        {
                            board[position.rank][position.file + 3]->move(board, position.rank, position.file + 1, false);
                        }
                        // queenside
                        if (pieceType == "king" && newFile == position.file - 2)
                        {
                            board[position.rank][position.file - 4]->move(board, position.rank, position.file - 1, false);
                        }
                        castle = false;
                    }
                    // en passant
                    if (pieceType == "pawn")
                    {
                        if (newRank - position.rank == 2 || newRank - position.rank == -2)
                        {
                            en_passant = true;
                        }
                        if (colour == true)
                        {
                            if (board[newRank - 1][newFile] != NULL)
                            {
                                if (board[newRank - 1][newFile]->en_passant == true)
                                {
                                    cout << "WHITE HAS KILLED WITH EP" << endl;
                                    board[newRank - 1][newFile]->captured = true;
                                    board[newRank - 1][newFile]->en_passant = false;
                                    board[newRank - 1][newFile] = NULL;
                                }
                            }
                        }
                        else if (colour == false)
                        {
                            if (board[newRank + 1][newFile] != NULL)
                            {
                                if (board[newRank + 1][newFile]->en_passant == true)
                                {
                                    cout << "BLACK HAS KILLED WITH EP" << endl;
                                    board[newRank + 1][newFile]->captured = true;
                                    board[newRank + 1][newFile]->en_passant = false;
                                    board[newRank + 1][newFile] = NULL;
                                }
                            }
                        }
                    }
                    board[position.rank][position.file] = NULL;
                    position = { newRank, newFile };
                    board[position.rank][position.file] = this;
                    findMoves(board);
                    return true;
                }
            }
        }
        return false;
    }
};

// show board
void showBoard(Piece* board[8][8])
{
    for (int i = 7; i >= 0; i--)
    {
        cout << "-----------------" << endl;
        for (int j = 0; j < 8; j++)
        {
            cout << "|";
            if (board[i][j] == NULL)
            {
                cout << " ";
            }
            else if (board[i][j]->pieceType == "knight")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "N";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "n";
                }
            }
            else if (board[i][j]->pieceType == "king")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "K";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "k";
                }
            }
            else if (board[i][j]->pieceType == "queen")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "Q";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "q";
                }
            }
            else if (board[i][j]->pieceType == "rook")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "R";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "r";
                }
            }
            else if (board[i][j]->pieceType == "bishop")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "B";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "b";
                }
            }
            else if (board[i][j]->pieceType == "pawn")
            {
                if (board[i][j]->colour == true)
                {
                    cout << "P";
                }
                else if (board[i][j]->colour == false)
                {
                    cout << "p";
                }
            }
        }
        cout << "|" << endl;
    }
    cout << "-----------------" << endl;
}

// checks whether a square is on the board
bool validSquare(int rank, int file, bool pieceColour, Piece* board[8][8])
{
    // check whether square is within bounds of board
    bool bounds;
    if (rank >= 0 && rank <= 7 && file >= 0 && file <= 7)
    {
        bounds = true;
    }
    else
    {
        bounds = false;
    }
    // check whether a piece lies on the square
    if (bounds == true)
    {
        if (board[rank][file] != NULL && board[rank][file]->colour == pieceColour)
        {
            return false;
        }
    }
    return bounds;
}

// checks whether or not king is in check
bool isCheck(Piece* oppSide, Square square, Piece* board[8][8])
{
    if (oppSide == NULL)
    {
        return true;
    }
    for (int i = 0; i < 16; i++)
    {
        oppSide[i].findMoves(board);
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < oppSide[i].moves.size(); j++)
        {
            if (oppSide[i].moves[j].file == square.file && oppSide[i].moves[j].rank == square.rank)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    string move;
    string currPiece;
    bool turn = true;
    bool checkmate;
    Square currPos;
    Square newPos;
    string promotion;
    Piece* tempPiece = NULL;
    int moveCount = 0;

    // create board
    Piece* board[8][8];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = NULL;
        }
    }

    // create white pieces
    Piece white[16] =
    {
      Piece("king", true, {0, 4}, board),
      Piece("rook", true, {0, 0}, board),
      Piece("knight", true, {0, 1}, board),
      Piece("bishop", true, {0, 2}, board),
      Piece("queen", true, {0, 3}, board),
      Piece("bishop", true, {0, 5}, board),
      Piece("knight", true, {0, 6}, board),
      Piece("rook", true, {0, 7}, board),
      Piece("pawn", true, {1, 0}, board),
      Piece("pawn", true, {1, 1}, board),
      Piece("pawn", true, {1, 2}, board),
      Piece("pawn", true, {1, 3}, board),
      Piece("pawn", true, {1, 4}, board),
      Piece("pawn", true, {1, 5}, board),
      Piece("pawn", true, {1, 6}, board),
      Piece("pawn", true, {1, 7}, board)
    };

    // create black pieces
    Piece black[16] =
    {
      Piece("king", false, {7, 4}, board),
      Piece("rook", false, {7, 0}, board),
      Piece("knight", false, {7, 1}, board),
      Piece("bishop", false, {7, 2}, board),
      Piece("queen", false, {7, 3}, board),
      Piece("bishop", false, {7, 5}, board),
      Piece("knight", false, {7, 6}, board),
      Piece("rook", false, {7, 7}, board),
      Piece("pawn", false, {6, 0}, board),
      Piece("pawn", false, {6, 1}, board),
      Piece("pawn", false, {6, 2}, board),
      Piece("pawn", false, {6, 3}, board),
      Piece("pawn", false, {6, 4}, board),
      Piece("pawn", false, {6, 5}, board),
      Piece("pawn", false, {6, 6}, board),
      Piece("pawn", false, {6, 7}, board)
    };

    // main program loop
    while (true)
    {
        // show board
        showBoard(board);
        // output whose turn it is
        if (turn == true)
        {
            cout << "WHITE'S TURN TO MOVE" << endl;
        }
        else if (turn == false)
        {
            cout << "BLACK'S TURN TO MOVE" << endl;
        }
        while (true)
        {
            while (true)
            {
                // determine possible moves for every piece on side
                if (turn == true)
                {
                    if (white[0].castle == true)
                    {
                        white[0].findMoves(board, black);
                    }
                    else
                    {
                        white[0].findMoves(board);
                    }
                    for (int i = 1; i < 16; i++)
                    {
                        white[i].findMoves(board);
                    }
                }
                else if (turn == false)
                {
                    if (black[0].castle == true)
                    {
                        black[0].findMoves(board, white);
                    }
                    else
                    {
                        black[0].findMoves(board);
                    }
                    for (int i = 1; i < 16; i++)
                    {
                        black[i].findMoves(board);
                    }
                }
                // get square of piece that needs to be moved
                cout << "Enter square of piece that you would like to move: ";
                cin >> currPiece;
                // ensure correct input
                if (currPiece.length() != 2 || currPiece[0] < 'a' || currPiece[0] > 'h' || currPiece[1] < '1' || currPiece[1] > '8')
                {
                    cout << "INVALID PIECE" << endl;
                }
                // ensure a valid piece that can move has been selected
                else if (board[currPiece[1] - 49][currPiece[0] - 97] == NULL || board[currPiece[1] - 49][currPiece[0] - 97]->colour != turn || board[currPiece[1] - 49][currPiece[0] - 97]->moves.empty())
                {
                    cout << "INVALID PIECE" << endl;
                }
                else
                {
                    break;
                }
            }
            // move piece
            cout << "Enter move: ";
            cin >> move;
            // save piece already on destination square
            if (validSquare(move[1] - 49, move[0] - 97, true, board) || validSquare(move[1] - 49, move[0] - 97, false, board))
            {
                tempPiece = board[move[1] - 49][move[0] - 97];
            }
            // ensure correct input
            if (move.length() != 2 || move[0] < 'a' || move[0] > 'h' || move[1] < '1' || move[1] > '8')
            {
                cout << "INVALID MOVE" << endl;
            }
            // ensure that piece can legally move to that square
            else if (!board[currPiece[1] - 49][currPiece[0] - 97]->move(board, move[1] - 49, move[0] - 97, false))
            {
                cout << "INVALID MOVE" << endl;
            }
            // ensure king is not in check
            else if ((turn == true && isCheck(black, white[0].position, board)) || (turn == false && isCheck(white, black[0].position, board)))
            {
                cout << "INVALID MOVE IN CHECK" << endl;
                board[move[1] - 49][move[0] - 97]->move(board, currPiece[1] - 49, currPiece[0] - 97, true);
                board[move[1] - 49][move[0] - 97] = tempPiece;
                if (tempPiece != NULL)
                {
                    board[move[1] - 49][move[0] - 97]->captured = false;
                }
                board[currPiece[1] - 49][currPiece[0] - 97]->en_passant = false;
            }
            else
            {
                break;
            }
        }
        // pawn promotion
        if (board[move[1] - 49][move[0] - 97]->pieceType == "pawn")
        {
            if (turn == true && move[1] - 49 == 7)
            {
                while (true)
                {
                    cout << "Enter the piece that you would like to promote this pawn to: ";
                    cin >> promotion;
                    if (promotion == "queen" || promotion == "rook" || promotion == "knight" || promotion == "bishop")
                    {
                        board[move[1] - 49][move[0] - 97]->pieceType = promotion;
                        break;
                    }
                }
            }
            else if (turn == false && move[1] - 49 == 0)
            {
                while (true)
                {
                    cout << "Enter the piece that you would like to promote this pawn to: ";
                    cin >> promotion;
                    if (promotion == "queen" || promotion == "rook" || promotion == "knight" || promotion == "bishop")
                    {
                        board[move[1] - 49][move[0] - 97]->pieceType = promotion;
                        break;
                    }
                }
            }
        }
        // fifty move rule
        if (board[move[1] - 49][move[0] - 97]->pieceType == "pawn" || tempPiece != NULL)
        {
            moveCount = 0;
        }
        else if (turn == false)
        {
            moveCount++;
        }
        if (moveCount >= 50)
        {
            showBoard(board);
            cout << "DRAW" << endl;
            break;
        }
        turn = !turn;
        // clear en_passant
        if (turn == true)
        {
            for (int i = 8; i < 16; i++)
            {
                white[i].en_passant = false;
            }
        }
        else if (turn == false)
        {
            for (int i = 8; i < 16; i++)
            {
                black[i].en_passant = false;
            }
        }
        // check for mate
        checkmate = true;
        // white's turn to move
        if (turn == true)
        {
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < white[i].moves.size(); j++)
                {
                    // move piece
                    currPos = white[i].position;
                    newPos = white[i].moves[j];
                    if (validSquare(newPos.rank, newPos.file, true, board))
                    {
                        tempPiece = board[newPos.rank][newPos.file];
                    }
                    white[i].move(board, newPos.rank, newPos.file, true);
                    // if still in check
                    if (isCheck(black, white[0].position, board))
                    {
                        // move piece back
                        white[i].move(board, currPos.rank, currPos.file, true);
                        board[newPos.rank][newPos.file] = tempPiece;
                        if (tempPiece != NULL)
                        {
                            board[newPos.rank][newPos.file]->captured = false;
                        }
                    }
                    else
                    {
                        // move piece back
                        white[i].move(board, currPos.rank, currPos.file, true);
                        board[newPos.rank][newPos.file] = tempPiece;
                        if (tempPiece != NULL)
                        {
                            board[newPos.rank][newPos.file]->captured = false;
                        }
                        // set checkmate to false and break
                        checkmate = false;
                        break;
                    }
                }
                if (!checkmate)
                {
                    break;
                }
            }
        }
        // black's turn to move
        else if (turn == false)
        {
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < black[i].moves.size(); j++)
                {
                    // move piece
                    currPos = black[i].position;
                    newPos = black[i].moves[j];
                    if (validSquare(newPos.rank, newPos.file, false, board))
                    {
                        tempPiece = board[newPos.rank][newPos.file];
                    }
                    black[i].move(board, newPos.rank, newPos.file, true);
                    // if still in check
                    if (isCheck(white, black[0].position, board))
                    {
                        // move piece back
                        black[i].move(board, currPos.rank, currPos.file, true);
                        board[newPos.rank][newPos.file] = tempPiece;
                        if (tempPiece != NULL)
                        {
                            board[newPos.rank][newPos.file]->captured = false;
                        }
                    }
                    else
                    {
                        // move piece back
                        black[i].move(board, currPos.rank, currPos.file, true);
                        board[newPos.rank][newPos.file] = tempPiece;
                        if (tempPiece != NULL)
                        {
                            board[newPos.rank][newPos.file]->captured = false;
                        }
                        // set checkmate to false and break
                        checkmate = false;
                        break;
                    }
                }
                if (!checkmate)
                {
                    break;
                }
            }
        }
        // end the game
        if (checkmate)
        {
            showBoard(board);
            // checkmate
            if (turn == true && isCheck(black, white[0].position, board))
            {
                cout << "BLACK WINS" << endl;
            }
            else if (turn == false && isCheck(white, black[0].position, board))
            {
                cout << "WHITE WINS" << endl;
            }
            // stalemate
            else
            {
                cout << "STALEMATE" << endl;
            }
            break;
        }
    }
}