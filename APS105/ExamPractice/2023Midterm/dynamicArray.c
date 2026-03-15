#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int newNumber = 3;
    int numbersInArray = 9;
    int *pArray = calloc(numbersInArray, sizeof(int));

    int *pNewArr = realloc(pArray, (numbersInArray + 1) * sizeof(int));
    *(pNewArr + numbersInArray) = newNumber;

    free(pArray); // DO NOT FREE AGAIN, realloc DOES IT FOR YOU
    pArray = NULL;
    return 0;
}
