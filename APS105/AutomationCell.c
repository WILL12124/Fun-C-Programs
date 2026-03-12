// this program iterates the Elementary Cellular Automaton
#include <stdio.h>
#include <stdlib.h>

int *convertToBinary(int rule);
int getRuleOutcome(int *ruleBinary, int left, int center, int right);

int main()
{
    int aliveCellIndex, rule, numIterations;
    printf("Input the Alive Cell Index, Rule, # of interations: ");
    scanf("%d %d %d", &aliveCellIndex, &rule, &numIterations);
    // the array is used in many functions, use calloc in heap
    int *cell = calloc(17, sizeof(int)); // try to use calloc
    int *nextCell = calloc(17, sizeof(int));
    // check if there is memory
    if (cell == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    // Set alive cell
    cell[aliveCellIndex] = 1;

    // print the starting row
    for (int i = 0; i < 17; i++)
    {
        if (cell[i] == 1)
        {
            printf("*");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");

    // convert rule to binary truth table
    int *ruleBinary = convertToBinary(rule);

    for (int i = 0; i < numIterations; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            int left = 0, right = 0;
            if (j == 0)
            {
                left = 0;
            }
            else
            {
                left = cell[j - 1];
            }
            if (j == 16)
            {
                right = 0;
            }
            else
            {
                right = cell[j + 1];
            }
            int aliveOrNot = getRuleOutcome(ruleBinary, left, cell[j], right);
            if (aliveOrNot == 1)
            {
                printf("*");
                nextCell[j] = 1;
            }
            else
            {
                printf(" ");
                nextCell[j] = 0;
            }
        }
        printf("\n");
        for (int k = 0; k < 17; k++)
        {
            cell[k] = nextCell[k];
        }
    }

    free(cell);
    free(ruleBinary);
    free(nextCell);
    return 0;
}

int *convertToBinary(int rule)
{
    int *ruleBinary = calloc(8, sizeof(int));
    for (int i = 0; i <= 7; i++)
    {
        ruleBinary[i] = rule % 2;
        rule /= 2;
    }
    return ruleBinary;
}

int getRuleOutcome(int *ruleBinary, int left, int center, int right)
{
    int decimal = left * 4 + center * 2 + right;
    return ruleBinary[decimal];
}