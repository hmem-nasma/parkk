#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parking.h"

int Ajout_Utilisateur(char login[110], char password[110], char nom[110], char role[110]) {
    FILE *fichier = fopen("utilisateur.txt", "r");
    if (fichier == NULL) {
        fichier = fopen("utilisateur.txt", "a");
        if (fichier == NULL) {
            return 0;
        }
        fclose(fichier);
        fichier = fopen("utilisateur.txt", "r");
    }

    char login_existant[110];
    char ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%[^,]", login_existant);
        if (strcmp(login_existant, login) == 0) {
            fclose(fichier);
            return 0;
        }
    }
    fclose(fichier);

    fichier = fopen("utilisateur.txt", "a");
    if (fichier == NULL) {
        return 0;
    }

    fprintf(fichier, "%s,%s,%s,%s\n", login, password, nom, role);

    fclose(fichier);
    return 1;
}



int Verifier_Utilisateur(char login[110], char password[110]) {
    FILE *fichier = fopen("utilisateur.txt", "r");
    if (fichier == NULL) {
        return 0; // Fichier introuvable
    }

    char login_existant[110], password_existant[110], ligne[1024];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%[^,],%[^,]", login_existant, password_existant);
        if (strcmp(login_existant, login) == 0 && strcmp(password_existant, password) == 0) {
            fclose(fichier);
            return 1; // Login et mot de passe trouvés
        }
    }

    fclose(fichier);
    return 0; // Login ou mot de passe incorrect
}





int Ajout_Parking(int numero, char nom[110], int capacite, float prix, int jour, int mois, int annee, char adresse[110], char securite[500], char secteur[110], char agent[110]) {
      FILE *fichier = fopen("Parking.txt", "r");
    if (fichier == NULL) {
        fichier = fopen("Parking.txt", "a");
        if (fichier == NULL) {
            return 0;
        }
        fclose(fichier);
        fichier = fopen("Parking.txt", "r");
    }

    int numero_existant;
    char nom_existant[110];
    char ligne[1024];

    // Vérification de l'existence du numéro ou du nom
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%d,%[^,]", &numero_existant, nom_existant);
        if (numero_existant == numero || strcmp(nom_existant, nom) == 0) {
            fclose(fichier);
            return 0; // Le numéro ou le nom existe déjà
        }
    }
    fclose(fichier);

    // Ajout du parking si aucune correspondance trouvée
    fichier = fopen("Parking.txt", "a");
    if (fichier == NULL) {
        return 0;
    }

    fprintf(fichier, "%d,%s,%d,%.2f,%02d,%02d,%04d,%s,%s,%s,%s\n", 
            numero, nom, capacite, prix, jour, mois, annee, adresse, securite, secteur, agent);

    fclose(fichier);
    return 1;
}

int Rechercher_Parking(int numero, char *nom, int *capacite, float *prix, int *jour, int *mois, int *annee, char *adresse, char *securite, char *secteur) {
    FILE *fichier = fopen("Parking.txt", "r");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier Parking.txt");
        return 0;
    }

    char ligne[1024];
    int num;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        int count = sscanf(ligne, "%d,%109[^,],%d,%f,%d,%d,%d,%109[^,],%109[^,],%109[^,\n]",
                           &num, nom, capacite, prix, jour, mois, annee, adresse, securite, secteur);
        if (count == 10 && num == numero) {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);
    return 0;
}


