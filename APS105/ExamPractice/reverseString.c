#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isStringRotation(char *s1, char *s2)
{
    bool isRotate = 0;
    int disp = 0;
    for (int i = 0; s1[i] != '\0'; i++) // not equal
    {
        for (disp = 0;; disp++)
        {
            if (s2[i + disp] != '\0')
            {
                if (s1[i] == s2[i + disp]) // yuejie
                {
                    isRotate = 1;
                    break;
                }
                else
                {
                    isRotate = 0;
                }
            }
            else
            {
                if (s1[i] == s2[i + disp - strlen(s1)])
                {
                    isRotate = 1;
                }
                else
                {
                    isRotate = 0;
                }
            }
        }
    }
    return isRotate;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
