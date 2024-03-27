#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// index = 0.0588 * (L - 0.296) * (S - 15.8)
// L = average number of letters per 100 words
// S is the average number of sentences per 100 words in the text.

// ascertain how many and what are:
// - pw many letters (chars?)
// - words (ending in " ")
// - sentences (ending in ".")

int Letter_Count(string passage, int l);
int Word_Count(string passage, int l);
int Sentence_Count(string passage, int l);

int main(void)
{
    // Get Text
    string Text = get_string("Text: ");

    // Text Length
    int length = strlen(Text);

    // Calculate letters
    int letter = Letter_Count(Text, length);

    // Calculate Words
    int words = Word_Count(Text, length);

    // Calculate Sentences
    int sentences = Sentence_Count(Text, length);

    // Calculate Grade

    float avg_letters_per100 = ((float) letter / (float) words) * 100;

    float avg_sentences_per100 = ((float) sentences / (float) words) * 100;

    float index = (0.0588 * avg_letters_per100) - (0.296 * avg_sentences_per100) - 15.8;

    index = round((double) index);

    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", (int) index);
    }
    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

}

int Letter_Count(string passage, int l)
{
    int j = 0;

    for (int i = 0; i < l; i++)
    {
        if (isalpha(passage[i]))
        {
            j++;
        }
    }

    return j;
}

int Word_Count(string passage, int l)
{
    int j = 0;

    for (int i = 0; i < l; i++)
    {
        if (isspace(passage[i]))
        {
            j++;
        }
    }

    j++;

    return j;
}

int Sentence_Count(string passage, int l)
{
    int j = 0;

    for (int i = 0; i < l; i++)
    {
        if (passage[i] == '!' || passage[i] == '?' || passage[i] == '.')
        {
            j++;
        }
    }

    return j;
}