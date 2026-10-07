#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996 6031 6054)

enum { NB_Max = 31, NB_PARTICIPANTS = 30, NB_CONCOURS = 20, COMMANDES = 40, Max_line = 100 };

typedef struct {
    char nom[NB_Max];
    char prenom[NB_Max];
    int NB_POINTS[NB_CONCOURS];
} INCRIRE;

typedef struct {
    char nom[NB_Max];
} CONCOURS;


int main() {
    // Appeler la fonction principale d'inscription 
    void inscrire_programme(void);

    inscrire_programme();

    return 0;
}


// Fonction qui contient tout le comportement d'inscription 

void inscrire_programme(void) {

    INCRIRE I[NB_PARTICIPANTS];
    char line[Max_line];

    int nombre_participants = 0;

    CONCOURS concours[NB_CONCOURS];
    int nombres_concours = 0;


    // Lire toute la ligne d'entrée 
    while (fgets(line, sizeof(line), stdin)) {

        char cmd[COMMANDES];
        char un[NB_Max];
        char deux[NB_Max];
        char trois[NB_Max];

        int n = sscanf(line, "%s %s %s %s", cmd, un, deux, trois);
        /* EXIT */

        if (n == 1 && strcmp(cmd, "EXIT") == 0) exit(0);


        /* INSCRIRE */

        else if (n == 3 && strcmp(cmd, "INSCRIRE") == 0) {

            if (nombre_participants >= NB_PARTICIPANTS || strlen(un) > NB_Max - 1 || strlen(deux) > NB_Max - 1) continue;
            

            //Vérifier le doublon prénom + nom 

            int doublon = 0;

            for (int j = 0; j < nombre_participants; ++j) {

                if (_stricmp(I[j].prenom, un) == 0 && _stricmp(I[j].nom, deux) == 0) {
                    doublon = 1;
                    break;
                }
            }


            if (doublon) printf("Nom incorrect\n");
            else {

                strncpy(I[nombre_participants].prenom, un, NB_Max - 1);
                I[nombre_participants].prenom[NB_Max - 1] = '\0';

                strncpy(I[nombre_participants].nom, deux, NB_Max - 1);
                I[nombre_participants].nom[NB_Max - 1] = '\0';


                /* Initialiser les scores */

                for (int p = 0; p < NB_CONCOURS; ++p) {
                    I[nombre_participants].NB_POINTS[p] = 0;
                }


                ++nombre_participants;

                printf("Inscription enregistree (%d)\n",
                    nombre_participants);
            }
        }


        /* PARTICIPANTS */

        else if (n == 1 && strcmp(cmd, "PARTICIPANTS") == 0) {

            if (nombre_participants == 0) {

                printf("Aucun participant inscrit\n");

            }
            else {

                for (int k = 0; k < nombre_participants; ++k) {

                    int nb_concours = 0;

                    /* Compter les concours dans lesquels
                       le participant a un score non nul */

                    for (int u = 0; u < nombres_concours; ++u) {

                        if (I[k].NB_POINTS[u] > 0) {
                            nb_concours++;
                        }
                    }
                    printf("(%d) %s %s : %d concours\n",
                        k + 1,
                        I[k].prenom,
                        I[k].nom,
                        nb_concours);
                }
            }
        }


        /* CREER */

        else if (n == 2 && strcmp(cmd, "CREER") == 0) {

            if (nombres_concours >= NB_CONCOURS) {
                continue;
            }


            /* Vérifier doublon de concours */

            int doublonC = 0;

            for (int j = 0; j < nombres_concours; ++j) {

                if (_stricmp(concours[j].nom, un) == 0) {

                    doublonC = 1;
                    break;
                }
            }


            if (doublonC) {

                printf("Nom incorrect\n");

            }
            else {

                strncpy(concours[nombres_concours].nom, un, NB_Max - 1);

                concours[nombres_concours].nom[NB_Max - 1] = '\0';

                printf("Creation enregistree (%d)\n", nombres_concours + 1);

                ++nombres_concours;
            }
        }


        /* CONCOURS */

        else if (n == 1 && strcmp(cmd, "CONCOURS") == 0) {

            if (nombres_concours == 0) printf("Aucun concours cree\n");
                else {

                for (int u = 0; u < nombres_concours; ++u) {

                    int nb_participants = 0;

                    /* Compter les participants ayant
                       un score non nul dans ce concours */

                    for (int p = 0; p < nombre_participants; ++p) {

                        if (I[p].NB_POINTS[u] > 0) {
                            nb_participants++;
                        }
                    }


                    printf("(%d) %s : %d participants\n",
                        u + 1,
                        concours[u].nom,
                        nb_participants);
                }
            }
        }


        /* GAIN */

        else if (n == 4 && strcmp(cmd, "GAIN") == 0) {

            int recup_1 = atoi(un);
            int recup_2 = atoi(deux);
            int recup_3 = atoi(trois);


            /* Vérifier le participant */

            if (recup_1 <= 0 || recup_1 > nombre_participants) {

                printf("Participant incorrect\n");
            }


            /* Vérifier le concours */

            else if (recup_2 <= 0 || recup_2 > nombres_concours) printf("Concours incorrect\n");



            /* Vérifier les points */

            else if (recup_3 <= 0) printf("Points incorrects\n");

            else {

                recup_1 = recup_1 - 1;
                recup_2 = recup_2 - 1;


                // Ajouter les points au participant pour le concours choisi 

                I[recup_1].NB_POINTS[recup_2] += recup_3;


                printf("Gain enregistre\n");
            }
        }


        /* SCORES */

        else if (n == 2 && strcmp(cmd, "SCORES") == 0) {

            int recup = atoi(un);


            /* Vérifier le participant */

            if (recup <= 0 || recup > nombre_participants) {

                printf("Identifiant incorrect\n");
                continue;
            }


            recup = recup - 1;


            printf("%s %s\n", I[recup].prenom, I[recup].nom);

            // Vérifier si le participant a au moins un gain 

            int aucun_gain = 1;
            for (int u = 0; u < nombres_concours; ++u) {

                if (I[recup].NB_POINTS[u] > 0) {

                    aucun_gain = 0;
                    break;
                }
            }
            if (aucun_gain) {

                printf("Aucun gain\n");

            }
            else {

                //Afficher uniquement les concours dans lesquels le score est non nul 
                for (int u = 0; u < nombres_concours; ++u) {

                    if (I[recup].NB_POINTS[u] > 0) {

                        printf("(%d) %s : %d points\n",
                            u + 1,
                            concours[u].nom,
                            I[recup].NB_POINTS[u]);
                    }
                }
            }
        }
    }
}