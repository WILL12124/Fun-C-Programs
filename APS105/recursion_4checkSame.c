/*
READ THE QUESTION!!!

Note!: The main trick is to use arr identifier as a pointer to index, which can be incremented.
当if里面只有return时候，可能！不需要else
*/
#include <stdio.h>
#include <stdbool.h>
bool compareLines(const char *lineOne, const char *lineTwo)
{
    while (*lineOne == ' ' || *lineOne == '.') // NOte: use while instead of if when multiple ignorance can occur
    {
        lineOne++; // change pointer to the "second" element
    }
    while (*lineTwo == ' ' || *lineTwo == '.')
    {
        lineTwo++;
    }

    // base case, 多个终止条件！
    if (*lineOne == '\0' && *lineTwo == '\0')
    {
        return 1;
    }
    // 已经handle了两个同时的情况， 用*lineOne == '\0' || *lineTwo == '\0'
    else if ((*lineOne == '\0' && *lineTwo != '\0') || (*lineOne != '\0' && *lineTwo == '\0'))
    {
        return 0;
    }
    else if (*lineOne == *lineTwo)
    {
        return compareLines(lineOne + 1, lineTwo + 1);
    }
    else
    {
        return 0;
    }
}
