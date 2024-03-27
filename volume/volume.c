// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TTOOOOOOO DOOOOOOOOOO;

    BYTE header[44];

    fread(&header, sizeof(BYTE), 44, input);
    fwrite(&header, sizeof(BYTE), 44, output);

    // Read samples and times by factor
    SAMPLE buffer;
    while (fread(&buffer, sizeof(SAMPLE), 1, input))
    {
        // times factor
        buffer *= factor;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);

    // remember to free what you malloced (buffer)
}