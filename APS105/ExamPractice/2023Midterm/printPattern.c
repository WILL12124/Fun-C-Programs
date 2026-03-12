#include <stdio.h>

int main(int argc, char const *argv[])
{

    int rows = 6;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows * 2 - 1; j++)
        {
            if (i == 0 || i == rows - 1)
            {
                printf("*");
            }
            else if (j == 0 || j == rows * 2 - 2 || j == rows - 1 - i || j == rows - 1 + i)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
