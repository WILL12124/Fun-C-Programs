/*Write a complete C function called sumDivisors, the prototype of which is
given below, that accepts one parameter named num of type int. The function
must return the sum of all divisors of num. You may assume that the argument
passed to the function is a positive integer. For example, if num was 6, the
divisors of 6 are 1, 2, 3. The function should return 1 + 2 + 3 = 6. The divisors
do not include the number itself, but they include 1*/
#include <stdio.h>

int sumDivisors(int num)
{
    int sum = 1;
    for (double i = 2; i <= num / 2; i++)
    {
        if ((double)num / i == (int)num / i)
        {
            sum = num + i;
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int num = 6, sum = 0;
    sum = sumDivisors(num);
    printf("%d", sum);
    return 0;
}
