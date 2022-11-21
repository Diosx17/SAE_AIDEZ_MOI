#include "fonctionImage.h"

void GrayScale(FILE *fIn, FILE *fOut)
{
    unsigned char header[54]; // Header de l'image en 24 bits
    fread(header, sizeof(unsigned char), 54, fIn); // Lecture de l'header sur l'image ouvertre
    fwrite(header, sizeof(unsigned char), 54, fOut); // Ecriture de l'header sur l'image resultat

    int width = *(int*)&header[18]; // La longueur de l'image se trouvant a cet élément du tableau header
    int height = abs(*(int*)&header[22]); // La hauteut de l'image se trouvant a cet élément du tableau header
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    unsigned char pixel[3];
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel, 3, 1, fIn);
            unsigned char gray = pixel[0] * 0.2125 + pixel[1] * 0.7154 + pixel[2] * 0.0721;
            memset(pixel, gray, sizeof(pixel));
            fwrite(&pixel, 3, 1, fOut);
        }
        fread(pixel, padding, 1, fIn);
        fwrite(pixel, padding, 1, fOut);
    }
}

void Invert(FILE *fIn, FILE *fOut)
{
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]);
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    unsigned char pixel[3];
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel, 3, 1, fIn);

            pixel[0] = 255-pixel[0];pixel[1]=255-pixel[1];pixel[2]=255-pixel[2];

            fwrite(&pixel, 3, 1, fOut);
        }
        fread(pixel, padding, 1, fIn);
        fwrite(pixel, padding, 1, fOut);
    }
}

void Mono(FILE *fIn, FILE *fOut)
{
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]);
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    unsigned char pixel[3];
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel, 3, 1, fIn);

            if(((pixel[0]+pixel[1]+pixel[2])/3) <= 128){pixel[0] = 0, pixel[1] = 0, pixel[2] = 0;}
            else if(((pixel[0]+pixel[1]+pixel[2])/3) >128){pixel[0] = 255, pixel[1] = 255, pixel[2] = 255;}

            fwrite(&pixel, 3, 1, fOut);
        }
        fread(pixel, padding, 1, fIn);
        fwrite(pixel, padding, 1, fOut);
    }

}

void Contours(FILE *fIn, FILE *fOut)
{
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]);
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    unsigned char pixel[3];
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel, 3, 1, fIn);
            unsigned char gray = pixel[0] * 0.2 + pixel[1] * 0.7 + pixel[2] * 0.7;
            memset(pixel, gray, sizeof(pixel));

            if(((pixel[0]+pixel[1]+pixel[2])/3) < 95)
                {
                    pixel[0] = 0;
                    pixel[1] = 0;
                    pixel[2] = 0;
                }
            else
                {
                    pixel[0] = 255;
                    pixel[1] = 255;
                    pixel[2] = 255;
                }

            fwrite(&pixel, 3, 1, fOut);
        }

        fread(pixel, padding, 1, fIn);
        fwrite(pixel, padding, 1, fOut);
    }

}

void Superposition(FILE *fIn, FILE *fIn2, FILE *fOut)
{
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, fIn);
    fwrite(header, sizeof(unsigned char), 54, fOut);

    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]);
    int stride = (width * 3 + 3) & ~3;
    int padding = stride - width * 3;

    unsigned char pixel[3];
    unsigned char pixel2[3];
    unsigned char pixel_moy[3];


    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            fread(pixel,3,1,fIn);
            fread(pixel2,3,1,fIn2);
            unsigned char pixel_moy[3]= {(pixel[0]+pixel2[0])/2 , (pixel[1]+pixel2[1])/2 , (pixel[2]+pixel2[2])/2};


            fwrite(&pixel_moy, 3, 1, fOut);
        }
        fread(pixel, padding, 1, fIn);
        fread(pixel2,padding, 1, fIn2);
        fwrite(pixel, padding, 1, fOut);
    }
}
