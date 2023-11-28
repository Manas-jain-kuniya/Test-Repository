#include <math.h>
#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // average
            // need to convert to 3.0 not 3 for coreect
            image[h][w].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtGreen = image[h][w].rgbtBlue;
            image[h][w].rgbtRed = image[h][w].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        // no need of going ahead else it will change again and no effect atall.
        for (int w = 0; w < width - 1 - w; w++)
        {
            // storing in buffer
            RGBTRIPLE BUFFFER = image[h][w];
            // changing which is stored in buffer
            image[h][w] = image[h][width - 1 - w];
            // setting buffer to the other
            image[h][width - 1 - w] = BUFFFER;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // When implementing the blur function, you might find that blurring one pixel ends
    // up affecting the blur of another pixel. Perhaps create a copy of image

    //copy
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }


    // first need to check whether it is in centre or edge or corner

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // sum and avg
            int rsum = 0;
            int gsum = 0;
            int bsum = 0;
            float n = 0.0;

            // for making the 3 X 3 squre
            int a = h - 1;

            for (int i = 0; i < 3; i++)
            {
                // need to take b inside one of the for to reassign the value after one loop on b.
                int b = w - 1;
                for (int j = 0; j < 3; j++)
                {
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        rsum += copy[a][b].rgbtRed;
                        gsum += copy[a][b].rgbtGreen;
                        bsum += copy[a][b].rgbtBlue;
                        // counting how many to average
                        n++;
                    }
                    b++;
                }
                a++;
            }

            // setting the value
            image[h][w].rgbtRed = round(rsum / n);
            image[h][w].rgbtGreen = round(gsum / n);
            image[h][w].rgbtBlue = round(bsum / n);
        }
    }

    return;
}

// check function declaration
int check (int x);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // box size
    int size = 3;

    // making an copy so change on pixels do not affect the other.
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }


    // declearing the kernel
    int gx[size][size];
    int gy[size][size];

    // setting the values
    gx[0][0] = -1, gx[1][0] = -2, gx[2][0] = -1;
    gx[0][2] = 1,  gx[1][2] = 2, gx[2][2] = 1;

    // middle column
    for (int k = 0; k < size; k++)
    {
        gx[k][1] = 0;
    }

    // transepose for gy
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gy[i][j] = gx[j][i];
        }
    }



    // for each pixel calculation
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // sum
            int gxr = 0, gxg = 0, gxb = 0;
            int gyr = 0, gyg = 0, gyb = 0;

            // for making the 3 X 3 square
            int a = h - 1;

            for (int i = 0; i < size; i++)
            {
                // need to take b inside one of the for to reassign the value after one loop on b.
                int b = w - 1;
                for (int j = 0; j < size; j++)
                {
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        // for red
                        gxr += (gx[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtRed);
                        gyr += (gy[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtRed);

                        // for green
                        gxg += (gx[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtGreen);
                        gyg += (gy[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtGreen);

                        // for blue
                        gxb += (gx[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtBlue);
                        gyb += (gy[(a-(h-1))][(b-(w-1))] * copy[a][b].rgbtBlue);
                    }
                    // else is same as nothing, as if not, then it will add 0
                    b++;
                }
                a++;
            }

            image[h][w].rgbtBlue = check(round(sqrt((gxb ^ 2) +(gyb ^ 2))));
            image[h][w].rgbtGreen = check(round(sqrt((gxg ^ 2) +(gyg ^ 2))));
            image[h][w].rgbtRed = check(round(sqrt((gxr ^ 2) +(gyr ^ 2))));
        }
    }
}

int check (int x)
{
    // taking in as only rgb values will be checked.
    if (x > 255)
    {
        return 225;
    }
    else
    {
        return x;
    }

}