int Modifier_Parking(int numero,char *nouveau_nom, int nouvelle_capacite, float nouveau_prix, int nouveau_jour, int nouveau_mois, int nouvelle_annee,char *nouvelle_adresse,  char *nouvelle_securite, 
 char *nouveau_secteur) {
    FILE *fichier = fopen("Parking.txt", "r");
    FILE *temporaire = fopen("Temp.txt", "w");
    if (fichier == NULL || temporaire == NULL) {
        if (fichier != NULL) fclose(fichier);
        if (temporaire != NULL) fclose(temporaire);
        perror("Erreur d'ouverture des fichiers");
        return 0;
    }

    char ligne[1024];
    int num;
    int modifie = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char nom[110], adresse[110], securite[110], secteur[110], agent[110];
        int capacite, jour, mois, annee;
        float prix;

        int count = sscanf(ligne, "%d,%109[^,],%d,%f,%d,%d,%d,%109[^,],%109[^,],%109[^,],%109[^,\n]",
                           &num, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur, agent);

        if (count == 11 && num == numero) {
            // Écrire les nouvelles informations pour ce parking
            fprintf(temporaire, "%d,%s,%d,%.2f,%d,%d,%d,%s,%s,%s,%s\n",
                    numero, nouveau_nom, nouvelle_capacite, nouveau_prix,
                    nouveau_jour, nouveau_mois, nouvelle_annee,
                    nouvelle_adresse, nouvelle_securite, nouveau_secteur, agent);
            modifie = 1;
        } else {
            // Réécrire la ligne telle quelle
            fprintf(temporaire, "%s", ligne);
        }
    }

    fclose(fichier);
    fclose(temporaire);

    // Remplacement du fichier original par le fichier temporaire
    if (modifie) {
        if (remove("Parking.txt") != 0 || rename("Temp.txt", "Parking.txt") != 0) {
            perror("Erreur lors du remplacement du fichier");
            return 0;
        }
    } else {
        remove("Temp.txt");
    }

    return modifie;
}
 

// Fonction pour récupérer les noms des parkings
int Rechercher_Noms_Parking(char noms[][110], int taille_max) {
    FILE *f = fopen("Parking.txt", "r");                                
    if (f == NULL) {
        return -1; // Erreur : fichier introuvable
    }

    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char id[20], nom[110], etat[20], prix[20], jour[10], mois[10], annee[10], adresse[110], type[50], categorie[50], etat_presence[50];

        // Analyse de la ligne pour extraire les informations
        if (sscanf(ligne, "%19[^,],%109[^,],%19[^,],%19[^,],%9[^,],%9[^,],%9[^,],%109[^,],%49[^,],%49[^,],%49s",
                   id, nom, etat, prix, jour, mois, annee, adresse, type, categorie, etat_presence) == 11) {
            if (count < taille_max) {
                strncpy(noms[count], nom, 109); // Copier le nom dans le tableau
                noms[count][109] = '\0';       // Assurer la terminaison de la chaîne
                count++;
            }
        }
    }

    fclose(f);
    return count; // Retourne le nombre de noms de parking trouvés
}

// Fonction pour supprimer un parking du fichier
int Supprimer_Parking(const char *nom_parking) {
    FILE *f = fopen("Parking.txt", "r");
    if (f == NULL) {
        return -1; // Erreur : fichier introuvable
    }

    FILE *temp = fopen("Temp_Parking.txt", "w");
    if (temp == NULL) {
        fclose(f);
        return -2; // Erreur : impossible de créer le fichier temporaire
    }

    char ligne[256];
    int ligne_supprimee = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char id[20], nom[110], reste[256];

        // Analyse de la ligne pour extraire le nom
        if (sscanf(ligne, "%19[^,],%109[^,],%255[^\n]", id, nom, reste) == 3) {
            if (strcmp(nom, nom_parking) == 0) {
                ligne_supprimee = 1; // Ligne correspondante trouvée et ignorée
                continue;
            }
        }

        // Copier les lignes restantes dans le fichier temporaire
        fprintf(temp, "%s", ligne);
    }

    fclose(f);
    fclose(temp);

    // Remplacer le fichier original par le fichier temporaire
    if (ligne_supprimee) {
        remove("Parking.txt");
        rename("Temp_Parking.txt", "Parking.txt");
    } else {
        // Supprimer le fichier temporaire si rien n'a été supprimé
        remove("Temp_Parking.txt");
    }

    return ligne_supprimee ? 0 : -3; // 0 si succès, -3 si aucun parking correspondant trouvé
}


int Rechercher_ID_Agents(char ids[][110], int taille_max) {
    FILE *f = fopen("Agent.txt", "r");
    if (f == NULL) {
        return -1; // Erreur : fichier introuvable
    }

    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char id[110], nom[110], etat[10];

        // Analyse de la ligne pour extraire les informations
        if (sscanf(ligne, "%109[^,],%109[^,],%9s", id, nom, etat) == 3) {
            if (atoi(etat) == 0) { // Vérifier si l'état de l'agent est 0
                if (count < taille_max) {
                    strncpy(ids[count], id, 19); // Copier l'ID dans le tableau
                    ids[count][109] = '\0';       // Assurer la terminaison de la chaîne
                    count++;
                }
            }
        }
    }

    fclose(f);
    return count; // Retourne le nombre d'IDs d'agents trouvés avec état 0
}

