#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ajout.h"

void ajouterParking(Parking* parking) {
    printf("Entrez le numero du parking : ");
    scanf("%d", &parking->numero);
    while (getchar() != '\n'); // Vider le tampon d'entrée

    printf("Entrez le nom du parking : ");
    scanf("%99s", parking->nom);
    while (getchar() != '\n');

    printf("Entrez l'adresse : ");
    scanf("%99s", parking->adresse);
    while (getchar() != '\n');

    printf("Entrez la date de construction : ");
    scanf("%99s", parking->date_construction);
    while (getchar() != '\n');

    printf("Entrez la capacité : ");
    scanf("%d", &parking->capacite);
    while (getchar() != '\n');

    /*printf("Entrez le nom de l'agent affecté : ");
    scanf("%99s", parking->agent);
    while (getchar() != '\n');*/

    printf("Entrez la description : ");
    scanf("%99s", parking->description);
    while (getchar() != '\n');

    printf("Entrez le secteur : ");
    scanf("%99s", parking->secteur);
    while (getchar() != '\n');

    printf("Entrez securite : ");
    scanf("%99s", parking->securite);
    while (getchar() != '\n');
    
    strcpy(parking->agent,"0");

    printf("Parking ajouté : %d %s %s %s %d %s %s %s %s\n",
        parking->numero, parking->nom, parking->adresse,
        parking->date_construction, parking->capacite,
        parking->agent, parking->description,
        parking->secteur, parking->securite);
}

int numeroDejaPresent(int numero, char *fichierParking) {
 FILE *f = fopen(fichierParking, "r"); 
if (f == NULL) { 
printf("Erreur lors de l'ouverture du fichier"); 
return 1;} 
Parking parking; 
while (fscanf(f, "%d %99s %99s %99s %d %99s %99s %99s %99s\n", &parking.numero, parking.nom, parking.adresse, parking.date_construction, &parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite) == 9) { if (parking.numero == numero) { 
fclose(f); 
return 1;} } 
fclose(f); 
return 0;}
 
void insererParking(Parking parking,char *fichierParking) { 
if(numeroDejaPresent(parking.numero, fichierParking)) { 
printf("Erreur : Le numéro du parking %d existe déjà.\n", parking.numero); return;}   
FILE *f = fopen(fichierParking, "a"); 
if (f != NULL) { 
fprintf(f, "%d\n %s\n %s\n %s\n %d\n %s\n %s\n %s\n %s\n", parking.numero, parking.nom, parking.adresse, parking.date_construction, parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite); 
fclose(f);} 
else { printf("Erreur lors de l'ouverture du fichier"); } } 





void modifierParking(int numero, char *fichierParking) {
FILE *f = fopen(fichierParking, "r"); 
if (f == NULL) {
 printf("Erreur lors de l'ouverture du fichier\n"); 
return; } 
Parking parking; 
int found = 0; 
FILE *temp = fopen("temp.txt", "w"); 
if (temp == NULL) { 
printf("Erreur lors de la création du fichier temporaire\n"); 
fclose(f); 
return; } 
while (fscanf(f, "%d %99s %99s %99s %d %99s %99s %99s %99s\n", &parking.numero, parking.nom, parking.adresse, parking.date_construction, &parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite) == 9) { if (parking.numero == numero) {
 found = 1; 
printf("Modifiez le parking (tapez les nouvelles valeurs, ou appuyez sur Entrée pour garder l'ancienne) :\n"); 
char input[100]; 
printf("Nom (ancien: %s): ", parking.nom);
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.nom); } printf("Adresse (ancien: %s): ", parking.adresse); if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { sscanf(input, "%99s", parking.adresse); } 
printf("Date de construction (ancien: %s): ", parking.date_construction); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.date_construction); }
printf("Capacité (ancien: %d): ", parking.capacite); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%d", &parking.capacite); } 
printf("Agent (ancien: %s): ", parking.agent); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.agent); } 
printf("Description (ancien: %s): ", parking.description); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.description); }
printf("Secteur (ancien: %s): ", parking.secteur); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.secteur); } 
printf("Sécurité (ancien: %s): ", parking.securite); 
if (fgets(input, sizeof(input), stdin) && input[0] != '\n') { 
sscanf(input, "%99s", parking.securite); } } 
fprintf(temp, "%d %s %s %s %d %s %s %s %s\n", parking.numero, parking.nom, parking.adresse, parking.date_construction, parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite); } 
fclose(f); 
fclose(temp); 
if (found) { 
remove(fichierParking); 
rename("temp.txt", fichierParking); 
printf("Parking %d modifié avec succès.\n", numero); } 
else { printf("Parking %d non trouvé.\n", numero); 
remove("temp.txt"); } }

