#include <stdio.h>

int lineStars(int);
int printStars(int, int);

int main(int argc, char const *argv[])
{
  int line = 0;
  do
  {
    printf("enter line #");
    scanf("%d", &line);
  } while ((line <= 3)); // input must be greater than 3 to form diagonal
  lineStars(line);

  return 0;
}

int lineStars(int line2) // Gemini: don't return a value, so leave as a void
{
  for (int row = 1; row <= line2; row++)
  {
    if (row == 1 || row == line2)
    {
      for (int j = 1; j <= line2; j++)
      {
        printf("*");
      }
      printf("\n");
    }
    else
    {
      printStars(row, line2);
      printf("\n");
    }
  }
}

int printStars(int row, int line)
{
  for (int column = 1; column <= line; column++)
  {
    if (column == line - (row - 1) || column == 1 || column == line)
    {
      printf("*");
    }
    else
    {
      printf("%c", ' ');
    }
  }
}

/*Use combined logic to print stars
if (row == 0 || row == size - 1 ||
                col == 0 || col == size - 1 ||
                col == size - 1 - row)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
*/