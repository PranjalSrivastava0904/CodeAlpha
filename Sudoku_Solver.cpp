#include <iostream>
using namespace std;

bool isValid(int board[9][9], int row, int col, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] == num)
            return false;
    }

    for (int i = 0; i < 9; i++)
    {
        if (board[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

bool solveSudoku(int board[9][9])
{
    int row = -1;
    int col = -1;
    bool emptyCell = false;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
            {
                row = i;
                col = j;
                emptyCell = true;
                break;
            }
        }

        if (emptyCell)
            break;
    }

    if (!emptyCell)
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isValid(board, row, col, num))
        {
            board[row][col] = num;

            if (solveSudoku(board))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

void displayBoard(int board[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << "-------------------------\n";

        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
                cout << "| ";

            cout << board[i][j] << " ";
        }

        cout << "|\n";
    }

    cout << "-------------------------\n";
}

int main()
{
    int board[9][9];

    cout << "Enter Sudoku puzzle:\n";
    cout << "Use 0 for empty cells.\n\n";

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> board[i][j];
        }
    }

    cout << "\nOriginal Sudoku:\n";
    displayBoard(board);

    if (solveSudoku(board))
    {
        cout << "\nSolved Sudoku:\n";
        displayBoard(board);
    }
    else
    {
        cout << "\nNo solution exists for this Sudoku.\n";
    }

    return 0;
}