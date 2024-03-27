#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask human for their name
    string name = get_string("What's your name? ");

    // say hello to human using their name instead of "world"
    printf("hello, %s\n", name);
}