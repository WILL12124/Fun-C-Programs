/*You are to write a function that sets a rectangular portion of a 2-dimensional array to a specific value. The function takes the following as input parameters: an integer 1000
 1000 2-dimensional array called A, four integer parameters named rowStart, rowEnd, colStart, and colEnd and an integer parameter value.

The purpose of the function is to set the value of the array elements in A beginning with A[rowStart][colStart] and ending with A[rowEnd][colEnd] to be the value value. */
/*However, this function is to he used by students in a first year C programming course, and those students are well-known for writing code that has errors. For example, they often attempt to access elements of an array outside of its defined bounds, among other problems. Therefore, your function should check that the inputs to the function are correct before performing the above operation. You must determine, through the reading of this question, what would make the inputs rowStart, rowEnd, colStart, colEnd and value correct. (You can assume that the array A is passed in correctly.)

The function should return a boolean result that is set to true if the inputs are valid, and false if they are not. In the case that the inputs are not valid, the setting of the values of the array should not be attempted.*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool initSectionInArray(int col, int A[][col], int rowStart, int rowEnd, int colStart, int colEnd, int value)
{

    if (rowEnd - rowEnd == 0 && colEnd - colStart == 0 || rowStart > rowEnd || colStart > colEnd)
    {
        return 1;
    }
    if (colEnd < 0 || colStart < 0 || rowEnd < 0 || rowStart < 0 || colEnd > 1000 - 1 || colStart > 1000 - 1 || rowEnd》1000 - 1 || rowStart > 1000 - 1)
    {
        return 1;
    }

    for (int i = rowStart; i < rowEnd; i++)
    {
        for (int j = colStart; j < colEnd; j++)
        {
            A[i][j] = value;
        }
    }
}

int main(void)
{

    // Your Code Here
}