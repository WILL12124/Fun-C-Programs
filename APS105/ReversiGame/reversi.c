//
// Author: William Li
//

#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 26

void setBoard(char board[][N], int n, char player, int row, int col);
void boardInit(char board[][N], int n);
void printBoard(char board[][N], int n);
char *availableMove(char board[][N], int n, char player);
bool isValid(char board[][N], int n, int row, int col, char player);
void placeDot(char board[][N], int n, int row, int col, char player);

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

    // find available move
    printf("Available moves for W:\n");
    char player = 'W';
    char *pW = availableMove(board, n, player);

    // print available move
    for (int i = 0; pW[i] != '\0'; i += 2)
    {
        printf("%c%c", pW[i], pW[i + 1]);
        printf("\n");
    }
    printf("Available moves for B:\n");
    player = 'B';
    char *pB = availableMove(board, n, player);
    for (int i = 0; pB[i] != '\0'; i += 2)
    {
        printf("%c%c", pB[i], pB[i + 1]);
        printf("\n");
    }

    char row, col;
    printf("Enter a move:\n");
    scanf(" %c%c%c", &player, &row, &col); // scanf前面加空格

    bool found = false;
    if (player == 'W')
    {
        for (int i = 0; pW[i] != '\0'; i += 2)
        {
            if (pW[i] == row && pW[i + 1] == col)
            {
                found = true;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; pB[i] != '\0'; i += 2)
        {
            if (pB[i] == row && pB[i + 1] == col)
            {
                found = true;
                break;
            }
        }
    }

    if (found)
    {
        printf("Valid move.\n");
        placeDot(board, n, row - 'a', col - 'a', player);
    }
    else
    {
        printf("Invalid move.\n");
    }

    printBoard(board, n);
    free(pW); // don't be memory leak
    free(pB);
    return 0;
}

/*functions




*/
void setBoard(char board[][N], int n, char player, int row, int col) // 这里的vla是指描述，不分配内存
{
    board[row][col] = player;
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
        if (tempCol - 'a' >= n || tempRow - 'a' >= n)
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
    int ver[] = {0, 1, 1, 1, 0, -1, -1, -1}; // star from 0 rad, counterclockwise
    int hor[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char other = (player == 'W') ? 'B' : 'W';
    if (board[row][col] != 'U')
    {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        bool foundOther = false;
        for (int num = 1; num < n; num++)
        {
            int nr = row + num * ver[i]; /////WRONG, i*ver
            int nc = col + num * hor[i]; // hor ver 不要反了

            // don't go out of bound
            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
            {
                break;
            }
            if (board[nr][nc] == other)
            {
                foundOther = true;
            }
            else if (board[nr][nc] == player) ////CORE!!! next depend on prevoius
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
    }
    return false;
}

void placeDot(char board[][N], int n, int row, int col, char player)
{
    int ver[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int hor[] = {1, 1, 0, -1, -1, -1, 0, 1};
    char other = (player == 'W') ? 'B' : 'W';
    board[row][col] = player; // forgot to place piece

    for (int i = 0; i < 8; i++) // direction first!
    {
        int count = 0;
        bool valid = false;               // 是否形成有效夹击
        for (int num = 1; num < n; num++) // r after
        {
            int nr = row + num * ver[i];
            int nc = col + num * hor[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                break;
            if (board[nr][nc] == other)
            {
                count++; // 遇到对手棋子, 计数!!! 能知道要循环几次
            }
            else if (board[nr][nc] == player)
            {
                valid = true; // 遇到自己棋子， 夹击成立
                break;
            }
            else
            {
                break; // empty
            }
        }
        if (valid)
        { // 要确认有效才能反转
            for (int j = 1; j <= count; j++)
            {
                board[row + j * ver[i]][col + j * hor[i]] = player;
            }
        }
    }
}