// This is the complete C program for testing the Goldbach conjecture
#include <stdio.h>
#include <stdbool.h>
// Function prototypes
bool testGoldbach(int);
void printConjResult(int);
void getUserInput(int *);
void nextPrimeNumber(int *);
bool isPrime(int);
int main(void)
{
    /*Main function is too simple, it calls a function to take input from the user
    and calls another function that checks and verifies if the number verifies the
        conjecture*/
    int number;
    getUserInput(&number);
    printConjResult(number);
    return 0;
}
void printConjResult(int number)
{
    // Call a function to verify the conjecture and prints the result
    bool verified = testGoldbach(number);
    if (verified)
    {
        printf("Goldbach conjecture is verified");
    }
    else
    {
        printf("Goldbach conjecture not verified");
    }
}
bool testGoldbach(int N)
{
    // Tests the Goldbach conjecture and returns true if verified or false if rejected
    int firstPart = 2, secondPart;
    bool stop = false;
    bool verified = false;
    while (!stop)
    {
        secondPart = N - firstPart;
        if (secondPart < firstPart)
        {
            stop = true;
        }
        else if (isPrime(secondPart))
        {
            stop = true;
            verified = true;
        }
        else
        {
            nextPrimeNumber(&firstPart);
        }
    }
    return verified;
}
void nextPrimeNumber(int *pFirst)
{
    // We will look for the numbers after *pFrist one by one until we find the next
    prime number int value = *pFirst + 1;
    while (!isPrime(value))
    {
        value += 1;
    }
    *pFirst = value;
}
bool isPrime(int num)
{
    // check if num is prime, by checking the remainder of num / all numbers from 2 to num - 1
    bool prime = true;
    if (num < 2)
    {
        prime = false;
    }
    else
    {
        for (int j = 2; j <= num - 1 && prime; j++)
        {
            if (num % j == 0)
            {
                prime = false;
            }
        }
    }
    return prime;
}
void getUserInput(int *number)
{
    // Get user input from the keyboard and verifies it is even and greater than 2
    bool firstEntry = true;
    do
    {
        if (firstEntry)
        {
            printf("Enter a number to test the Goldbach conjecture: ");
            firstEntry = false;
        }
        else
        {
            printf("Your input was invalid, please enter another number > 2: ");
        }
        scanf("%d", number);
    } while (*number <= 2 || *number % 2 != 0);
}
