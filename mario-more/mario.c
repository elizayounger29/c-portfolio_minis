#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user for height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // counter for how many downward lines
    for (int i = 0; i < n; i++)
    {
        // counter for every space
        for (int k = 0; k < ((n - i) - 1); k++)
        {
            printf(" ");
        }

        //counter for how many lines across
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("  ");

        //counter for # second pyramid side
        for (int p = 0; p <= i; p++)
        {
            printf("#");
        }

        printf("\n");
    }

}