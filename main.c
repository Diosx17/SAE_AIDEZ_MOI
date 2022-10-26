#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GrayScale(FILE * , FILE *);
void Invert(FILE *, FILE *);
void Mono(FILE *, FILE *);
void Contours(FILE *, FILE *);
void Superposition(FILE *, FILE *, FILE *);

int main(int argc, char *argv[])
{
    FILE *fIn;
    FILE *fIn2;
    FILE *fOut;
    char repertoire[100];
    char NomF1[100];
    char NomF2[100]="";
    char temp[100];
    int operation = -1;
    char double_quote_path[100] = "\x22";


    if(argv[1])
    {
        operation = atoi(argv[2])-1; // r�cuperer op�ration si elle est pass�e en argument

    }

    switch (argc) // On teste le nombre d'arguments rentr�s pendant l'execution
    {

        case 1: // Cas ou il n'y a aucun autre argument que l'executable en lui meme : ouvrir menu texte ou saisir le path du repertoire de travail, numero traitement, nom fichier, nom eventuel 2eme fichier si argv[] = 4
            printf("Rentrez le chemin du repertoire de travail sans antislash a la fin et sans double quote : ");
            gets(repertoire);
            printf("\n");
            strcat(double_quote_path,repertoire);

            puts(double_quote_path);
            printf("1 : Image en niveaux de gris\n");
            printf("2 : Image en couleurs inversees\n");
            printf("3 : Image monochrome\n");
            printf("4 : Extraction des contours\n");
            printf("5 : Superposition de 2 images\n");
            printf("Rentrez le num�ro du traitement : ");
            scanf("%d",&operation);
            operation--;
            printf("\n");
            printf("Rentrez le nom du fichier avec extension : ");
            scanf("%s",NomF1);

            printf("\n");
            if(operation==4) // Si l'operation est la superposition on met demande le nom du fichier
            {
                printf("Rentrez le nom du 2eme fichier avec extension : ");
                scanf("%s",NomF2);
                printf("\n");
            }
            strcpy(temp,double_quote_path);

            strcat(double_quote_path,"/");

            strcat(double_quote_path,NomF1);

            strcat(double_quote_path,"\x22");
            fIn = fopen(double_quote_path,"rb"); // Pour retrouver sur le repertoire on le concatene avec le nom du fichier pour le trouver
            puts(double_quote_path);
            if(NomF2!=NULL)
            {
                strcpy(double_quote_path,temp);
                strcat(double_quote_path,"/\x22");
                fIn2 = fopen(strcat(double_quote_path,NomF2),"rb"); // Meme chose qu'en haut
            }
            strcpy(double_quote_path,temp);

            puts(double_quote_path);
            strcat(double_quote_path,"/");
            strcat(double_quote_path,"result.bmp");
            puts(double_quote_path);
            strcat(double_quote_path,"\x22");
            fOut = fopen(double_quote_path,"wb"); // Meme chose mais avec fichier resultat
            puts(double_quote_path);
            printf("Fin : %d\n",!fIn);
            printf("FOut : %d\n",!fOut);
            switch(operation) //  On check l'operation en question
                {
                    case 0: // Niveau de gris
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        GrayScale(fIn,fOut);
                        break;

                    case 1: // Inversion des couleurs
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Invert(fIn,fOut);
                        break;

                    case 2: // Image monochrome
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Mono(fIn,fOut);
                        break;

                    case 3: // Contours de l'image
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Contours(fIn,fOut);
                        break;



                    case 4: // Superposition des deux images
                        if (!fIn || !fOut || !fIn2)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Superposition(fIn,fIn2,fOut);
                        break;

                    default:
                        return -1; //Le traitement n'existe pas
                }
            break;

        case 4: // Cas 2 ou on met les arguments directement dans la fonction (toutes operation sauf superposition)
            switch(operation)
                {
                    case 0: // Niveaux de gris
                        strcpy(temp,argv[1]); // On stocke le path du dossier dans temp

                        fIn  = fopen(strcat(temp,argv[3]), "rb");
                        fOut = fopen(strcat(argv[1],"result.bmp"), "wb");
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        GrayScale(fIn,fOut);
                        break;

                    case 1: // Inversion des couleurs
                        strcpy(temp,argv[1]);


                        fIn  = fopen(strcat(temp,argv[3]), "rb");


                        fOut = fopen(strcat(argv[1],"\\result.bmp"), "wb");
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Invert(fIn,fOut);
                        break;

                    case 2: // Image monochrome
                        strcpy(temp,argv[1]);

                        fIn  = fopen(strcat(temp,argv[3]), "rb");

                        fOut = fopen(strcat(argv[1],"\\result.bmp"), "wb");
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Mono(fIn,fOut);
                        break;

                    case 3: // Contours de l'image
                        strcpy(temp,argv[1]);

                        fIn  = fopen(strcat(temp,argv[3]), "rb");


                        fOut = fopen(strcat(argv[1],"\\result.bmp"), "wb");
                        if (!fIn || !fOut)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Contours(fIn,fOut);
                        break;


                    case 4: // Superpostion des deux images
                        strcpy(temp,argv[1]);

                        fIn  = fopen(strcat(temp,argv[3]), "rb");
                        strcpy(temp,argv[1]);

                        fIn2 = fopen(strcat(temp,argv[4]),"rb");
                        strcpy(temp,argv[1]);

                        fOut = fopen(strcat(argv[1],"\\result.bmp"), "wb");
                        if (!fIn || !fOut || !fIn2)
                            {
                                printf("File error.\n");
                                return 0;
                            }
                        Superposition(fIn,fIn2,fOut);
                        break;


                    default:
                        return -1; //Le traitement n'existe pas
                }
                break;

        case 5: // Cas 3 ou on met les arguments directement dans la fonction donc superposition
            switch(operation)
            {
                case 4:
                    strcpy(temp,argv[1]);

                    fIn  = fopen(strcat(temp,argv[3]), "rb");
                    strcpy(temp,argv[1]);

                    fIn2 = fopen(strcat(temp,argv[4]),"rb");
                    strcpy(temp,argv[1]);

                    fOut = fopen(strcat(argv[1],"\\result.bmp"), "wb");
                    if (!fIn || !fOut || !fIn2)
                        {
                            printf("File error.\n");
                            return 0;
                        }
                    Superposition(fIn,fIn2,fOut);
                    break;


                default:
                    return -1; //Le traitement n'existe pas
                break;
            }
    default:
        break;


    }

}

void GrayScale(FILE *fIn, FILE *fOut)
{
    unsigned char header[54]; // Header de l'image en 24 bits
    fread(header, sizeof(unsigned char), 54, fIn); // Lecture de l'header sur l'image ouvertre
    fwrite(header, sizeof(unsigned char), 54, fOut); // Ecriture de l'header sur l'image resultat

    int width = *(int*)&header[18]; // La longueur de l'image calcul�e par
    int height = abs(*(int*)&header[22]); // La hauteut de l'image calcul�e par
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

