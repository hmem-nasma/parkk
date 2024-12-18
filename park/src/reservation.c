#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"

typedef struct {
    int id;
    char owner[50];
    char location[50];
    char date[20];
    int capacity;
    float price;
    char type[20];
    char vehicle_type[20];
    char size[20];
    char phone[15];
} Parking;

// Add a reservation to the file
void ajouter_reservation(const char *filename, Reservation r) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier en mode ajout");
        return;
    }
    fprintf(f, "%d %d %d %s %s %s %s\n", r.num_reservation, r.num_citoyen, r.num_parking,
            r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation); // Write status_reservation
    fclose(f);
}

int ajouter(const char *num_reservation, const char *num_citoyen, const char *num_parking,
            const char *matricule_vehicule, const char *date_reservation, const char *service_reservation, const char *status_reservation) {
    // Convert input strings to integers
    int num_res = atoi(num_reservation);
    int num_cit = atoi(num_citoyen);
    int num_park = atoi(num_parking);

    // Validate mandatory fields
    if (num_res <= 0 || num_cit <= 0 || num_park <= 0 || strlen(matricule_vehicule) == 0 ||
        strlen(date_reservation) == 0 || strlen(service_reservation) == 0 || strlen(status_reservation) == 0) {
        printf("Erreur : Champs obligatoires manquants ou invalides.\n");
        return 0; // Failure
    }

    // Check for uniqueness of num_reservation
    if (!is_num_reservation_unique("reservations.txt", num_res)) {
        printf("Erreur : Num_reservation doit être unique.\n");
        return 0; // Failure
    }

    // Create a Reservation instance
    Reservation r = {num_res, num_cit, num_park, "", "", "", ""};
    strncpy(r.matricule_vehicule, matricule_vehicule, sizeof(r.matricule_vehicule) - 1);
    strncpy(r.date_reservation, date_reservation, sizeof(r.date_reservation) - 1);
    strncpy(r.service_reservation, service_reservation, sizeof(r.service_reservation) - 1);
    strncpy(r.status_reservation, status_reservation, sizeof(r.status_reservation) - 1);

    // Null-terminate the strings
    r.matricule_vehicule[sizeof(r.matricule_vehicule) - 1] = '\0';
    r.date_reservation[sizeof(r.date_reservation) - 1] = '\0';
    r.service_reservation[sizeof(r.service_reservation) - 1] = '\0';
    r.status_reservation[sizeof(r.status_reservation) - 1] = '\0';

    // Save the reservation to the file
    ajouter_reservation("reservations.txt", r);

    return 1; // Success
}


// Delete a reservation by ID
int supprimer_reservation(const char *filename, int num_reservation) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier de réservations.");
        return 0; // Failure
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erreur : Impossible de créer le fichier temporaire.");
        fclose(f);
        return 0; // Failure
    }

    Reservation r;
    int found = 0;

    // Process each reservation in the file
    while (fscanf(f, "%d %d %d %49s %19s %49s\n",
                  &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation) == 6) {
        if (r.num_reservation != num_reservation) {
            // Write non-matching reservations to the temp file
            fprintf(temp, "%d %d %d %s %s %s\n",
                    r.num_reservation, r.num_citoyen, r.num_parking,
                    r.matricule_vehicule, r.date_reservation, r.service_reservation);
        } else {
            found = 1; // Reservation found
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);         // Remove the original file
        rename("temp.txt", filename); // Replace with updated file
        return 1; // Success
    } else {
        remove("temp.txt"); // Clean up
        return 0; // Failure
    }
}


int modifier_reservation(const char *filename, const char *num_reservation, const char *num_citoyen, int num_parking,
                         const char *matricule_vehicule, const char *date_reservation, const char *service_reservation,
                         const char *status_reservation) {
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        if (f != NULL) fclose(f);
        if (temp != NULL) fclose(temp);
        return 0; // Failure
    }

    Reservation r;
    int found = 0;

    // Read each reservation and write updated data
    while (fscanf(f, "%d %d %d %49s %19s %49s %19s\n", &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation) == 7) {
        if (r.num_reservation == atoi(num_reservation)) {
            found = 1;
            fprintf(temp, "%d %d %d %s %s %s %s\n", atoi(num_reservation), atoi(num_citoyen), num_parking,
                    matricule_vehicule, date_reservation, service_reservation, status_reservation);
        } else {
            fprintf(temp, "%d %d %d %s %s %s %s\n", r.num_reservation, r.num_citoyen, r.num_parking,
                    r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation);
        }
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        return 1; // Success
    } else {
        remove("temp.txt");
        return 0; // Failure
    }
}

int is_num_reservation_unique(const char *filename, int num_reservation) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        return 1; // Assume unique if the file doesn't exist yet.
    }

    Reservation r;
    while (fscanf(f, "%d %d %d %49s %19s %49s %19s\n", &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation) == 7) {
        if (r.num_reservation == num_reservation) {
            fclose(f);
            return 0; // Num_reservation already exists.
        }
    }

    fclose(f);
    return 1; // Num_reservation is unique.
}


