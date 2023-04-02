#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //This line averages out all thre colors to get one value.
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width / 2;

    //Loops through midway and swaps the pixels at the end with the one we are on.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
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
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            float counter = 0;

            //This nested for loop loops through the 3x3 grid around each pixel.
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    //This conditional ensures only valid pixels are added and no values outside the image are taken.
                    if (!(i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1))
                    {
                        sumRed += image[i + k][j + l].rgbtRed;
                        sumGreen += image[i + k][j + l].rgbtGreen;
                        sumBlue += image[i + k][j + l].rgbtBlue;
                        counter++;
                    }
                }
            }

            temp[i][j].rgbtRed = round(sumRed / counter);
            temp[i][j].rgbtGreen = round(sumGreen / counter);
            temp[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }

    //This replaces the original images with the temp 2D array we created.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0, gxGreen = 0, gxBlue = 0;
            float gyRed = 0, gyGreen = 0, gyBlue = 0;

            //This nested for loop loops through the 3x3 grid around each pixel.
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    //This conditional ensures only valid pixels are added and no values outside the image are taken.
                    if (!(i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1))
                    {
                        gxRed += (gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed);
                        gxGreen += (gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen);
                        gxBlue += (gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue);
                        gyRed += (gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed);
                        gyGreen += (gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen);
                        gyBlue += (gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue);
                    }
                }
            }

            int gxyRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int gxyGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int gxyBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            //This code checks whether the values of the channels are above 255 or not.
            //This is for red.
            if (gxyRed > 255)
            {
                temp[i][j].rgbtRed = 255;
            }
            else
            {
                temp[i][j].rgbtRed = gxyRed;
            }

            //This is for green.
            if (gxyGreen > 255)
            {
                temp[i][j].rgbtGreen = 255;
            }
            else
            {
                temp[i][j].rgbtGreen = gxyGreen;
            }

            //This is for blue.
            if (gxyBlue > 255)
            {
                temp[i][j].rgbtBlue = 255;
            }
            else
            {
                temp[i][j].rgbtBlue = gxyBlue;
            }
        }
    }

    //This replaces the original images with the temp 2D array we created.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
