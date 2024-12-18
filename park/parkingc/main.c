#include <stdio.h>
#include <stdlib.h>
#include "ajout.h"

int main() {
    Parking parking;
    int numero, choix;

     
   // ajouterParking(&parking);
    //insererParking(parking, "Parking.txt");

    do { 
        printf("\n--- Menu Principal ---\n");
        printf("1. Ajouter un parking\n");
        printf("2. Modifier un parking\n");
        printf("3. Supprimer un parking\n");
        printf("4. Chercher un parking\n");
        printf("5. Affecter un agent à un parking\n");
        printf("6. Quitter\n");
        printf("Veuillez entrer le numéro de l'option: ");
       
        
        scanf("%d", &choix);
        while (getchar() != '\n');  

        switch (choix) {
            case 1:
                
                ajouterParking(&parking);
                insererParking(parking, "Parking.txt");
                printf("Parking ajouté avec succès.\n");
                break;

            case 2:
               
                printf("Entrez le numéro du parking à modifier : ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                modifierParking(numero, "Parking.txt");
                printf("Parking modifié avec succès.\n");
                break;

            case 3:
               
                printf("Entrez le numéro du parking à supprimer : ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                supprimerParking(numero, "Parking.txt");
                printf("Parking supprimé avec succès.\n");
                break;

            case 4:
                 
                printf("Entrez le numéro du parking à chercher : ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                chercherParking(numero, "Parking.txt");
                break;

            case 5:
              
                printf("Entrez le numéro du parking à affecter : ");
                scanf("%d", &numero);
                while (getchar() != '\n');
                AffecterAgent(numero, "Parking.txt");
                printf("Agent affecté avec succès.\n");
                break;

            case 6:
               
                printf("Merci d'avoir utilisé le programme. À bientôt !\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 6);   

    return 0;
}

	

