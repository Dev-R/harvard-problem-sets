#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>





int main(int argc, char *argv[])
{
    // remind user of correct usage
    
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //pointer to the image file
    FILE *IMAGE_FILE = fopen(argv[1], "r");
    //FILE * IMAGE_FILE = fopen("card.raw", "r");
    // check if the file not corrupt
    if (IMAGE_FILE == NULL)
    {
        printf("Error, cannot open file");
        return 1;
    }
    // file name is made of 3
    //char * file_name = malloc(sizeof(char) * 3);
    // tmp storage for the images;
    uint8_t *buffer = malloc(sizeof(uint8_t) * 512);
    FILE *TEMP_IMG = NULL;
    // looping through the file
    int file_name_counter = 0;
    char *temp_file_name = malloc(sizeof(char) * 3);
    while (fread(buffer, 512, 1, IMAGE_FILE) == 1)
    {
        // check for a jpg header
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (file_name_counter == 0)
            {
                // create file name
                sprintf(temp_file_name, "%03i.jpg", file_name_counter);
                // create a file with file name
                TEMP_IMG = fopen(temp_file_name, "w");
                fwrite(buffer, 512, 1, TEMP_IMG);
                file_name_counter++;
                //free(temp_file_name);
            }
            else
            {
                fclose(TEMP_IMG);
                // create file name
                sprintf(temp_file_name, "%03i.jpg", file_name_counter);
                // create file with file name
                TEMP_IMG = fopen(temp_file_name, "w");
                //write data on the file
                fwrite(buffer, 512, 1, TEMP_IMG);
                file_name_counter++;
                //free(temp_file_name);
            }

        }
        else if (file_name_counter  > 0)
        {
            fwrite(buffer, 512, 1, TEMP_IMG);
            
        }
    }
    // free memory
    free(buffer);
    free(temp_file_name);
}
    
    