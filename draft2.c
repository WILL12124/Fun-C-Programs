/*Write a C function named printPairs that would search through an array of integers
 named arr and print pairs of numbers whose sum is equal to target.
 The size of the array is stored in size.
 You MUST assume the numbers in the array are sorted in ascending order.
 You need to make sure you are not printing duplicates, although there might be duplicates in the array.
 This means if 2 and 5 appear multiple times in the array and the target is 7, you should not print (2, 5) multiple times.
 Also, if the target is 10, and 5 appears two or more times print (5, 5) once.
*/

#include <stdio.h>

void printPairs(int arr[], int size, int target);

int main(int argc, char const *argv[])
{
    int arr[] = {1, 2, 3, 3, 4, 4, 5, 6, 7, 7, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    printPairs(arr, size, target);
    return 0;
}

void printPairs(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            arr[i + 1] = 10e5;
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 1; i < size; i++)
        {
            if (arr[i] + arr[i + j] == target)
            {
                printf("(%d,%d)", arr[i], arr[i + j]);
            }
            else
            {
                break;
            }
        }
    }
}