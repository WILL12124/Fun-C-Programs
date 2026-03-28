//
// Author: William Li
//

#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 26
bool isWin = 0;

void setBoard(char board[][N], int n, char player, int row, int col);
void boardInit(char board[][N], int n);
void printBoard(char board[][N], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol);
char *availableMove(char board[][N], int n, char player);
bool isValid(char board[][N], int n, int row, int col, char player);
void placeDot(char board[][N], int n, int row, int col, char player);
void killTheGame(char board[][N], int n, char botPlay);

int main(void)
{
    int n = 0;
    do
    {
        printf("Enter the board dimension: ");
        scanf(" %3d", &n);
    } while (n > 26 || n < 2);

    char board[N][N]; // 注意！！！macro在这一行之后才能看到
    boardInit(board, n);
    printBoard(board, n);

    char botPlay = '\0', userPlay = '\0';
    printf("Computer plays (B/W): ");
    do
    {
        scanf(" %c", botPlay);
    } while (botPlay != 'B' || botPlay != 'W');

    if (botPlay == 'B')
    {
        printBoard(board, n);
        killTheGame(board, n, botPlay);
    }

    userPlay = (botPlay == 'B') ? 'W' : 'B';
    char userRow, userCol;
    while (!isWin)
    {
        printBoard(board, n);
        printf("Enter move for colour %c (RowCol): ", userPlay);
        scanf(" %c%c", &userRow, &userCol);
        if (isValid(board, n, userRow - 'a', userCol - 'a', userPlay))
        {
            placeDot(board, n, userRow, userCol, userPlay);
        }
        else
        {
            printf("Invalid move.\n%c player wins.\n", botPlay);
            return 0;
        }
        killTheGame(board, n, botPlay);
    }

    return 0;
}

/*functions




*/
void setBoard(char board[][N], int n, char player, int row, int col) // 这里的vla是指描述，不分配内存
{
    board[row][col] = player;
}

bool positionInBounds(int n, int row, int col)
{
    return (row >= 0 && row < n && col >= 0 && col < n);
}

bool checkLegalInDirection(char board[][N], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    char other = (colour == 'W') ? 'B' : 'W';
    bool foundOther = false;
    for (int num = 1; num < n; num++)
    {
        int nr = row + num * deltaRow;
        int nc = col + num * deltaCol;

        // don't go out of bound
        if (!positionInBounds(n, nr, nc))
        {
            break;
        }
        if (board[nr][nc] == other)
        {
            foundOther = true;
        }
        else if (board[nr][nc] == colour) ////CORE!!! next depend on prevoius
        {
            if (foundOther)
            {
                return true;
            }
            break;
        }
        else
        {
            break; // empty
        }
    }
    return false;
}

void boardInit(char board[][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 'U';
        }
    }
    int mid = n / 2;
    board[mid - 1][mid - 1] = 'W';
    board[mid - 1][mid] = 'B';
    board[mid][mid - 1] = 'B';
    board[mid][mid] = 'W';

    printBoard(board, n);

    // setBoard
    char player, tempRow, tempCol;
    printf("Enter board configuration:\n");
    for (int i = 0; i < n * n; i++) // 如果觉得需要记array信息的，不妨直接输入一次做一次
    {
        scanf(" %c%c%c", &player, &tempRow, &tempCol);
        if (player == '!')
        {
            return; // void 用return就可以了
        }
        if (player != 'B' && player != 'W')
        {
            printf("Invalid\n");
            continue;
        }
        if (!positionInBounds(n, tempRow - 'a', tempCol - 'a'))
        {
            printf("Invalid\n");
            continue;
        }

        setBoard(board, n, player, tempRow - 'a', tempCol - 'a');
    }
}

void printBoard(char board[][N], int n)
{
    // print board legend
    printf("  ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a' + i); // use char 'a' + i (ASCII code), not arrays
    }
    printf("\n");

    // print inner board
    for (int i = 0; i < n; i++)
    {
        printf("%c ", 'a' + i);
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

char *availableMove(char board[][N], int n, char player)
{
    char *p = calloc(2 * n * n, sizeof(char));
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isValid(board, n, i, j, player))
            {
                p[num] = 'a' + i;
                p[num + 1] = 'a' + j;
                num += 2;
            }
        }
    }
    p[num] = '\0';
    return p;
}

bool isValid(char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1}; // star from 0 rad, counterclockwise
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    if (board[row][col] != 'U')
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        if (checkLegalInDirection(board, n, row, col, player, deltaRows[i], deltaCols[i]))
        {
            return true;
        }
    }
    return false;
}

void placeDot(char board[][N], int n, int row, int col, char player)
{
    int deltaRows[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int deltaCols[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char other = (player == 'W') ? 'B' : 'W';
    board[row][col] = player; // forgot to place piece

    for (int i = 0; i < 8; i++) // direction first!
    {
        if (checkLegalInDirection(board, n, row, col, player, deltaRows[i], deltaCols[i]))
        {
            // 遇到对手棋子, flip them
            for (int num = 1; num < n; num++)
            {
                int nr = row + num * deltaRows[i];
                int nc = col + num * deltaCols[i];
                if (!positionInBounds(n, nr, nc))
                    break;
                if (board[nr][nc] == other)
                {
                    board[nr][nc] = player; // 要确认有效才能反转
                }
                else
                {
                    break; // hit own piece or empty, stop
                }
            }
        }
    }
}

void killTheGame(char board[][n], int n, char botPlay)
{
    //
    printf("Computer places %c at bc.\n", botPlay);
}