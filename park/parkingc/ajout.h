#ifndef AJOUT_H
#define AJOUT_H

typedef struct {
    int numero;
    char nom[100];
    char date_construction[100];
    char securite[100];
    char adresse[100];
    int capacite;
    char secteur[100];
    char description[100];
    char agent[100];
} Parking;

void ajouterParking(Parking* parking);
int numeroDejaPresent(int numero, char *fichierParking);
void insererParking(Parking parking,char *fichierParking);
void modifierParking(int numero, char *fichierParking);
void supprimerParking(int numero, char *fichierParking);
void chercherParking(int numero, char *fichierParking);
void AffecterAgent(int numero, char *fichierParking);
 

 
 

#endif // AJOUT_H
