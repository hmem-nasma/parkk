#ifndef SERVICE_H
#define SERVICE_H
#include <stdbool.h>
#include <gtk/gtk.h>

#include <stdio.h>
#include <glib.h> // Pour les types gchar et les fonctions GTK compatibles
typedef struct {
    int numeroService;
    char typeService[50];
    char disponibilite[20];
    float tarifService;
    int dureeEstimee;
    char vehiculeconcerne[50];
} Service;
void sauvegarderService(Service service, FILE *fichier);
bool ajouterService(Service service);
Service* chercherServiceParType(const char* typeService);
bool modifierService(Service service);
bool supprimerService(int *numeroService);
void listerServices();
char* convertir_en_utf8(const char *input);
void supprimer_element_combobox(GtkWidget *combobox, const char *valeur);
void remplir_combobox_services(GtkWidget *combobox);
void remplir_treeview_services(GtkWidget *treeview);
void affecterServiceReservation(int idReservation, int idService);
void configurer_treevieww(GtkWidget *treeview);
bool existeService(int numeroService, const char *typeService);

#endif 

