#include <stdio.h>

int dotProduct(int arr1[], int arr2[])
{
    int size1 = 0, size2 = 0;
    while (arr1[i] != -1)
    {
        size1++;
    }
    while (arr2[i] != -1)
    {
        size2++;
    }
    (size1 == size2) ?: return -1;

    int sum = 0;
    for (int i = 0; i <= size1; i++)
    {
        sum += arr1[i] * arr2[i];
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    arr1[] return 0;
}
