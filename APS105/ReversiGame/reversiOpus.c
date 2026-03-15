//
// Author: William Li
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 26

void setBoard(char board[][MAX_N], int n, char player, int row, int col);
void boardInit(char board[][MAX_N], int n);
void printBoard(char board[][MAX_N], int n);
int availableMove(char board[][MAX_N], int n, char player, char moves[]);
bool isValid(char board[][MAX_N], int n, int row, int col, char player);
bool checkDirection(char board[][MAX_N], int n, int row, int col, char player, int dRow, int dCol);
void placeDot(char board[][MAX_N], int n, int row, int col, char player);

int main(void)
{
    int n = 0;
    do
    {
        printf("Enter the board dimension: ");
        scanf("%3d", &n);
    } while (n < 2 || n > 26);

    char board[MAX_N][MAX_N];
    boardInit(board, n);
    printBoard(board, n);

    // Find and print available moves for W
    char movesW[MAX_N * MAX_N * 2 + 1];
    int numW = availableMove(board, n, 'W', movesW);
    printf("Available moves for W:\n");
    for (int i = 0; i < numW; i += 2)
    {
        printf("%c%c\n", movesW[i], movesW[i + 1]);
    }

    // Find and print available moves for B
    char movesB[MAX_N * MAX_N * 2 + 1];
    int numB = availableMove(board, n, 'B', movesB);
    printf("Available moves for B:\n");
    for (int i = 0; i < numB; i += 2)
    {
        printf("%c%c\n", movesB[i], movesB[i + 1]);
    }

    // Ask user for a move
    char player, row, col;
    printf("Enter a move:\n");
    scanf(" %c%c%c", &player, &row, &col);

    // Choose the correct move list
    char *moveList = (player == 'W') ? movesW : movesB;
    int moveCount = (player == 'W') ? numW : numB;

    bool found = false;
    for (int i = 0; i < moveCount; i += 2)
    {
        if (moveList[i] == row && moveList[i + 1] == col)
        {
            found = true;
            break;
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
    return 0;
}

/* ====================== Functions ====================== */

void setBoard(char board[][MAX_N], int n, char player, int row, int col)
{
    board[row][col] = player;
}

void boardInit(char board[][MAX_N], int n)
{
    // Initialize all cells to 'U' (unoccupied)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 'U';
        }
    }

    // Place the initial 4 pieces in the centre
    int mid = n / 2;
    board[mid - 1][mid - 1] = 'W';
    board[mid - 1][mid] = 'B';
    board[mid][mid - 1] = 'B';
    board[mid][mid] = 'W';

    // Read board configuration
    char input[4];
    printf("Enter board configuration:\n");
    while (1)
    {
        scanf(" %3s", input);
        if (strcmp(input, "!!!") == 0)
        {
            break;
        }

        char player = input[0];
        char tempRow = input[1];
        char tempCol = input[2];

        if (player != 'B' && player != 'W')
        {
            printf("Invalid\n");
            continue;
        }

        int r = tempRow - 'a';
        int c = tempCol - 'a';
        if (r < 0 || r >= n || c < 0 || c >= n)
        {
            printf("Invalid\n");
            continue;
        }

        setBoard(board, n, player, r, c);
    }
}

void printBoard(char board[][MAX_N], int n)
{
    // Print column header
    printf("  ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", 'a' + i);
    }
    printf("\n");

    // Print rows
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

bool checkDirection(char board[][MAX_N], int n, int row, int col, char player, int dRow, int dCol)
{
    char other = (player == 'W') ? 'B' : 'W';
    int r = row + dRow;
    int c = col + dCol;
    int count = 0;

    // Walk in the direction, counting opponent pieces
    while (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == other)
    {
        count++;
        r += dRow;
        c += dCol;
    }

    // Valid if we found at least one opponent piece and then our own piece
    if (count > 0 && r >= 0 && r < n && c >= 0 && c < n && board[r][c] == player)
    {
        return true;
    }
    return false;
}

bool isValid(char board[][MAX_N], int n, int row, int col, char player)
{
    // Must be an unoccupied cell
    if (board[row][col] != 'U')
    {
        return false;
    }

    // 8 directions: E, NE, N, NW, W, SW, S, SE
    int dRow[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dCol[] = {1, 1, 0, -1, -1, -1, 0, 1};

    for (int i = 0; i < 8; i++)
    {
        if (checkDirection(board, n, row, col, player, dRow[i], dCol[i]))
        {
            return true;
        }
    }
    return false;
}

int availableMove(char board[][MAX_N], int n, char player, char moves[])
{
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (isValid(board, n, i, j, player))
            {
                moves[num] = 'a' + i;
                moves[num + 1] = 'a' + j;
                num += 2;
            }
        }
    }
    moves[num] = '\0';
    return num;
}

void placeDot(char board[][MAX_N], int n, int row, int col, char player)
{
    int dRow[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dCol[] = {1, 1, 0, -1, -1, -1, 0, 1};

    board[row][col] = player;

    for (int i = 0; i < 8; i++)
    {
        // Only flip in directions that are valid
        if (checkDirection(board, n, row, col, player, dRow[i], dCol[i]))
        {
            char other = (player == 'W') ? 'B' : 'W';
            int r = row + dRow[i];
            int c = col + dCol[i];
            while (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == other)
            {
                board[r][c] = player;
                r += dRow[i];
                c += dCol[i];
            }
        }
    }
}