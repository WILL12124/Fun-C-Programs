#include <stdio.h>

int printNthElementinSpiralOrder(int rows, int cols, int arr[rows][cols], int n)
{
    int b = 0, num = 0;
    int j = 0, i = 0;
    while (num < cols * rows) // less or equal
    {
        for (; i < cols - b; j++)
        {
            num++;
            if (num == n)
            {
                return arr[i][j];
            }
        }
        for (; i < rows - b; i++)
        {
            num++;
            if (num == n)
            {
                return arr[i][j];
            }
        }

        for (; j < cols - b; j--)
        {
            num++;
            if (num == n)
            {
                return arr[i][j];
            }
        }
        b++;
        for (; i < rows - b; i--)
        {
            num++;
            if (num == n)
            {
                return arr[i][j];
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    const int cols = 4, rows = 6, n = 7;
    int arr[4][6] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    printNthElementinSpiralOrder(rows, cols, arr, n);
}
