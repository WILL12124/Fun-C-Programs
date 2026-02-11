/*in version one, i realized that i did not include situation where user inputed zero
also, the code was repetitive and tedious*/
/*in this version2, i learned to use if and while to improve my program*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int input = 0;
    int binaryNum[32];
    double remainder = 0;
    int i = 0;
    int j = 0;

    printf("Enter a decimal number to convert: ");
    scanf("%d", &input);

    if (input == 0)
    {
        printf("In binary is: 0\n");
        return 0;
    }

    while (input > 0)
    {
        binaryNum[i] = input % 2;
        input = input / 2;
        i++;
    }

    printf("In binary: ");
    for (j = i - 1; j >= 1; j--)
    {
        printf("%d", binaryNum[j]);
    }

    return 0;
}
