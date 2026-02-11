#include <stdio.h>   //preprocessor directive
#include <stdbool.h> //include boolean var

int main(int argc, char const *argv[]) // entry point of the function
{
    int age = 23;                 // integer variable
    float gpa = 3.88;             // floating point number variabel; default is displaying six digits after the decimal
    double bookCourt = 0.0000001; // a double variable can store up to 15/16 digits
    char gradeESP = 'A';          // a char variable can store one character/symbol
    char xp[] = "legs";           // array of characters to represent a string
    bool isTurnOn = 0;            // bools are either true or false, '1' means true; if use 'printf' use '%d'

    printf("My favorite age is %d, what's yours\n", age);                            //'%' is format specifier; 'd' means decimal
    printf("How did u know i got %.2f GPA?\n", gpa);                                 //'f' means float; '.2' means display two digits after
    printf("How close am I from booking the court on saturday? %.7lf\n", bookCourt); //'lf' means long float
    printf("My grade for ESP is %c", gradeESP);                                      // 'c' means char
    printf("My favorite xp is %s, what is your favorite xp?\n", xp);                 //'s' means string

    if (isTurnOn)
    {
        printf("Let's fk\n");
    }
    else
    {
        printf("I like your skirt\n");
    }

    return 0;
}
