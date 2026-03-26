/*CORRECT！！！
Just reminder it is a bit inefficient to calculate strlen,
it is better to just pass
......
    str[0] = str[len - 1];          // Last character
    str[len - 1] = temp;

    // Recurse:
    // str + 1 shifts the starting pointer one character to the right
    // len - 2 accounts for the two characters we just swapped at the ends
    revStr(str + 1, len - 2);
*/
#include <stdio.h>
#include <string.h>
void revStr(char *str, int len)
{
    // find arr len
    int size = strlen(str);

    int low = size - len, high = len - 1, temp = 0;
    // base case
    if (low >= high)
    {
        return;
    }

    // R case
    temp = str[low];
    str[low] = str[high];
    str[high] = temp;

    revStr(str, len - 1);
}