#include "helpers.h"
#include "math.h"

/*

./filter -g images/yard.bmp outGrayScale.bmp
./filter -s images/tower.bmp outSepia.bmp
./filter -r images/yard.bmp outReflection.bmp
./filter -b images/yard.bmp outBlur.bmp
*/
long double get_average(int sum, float total_num);

void implement_sepia_algorithm(int originalRed, int originalGreen, int originalBlue, long double *sepiaRed, long double *sepiaGreen,
                               long double *sepiaBlue);

/*
take the average of the red, green, and blue values
apply that average[ (R + G + B) / 3 ] to each pixel in the image,

*/
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // current pixel color RGB values
    //int current_r_value, current_g_value, current_b_value, sum;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            long double color_average;
            int sum = 0;
            /*
            current_r_value = image[y][x].rgbtRed;
            current_g_value = image[y][x].rgbtGreen;
            current_b_value = image[y][x].rgbtBlue;
            */
            sum = image[y][x].rgbtRed + image[y][x].rgbtGreen + image[y][x].rgbtBlue;
            //take the average of the red, green, and blue values
            color_average = get_average(sum, (float) 3);

            //apply that average[ (R + G + B) / 3 ] to each pixel in the image,
            image[y][x].rgbtRed = (int) round(color_average);
            image[y][x].rgbtGreen = (int) round(color_average);
            image[y][x].rgbtBlue = (int) round(color_average);
        }
    }
}

/*
 taking each pixel, and computing new red, green, and blue values based on the original
 set each pixel values to the  the original the sepia color values

*/
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            long double sepiaRed, sepiaGreen, sepiaBlue;
            // taking each pixel, and computing new red, green, and blue values based on the original
            implement_sepia_algorithm(image[y][x].rgbtRed, image[y][x].rgbtGreen, image[y][x].rgbtBlue, &sepiaRed, &sepiaGreen, &sepiaBlue);
            //set each pixel values to the  the original the sepia color values
            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue;
        }
    }
}

