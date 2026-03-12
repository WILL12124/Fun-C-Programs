/*Write a C function named secondLargest that takes two arguments: an array
of positive integers and the size of the array. The function should return the
second largest element in the array. Assume that the array always has at least
two elements. For example, given the array {3, 1, 4, 1, 5, 9, 2, 6, 5,
3, 5} with length 11, the function should return 6. If all elements have the
same value, the function should return 0*/
#include <stdio.h>

int secondLargest(int arr[], int size)
{
    int large = 0, second = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > large)
        {
            second = large;
            large = arr[i];
        }
        if (arr[i] < large && arr[i] > second)
        {
            second = arr[i];
        }
    }
    return second;
}
