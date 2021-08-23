#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            int avgr = roundf(avg);

            image[i][j].rgbtRed = avgr;
            image[i][j].rgbtGreen = avgr;
            image[i][j].rgbtBlue = avgr;
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
            //get sapias
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            //round
            int sR = roundf(sepiaRed);

            if (sR > 255)
            {
                sR = 255;
            }

            int sG = roundf(sepiaGreen);

            if (sG > 255)
            {
                sG = 255;
            }

            int sB = roundf(sepiaBlue);

            if (sB > 255)
            {
                sB = 255;
            }

            image[i][j].rgbtRed = sR;
            image[i][j].rgbtBlue = sB;
            image[i][j].rgbtGreen = sG;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int halfW = round((float)1 / 2 * width);
        for (int j = 0; j < width; j++)
        {
            while (j < halfW)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = temp;

                break;
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    //create a new copied file
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    
    //iterate through temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_blue = 0;
            int sum_green = 0;
            int divider = 0;

            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    //if pixel is outside the image (column)
                    if (i + h < 0 || i + h > (height - 1))
                    {
                        continue; //skip
                    }                    //if pixel is outside the image (row)
                    if (j + w  < 0 || j + w > (width - 1))
                    {
                        continue; //skip
                    }                                        
                    
                    //sum up the values of all the pixels
                    
                    sum_blue += temp[i + h][j + w].rgbtBlue;
                    sum_red += temp[i + h][j + w].rgbtRed;
                    sum_green += temp[i + h][j + w].rgbtGreen;
                    divider++;
                }
            }
            //copy over the pixels
            image[i][j].rgbtRed = round((float) sum_red / divider);
            image[i][j].rgbtBlue = round((float) sum_blue / divider);
            image[i][j].rgbtGreen = round((float) sum_green / divider);
        }
        
    }
    return;
}
