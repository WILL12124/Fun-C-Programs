/*Write a C main function that takes in the number of lines, and prints the
following pattern depending on the number of lines entered by the user.*/

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int num = 0;
    printf("Enter number of lines: ");
    scanf("%d", &num);
    for (int row = 0; row < num; row++)
    {
        for (int col = 0; col < num; col++)
        {
            if (row == num - 1 || row == 0)
            {
                printf("*");
                continue;
            }

            if (col == row || col == num - 1 - row)
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
