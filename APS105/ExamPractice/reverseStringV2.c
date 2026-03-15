#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isStringRotation(char *s1, char *s2)
{
    bool isRotate = 0;
    int disp = 0;
    if (strlen(s1) != strlen(s2))
    {
        return false;
    }

    for (; disp < strlen(s1); disp++)
    {
        for (int i = 0; s1[i] != '\0'; i++) // char 一定要在‘’当中
        {
            if (s1[i] == (s2[i + disp]) % strlen(s1)) // wrong，必须当他完成，出现错误报错
            {
                isRotate = 1;
            }
            else
            {
                isRotate = 0;
            }
        }
        if (isRotate)
        {
            return true;
        }
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
