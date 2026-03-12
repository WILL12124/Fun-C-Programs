#include <stdio.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7
#define CONNECT 4
#define P1 'X'
#define P2 'O'
#define EMPTY '-'

void printBoard();
int fallColumn(int, bool);
bool isFull(int);
bool checkForWin(int, int, bool);
int arr[ROWS][COLS];

int main(int argc, char const *argv[])
{
    // clear board!
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            arr[i][j] = 0;
        }
    }

    char buffer[10] = "\0";
    bool isFinish = 0, user = 0;
    int column = 0, currentRow = 0;

    printBoard();

    while (isFinish == 0)
    {
        user = 0;
        do
        {
            printf("Player X enter column: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &column);
            // exit to program
            if (column < 0)
            {
                return 0;
            }
        } while (column > 6 || isFull(column) != 0); // 用OR注意数据越界

        currentRow = fallColumn(column, user);
        isFinish = checkForWin(currentRow, column, user);
        printBoard();
        if (isFinish == 1)
        {
            printf("Player X wins!");
            return 0;
        }

        user = 1;
        do
        {
            printf("Player O enter column: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &column);
            // exit to program
            if (column < 0)
            {
                return 0;
            }
        } while (column > 6 || isFull(column) != 0); // need negative to end program

        currentRow = fallColumn(column, user);
        isFinish = checkForWin(currentRow, column, user);
        printBoard();
        if (isFinish == 1)
        {
            printf("Player O wins!");
            return 0;
        }
    }

    return 0;
}

void printBoard()
{
    // print first line
    for (int i = 0; i < COLS; i++)
    {
        printf("%d ", 0 + i);
    }
    printf("\n");

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (arr[row][col] == 1)
            {
                printf("%c ", P1);
            }
            else if (arr[row][col] == 2)
            {
                printf("%c ", P2);
            }
            else
            {
                printf("%c ", EMPTY);
            }
        }
        printf("\n");
    }
}

int fallColumn(int column, bool user)
{
    int row = ROWS - 1;
    for (; row >= 0; row--)
    {
        // nested if statement
        if (arr[row][column] == 0)
        {
            if (user == 0)
            {
                arr[row][column] = 1;
            }
            else
            {
                arr[row][column] = 2;
            }
            break;
        }
    }
    return row;
}

bool isFull(int column)
{
    if (arr[0][column] != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// need of final position
// dir arr?
bool checkForWin(int row, int col, bool user)
{
    int userInArr = 0;
    int directionCol[4] = {1, 0, 1, 1}; // Index: down 0;right 1;down-right 2; down-left 3
    int directionRow[4] = {0, 1, 1, -1};
    if (user == 0)
    {
        userInArr = 1;
    }
    else
    {
        userInArr = 2;
    }

    for (int numDir = 0; numDir < 4; numDir++)
    {
        int count = 1;
        // verticle
        for (int i = 1; i <= CONNECT - 1; i++) // must start from 1
        {
            // calculate next row,col index
            int nextRow = row + i * directionRow[numDir]; // note numDir!!!
            int nextCol = col + i * directionCol[numDir];
            // 防止越界！！！
            if (nextRow < 0 || nextRow >= ROWS || nextCol < 0 || nextCol >= COLS)
            {
                break;
            }
            if (arr[nextRow][nextCol] == userInArr)
            {
                count++;
            }
            else
            {
                break;
            }
        }

        // reverse direction
        for (int i = 1; i <= 3; i++)
        {
            int nextRow = row - i * directionRow[numDir];
            int nextCol = col - i * directionCol[numDir];

            // 防止越界
            if (nextRow < 0 || nextRow >= ROWS || nextCol < 0 || nextCol >= COLS)
                break;

            if (arr[nextRow][nextCol] == userInArr)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if (count == CONNECT)
        {
            return true;
        }
    }
    return false;
}