void implement_sepia_algorithm(int originalRed, int originalGreen, int originalBlue, long double *sepiaRed, long double *sepiaGreen,
                               long double *sepiaBlue)
{
    /*
    Implement sepia algorithm to an image pixel color values
    */

    *sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
    *sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
    *sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

    // verify pixel color range is not greater than 255
    if (*sepiaRed > 255)
    {
        *sepiaRed = 255;
    }
    if (*sepiaGreen > 255)
    {
        *sepiaGreen = 255;
    }
    if (*sepiaBlue > 255)
    {
        *sepiaBlue = 255;
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        //int pixel_inverser = 0;
        for (int x = 0; x < width; x++)
        {
            /*
            image[y][x + i].rgbtRed   =  image[y][width - i].rgbtRed;
            image[y][x + i].rgbtGreen =  image[y][width - i].rgbtGreen;
            image[y][x + i].rgbtBlue  =  image[y][width - i].rgbtBlue;
            */
            // check if the R.H.S pixels and L.H.S pixels has been fully swapped.
            if (x > (width - x) - 1)
            {
                break;
            }
            int tmp_r, tmp_g = 0, tmp_b;

            //temporary value holder for the pixel
            tmp_r = image[y][(width - 1) - x].rgbtRed;
            tmp_g = image[y][(width - 1) - x].rgbtGreen;
            tmp_b = image[y][(width - 1) - x].rgbtBlue;

            // swap LHS pixels to RHS
            image[y][(width - 1) - x].rgbtRed = image[y][x].rgbtRed;
            image[y][(width - 1) - x].rgbtGreen = image[y][x].rgbtGreen;
            image[y][(width - 1) - x].rgbtBlue = image[y][x].rgbtBlue;

            // swap RHS pixels to LHS
            image[y][x].rgbtRed = tmp_r;
            image[y][x].rgbtGreen = tmp_g;
            image[y][x].rgbtBlue = tmp_b;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of the image
    RGBTRIPLE image_copy[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image_copy[y][x].rgbtRed = image[y][x].rgbtRed;
            image_copy[y][x].rgbtGreen = image[y][x].rgbtGreen;
            image_copy[y][x].rgbtBlue = image[y][x].rgbtBlue;
        }
    }

    // looping through orginial image
    for (int y = 0; y < height; y++)
    {
        int pixel_current_height = y;

        for (int x = 0; x < width; x++)
        {

            int total_r = 0, total_g = 0, total_b = 0;
            int total_num_pixels = 0;

            int pixel_current_width = x;

            ///////////////////////////////
            //check upper_height(row) of the pixel
            if (pixel_current_height - 1 >= 0)
            {
                // check if left pixel exist
                if (pixel_current_width - 1 >= 0)
                {
                    total_r += image_copy[pixel_current_height - 1][pixel_current_width - 1].rgbtRed;
                    total_g += image_copy[pixel_current_height - 1][pixel_current_width - 1].rgbtGreen;
                    total_b += image_copy[pixel_current_height - 1][pixel_current_width - 1].rgbtBlue;
                    total_num_pixels++;
                }

                // check if right pixel exist
                if (pixel_current_width + 1 <= width - 1)
                {
                    total_r += image_copy[pixel_current_height - 1][pixel_current_width + 1].rgbtRed;
                    total_g += image_copy[pixel_current_height - 1][pixel_current_width + 1].rgbtGreen;
                    total_b += image_copy[pixel_current_height - 1][pixel_current_width + 1].rgbtBlue;
                    total_num_pixels++;
                }
                // get center pixel height
                total_r += image_copy[pixel_current_height - 1][pixel_current_width + 0].rgbtRed;
                total_g += image_copy[pixel_current_height - 1][pixel_current_width + 0].rgbtGreen;
                total_b += image_copy[pixel_current_height - 1][pixel_current_width + 0].rgbtBlue;
                total_num_pixels++;
            }
            ////////////////////////////////////////
            //check lower_height(row) of the pixel
            if (pixel_current_height + 1 <= height - 1)
            {
                // check if left pixel exist
                if (pixel_current_width - 1 >= 0)
                {

                    total_r += image_copy[pixel_current_height + 1][pixel_current_width - 1].rgbtRed;
                    total_g += image_copy[pixel_current_height + 1][pixel_current_width - 1].rgbtGreen;
                    total_b += image_copy[pixel_current_height + 1][pixel_current_width - 1].rgbtBlue;
                    total_num_pixels++;
                }
                // check if right pixel exist
                if (pixel_current_width + 1 <= width - 1)
                {
                    total_r += image_copy[pixel_current_height + 1][pixel_current_width + 1].rgbtRed;
                    total_g += image_copy[pixel_current_height + 1][pixel_current_width + 1].rgbtGreen;
                    total_b += image_copy[pixel_current_height + 1][pixel_current_width + 1].rgbtBlue;
                    total_num_pixels++;
                }
                //get pixel_values
                // get center pixel height
                total_r += image_copy[pixel_current_height + 1][pixel_current_width + 0].rgbtRed;
                total_g += image_copy[pixel_current_height + 1][pixel_current_width + 0].rgbtGreen;
                total_b += image_copy[pixel_current_height + 1][pixel_current_width + 0].rgbtBlue;
                total_num_pixels++;

                // blur orginial pixel

            }
            ////////////////////////////////////

            // check current_height(row) of the pixel

            // check if left pixel exist
            if (pixel_current_width - 1 >= 0)

            {

                total_r += image_copy[pixel_current_height + 0][pixel_current_width - 1].rgbtRed;
                total_g += image_copy[pixel_current_height + 0][pixel_current_width - 1].rgbtGreen;
                total_b += image_copy[pixel_current_height + 0][pixel_current_width - 1].rgbtBlue;
                total_num_pixels++;
            }

            // check if right pixel exist
            if (pixel_current_width + 1 <= width - 1)

            {

                total_r += image_copy[pixel_current_height - 0][pixel_current_width + 1].rgbtRed;
                total_g += image_copy[pixel_current_height - 0][pixel_current_width + 1].rgbtGreen;
                total_b += image_copy[pixel_current_height - 0][pixel_current_width + 1].rgbtBlue;
                total_num_pixels++;
            }

            //get center_pixel_value
            total_r += image_copy[pixel_current_height + 0][pixel_current_width + 0].rgbtRed;
            total_g += image_copy[pixel_current_height + 0][pixel_current_width + 0].rgbtGreen;
            total_b += image_copy[pixel_current_height + 0][pixel_current_width + 0].rgbtBlue;
            total_num_pixels++;

            // blur orginial pixel
            image[pixel_current_height][pixel_current_width].rgbtGreen = (int) round((total_g) / (float) total_num_pixels);
            image[pixel_current_height][pixel_current_width].rgbtRed = (int) round((total_r) / (float) total_num_pixels);
            image[pixel_current_height][pixel_current_width].rgbtBlue = (int) round((total_b) / (float) total_num_pixels);
        }
    }
}

long double get_average(int sum, float total_num)
{
    return (sum / total_num);
}
