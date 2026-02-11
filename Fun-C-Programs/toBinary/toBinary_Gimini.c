#include <stdio.h>

int main()
{
    int input;
    // 1. 定义一个数组来存余数。
    // int通常是32位，所以我们准备32个格子就足够存任何int了
    int binaryNum[32];
    int i = 0;

    printf("Input a decimal number: ");
    scanf("%d", &input);

    if (input == 0)
    {
        printf("Binary: 0\n");
        return 0;
    }

    // 2. 使用 while 循环
    // 只要 input 大于 0，我们就一直做“除以2，取余数”的操作
    while (input > 0)
    {
        // 这一句 input % 2 等同于你写的 input - (input/2)*2
        binaryNum[i] = input % 2;
        input = input / 2;
        i++; // 移动到数组的下一个格子
    }

    // 3. 倒序打印
    // 因为算出来的余数是反着的（低位在前），所以我们要从后往前打印
    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%d", binaryNum[j]);
    }
    printf("\n");

    return 0;
}