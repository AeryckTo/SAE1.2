#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996 6031 6054)

enum { NB_Max = 31, NB_PARTICIPANTS = 30, NB_CONCOURS = 20, COMMANDES = 30 };

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
	int nombre_participants = 0;

	CONCOURS concours[NB_CONCOURS];
	int nombres_concours = 0;
	char cmd[COMMANDES];
	char un[NB_Max];
	char deux[NB_Max];
	char trois[NB_Max];

	// Lire toute la ligne d'entrée 
	while (scanf("%s", cmd) == 1) {



		/* EXIT */

		if (strcmp(cmd, "EXIT") == 0) exit(0);


		/* INSCRIRE */
		else if (strcmp(cmd, "INSCRIRE") == 0) {
			if (scanf("%s" "%s", un, deux) != 2) continue;
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

				++nombre_participants;

				printf("Inscription enregistree (%d)\n", nombre_participants);

			}

		}


		/* PARTICIPANTS */

		else if (strcmp(cmd, "PARTICIPANTS") == 0) {

			if (nombre_participants == 0) printf("Aucun participant inscrit\n");
			else {

				for (int k = 0; k < nombre_participants; ++k) {

					int nb_concours = 0;

					/* Compter les concours dans lesquels
					   le participant a un score non nul */

					for (int u = 0; u < nombres_concours; ++u) {

						if (I[k].NB_POINTS[u] > 0) {
							++nb_concours;
						}
					}
					printf("(%d) %s %s : %d concours\n", k + 1, I[k].prenom, I[k].nom, nb_concours);
				}
			}
		}


		/* CREER */

		else if (strcmp(cmd, "CREER") == 0) {
			if (scanf("%s", un) != 1) continue;
			if (nombres_concours >= NB_CONCOURS || strlen(un) > NB_Max - 1) continue;



			/* Vérifier doublon de concours */

			int doublon2 = 0;

			for (int j = 0; j < nombres_concours; ++j) {

				if (_stricmp(concours[j].nom, un) == 0) {

					doublon2 = 1;
					break;
				}
			}


			if (doublon2) printf("Nom incorrect\n");
			else {

				strncpy(concours[nombres_concours].nom, un, NB_Max - 1);
				concours[nombres_concours].nom[NB_Max - 1] = '\0';
				printf("Creation enregistree (%d)\n", nombres_concours + 1);
				++nombres_concours;
			}
		}



		/* CONCOURS */

		else if (strcmp(cmd, "CONCOURS") == 0) {

			if (nombres_concours == 0) printf("Aucun concours cree\n");
			else {

				for (int u = 0; u < nombres_concours; ++u) {

					int nb_participants = 0;

					/* Compter les participants ayant
					   un score non nul dans ce concours */

					for (int p = 0; p < nombre_participants; ++p) {

						if (I[p].NB_POINTS[u] > 0) nb_participants++;
					}


					printf("(%d) %s : %d participants\n", u + 1, concours[u].nom, nb_participants);
				}
			}
		}


		/* GAIN */

		else if (strcmp(cmd, "GAIN") == 0) {
			if (scanf("%s" "%s" "%s", un, deux, trois) != 3) return;

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

		else if (strcmp(cmd, "SCORES") == 0) {
			if (scanf("%s", un) != 1) return;
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
			if (aucun_gain) printf("Aucun gain\n");


			else {

				//Afficher uniquement les concours dans lesquels le score est non nul 
				for (int u = 0; u < nombres_concours; ++u) {

					if (I[recup].NB_POINTS[u] > 0) {

						printf("(%d) %s : %d point\n", u + 1, concours[u].nom, I[recup].NB_POINTS[u], I[recup].NB_POINTS[u] > 1 ? "s" : "");
					}
				}

			}
		}
		/* CLASSEMENT */
		else if (strcmp(cmd, "CLASSEMENT") == 0) {

			if (scanf("%s", un) != 1) break;


			int recup = atoi(un);

			if (recup <= 0 ||
				recup > nombres_concours) {
				printf("Identifiant incorrect\n");
				continue;
			}

			--recup;

			printf("%s\n", concours[recup].nom);

			typedef struct {
				int id;
				int points;
				int places;
			} Liste;

			Liste list[NB_PARTICIPANTS];
			int compte = 0;

			/* Garder les participants ayant des points */
			for (int i = 0; i < nombre_participants; ++i) {
				int pts = I[i].NB_POINTS[recup];

				if (pts > 0) {
					list[compte].id = i + 1;
					list[compte].points = pts;
					++compte;
				}
			}

			if (compte == 0) {
				printf("Aucun participant\n");
				continue;
			}

			/* Trier par points décroissants,
			   puis par identifiant croissant */
			for (int i = 0; i < compte - 1; ++i) {
				for (int j = i + 1; j < compte; ++j) {

					if (list[j].points > list[i].points || list[i].points == list[j].points && list[i].id > list[j].id) {

						Liste tmp = list[i];
						list[i] = list[j];
						list[j] = tmp;
					}
				}
			}

			for (int i = 0; i < compte; ++i) {
				if (i == 0)	list[i].places = 1;

				else if (list[i].points == list[i - 1].points) 	list[i].places = list[i - 1].places;

				else list[i].places = i + 1;

			}

			/* Afficher le classement */
			for (int i = 0; i < compte; ++i) {

				int id = list[i].id;

				int tied =
					(i > 0 && list[i].points == list[i - 1].points) ||
					(i + 1 < compte && list[i].points == list[i + 1].points);

				if (tied) {
					printf("%dex -> (%d) %s %s : %d point%s\n", list[i].places, id, I[id - 1].prenom, I[id - 1].nom, list[i].points, list[i].points > 1 ? "s" : "");
				}
				else {
					printf("%d -> (%d) %s %s : %d point%s\n", list[i].places, id, I[id - 1].prenom, I[id - 1].nom, list[i].points, list[i].points > 1 ? "s" : "");
				}
			}
		}

		/* COMPARAISON */
		else if (strcmp(cmd, "COMPARAISON") == 0) {

			if (scanf("%s %s", un, deux) != 2) {
				continue;
			}

			int c = atoi(un);
			int v = atoi(deux);

			if (c <= 0 || c > nombres_concours || v <= 0 || v > nombres_concours) {
				printf("Identifiant incorrect\n");
				continue;
			}

			--c;
			--v;

			int nb_participants = 0;
			int pas_concours = 0;

			printf("%s versus %s\n", concours[v].nom, concours[c].nom);

			/* Vérifier les participants et la compatibilité */
			for (int i = 0; i < nombre_participants; ++i) {

				if (I[i].NB_POINTS[v] > 0 || I[i].NB_POINTS[c] > 0) ++nb_participants;
				if (I[i].NB_POINTS[c] > 0) ++pas_concours;
			}

			if (nb_participants == 0) {
				printf("Aucun participant\n");
				continue;
			}

			if (pas_concours == 0) {
				printf("Concours incompatibles\n");
				continue;
			}


			// Afficher les participants ayant un score

			for (int i = 0; i < nombre_participants; ++i) {

				int pts1 = I[i].NB_POINTS[v];
				int pts2 = I[i].NB_POINTS[c];

				if (pts2 > 0) {

					float pourcentage = 100.0f * (float)pts1 / (float)pts2;

					printf("(%d) %s %s : %d point%s/%d point%s : %.2f%%\n", i + 1, I[i].prenom, I[i].nom, pts1, pts1 > 1 ? "s" : "", pts2, pts2 > 1 ? "s" : "", pourcentage);
				}
			}
		}
	}
}