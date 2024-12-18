#ifndef RESERVATION_H
#define RESERVATION_H

#include <gtk/gtk.h> // Include GTK+ header for GtkListStore and other GTK+ types


// Define the Reservation structure
typedef struct {
    int num_reservation;
    int num_citoyen;
    int num_parking;
    char matricule_vehicule[50];
    char date_reservation[20];
    char service_reservation[50];
    char status_reservation[20]; 
} Reservation;



// Declare the ajouter function
int ajouter(const char *num_reservation, const char *num_citoyen, const char *num_parking,
            const char *matricule_vehicule, const char *date_reservation, const char *service_reservation,
            const char *status_reservation);

// Declaration of supprimer_reservation
int supprimer_reservation(const char *filename, int num_reservation);
int modifier_reservation(const char *filename, const char *num_reservation, const char *num_citoyen, int num_parking,
                         const char *matricule_vehicule, const char *date_reservation, const char *service_reservation,
                         const char *status_reservation);


int is_num_reservation_unique(const char *filename, int num_reservation);

void load_reservations(const char *filename, GtkListStore *store);
void populate_tree_view(const char *filename, GtkTreeView *treeview);
void populate_parking_tree_view(const char *filename, GtkTreeView *treeview);
int update_reservation_parking(const char *filename, int reservation_id, int parking_id);
int update_parking_capacity(const char *filename, int parking_id, int decrement);



#endif // RESERVATION_H

