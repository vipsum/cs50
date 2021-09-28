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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int inverso = width - 1 - j;
            int tmp[3] = {image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed};
            image[i][j].rgbtBlue = image[i][inverso].rgbtBlue;
            image[i][j].rgbtGreen = image[i][inverso].rgbtGreen;
            image[i][j].rgbtRed = image[i][inverso].rgbtRed;

            image[i][inverso].rgbtBlue = tmp[0];
            image[i][inverso].rgbtGreen = tmp[1];
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
            //para ver donde empieza e el ejeY tenes que ir arriba y para ver donde termina ver para abajo
            // si estas en la posicion 0 del ejey y le restas 1 te va a dar  1 xq estas fuera de la imagen
            // entonces tenes que ver si el ejey es mayor a -1

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //definimos una imagen vacia con el mismo tamaño de la imagen de input
    RGBTRIPLE originalImage[height][width];
    //copiamos cada pixel de la imagen del input a la imagen vacia (originalimage)
    for (int ejeY = 0; ejeY < height; ejeY++)
    {
        for (int ejeX = 0; ejeX < width; ejeX++)
        {
            originalImage[ejeY][ejeX] = image[ejeY][ejeX];
        }
    }
    //definimos el array GX
    int Xmatrix[3][3] = {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
    //definimos el array GY kernel
    int Ymatrix[3][3] = {{-1, -2, -1},
                         {0, 0, 0},
                         {1, 2, 1}};
    //iteramos la posicion en Y de la imagen
    for (int ejeY = 0; ejeY < height; ejeY++)
    { //iteramos la posicion en X de la imagen
        for (int ejeX = 0; ejeX < width; ejeX++)
        { //definimos variables para guardar la sumatoria de las multiplicaciones correspondientes al algortimo
            float Xred = 0;
            float Xgreen = 0;
            float Xblue = 0;

            float Yred = 0;
            float Ygreen = 0;
            float Yblue = 0;
            //iteramos la posicion en Y de los pixeles al rededor del pixel actual (ejeY, ejeX)
            for (int ejeYPegadito = -1; ejeYPegadito <= 1; ejeYPegadito++)
            {
                //iteramos la posicion en X de los pixeles al rededor del pixel actual (ejeY, ejeX)
                for (int ejeXPegadito = -1; ejeXPegadito <= 1; ejeXPegadito++)
                {
                    //chequear si el pixel actual existe, si no vale 0
                    if (ejeY + ejeYPegadito < 0 || ejeY + ejeYPegadito >= height)
                    {
                        continue;
                    }
                    if (ejeX + ejeXPegadito < 0 || ejeX + ejeXPegadito >= width)
                    {
                        continue;
                    }

                    //multiplicamos cada clor del pixel por el valor correspondiente de su matriz y lo sumamos a la variable
                    //que contiene sus sumas.
                    Xred += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtRed * Xmatrix[ejeYPegadito + 1][ejeXPegadito + 1];
                    Xgreen += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtGreen * Xmatrix[ejeYPegadito + 1][ejeXPegadito + 1];
                    Xblue += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtBlue * Xmatrix[ejeYPegadito + 1][ejeXPegadito + 1];

                    Yred += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtRed * Ymatrix[ejeYPegadito + 1][ejeXPegadito + 1];
                    Ygreen += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtGreen * Ymatrix[ejeYPegadito + 1][ejeXPegadito + 1];
                    Yblue += originalImage[ejeY + ejeYPegadito][ejeX + ejeXPegadito].rgbtBlue * Ymatrix[ejeYPegadito + 1][ejeXPegadito + 1];
                }
            }
            //asignacion de colores
            int red = round(sqrt(Xred * Xred + Yred * Yred));
            if (red > 255)
            {
                red = 255;
            }
            int green = round(sqrt(Xgreen * Xgreen + Ygreen * Ygreen));
            if (green > 255)
            {
                green = 255;
            }
            int blue = round(sqrt(Xblue * Xblue + Yblue * Yblue));
            if (blue > 255)
            {
                blue = 255;
            }

            image[ejeY][ejeX].rgbtRed = red;
            image[ejeY][ejeX].rgbtGreen = green;
            image[ejeY][ejeX].rgbtBlue = blue;
        }
    }
    return;
}
