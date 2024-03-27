#include "helpers.h"

#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    index into image
    */
    float avgcolour = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgcolour = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            avgcolour = round(avgcolour);

            // set all pixels to the average number
            image[i][j].rgbtBlue = avgcolour;
            image[i][j].rgbtGreen = avgcolour;
            image[i][j].rgbtRed = avgcolour;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    */

    float sepiaRed = 0;
    float sepiaGreen = 0;
    float sepiaBlue = 0;
    float originalRed = 0;
    float originalGreen = 0;
    float originalBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store original pixel colours in temp variables
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // calculate new colours
            sepiaRed = (.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue);
            sepiaRed = round(sepiaRed);

            sepiaGreen = (.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue);
            sepiaGreen = round(sepiaGreen);

            sepiaBlue = (.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue);
            sepiaBlue = round(sepiaBlue);

            if (sepiaRed > 255.0)
            {
                sepiaRed = 255.0;
            }

            if (sepiaGreen > 255.0)
            {
                sepiaGreen = 255.0;
            }

            if (sepiaBlue > 255.0)
            {
                sepiaBlue = 255.0;
            }

            // set new colours
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temp space to hold original picture
    RGBTRIPLE tempimage[height][width];

    for (int i = 0; i < height; i++)
    {
        // for the number of pixels in every row
        for (int j = 0; j < width; j++)
        {
            // set each pixel to the original
            tempimage[i][j].rgbtRed = image[i][j].rgbtRed;
            tempimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempimage[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = tempimage[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = tempimage[i][(width - 1) - j].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];

    for (int i = 0; i < height; i++)
    {
        // for the number of pixels in every row
        for (int j = 0; j < width; j++)
        {
            // set each pixel to the original
            tempimage[i][j].rgbtRed = image[i][j].rgbtRed;
            tempimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // RED

    // for every row
    for (int i = 0; i < height; i++)
    {
        // for the number of pixels in every row
        for (int j = 0; j < width; j++)
        {
            // do the maths for the pixel
            float r = 0;
            int count = 0;

            r = tempimage[i][j].rgbtRed;
            count++;

            // if too close to left, ignore this section
            if (j != 0)
            {
                r = r + tempimage[i][j - 1].rgbtRed;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j - 1].rgbtRed;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j - 1].rgbtRed;
                    count++;
                }
            }

            // if too close to right, ignore this section
            if (j != width - 1)
            {
                r = r + tempimage[i][j + 1].rgbtRed;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j + 1].rgbtRed;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j + 1].rgbtRed;
                    count++;
                }
            }

            // directly below
            if (i != 0)
            {
                r = r + tempimage[i - 1][j].rgbtRed;
                count++;
            }
            // directly above
            if (i != height - 1)
            {
                r = r + tempimage[i + 1][j].rgbtRed;
                count++;
            }

            r = r / count;
            r = round(r);

            // log red pixel into image
            image[i][j].rgbtRed = r;
        }
    }

    // GREEN

    // for every row
    for (int i = 0; i < height; i++)
    {
        // for the number of pixels in every row
        for (int j = 0; j < width; j++)
        {
            // do the maths for the pixel
            float r = 0;
            int count = 0;

            r = tempimage[i][j].rgbtGreen;
            count++;

            // if too close to left
            if (j != 0)
            {
                r = r + tempimage[i][j - 1].rgbtGreen;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j - 1].rgbtGreen;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j - 1].rgbtGreen;
                    count++;
                }
            }

            // if too close to right
            if (j != width - 1)
            {
                r = r + tempimage[i][j + 1].rgbtGreen;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j + 1].rgbtGreen;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j + 1].rgbtGreen;
                    count++;
                }
            }

            if (i != 0)
            {
                r = r + tempimage[i - 1][j].rgbtGreen;
                count++;
            }
            if (i != height - 1)
            {
                r = r + tempimage[i + 1][j].rgbtGreen;
                count++;
            }

            r = r / count;
            r = round(r);

            // log red pixel into image
            image[i][j].rgbtGreen = r;
        }
    }

    // BLUE

    // for every row
    for (int i = 0; i < height; i++)
    {
        // for the number of pixels in every row
        for (int j = 0; j < width; j++)
        {
            // do the maths for the pixel
            float r = 0;
            int count = 0;

            r = tempimage[i][j].rgbtBlue;
            count++;

            // if too close to left
            if (j != 0)
            {
                r = r + tempimage[i][j - 1].rgbtBlue;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j - 1].rgbtBlue;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j - 1].rgbtBlue;
                    count++;
                }
            }

            // if too close to right
            if (j != width - 1)
            {
                r = r + tempimage[i][j + 1].rgbtBlue;
                count++;
                if (i != 0)
                {
                    r = r + tempimage[i - 1][j + 1].rgbtBlue;
                    count++;
                }
                if (i != height - 1)
                {
                    r = r + tempimage[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }

            if (i != 0)
            {
                r = r + tempimage[i - 1][j].rgbtBlue;
                count++;
            }
            if (i != height - 1)
            {
                r = r + tempimage[i + 1][j].rgbtBlue;
                count++;
            }

            r = r / count;
            r = round(r);

            // log red pixel into image
            image[i][j].rgbtBlue = r;
        }
    }

    return;
}
