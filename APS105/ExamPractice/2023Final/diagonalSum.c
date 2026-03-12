#include <stdio.h>

int diagonalsSum(int n, int square[][n])
{
    int sum1 = 0, sum2 = 0;
    // sum main dia
    for (int i = 0; i < n; i++)
    {
        sum1 += square[i][i];
    }

    // sum other dia
    for (int i = 0; i < n; i++)
    {
        sum2 += square[i][n - 1 - i];
    }

    return sum1 + sum2;
}

int main(int argc, char const *argv[])
{
    //
    return 0;
}
