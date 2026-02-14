#include <stdio.h>

void printTriangle(int);

int main(int argc, char const *argv[])
{
    int line = 0;
    scanf("%d", &line);
    printTriangle(line);
    return 0;
}

void printTriangle(int line)
{
    for (int i = 1; i <= line; i++)
    {
        for (int j = 1; j <= line * 3 * 2 - 1 * 3; j += 3)
        {
            if (i == line)
            {
                printf("arc");
            }

            else if (j == 3 * (line - i) + 1 || j == line * 3 - 2 + 3 * (i - 1))
            {
                printf("arc");
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
}