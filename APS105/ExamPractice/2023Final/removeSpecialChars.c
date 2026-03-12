#include <stdio.h>
#include <string.h>

char *removeSpecialChars(char *str)
{
    int i = 0;
    while (str + i != \0) // WRONG NAME!!!
    {
        if (str + i > 122 || char + i < 97)
        {
            *(str + i) = 0;
        }
        i++;
    }

    char *str2;
    i = 0;
    int n = 0;
    while (str + i !=\0)
    {
        if (str + i != 0)
        {
            *(str2 + n) = char + i;
            n++;
        }
        i++;
    }
    *(str2 + n + 1) =\0;
    return str2;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