void load_reservations(const char *filename, GtkListStore *store) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    // Clear the store before populating it
    gtk_list_store_clear(store);

    Reservation r;
    GtkTreeIter iter;

    // Read each reservation and add it to the store
    while (fscanf(f, "%d %d %d %49s %19s %49s\n", &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation) == 6) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, r.num_reservation,
                           1, r.num_citoyen,
                           2, r.num_parking,
                           3, r.matricule_vehicule,
                           4, r.date_reservation,
                           5, r.service_reservation,
                           -1);
    }

    fclose(f);
}

void populate_tree_view(const char *filename, GtkTreeView *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *file;
    Reservation r;

    // Define the model with columns for each reservation field
    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Open the reservations file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier reservations.txt");
        return;
    }

    // Read each line and populate the list store
    while (fscanf(file, "%d %d %d %49s %19s %49s %19s\n", &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation) == 7) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, r.num_reservation,
                           1, r.num_citoyen,
                           2, r.num_parking,
                           3, r.matricule_vehicule,
                           4, r.date_reservation,
                           5, r.service_reservation,
                           6, r.status_reservation,
                           -1);
    }

    fclose(file);

    // Set the model to the TreeView
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));

    // Unreference the store as it's now handled by the TreeView
    g_object_unref(store);
}

void populate_parking_tree_view(const char *filename, GtkTreeView *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    Parking p;

    // Set up the model for the TreeView
    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(10,
                                   G_TYPE_INT,      // ID
                                   G_TYPE_STRING,   // Owner
                                   G_TYPE_STRING,   // Location
                                   G_TYPE_STRING,   // Date
                                   G_TYPE_INT,      // Capacity
                                   G_TYPE_FLOAT,    // Price
                                   G_TYPE_STRING,   // Type
                                   G_TYPE_STRING,   // Vehicle Type
                                   G_TYPE_STRING,   // Size
                                   G_TYPE_STRING);  // Phone
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
    }

    gtk_list_store_clear(store);

    f = fopen(filename, "r");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier des parkings.");
        return;
    }

    // Read each line from the file and populate the TreeView
    while (fscanf(f, "%d,%49[^,],%49[^,],%19[^,],%d,%f,%19[^,],%19[^,],%19[^,],%14s\n",
                  &p.id, p.owner, p.location, p.date, &p.capacity, &p.price,
                  p.type, p.vehicle_type, p.size, p.phone) == 10) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, p.id,
                           1, p.owner,
                           2, p.location,
                           3, p.date,
                           4, p.capacity,
                           5, p.price,
                           6, p.type,
                           7, p.vehicle_type,
                           8, p.size,
                           9, p.phone,
                           -1);
    }

    fclose(f);

    // Sort the GtkListStore by Capacity (column index 4)
    GtkTreeSortable *sortable = GTK_TREE_SORTABLE(store);
    gtk_tree_sortable_set_sort_column_id(sortable, 4, GTK_SORT_DESCENDING);
}


int update_reservation_parking(const char *filename, int reservation_id, int new_parking_id) {
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        if (f != NULL) fclose(f);
        if (temp != NULL) fclose(temp);
        return 0;
    }

    Reservation r;
    int found = 0;

    // Read each reservation and update the parking ID if it matches
    while (fscanf(f, "%d %d %d %49s %19s %49s %19s\n", &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation) == 7) {
        if (r.num_reservation == reservation_id) {
            found = 1;
            r.num_parking = new_parking_id; // Update the parking ID
        }
        fprintf(temp, "%d %d %d %s %s %s %s\n", r.num_reservation, r.num_citoyen, r.num_parking,
                r.matricule_vehicule, r.date_reservation, r.service_reservation, r.status_reservation);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
    } else {
        remove("temp.txt");
    }

    return found;
}

int update_parking_capacity(const char *filename, int parking_id, int decrement) {
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp_parkings.txt", "w");
    if (f == NULL || temp == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier des parkings.");
        if (f != NULL) fclose(f);
        if (temp != NULL) fclose(temp);
        return 0;
    }

    Parking p;
    int found = 0;

    // Read each parking and update the capacity for the matched ID
    while (fscanf(f, "%d,%49[^,],%49[^,],%19[^,],%d,%f,%19[^,],%19[^,],%19[^,],%14s\n",
                  &p.id, p.owner, p.location, p.date, &p.capacity, &p.price,
                  p.type, p.vehicle_type, p.size, p.phone) == 10) {
        if (p.id == parking_id) {
            found = 1;
            if (p.capacity > 0) {
                p.capacity -= decrement; // Decrease capacity
            } else {
                printf("Erreur : La capacité du parking %d est déjà à zéro.\n", parking_id);
            }
        }
        fprintf(temp, "%d,%s,%s,%s,%d,%.2f,%s,%s,%s,%s\n", p.id, p.owner, p.location, p.date,
                p.capacity, p.price, p.type, p.vehicle_type, p.size, p.phone);
    }

    fclose(f);
    fclose(temp);

    if (found) {
        remove(filename);
        rename("temp_parkings.txt", filename);
        return 1; // Success
    } else {
        remove("temp_parkings.txt");
        printf("Parking ID %d non trouvé.\n", parking_id);
        return 0; // Failure
    }
}