int Rechercher_Parkings_Sans_Agent(char noms[][110], int taille_max) {
    FILE *f = fopen("Parking.txt", "r");
    if (f == NULL) {
        return -1; // Erreur : fichier introuvable
    }

    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        char id[20], nom[110], etat[20], prix[20], jour[10], mois[10], annee[10], adresse[110], type[50], categorie[50], etat_presence[50];

        // Analyse de la ligne pour extraire les informations
        if (sscanf(ligne, "%19[^,],%109[^,],%19[^,],%19[^,],%9[^,],%9[^,],%9[^,],%109[^,],%49[^,],%49[^,],%49s",
                   id, nom, etat, prix, jour, mois, annee, adresse, type, categorie, etat_presence) == 11) {
            // Si l'état de présence est "Absent"
            if (strcmp(etat_presence, "Absent") == 0) {
                if (count < taille_max) {
                    strncpy(noms[count], nom, 109); // Copier le nom dans le tableau
                    noms[count][109] = '\0';       // Assurer la terminaison de la chaîne
                    count++;
                }
            }
        }
    }

    fclose(f);
    return count; // Retourne le nombre de parkings dont l'agent est absent
}

int affectAgent(char *nom_parking, char *id_agent) {
    FILE *fichier_parking = fopen("Parking.txt", "r");
    if (fichier_parking == NULL) {
        perror("Erreur : Fichier Parking.txt introuvable");
        return -1;
    }

    FILE *fichier_temp = fopen("Parking_temp.txt", "w");
    if (fichier_temp == NULL) {
        perror("Erreur : Impossible de créer le fichier temporaire");
        fclose(fichier_parking);
        return -1;
    }

    int numero, capacite, jour, mois, annee;
    float prix;
    char nom[110], adresse[110], securite[110], secteur[110], agent[110];
    int trouve = 0;

    while (fscanf(fichier_parking, "%d,%109[^,],%d,%f,%d,%d,%d,%109[^,],%109[^,],%109[^,],%109[^\n]",
                  &numero, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur, agent) != EOF) {
        if (strcmp(nom, nom_parking) == 0) {
            strcpy(agent, id_agent);  // Mise à jour de l'ID de l'agent
            trouve = 1;
        }

        fprintf(fichier_temp, "%d,%s,%d,%.2f,%02d,%02d,%04d,%s,%s,%s,%s\n",
                numero, nom, capacite, prix, jour, mois, annee, adresse, securite, secteur, agent);
    }

    fclose(fichier_parking);
    fclose(fichier_temp);

    if (!trouve) {
        remove("Parking_temp.txt");
        return 0;  // Parking non trouvé
    }

    if (remove("Parking.txt") != 0 || rename("Parking_temp.txt", "Parking.txt") != 0) {
        perror("Erreur lors du remplacement de Parking.txt");
        return -1;
    }

    FILE *fichier_agents = fopen("Agent.txt", "r+");
    if (fichier_agents == NULL) {
        perror("Erreur : Fichier Agent.txt introuvable");
        return -1;
    }

    char id[110], nom_agent[110];
    int etat;
    int agent_trouve = 0;

    while (fscanf(fichier_agents, "%109[^,],%109[^,],%d\n", id, nom_agent, &etat) != EOF) {
        if (strcmp(id, id_agent) == 0 && etat == 0) {
            fseek(fichier_agents, -(strlen(id) + strlen(nom_agent) + 4), SEEK_CUR);
            fprintf(fichier_agents, "%s,%s,1\n", id, nom_agent);  // Mise à jour de l'état
            agent_trouve = 1;
            break;
        }
    }

    fclose(fichier_agents);

    if (!agent_trouve) {
        return 0;  // Agent non trouvé ou déjà affecté
    }

    return 1;  // Succès
}




