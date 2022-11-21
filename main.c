#include "fonctionImage.h"

int demandes_lineaire(char*, int*, char*, char*);
FILE * ouverture_fichier(char*, char*, char*);
int commandes(char* , int*, char*, char*);

int main(int argc, char *argv[])
{
    char * repertoire = malloc(350);
    int operation = -1; // numéro de l'opération à effectuer (init à -1)
    char * NomF1 = malloc(50); // nom du fichier source 1
    char * NomF2 = malloc(50); // nom du fichier source 2

    int errorValue = 0;

    switch(argc){
        //Executable
        case 1:
            demandes_lineaire(repertoire, &operation, NomF1, NomF2);
            errorValue = commandes(repertoire, &operation, NomF1, NomF2);
            break;
        //PRECEDENT + premier fichier bmp
        case 4:
            repertoire = strcat(argv[1],"/");
            operation = atoi(argv[2]);
            NomF1 = strcat(argv[3],".bmp");
            errorValue = commandes(repertoire, &operation, NomF1, NomF2);
            break;
        //PRECEDENT + second fichier bmp
        case 5:
            operation = atoi(argv[2]);
            if(operation==5){
                repertoire = strcat(argv[1],"/");

                strcpy(NomF1, argv[3]);
                NomF1 = strcat(NomF1, ".bmp");

                strcpy(NomF2, argv[4]);
                NomF2 = strcat(NomF2, ".bmp");
                errorValue = commandes(repertoire, &operation, NomF1, NomF2);
                break;
            }
        //RIEN TROUVE
        default : printf("Traitement impossible\n");
                  errorValue = -1;
    }

    free(repertoire);
    free(NomF1);
    free(NomF2);

    if(errorValue){
        printf("erreur type : %d", errorValue);
    }
    else{
        printf("Le traitement de l'image s'est bien deroule");
    }

    return errorValue;
}

int demandes_lineaire(char * repertoire, int * operation, char* NomF1, char* NomF2){

    //DEMANDE REPERTOIRE
    printf("Rentrer le chemin (ex -> C: ou C:/.../dossier) : ");
    gets(repertoire); //AJOUT repertoire de travail

    repertoire = strcat(repertoire,"/");

    //DEMANDE OPERATION SUR IMAGE
    printf("1 : Image en niveaux de gris\n");// affichage des différentes opérations
    printf("2 : Image en couleurs inversees\n");
    printf("3 : Image monochrome\n");
    printf("4 : Extraction des contours\n");
    printf("5 : Superposition de 2 images\n");
    printf("\nRentrez le numero du traitement : ");

        //prise de l'opération
    scanf("%d",operation); // récupération du numéro de l'opération

        //saut de ligne
    printf("\n");

    //DEMANDE FICHIER 1
    printf("Nom premier fichier : ");
    scanf("%s", NomF1); // récupération nom fichier 1
    strcat(NomF1,".bmp"); // AJOUT extension

    //DEMANDE FICHIER 2 SI OPERATION = (SUPERPOSITION - 1)
    if(*operation==5) // Si l'operation est la superposition on met demande le nom du fichier
    {
        printf("Nom second fichier : ");
        scanf("%s", NomF2); // récupération nom fichier 2
        strcat(NomF2, ".bmp"); // AJOUT extension
    }

    return 0;
}

FILE * ouverture_fichier(char* repertoire, char* NomF, char* option){
    FILE * fFile = fopen(strcat(repertoire,NomF),option);
    return fFile;
}

int commandes(char * repertoire, int * operation, char* NomF1, char* NomF2){

    char * repertoire_tampon = malloc(350);
    strcpy(repertoire_tampon, repertoire);
    FILE * fIn1 = ouverture_fichier(repertoire_tampon, NomF1, "rb");

    strcpy(repertoire_tampon, repertoire);
    FILE * fIn2 = ouverture_fichier(repertoire_tampon, NomF2, "rb");

    strcpy(repertoire_tampon, repertoire);
    FILE * fOut = ouverture_fichier(repertoire_tampon, "result.bmp", "wb");
    free(repertoire_tampon);

    if(fIn1){
        if(fOut){
            switch(*operation){
                case 1: GrayScale(fIn1, fOut);
                        return 0;
                        break;
                case 2: Invert(fIn1, fOut);
                        return 0;
                        break;
                case 3: Mono(fIn1, fOut);
                        return 0;
                        break;
                case 4: Contours(fIn1, fOut);
                        return 0;
                        break;
                case 5: if(NomF2){
                            Superposition(fIn1, fIn2, fOut);
                            return 0;
                            break;
                        }
                default:printf("Traitement impossible\n");
                        return -1;
                        break;
            }
        }else{
            printf("Le fichier de résultat ne peut etre créé\n");
            return -3;
        }

    }else{
        printf("Un (ou plusieurs) fichier(s) n'existe(nt) pas\n");
        return -2;
    }
}
