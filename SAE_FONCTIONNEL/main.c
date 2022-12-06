#include "fonctionImage.h"

int demandes_lineaire(char*, int*, char*, char*);

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
            errorValue = demandes_lineaire(repertoire, &operation, NomF1, NomF2);
            errorValue = fonctionImage(repertoire, &operation, NomF1, NomF2);
            break;
        //PRECEDENT + premier fichier bmp
        case 4:
            repertoire = strcat(argv[1],"/");
            operation = atoi(argv[2]);
            strcpy(NomF1, argv[3]);
            errorValue = fonctionImage(repertoire, &operation, NomF1, NomF2);
            break;
        //PRECEDENT + second fichier bmp
        case 5:
            operation = atoi(argv[2]);
            if(operation==5){
                repertoire = strcat(argv[1],"/");

                strcpy(NomF1, argv[3]);
                strcpy(NomF2, argv[4]);
                errorValue = fonctionImage(repertoire, &operation, NomF1, NomF2);
            }
            else{
                errorValue = -1;
            }
            break;
        //RIEN TROUVE
        default : errorValue = -1;
    }

    free(repertoire);
    free(NomF1);
    free(NomF2);

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
    printf("Nom premier fichier (sans l'extension) : ");
    scanf("%s", NomF1); // récupération nom fichier 1
    strcat(NomF1,".bmp"); // AJOUT extension

    //DEMANDE FICHIER 2 SI OPERATION = (SUPERPOSITION - 1)
    if(*operation==5) // Si l'operation est la superposition on demande le nom du fichier
    {
        printf("Nom second fichier (sans l'extension) : ");
        scanf("%s", NomF2); // récupération nom fichier 2
        strcat(NomF2, ".bmp"); // AJOUT extension
    }
    else{
        NomF2 = NULL;
    }

    return 0;
}
