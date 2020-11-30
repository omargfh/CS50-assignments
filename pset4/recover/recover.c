#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check arguments
    if (argc < 2)
    {
        fprintf(stderr, "Missing argument [filename]. Terminate...\n");
        return 1;
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Usage: recover [filename]. Terminate...\n");
        return 1;
    }

    // Load file
    char *file = argv[1];
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "File failed to load into memory. Terminate...\n");
        return 1;
    }

    // Find file size
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    long blocks = size / 512;
    fseek(fptr, 0, SEEK_SET);

    // Read file into array
    BYTE(*image)[512] = calloc(blocks, 512);
    for (int i = 0; i < blocks; i++)
    {
        fread(image[i], 1, 512, fptr);
    }

    // Loop through blocks
    int status = 0;
    int n_img = 0;
    char img_name[10] = "000.jpg";
    for (int i = 0; i < blocks; i++)
    {
        FILE *img = fopen(img_name, "a");
        if (image[i][0] == 255 && image[i][1] == 216 && image [i][2] == 255)
        {
            if (image[i][3] >= 224 && image[i][3] <= 239)
            {
                if (status > 0)
                {
                    n_img++;
                    n_img < 10 ? sprintf(img_name, "00%d.jpg", n_img) : sprintf(img_name, "0%d.jpg", n_img);
                    fclose(img);
                    img = fopen(img_name, "a");
                }
                fwrite(image[i], 1, 512, img);
                status++;
            }
        }
        else
        {
            if (status != 0)
            {
                fwrite(image[i], 1, 512, img);
            }
        }
        fclose(img);
    }
}