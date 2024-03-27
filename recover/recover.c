#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

/*
    - open memory card
    - how much memory?
    - read 512bytes into buffer
    - if start of jpeg
    - open new jpeg file
    - write 512bytes until anew jpg is found
    - stop at end of file

    - each jpeg starts with distinct header
    - first three bytes: 0xff   0xd8    0xff
    - jpegs stored back-to-back in memory card
    - each block is 512 bytes
*/

int main(int argc, char *argv[])
{
    // check user input correctly
    if (argc != 2)
    {
        printf("usage; ./PROGRAM IMAGE");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.");
        return 2;
    }

    // the number of jpg files counter
    int jpgcount = 0;
    // initialise buffer to hold jpg sized chunks
    BYTE buffer[512] = {0};
    // store new generated filename here (one at a time)
    char filename[8] = {0};
    // pointer to whatever new file you will open
    FILE *imgptr = NULL;

    // read first bit of data into buffer
    while (fread(&buffer, 512, 1, file) == 1)
    {
        // Check for jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close old file, if previous
            if (jpgcount != 0)
            {
                fclose(imgptr);
            }

            // make name of new file
            sprintf(filename, "%03i.jpg", jpgcount);

            // pointer to new file. Open file in that new place
            imgptr = fopen(filename, "w");

            if (imgptr == NULL)
            {
                printf("imgptr unsuccessful");
            }

            // check successful then write
            else
            {
                // write into open file using its pointer
                fwrite(buffer, sizeof(buffer), 1, imgptr);
            }

            jpgcount++;
        }

        // if next 512bytes of data is not the beginning of file. But jpgcount is 1 or more (therefore middle of file), continue to read into file
        if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff || (buffer[3] & 0xf0) != 0xe0)
        {
            if (jpgcount != 0)
            {
                fwrite(buffer, sizeof(buffer), 1, imgptr);
            }
        }
    }

    fclose(file);
    fclose(imgptr);
}