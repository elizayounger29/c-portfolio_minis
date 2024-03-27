#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ci = (p[i] + k)%26

string compute_cipher(string message, int key);
int key_legal(string SpecialK);
int compute_key(string SpecialK);

int alphabetU[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int alphabetl[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    // make sure the human has typed the correct number of things
    if (argc == 2)
    {
        // is the key made up of digits?
        int k = key_legal(argv[argc - 1]);

        //if Key is illegal
        if (k != 0)
        {
            printf("Usage: ./caesar key\n");
            return (1);
        }

        if (k == 0)
        {
            // convert key to int from string
            k = compute_key(argv[argc - 1]);

            //input message
            string plaintext = get_string("Plaintext: ");

            // work out cipher
            string cipher = compute_cipher(plaintext, k);
        }
    }

    else
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }

    return (0);
}



int key_legal(string SpecialK)
{
    // length of key string
    int j = strlen(SpecialK);

    for (int i = 0; i < j; i++)
    {
        if (isdigit(SpecialK[i]))
        {

        }
        else
        {
            i = i + j;
            return (1);
        }

    }

    return (0);

}



int compute_key(string SpecialK)
{
    int x = atoi(SpecialK);
    return (x);
}



string compute_cipher(string message, int key)
{
    //Get length
    int l = strlen(message);

    // ciphertext letter
    int ci = 0;

    printf("ciphertext: ");

    // for every letter in message
    for (int i = 0; i < l; i++)
    {
        // every alphabet cycle for each letter.
        for (int j = 0; j < 26; j++)
        {
            if (isupper(message[i]))
            {
                // print the letter plus key
                if (message[i] == alphabetU[j])
                {
                    // place in alphabet new cipher letter is
                    ci = (j + key) % 26;
                    j = j + 26;

                    printf("%c", alphabetU[ci]);

                }
            }

            if (islower(message[i]))
            {
                // print the letter plus key
                if (message[i] == alphabetl[j])
                {
                    ci = (j + key) % 26;
                    j = j + 26;

                    printf("%c", alphabetl[ci]);
                }

            }

            if (message[i] == '\0')
            {
                i = i + l;
                j = j + 26;
            }

            if (message[i] < 65 || message[i] > 122)
            {
                printf("%c", message[i]);
                j = j + 26;
            }
        }


    }

    printf("\n");

    return (0);

}