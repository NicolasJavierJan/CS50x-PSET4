#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ask for forensic image

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open file

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Error.\n");
        return 2;
    }

    // read 512 byte chunks and check jpeg header

    FILE *img = NULL;
    char filename[8];
    unsigned char buffer[512];
    int counter = 0;

    while (fread(buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }
        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
        if (img == NULL)
        {
            continue;
        }
    }

}
