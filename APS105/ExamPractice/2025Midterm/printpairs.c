/*Write a C function named printPairs that would search through an array of integers named arr and print pairs of numbers whose sum is equal to target. The size of the array is stored in size. You MUST assume the numbers in the array are sorted in ascending order. You need to make sure you are not printing duplicates, although there might be duplicates in the array. This means if 2 and 5 appear multiple times in the array and the target is 7, you should not print (2, 5) multiple times. Also, if the target is 10, and 5 appears two or more times print (5, 5) once.

The function prototype is as follows:

void printPairs(int arr[], int size, int target);
Example 1: if the arr has {2, 2, 3, 4, 4, 5, 5} and target is 7, the expected output should be as follows, since 2 and 5 add up to 7 and 3 and 4 add up to 7.

(2, 5)
(3, 4)
Example 2: if the arr has {1, 4, 4, 4, 5} and target is 9, the expected output should be as follows, since 4 and 5 and up to 9.

(4, 5)
Example 3: if the arr has {1, 4, 4, 5, 5} and target is 10, the expected output should be as follows, since 5 and 5 and up to 10.

(5, 5)
Example 4: if the arr has {1, 4, 4, 4, 5} and target is 10, the function should not print anything, since no two numbers add up to 10.*/
#include <stdio.h>

void printPairs(int arr[], int size, int target)
{
    // get rid of duplicates
    int duplicates[size] = {0}; // 初始化数组需要用大括号
    for (int i = 0; i < size; i++)
    {
        if (arr[i + 1] == arr[i])
        {
            duplicates[i + 1] = 1;
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (duplicates[i] == 1)
        {
            arr[i] = -10e-3;
        }
    }

    // solve pairs
    int left = 0, right = size;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i + j] + arr[i] == target)
            {
                printf("(%d,%d)", arr[i], arr[i + j]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
