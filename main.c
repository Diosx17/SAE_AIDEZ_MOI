#include "fonctionImage.h"
#define TEST

#ifdef TEST
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
            commandes(repertoire, &operation, NomF1, NomF2);
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
        }
        else{
            printf("Le fichier de résultat ne peut etre créé\n");
            return -3;
        }

    }
    else{
        printf("Un (ou plusieurs) fichier(s) n'existe(nt) pas\n");
        return -2;
    }

}
#else
int main(int argc, char *argv[])
{
    FILE *fIn; // fichier d'entrée déclaré avec type FILE
    FILE *fIn2; // fichier d'entrée 2 délcaré avec type FILE
    FILE *fOut; // fichier de sortie déclaré avec type FILE

    char *repertoire_temporaire = malloc(350); // chaine de caractère stockant le repertoire du fichier source rentré par l'utilisateur
    char NomF1[100]; // nom du fichier source 1
    char NomF2[100]; // nom du fichier source 2
    char *temp = malloc(350); // Repertoire temporaire servant a stocker le repertoire avant concatenation avec le nom du fichier
    int operation = -1; // numéro de l'opération à effectuer (init à -1)
    char *slash = "/"; // Servira a rajouter un slash a la fin du repertoire pour ensuite concatener le nom du fichier
    char repertoire[100]=""; //Rajouter des doubles quotes pour ouvrir le dossier

    if(argv[1])
    {
        operation = atoi(argv[2]-1); // recuperer operation si elle est passee en argument
    }

    switch (argc) // On teste le nombre d'arguments rentrés pendant l'execution
    {
        case 1: // Cas ou il n'y a aucun autre argument que l'executable en lui meme : ouvrir menu texte ou saisir le path du repertoire de travail, numero traitement, nom fichier, nom eventuel 2eme fichier si argv[] = 4
            printf("Rentrez le chemin du repertoire de travail sans antislash a la fin et sans double quote : ");
            gets(repertoire_temporaire); // récupération du repertoire

            strcat(repertoire,repertoire_temporaire); // concaténation du repertoire avec des doubles quotes

            strcat(repertoire,slash); // concaténation d'un slash a la fin du repertoire pour obtenir le path complet

            printf("1 : Image en niveaux de gris\n");        // affichage des différentes opérations
            printf("2 : Image en couleurs inversees\n");
            printf("3 : Image monochrome\n");
            printf("4 : Extraction des contours\n");
            printf("5 : Superposition de 2 images\n");
            printf("Rentrez le numero du traitement : ");
            scanf("%d",&operation); // récupération du numéro de l'opération
            operation--; // opération -1 car nous faisons notre switch case plus bas avec des valeurs allant de 0 à 4 (l'utilisateur en entrant une de 1 à 5)
            printf("\n");
            printf("Rentrez le nom du fichier avec extension : ");
            scanf("%s",NomF1); // récupération nom fichier 1


            if(operation==4) // Si l'operation est la superposition on met demande le nom du fichier
            {
                printf("Rentrez le nom du 2eme fichier avec extension : ");
                scanf("%s",NomF2); // récupération nom fichier 2

            }
            strcpy(temp,repertoire); // copie du path dans une autre chaine de caractere vierge car nous voulons le réutiliser apres la premiere concatenation avec le nom
            strcat(repertoire,NomF1); // concatener path avec nom fichier 1
            //strcat(repertoire,"\x22");
            fIn = fopen(repertoire,"rb"); // Pour retrouver sur le repertoire on le concatene avec le nom du fichier pour le trouver
            puts(repertoire);


            if(NomF2!=NULL)
            {
                strcpy(repertoire,temp); // copie du path dans une autre chaine de caractere vierge car nous voulons le réutiliser apres la premiere concatenation avec le nom
                strcat(repertoire,NomF2);// concatener path avec nom fichier 2
                fIn2 = fopen(repertoire,"rb"); // Meme chose qu'en haut
            }
            strcpy(repertoire,temp); // remettre à la chaine repetertoire le path
            strcat(repertoire,"result.bmp"); // concatener
            //strcat(repertoire,"\x22");


            fOut = fopen(repertoire,"wb"); // Meme chose mais avec fichier resultat
            puts(repertoire);

            switch(operation) //  On check l'operation en question
                {
                    case 0: // Niveau de gris
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        GrayScale(fIn,fOut);
                        break;

                    case 1: // Inversion des couleurs
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        Invert(fIn,fOut);
                        break;

                    case 2: // Image monochrome
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        Mono(fIn,fOut);
                        break;

                    case 3: // Contours de l'image
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        Contours(fIn,fOut);
                        break;



                    case 4: // Superposition des deux images
                        if (!fIn || !fIn2)
                            {
                                printf("Erreur, fichier(s) source(s) non trouv%c(s)\n",130);
                                printf("-2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        Superposition(fIn,fIn2,fOut);
                        break;

                    default:
                        printf("Le traitement demand%c est impossible ou n'existe pas\n",130);
                        printf("-1");
                        return -1; //Le traitement n'existe pas
                }
            break;

        case 4: // Cas 2 ou on met les arguments directement dans la fonction (toutes operation sauf superposition)

            if(!argv[3])
            {
                printf("Fichier(s) n'existe(nt) pas\n");
                printf("-2 1");
                return -2;
            }
            printf("test");
            printf("%d", operation);

            switch(operation)
                {
                    printf("%d", operation);
                    strcpy(temp,argv[1]); // On stocke le path du dossier dans temp
                    strcat(temp,slash);
                    fIn  = fopen(strcat(temp,argv[3]), "rb");
                    fOut = fopen(strcat(argv[1],"result.bmp"), "wb");

                    case 0: // Niveaux de gris
                        if (!fIn)
                            {
                                 printf("Erreur, fichier source non trouv%c\n",130);
                                 printf("-2 2");
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                return -3;
                            }
                        GrayScale(fIn,fOut);
                        break;

                    case 1: // Inversion des couleurs
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2;3");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -3;
                            }
                        Invert(fIn,fOut);
                        break;

                    case 2: // Image monochrome
                        if (!fIn)
                            {
                                printf("Erreur, fichier source non trouv%c\n",130);
                                printf("-2 4");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -3;
                            }
                        Mono(fIn,fOut);
                        break;

                    case 3: // Contours de l'image
                        if (!fIn)
                            {
                                 printf("Erreur, fichier source non trouv%c\n",130);
                                 printf("-2");
                                 fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -3;
                            }
                        Contours(fIn,fOut);
                        break;

                    case 4: // Superpostion des deux images
                        strcpy(temp,argv[1]);
                        strcat(temp,slash);

                        if(argv[4])
                        {
                            fIn2 = fopen(strcat(temp,argv[4]),"rb");

                        }
                        else
                        {
                            printf("le fichier 2 n'existe pas \n");
                            printf("-2");
                            fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                            return -2;
                        }


                        strcpy(temp,argv[1]);
                        strcat(temp,slash);

                        fOut = fopen(strcat(argv[1],"/result.bmp"), "wb");
                        if (!fIn || !fIn2)
                            {
                                printf("Erreur, fichier(s) source(s) non trouv%c(s)\n",130);
                                printf("-2");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -2;
                            }
                        else if (!fOut)
                            {
                                printf("Erreur, impossible de cr%cer le fichier de sortie\n",130);
                                printf("-3");
                                fclose(fIn);
                                fclose(fOut);
                                free(temp);
                                free(repertoire_temporaire);
                                return -3;
                            }

                        Superposition(fIn,fIn2,fOut);
                        break;


                    default:
                        printf("Le traitement demand%c est impossible ou n'existe pas\n",130);
                        printf("-1");
                        return -1; //Le traitement n'existe pasprintf("test2");
                }
                break;
        case 5: // Cas 3 ou on met les arguments directement dans la fonction donc superposition
            if(!argv[3] || !argv[4])
            {
                printf("Fichier(s) introuvable(s)\n");
                printf("-2");
                fclose(fIn);
                fclose(fOut);
                free(temp);
                free(repertoire_temporaire);
                return -2;
            }
            switch(operation)
            {
                printf("coucou");
                case 4:
                    strcpy(temp,argv[1]);
                    strcat(temp,slash);

                    fIn  = fopen(strcat(temp,argv[3]), "rb");
                    strcpy(temp,argv[1]);
                    strcat(temp,slash);

                    fIn2 = fopen(strcat(temp,argv[4]),"rb");
                    strcpy(temp,argv[1]);
                    strcat(temp,slash);

                    fOut = fopen(strcat(argv[1],"/result.bmp"), "wb");
                    if (!fIn || !fIn2)
                        {
                            printf("Erreur, fichier(s) source(s) non trouv%c(s)\n",130);
                            printf("-2");
                            fclose(fIn);
                            fclose(fOut);
                            free(temp);
                            free(repertoire_temporaire);
                            return -2;
                        }
                    Superposition(fIn,fIn2,fOut);
                    break;


                default:
                    printf("Le traitement demand%c est impossible ou n'existe pas\n",130);
                    printf("-1");
                    fclose(fIn);
                    fclose(fOut);
                    free(temp);
                    free(repertoire_temporaire);
                    return -1; //Le traitement n'existe pas
                break;
            }
    default:
        printf("%d\n", operation);
        printf("-2");
        fclose(fIn);
        fclose(fOut);
        free(temp);
        free(repertoire_temporaire);
        return -2;
        break;


    }
    printf("Traitement effectu%c",130);
    fclose(fIn);
    fclose(fOut);
    free(temp);
    free(repertoire_temporaire);
    return 0; // Le traitement s'est bien déroulé
}

#endif // TEST







