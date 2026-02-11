#include <stdio.h>

int main(int argc, char const *argv[])
{
    int input = 0;
    int buffer1 = 0;
    int buffer2 = 0;
    int remainder1 = 0;
    int remainder2 = 0;
    int remainder3 = 0;
    int remainder4 = 0;
    int remainder5 = 0;
    int remainder6 = 0;
    int remainder7 = 0;
    int remainder8 = 0;
    int remainder9 = 0;
    int remainder10 = 0;
    int remainder11 = 0;
    int remainder12 = 0;
    int remainder13 = 0;
    int remainder14 = 0;

    printf("Input a decimal number\n");
    scanf("%d", &input);

    buffer1 = input / 2;
    remainder1 = input - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder2 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder3 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder4 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder5 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder6 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder7 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder8 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder9 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder10 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder11 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder12 = buffer1 - buffer2 * 2;

    buffer1 = buffer2 / 2;
    remainder13 = buffer2 - buffer1 * 2;

    buffer2 = buffer1 / 2;
    remainder14 = buffer1 - buffer2 * 2;

    printf("Binary:%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", remainder14, remainder13, remainder12, remainder11, remainder10, remainder9, remainder8, remainder7, remainder6, remainder5, remainder4, remainder3, remainder2, remainder1);

    return 0;
}
