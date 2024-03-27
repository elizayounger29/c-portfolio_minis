#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);


    // Look at scores and announce the winner!
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!\n");
    }

}

int compute_score(string word)
{
    // work out length of word; store in variable L
    int l = strlen(word);

    // i is place in scrabble word. j is place in alphabet. k counts the letter score points.
    int k = 0;

    for (int i = 0; i < l; i++)
    {
        // alphabet cycle per letter.
        for (int j = 0; j < 26; j++)
        {
            word[i] = tolower(word[i]);

            if (word[i] == alphabet[j])
            {
                int m = POINTS[j];
                printf("Points: %i\n", POINTS[j]);
                k = k + m;
                j = j + 26;
            }

            if (word[i] == '\0')
            {
                j = j + 26;
            }

            if (word[i] < 'a' || word[i] > 'z')
            {
                j = j + 26;
            }
        }

    }

    return (k);

}