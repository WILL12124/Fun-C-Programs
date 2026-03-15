#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *deleteSubString(char *source, char *substring)
{
    // find lenth
    int lenth = 0, sublenth = 0;
    for (int i = 0; source[i] != '\0'; i++) /////////USE strlen!!!
    {
        lenth++;
    }

    for (int i = 0; substring[i] != '\0'; i++)
    {
        sublenth++;
    }

    char *p = strstr(source, substring);                    //////Handle when string not found!!!
    char *new = calloc(lenth - sublenth + 1, sizeof(char)); /////allocate too much

    for (int i = 0, j = 0; i < lenth; i++) // NO
    {
        if (i < p - source || i > p - source + sublenth) /////OFF by one
        {
            new[j] = source[i];
            j++;
        }
    }
    return new;
}