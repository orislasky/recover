#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
   // typedef uint8_t  BYTE;
    //BYTE buffer;
    unsigned char buffer[512];
    char filename[7];
    FILE *img;

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

     // remember filenames
    ;
    char *infile = argv[1];
    int found=0;
    int filenumber=0;

    // open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open -  %s.\n", infile);
        return 2;
    }

    sprintf(filename , "%03i.jpg", 2);
    img = fopen (filename,"w");
    while (fread (buffer,1,512,inptr))
    {
     if ((buffer[0] == 0xff) && (buffer[1]==0xd8) && (buffer[2]==0xff) && ((buffer[3] & 0xf0) == 0xe0))
     {
         if (found==1)
         {
             fclose(img);
             filenumber++;
             found=0;
         }
         sprintf(filename , "%03i.jpg", filenumber);
         img = fopen (filename,"w");
         found=1;
     }
     fwrite (&buffer, 1, 512,img);
    }

}