void supprimerParking(int numero, char *fichierParking) {
 FILE *f = fopen(fichierParking, "r"); 
if (f == NULL) { 
printf("Erreur lors de l'ouverture du fichier\n"); 
return; } 
Parking parking; 
int found = 0; 
FILE *temp = fopen("temp.txt", "w"); 
if (temp == NULL) { 
printf("Erreur lors de la création du fichier temporaire\n"); 
fclose(f); 
return; } 
while (fscanf(f, "%d %99s %99s %99s %d %99s %99s %99s %99s\n", &parking.numero, parking.nom, parking.adresse, parking.date_construction, &parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite) == 9) { if (parking.numero == numero) { 
found = 1; 
continue; } 
fprintf(temp, "%d %s %s %s %d %s %s %s %s\n", parking.numero, parking.nom, parking.adresse, parking.date_construction, parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite); } 
fclose(f);
fclose(temp); 
if (found) { 
remove(fichierParking); 
rename("temp.txt", fichierParking); 
printf("Parking %d supprimé avec succès.\n", numero); } 
else { 
printf("Parking %d non trouvé.\n", numero); 
remove("temp.txt"); } }


void chercherParking(int numero, char *fichierParking) { 
FILE *f = fopen(fichierParking, "r"); 
if (f == NULL) { 
printf("Erreur lors de l'ouverture du fichier\n"); 
return; } 
Parking parking; 
int found = 0; 
while (fscanf(f, "%d %99s %99s %99s %d %99s %99s %99s %99s\n", &parking.numero, parking.nom, parking.adresse, parking.date_construction, &parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite) == 9) { if (parking.numero == numero) { 
found = 1; 
printf("Parking trouvé :\n"); 
printf("Numéro : %d\n", parking.numero); 
printf("Nom : %s\n", parking.nom);
 printf("Adresse : %s\n", parking.adresse); 
printf("Date de construction : %s\n", parking.date_construction); printf("Capacité : %d\n", parking.capacite); 
printf("Agent : %s\n", parking.agent); 
printf("Description : %s\n", parking.description); 
printf("Secteur : %s\n", parking.secteur); 
printf("Sécurité : %s\n", parking.securite);
break; } } 
if (!found) { 
printf("Parking %d non trouvé.\n", numero); } 
fclose(f); } 

 
void AffecterAgent(int numero, char *fichierParking) { 
FILE *f = fopen(fichierParking, "r"); if (f == NULL) { printf("Erreur lors de l'ouverture du fichier\n"); return; } Parking parking; int found = 0; FILE *temp = fopen("temp.txt", "w"); if (temp == NULL) { printf("Erreur lors de la création du fichier temporaire\n"); fclose(f); return; } while (fscanf(f, "%d %99s %99s %99s %d %99s %99s %99s %99s\n", &parking.numero, parking.nom, parking.adresse, parking.date_construction, &parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite) == 9) { if (parking.numero == numero) { found = 1; 
 if (strcmp(parking.agent, "0") == 0) { 
printf("Le parking %d a un agent non affecté (agent: %s).\n", numero, parking.agent); 
printf("Entrez le nom de l'agent à affecter : "); 
char newAgent[100]; fgets(newAgent, sizeof(newAgent), stdin); 
sscanf(newAgent, "%99s", parking.agent); } 
else { printf("Parking %d déjà affecté à un agent : %s\n", numero, parking.agent); } }  
fprintf(temp, "%d %s %s %s %d %s %s %s %s\n", parking.numero, parking.nom, parking.adresse, parking.date_construction, parking.capacite, parking.agent, parking.description, parking.secteur, parking.securite); } fclose(f); fclose(temp); 
if (found) { 
remove(fichierParking); 
rename("temp.txt", fichierParking); 
printf("Agent affecté avec succès pour le parking %d.\n", numero); } 
else { printf("Parking %d non trouvé.\n", numero); 
remove("temp.txt"); } }  
  
  
 
