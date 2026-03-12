/*Write a C main function that takes in two dates from the user, and determines
if the first date or the second date is later or if they are the same date. Three
examples are shown below. User input is in bold.*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int isFirst;
    int date1 = 0, mon1 = 0;
    int date2 = 0, mon2 = 0;

    printf("Enter first date (day/month): ");
    scanf("%d/%d", &date1, &mon1);

    printf("Enter second date (day/month): ");
    scanf("%d/%d", &date2, &mon2);

    date1 = date1 + mon1 * 300;
    date2 = date2 + mon2 * 300;
    if (date1 < date2)
    {
        isFirst = 0;
    }
    else if (date1 == date2)
    {
        isFirst = 3;
    }
    else
    {
        isFirst = 1;
    }

    if (isFirst == 3)
    {
        printf("It's the same date");
        return 0;
    }

    printf("%s date is later", (isFirst == 1) ? "First" : "Second");

    return 0;
}
