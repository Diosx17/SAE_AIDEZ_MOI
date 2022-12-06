#include "fonctionImage.h"

//OUVERTURE FICHIER
FILE * ouverture_fichier(char* repertoire, char* nomF, char* option){
    FILE * f = fopen(strcat(repertoire, nomF), option);
    return f;
}

int fonctionImage(char* repertoire, int * operation, char* NomF1, char* NomF2){
    char * repertoire_tampon = malloc(350);
    strcpy(repertoire_tampon, repertoire);
    FILE * fIn1 = ouverture_fichier(repertoire_tampon, NomF1, "rb");

    FILE * fIn2 = NULL;

    if(NomF2 != NULL){
        strcpy(repertoire_tampon, repertoire);
        fIn2 = ouverture_fichier(repertoire_tampon, NomF2, "rb");
    }

    if(fIn1){
        unsigned char header[54]; // Header de l'image en 24 bits
        unsigned char header2[54]; // Header de l'image en 24 bits
        fread(header, sizeof(unsigned char), 54, fIn1); // Lecture de l'header
        fread(header2, sizeof(unsigned char), 54, fIn2); //Lecture de l'header du fichier 2

        int width = *(int*)&header[18]; // La longueur de l'image se trouve ici
        int height = abs(*(int*)&header[22]); // La hauteur de l'image se trouve ici
        int stride = (width * 3 + 3) & ~3;
        int padding = stride - width * 3;

        unsigned char imageG[height][width]; //Tableau pour niveau de gris
        unsigned char image[height][width][3]; //Tableau pour les autres opération

        unsigned char pixel[3]; // Lecture pixel fichier 1
        unsigned char pixel2[3]; // Lecture pixel fichier 2

        for(int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x)
            {
                fread(pixel, 3, 1, fIn1);

                if(*operation == 1){
                    //NIVEAU DE GRIS
                    imageG[y][x] = pixel[0] * 0.2125 + pixel[1] * 0.7154 + pixel[2] * 0.0721;
                }
                else if (*operation == 2){
                    //INVERSION
                    image[y][x][0] = 255-pixel[0];
                    image[y][x][1] = 255-pixel[1];
                    image[y][x][2] = 255-pixel[2];
                }
                else if(*operation == 3){
                    //MONOCHROME
                    if(((pixel[0]+pixel[1]+pixel[2])/3) <= 128)
                    {
                        image[y][x][0] = 0;
                        image[y][x][1] = 0;
                        image[y][x][2] = 0;
                    }
                    else if(((pixel[0]+pixel[1]+pixel[2])/3) >128)
                    {
                        image[y][x][0] = 255;
                        image[y][x][1] = 255;
                        image[y][x][2] = 255;
                    }
                }
                else if(*operation == 4){
                    //CONTOURS
                    unsigned char gray = pixel[0] * 0.2 + pixel[1] * 0.7 + pixel[2] * 0.7;
                    memset(pixel, gray, sizeof(pixel));

                    if(((pixel[0]+pixel[1]+pixel[2])/3) < 95)
                    {
                        image[y][x][0] = 0;
                        image[y][x][1] = 0;
                        image[y][x][2] = 0;
                    }
                    else if(((pixel[0]+pixel[1]+pixel[2])/3) >=95)
                    {
                        image[y][x][0] = 255;
                        image[y][x][1] = 255;
                        image[y][x][2] = 255;

                    }


                }
                else if (*operation == 5){
                    //FUSION
                    if(fIn2){
                        fread(pixel2,3,1,fIn2);
                        image[y][x][0] = (pixel[0]+pixel2[0])/2;
                        image[y][x][1] = (pixel[1]+pixel2[1])/2;
                        image[y][x][2] = (pixel[2]+pixel2[2])/2;
                    }
                    else{
                        printf("%s", NomF2);
                        return -5;
                    }

                }
                else{
                    return -3;
                }
            }
            fread(pixel2, padding, 1, fIn2);
            fread(pixel, padding, 1, fIn1);

        }

        //On ferme les fichiers
        fclose(fIn1);
        fclose(fIn2);

        strcpy(repertoire_tampon, repertoire);
        FILE * fOut = ouverture_fichier(repertoire_tampon, "result.bmp", "wb");
        free(repertoire_tampon);

        if(fOut){
            fwrite(header, sizeof(unsigned char), 54, fOut);

            for(int y = 0; y < height; ++y){
                for (int x = 0; x < width; ++x)
                {
                    if(*operation == 1){
                        fwrite(&imageG[y][x], 3, 1, fOut);
                    }

                    else{
                        for(int pix = 0; pix < 3; pix++){
                            fwrite(&image[y][x][pix], 1, 1, fOut);
                        }
                    }
                }
                fwrite(pixel, padding, 1, fOut);
            }

            fclose(fOut);
        }
        else{
            return -2;
        }
    }
    else{
        printf("%s", NomF1);
        return -1;
    }

    return 0;
}
