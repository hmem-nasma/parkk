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

