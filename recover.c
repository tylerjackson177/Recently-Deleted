#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    bool found_jpeg = false;
    int counter = 0;
    uint8_t buffer[512];
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, 512, card))
    {
        // Check if the start of a new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (found_jpeg)
            {
                // Close the previous JPEG file
                fclose(img);
            }

            // Start a new JPEG file
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output JPEG file.\n");
                fclose(card);
                return 1;
            }
            counter++;
            found_jpeg = true;
        }

        // If a JPEG file is open, write to it
        if (found_jpeg)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining files
    fclose(card);
    if (img != NULL)
    {
        fclose(img);
    }

    return 0;
}
