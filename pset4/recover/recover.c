#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argumentCount, char *argumentList[])
{
    typedef uint8_t BYTE;

    // Ensure proper usage
    if (argumentCount != 2)
    {
        printf("Usage: ./recover infile");
        return 1;
    }
    // Remember filenames
    char *infile = argumentList[1];

    FILE *inputfile = fopen(infile, "r");
    if (inputfile == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    BYTE buffer[512];
    int counter = 0;
    char filename[8];
    FILE *img;
    while (fread(buffer, sizeof(BYTE), 512, inputfile) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, img);
            counter++;
        }
        else
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    fclose(inputfile);
}