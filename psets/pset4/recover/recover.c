#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

//New datatype for a byte of data.
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Checks whether the number of command line arguments is correct.
    if (argc != 2)
    {
        printf("Usage: ./recover.\n");
        return 1;
    }

    //Opening card.raw for reading.
    FILE *ptr = fopen(argv[1], "r");

    //Checking whether pointer obtained is valid and useable.
    if (ptr == NULL)
    {
        printf("Unable to open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    int image_counter = 0;
    FILE *img = NULL;
    char filename[8];

    //Looping through card.raw in 512 byte chunks.
    while (fread(buffer, sizeof(BYTE), 512, ptr) == 512)
    {
        //If this is the start of a new jpg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If this is the first jpeg.
            if (image_counter == 0)
            {
                sprintf(filename, "%03i.jpg", image_counter);
                image_counter++;

                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            //If not first jpeg.
            else
            {
                fclose(img);

                sprintf(filename, "%03i.jpg", image_counter);
                image_counter++;

                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
        //If not new jpeg.
        else if (image_counter > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    //Closing any open files.
    fclose(img);
    fclose(ptr);
}