#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printSpiral(char fucku[], int size)
{
    char *p = calloc(size * 2 + 1, sizeof(char)); // size 需要2倍加1
    memcpy(p, fucku, (size) * sizeof(char));      // size 小心！！！
    strcat(p, fucku);
    for (int step = 0; step < size; step++)
    {
        for (int i = 0; i < size; i++)
        {
            printf("%s", p[step + i]); // 是char啊！！！！！
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    char fucku[] = "fuckyou";
    int size = 7;
    printSpiral(fucku, size);
    return 0;
}
