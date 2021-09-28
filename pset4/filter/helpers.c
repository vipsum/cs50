#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float promedio = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            int average = round(promedio);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
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
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            int inverso = width - 1 - j;
            int tmp[3] = {image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed};
            image[i][j].rgbtBlue = image[i][inverso].rgbtBlue;
            image[i][j].rgbtGreen = image[i][inverso].rgbtGreen;
            image[i][j].rgbtRed = image[i][inverso].rgbtRed;

            image[i][inverso].rgbtBlue = tmp[0];
            image[i][inverso].rgbtGreen= tmp[1];
            image[i][inverso].rgbtRed = tmp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];
    for (int ejeY = 0; ejeY < height; ejeY++)
    {
        for (int ejeX = 0; ejeX < width; ejeX++)
        {
            originalImage[ejeY][ejeX] = image[ejeY][ejeX];
        }
    }

    for (int ejeY = 0; ejeY < height; ejeY++)
    {
        for (int ejeX = 0; ejeX < width; ejeX++)
        {
            float redSumatory = 0;
            float greenSumatory = 0;
            float blueSumatory = 0;
            int pixelCounter = 0;

            int yInicial;
            if (ejeY - 1 >= 0)
            {
                yInicial = ejeY - 1;
            }
            else
            {
                yInicial = ejeY;
            }
            int yFinal;
            if (ejeY + 1 < height)
            {
                yFinal = ejeY + 1;
            }
            else
            {
                yFinal = ejeY;
            }

            for (int ejeYPegadito = yInicial; ejeYPegadito <= yFinal; ejeYPegadito++)
            {
                int xInicial;
                if (ejeX - 1 >= 0)
                {
                    xInicial = ejeX - 1;
                }
                else
                {
                    xInicial = ejeX;
                }
                int xFinal;
                if (ejeX + 1 < width)
                {
                    xFinal = ejeX + 1;
                }
                else
                {
                    xFinal = ejeX;
                }
                for (int ejeXPegadito = xInicial; ejeXPegadito <= xFinal; ejeXPegadito++)
                {
                    redSumatory += originalImage[ejeYPegadito][ejeXPegadito].rgbtRed;
                    greenSumatory += originalImage[ejeYPegadito][ejeXPegadito].rgbtGreen;
                    blueSumatory += originalImage[ejeYPegadito][ejeXPegadito].rgbtBlue;
                    pixelCounter++;
                }
            }
            image[ejeY][ejeX].rgbtRed = round(redSumatory / pixelCounter);
            image[ejeY][ejeX].rgbtGreen = round(greenSumatory / pixelCounter);
            image[ejeY][ejeX].rgbtBlue = round(blueSumatory / pixelCounter);
        }
    }
    return;
}
