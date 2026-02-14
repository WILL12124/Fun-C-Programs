#include <stdio.h>

void printArc(int);

int main(int argc, char const *argv[])
{
    int n = 0;
    scanf("%d", &n);
    printArc(n);
    printf("come play Arc Raiders!\n");
    return 0;
}

void printArc(int n)
{
    for (int row = 1; row <= n; row++)
    {
        for (int i = 0; i < row; i++)
        {
            printf("arc ");
        }
        printf("\n");
    }
}