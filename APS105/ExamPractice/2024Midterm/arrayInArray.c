/*Write a complete C function called arrayInArray, the prototype of which is
given below. The function accepts two arrays of type int as parameters,
named a and b. The sizes of b and a are unknown, but the last element in
both array is always -1. All other elements in the arrays are positive integers.
The function must return true if the sequence of numbers in array b is found
in array a excluding the last element in the array, which is always -1.
For example, if a = {6, 8, 7, 6, 1, 7, 4, -1} and b = {6, 1, -1}, the
function returns true as the sequence of {6, 1} is available in a at index 3.
Another example, if a = {6, 8, 7, 6, 1, 7, 4, -1} and b = {7, 8, -1},
the function returns false as the sequence of {7, 8} is not available in a*/

#include <stdio.h>
#include <stdbool.h> //include bool

bool arrayInArray(int a[], int b[])
{
    bool isIn = 0;
    int sizeB = 0;
    for (int i = 0;; i++)
    {
        if (b[i] == -1)
        {
            break;
        }
        sizeB++;
    }

    for (int i = 0; a[i] != -1; i++)
    {
        if (b[0] == a[i])
        {
            int numberSame = 0;
            for (int j = 0; b[j] != -1; j++)
            {

                if (b[j] == a[i + j])
                {
                    numberSame++;
                }
            }
            if (numberSame == sizeB)
            {
                isIn = 1;
                return isIn;
            }
            else
            {
                numberSame = 0;
                break; // 不对就赶紧停啊喂！
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
