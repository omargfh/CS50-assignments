#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLUR 3
#define AXES 2
#define SCOPE_EDGE 3

typedef struct
{
    double red;
    double green;
    double blue;
}
RGBDOUBLE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double grayscale_value = round((double)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = grayscale_value;
            image[i][j].rgbtGreen = grayscale_value;
            image[i][j].rgbtRed = grayscale_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int row_size = sizeof(image[height]);
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE *row = malloc(row_size);
        for (int j = 0; j < width; j++)
        {
            row[j] = image[i][j];
        }
        for (int j = width - 1; j >= 0; j--)
        {
            image[i][width - (j + 1)] = row[j];
        }
        free(row);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    double average_blue, average_green, average_red;
    int stat;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_blue = average_green = average_red = stat = 0;
            // Box Blur
            for (int rows = i - ((BLUR - 1) / 2); rows <= i + ((BLUR - 1) / 2); rows++)
            {
                for (int cols = j - ((BLUR - 1) / 2); cols <= j + ((BLUR - 1) / 2); cols++)
                {
                    if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                    {
                        average_blue += image[rows][cols].rgbtBlue;
                        average_green += image[rows][cols].rgbtGreen;
                        average_red += image[rows][cols].rgbtRed;
                        stat++;
                    }
                }
            }
            if (stat != 0)
            {
                average_blue =  round(average_blue / (double) stat);
                average_green = round(average_green / (double) stat);
                average_red = round(average_red / (double) stat);
                new_image[i][j].rgbtBlue = average_blue;
                new_image[i][j].rgbtGreen = average_green;
                new_image[i][j].rgbtRed = average_red;
            }
            else
            {
                return;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    int detector[AXES][SCOPE_EDGE * SCOPE_EDGE] =
    {
        {-1, 0, 1, -2, 0, 2, -1, 0, 1},
        {-1, -2, -1, 0, 0, 0, 1, 2, 1}
    };
    // Declare tracking value, Gx, and Gy
    RGBDOUBLE G_val[AXES + 1];
    // Loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize Gx and Gy as zero (and tracker)
            for (int axis = 0; axis < AXES + 1; axis++)
            {
                G_val[axis].red = 0;
                G_val[axis].green = 0;
                G_val[axis].blue = 0;
            }
            // Loop over array "detector"
            for (int axis = 0; axis < AXES; axis++)
            {
                int cell = 0;
                for (int rows = i - 1; rows <= i + 1; rows++)
                {
                    for (int cols = j - 1; cols <= j + 1; cols++)
                    {
                        // Avoid checking elements out of bounds
                        if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                        {
                            G_val[axis].red += (image[rows][cols].rgbtRed * detector[axis][cell]);
                            G_val[axis].green += (image[rows][cols].rgbtGreen * detector[axis][cell]);
                            G_val[axis].blue += (image[rows][cols].rgbtBlue * detector[axis][cell]);
                        }
                        cell++;
                    }
                }
            }
            // Solber Filter Algorithim
            G_val[AXES].red = round(sqrt((pow(G_val[0].red, 2)
                                          + pow(G_val[1].red, 2))));
            G_val[AXES].green = round(sqrt((pow(G_val[0].green, 2)
                                            + pow(G_val[1].green, 2))));
            G_val[AXES].blue = round(sqrt((pow(G_val[0].blue, 2)
                                           + pow(G_val[1].blue, 2))));
            // Change pixel
            new_image[i][j].rgbtRed = G_val[AXES].red <= 255 ? (BYTE) G_val[AXES].red : (BYTE) 255;
            new_image[i][j].rgbtGreen = G_val[AXES].green <= 255 ? (BYTE) G_val[AXES].green : (BYTE) 255;
            new_image[i][j].rgbtBlue = G_val[AXES].blue <= 255 ? (BYTE) G_val[AXES].blue : (BYTE) 255;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
