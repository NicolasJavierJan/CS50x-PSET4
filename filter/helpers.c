#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rgbtB = image[i][j].rgbtBlue;
            float rgbtG = image[i][j].rgbtGreen;
            float rgbtR = image[i][j].rgbtRed;

            int rgbtgrey = round(((rgbtB + rgbtG + rgbtR) / 3));

            image[i][j].rgbtBlue = rgbtgrey;
            image[i][j].rgbtGreen = rgbtgrey;
            image[i][j].rgbtRed = rgbtgrey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rgbtB = image[i][j].rgbtBlue;
            float rgbtG = image[i][j].rgbtGreen;
            float rgbtR = image[i][j].rgbtRed;

            float sepiaBlue = round((.272 * rgbtR) + (.534 * rgbtG) + (.131 * rgbtB));
            float sepiaGreen = round((.349 * rgbtR) + (.686 * rgbtG) + (.168 * rgbtB));
            float sepiaRed = round((.393 * rgbtR) + (.769 * rgbtG) + (.189 * rgbtB));

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //if corner
            if (i == 0 && j == 0)
            {
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;
                float b9 = temp[i + 1][j + 1].rgbtBlue;

                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;
                float g9 = temp[i + 1][j + 1].rgbtGreen;

                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;
                float r9 = temp[i + 1][j + 1].rgbtRed;

                int promedioBlue = round((b5 + b6 + b8 + b9) / 4);
                int promedioGreen = round((g5 + g6 + g8 + g9) / 4);
                int promedioRed = round((r5 + r6 + r8 + r9) / 4);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i == 0 && j == (width - 1))
            {
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b7 = temp[i + 1][j - 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;

                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g7 = temp[i + 1][j - 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;

                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r7 = temp[i + 1][j - 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;

                int promedioBlue = round((b4 + b5 + b7 + b8) / 4);
                int promedioGreen = round((g4 + g5 + g7 + g8) / 4);
                int promedioRed = round((r4 + r5 + r7 + r8) / 4);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i == (height - 1) && j == 0)
            {
                float b2 = temp[i - 1][j].rgbtBlue;
                float b3 = temp[i - 1][j + 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;

                float g2 = temp[i - 1][j].rgbtGreen;
                float g3 = temp[i - 1][j + 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;

                float r2 = temp[i - 1][j].rgbtRed;
                float r3 = temp [i - 1][j + 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;

                int promedioBlue = round((b2 + b3 + b5 + b6) / 4);
                int promedioGreen = round((g2 + g3 + g5 + g6) / 4);
                int promedioRed = round((r2 + r3 + r5 + r6) / 4);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i == (height - 1) && j == (width - 1))
            {
                float b1 = temp[i - 1][j - 1].rgbtBlue;
                float b2 = temp[i - 1][j].rgbtBlue;
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;

                float g1 = temp[i - 1][j - 1].rgbtGreen;
                float g2 = temp[i - 1][j].rgbtGreen;
                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;

                float r1 = temp[i - 1][j - 1].rgbtRed;
                float r2 = temp[i - 1][j].rgbtRed;
                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;

                int promedioBlue = round((b1 + b2 + b4 + b5) / 4);
                int promedioGreen = round((g1 + g2 + g4 + g5) / 4);
                int promedioRed = round((r1 + r2 + r4 + r5) / 4);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }
            // if line
            else if (i == 0 && j > 0 && j < (width - 1))
            {
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;
                float b7 = temp[i + 1][j - 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;
                float b9 = temp[i + 1][j + 1].rgbtBlue;

                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;
                float g7 = temp[i + 1][j - 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;
                float g9 = temp[i + 1][j + 1].rgbtGreen;

                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;
                float r7 = temp[i + 1][j - 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;
                float r9 = temp[i + 1][j + 1].rgbtRed;

                int promedioBlue = round((b4 + b5 + b6 + b7 + b8 + b9) / 6);
                int promedioGreen = round((g4 + g5 + g6 + g7 + g8 + g9) / 6);
                int promedioRed = round((r4 + r5 + r6 + r7 + r8 + r9) / 6);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i == (height - 1) && j > 0 && j < (width - 1))
            {
                float b1 = temp[i - 1][j - 1].rgbtBlue;
                float b2 = temp[i - 1][j].rgbtBlue;
                float b3 = temp[i - 1][j + 1].rgbtBlue;
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;

                float g1 = temp[i - 1][j - 1].rgbtGreen;
                float g2 = temp[i - 1][j].rgbtGreen;
                float g3 = temp[i - 1][j + 1].rgbtGreen;
                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;

                float r1 = temp[i - 1][j - 1].rgbtRed;
                float r2 = temp[i - 1][j].rgbtRed;
                float r3 = temp [i - 1][j + 1].rgbtRed;
                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;

                int promedioBlue = round((b1 + b2 + b3 + b4 + b5 + b6) / 6);
                int promedioGreen = round((g1 + g2 + g3 + g4 + g5 + g6) / 6);
                int promedioRed = round((r1 + r2 + r3 + r4 + r5 + r6) / 6);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i > 0 && i < (height - 1) && j == 0)
            {
                float b2 = temp[i - 1][j].rgbtBlue;
                float b3 = temp[i - 1][j + 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;
                float b9 = temp[i + 1][j + 1].rgbtBlue;

                float g2 = temp[i - 1][j].rgbtGreen;
                float g3 = temp[i - 1][j + 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;
                float g9 = temp[i + 1][j + 1].rgbtGreen;

                float r2 = temp[i - 1][j].rgbtRed;
                float r3 = temp [i - 1][j + 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;
                float r9 = temp[i + 1][j + 1].rgbtRed;

                int promedioBlue = round((b2 + b3 + b5 + b6 + b8 + b9) / 6);
                int promedioGreen = round((g2 + g3 + g5 + g6 + g8 + g9) / 6);
                int promedioRed = round((r2 + r3 + r5 + r6 + r8 + r9) / 6);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }

            else if (i > 0 && i < (height - 1) && j == (width - 1))
            {
                float b1 = temp[i - 1][j - 1].rgbtBlue;
                float b2 = temp[i - 1][j].rgbtBlue;
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b7 = temp[i + 1][j - 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;

                float g1 = temp[i - 1][j - 1].rgbtGreen;
                float g2 = temp[i - 1][j].rgbtGreen;
                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g7 = temp[i + 1][j - 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;


                float r1 = temp[i - 1][j - 1].rgbtRed;
                float r2 = temp[i - 1][j].rgbtRed;
                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r7 = temp[i + 1][j - 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;


                int promedioBlue = round((b1 + b2 + b4 + b5 + b7 + b8) / 6);
                int promedioGreen = round((g1 + g2 + g4 + g5 + g7 + g8) / 6);
                int promedioRed = round((r1 + r2 + r4 + r5 + r7 + r8) / 6);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }
            // else
            else
            {
                float b1 = temp[i - 1][j - 1].rgbtBlue;
                float b2 = temp[i - 1][j].rgbtBlue;
                float b3 = temp[i - 1][j + 1].rgbtBlue;
                float b4 = temp[i][j - 1].rgbtBlue;
                float b5 = temp[i][j].rgbtBlue;
                float b6 = temp[i][j + 1].rgbtBlue;
                float b7 = temp[i + 1][j - 1].rgbtBlue;
                float b8 = temp[i + 1][j].rgbtBlue;
                float b9 = temp[i + 1][j + 1].rgbtBlue;

                float g1 = temp[i - 1][j - 1].rgbtGreen;
                float g2 = temp[i - 1][j].rgbtGreen;
                float g3 = temp[i - 1][j + 1].rgbtGreen;
                float g4 = temp[i][j - 1].rgbtGreen;
                float g5 = temp[i][j].rgbtGreen;
                float g6 = temp[i][j + 1].rgbtGreen;
                float g7 = temp[i + 1][j - 1].rgbtGreen;
                float g8 = temp[i + 1][j].rgbtGreen;
                float g9 = temp[i + 1][j + 1].rgbtGreen;

                float r1 = temp[i - 1][j - 1].rgbtRed;
                float r2 = temp[i - 1][j].rgbtRed;
                float r3 = temp [i - 1][j + 1].rgbtRed;
                float r4 = temp [i][j - 1].rgbtRed;
                float r5 = temp [i][j].rgbtRed;
                float r6 = temp[i][j + 1].rgbtRed;
                float r7 = temp[i + 1][j - 1].rgbtRed;
                float r8 = temp[i + 1][j].rgbtRed;
                float r9 = temp[i + 1][j + 1].rgbtRed;

                int promedioBlue = round((b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9) / 9);
                int promedioGreen = round((g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8 + g9) / 9);
                int promedioRed = round((r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9) / 9);

                image[i][j].rgbtBlue = promedioBlue;
                image[i][j].rgbtGreen = promedioGreen;
                image[i][j].rgbtRed = promedioRed;
            }
        }
    }
    return;
}
