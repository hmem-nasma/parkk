#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "reservation.h"



void on_button_supprimer_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *inputNumRes, *outputLabel;

    // Retrieve widgets
    inputNumRes = lookup_widget(GTK_WIDGET(button), "entr5"); // Entry for num_reservation
    outputLabel = lookup_widget(GTK_WIDGET(button), "label_feedback"); // Label for feedback

    // Get the reservation number from the input field
    const char *num_reservation_str = gtk_entry_get_text(GTK_ENTRY(inputNumRes));

    // Ensure the input is not empty
    if (strlen(num_reservation_str) == 0) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Veuillez entrer un numéro de réservation.");
        return;
    }

    // Convert the string to an integer
    int num_reservation = atoi(num_reservation_str);

    // Call the backend function to delete the reservation
    int result = supprimer_reservation("reservations.txt", num_reservation);

    // Display feedback based on the result
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Réservation supprimée avec succès !");
        gtk_entry_set_text(GTK_ENTRY(inputNumRes), ""); // Clear the input field
    } else {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Échec : Réservation introuvable.");
    }
}



void on_modifier_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *inputNumRes, *inputNumCit, *inputNumPark, *inputMatricule, *calendarDate, *comboService, *outputLabel;
    GtkWidget *radioConfirmer, *radioEnAttente, *radioAnnule;

    char num_reservation[20], num_citoyen[20], matricule_vehicule[50], service_reservation[50], date_reservation[20], status_reservation[20];
    int num_parking;
    guint year, month, day;
    int result; // Variable to track success of the operation

    // Retrieve widgets from the interface
    inputNumRes = lookup_widget(GTK_WIDGET(button), "entresv");
    inputNumCit = lookup_widget(GTK_WIDGET(button), "entrnumcit");
    inputNumPark = lookup_widget(GTK_WIDGET(button), "spnbnumpark");
    inputMatricule = lookup_widget(GTK_WIDGET(button), "entrmatr3");
    calendarDate = lookup_widget(GTK_WIDGET(button), "calendar16");
    comboService = lookup_widget(GTK_WIDGET(button), "comsev");
    outputLabel = lookup_widget(GTK_WIDGET(button), "label_reslt");

    // Retrieve radio buttons for status
    radioConfirmer = lookup_widget(GTK_WIDGET(button), "radioConfirmerModify");
    radioEnAttente = lookup_widget(GTK_WIDGET(button), "radioEnAttenteModify");
    radioAnnule = lookup_widget(GTK_WIDGET(button), "radioAnnuleModify");

    // Retrieve input values from entries
    strcpy(num_reservation, gtk_entry_get_text(GTK_ENTRY(inputNumRes)));
    strcpy(num_citoyen, gtk_entry_get_text(GTK_ENTRY(inputNumCit)));
    strcpy(matricule_vehicule, gtk_entry_get_text(GTK_ENTRY(inputMatricule)));
    num_parking = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(inputNumPark));

    // Retrieve the selected date from the calendar
    gtk_calendar_get_date(GTK_CALENDAR(calendarDate), &year, &month, &day);
    sprintf(date_reservation, "%04d-%02d-%02d", year, month + 1, day);

    // Retrieve the active text from the combo box
    const char *selected_service = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboService));
    if (selected_service != NULL) {
        strcpy(service_reservation, selected_service);
    } else {
        strcpy(service_reservation, "0");
    }

    // Determine the selected status
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioConfirmer))) {
        strcpy(status_reservation, "confirme");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioEnAttente))) {
        strcpy(status_reservation, "en_attente");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioAnnule))) {
        strcpy(status_reservation, "annule");
    } else {
        strcpy(status_reservation, ""); // Default if no selection
    }

    // Call the backend function to modify reservation
    result = modifier_reservation("reservations.txt", num_reservation, num_citoyen, num_parking, matricule_vehicule,
                                   date_reservation, service_reservation, status_reservation);

    // Display feedback based on the result
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Modification réussie !");
    } else {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Échec de la modification : Réservation introuvable.");
    }
}

void on_ajouter_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *inputNumRes, *inputNumCit, *spinNumPark, *inputMatricule, *comboService, *outputLabel;
    GtkWidget *calendarDate;
    GtkWidget *radioConfirmer, *radioEnAttente, *radioAnnule;

    char num_reservation[20], num_citoyen[20];
    int num_parking;
    char matricule_vehicule[50], service_reservation[50], date_reservation[20], status_reservation[20];
    int test; // Variable to track success of the operation
    guint year, month, day;

    // Retrieve widgets from the interface
    inputNumRes = lookup_widget(GTK_WIDGET(button), "entr7");         // Entry for num_reservation
    inputNumCit = lookup_widget(GTK_WIDGET(button), "entr");          // Entry for num_citoyen
    spinNumPark = lookup_widget(GTK_WIDGET(button), "spinNumPark");   // SpinButton for num_parking
    inputMatricule = lookup_widget(GTK_WIDGET(button), "entrmat");    // Entry for matricule_vehicule
    comboService = lookup_widget(GTK_WIDGET(button), "comboService"); // ComboBox for service_reservation
    calendarDate = lookup_widget(GTK_WIDGET(button), "calendarDate"); // Calendar widget for date_reservation
    outputLabel = lookup_widget(GTK_WIDGET(button), "lablResult");    // Label for feedback

    // Radio buttons for status
    radioConfirmer = lookup_widget(GTK_WIDGET(button), "radioConfirmer");
    radioEnAttente = lookup_widget(GTK_WIDGET(button), "radioEnAttente");
    radioAnnule = lookup_widget(GTK_WIDGET(button), "radioAnnule");

    // Retrieve input values from entries
    strcpy(num_reservation, gtk_entry_get_text(GTK_ENTRY(inputNumRes)));
    strcpy(num_citoyen, gtk_entry_get_text(GTK_ENTRY(inputNumCit)));
    num_parking = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinNumPark));
    strcpy(matricule_vehicule, gtk_entry_get_text(GTK_ENTRY(inputMatricule)));
     
    // Validation des champs Num_reservation et Num_citoyen
    if (atoi(num_reservation) <= 0) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Erreur : Num_reservation doit être un entier positif.");
        return;
    }

    if (atoi(num_citoyen) <= 0) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Erreur : Num_citoyen doit être un entier positif.");
        return;
    }

    // Vérification de l'unicité de Num_reservation
    if (!is_num_reservation_unique("reservations.txt", atoi(num_reservation))) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Erreur : Num_reservation doit être unique.");
        return;
    }


    // Retrieve the selected value from the combo box
    const char *selected_service = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(comboService));
    if (selected_service != NULL) {
        strcpy(service_reservation, selected_service);
    } else {
        strcpy(service_reservation, "0"); // Default to "0" if no selection
    }

    // Retrieve the date from the calendar
    gtk_calendar_get_date(GTK_CALENDAR(calendarDate), &year, &month, &day);
    sprintf(date_reservation, "%04d-%02d-%02d", year, month + 1, day); // Format date as YYYY-MM-DD

    // Determine the selected status
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioConfirmer))) {
        strcpy(status_reservation, "confirme");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioEnAttente))) {
        strcpy(status_reservation, "en_attente");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioAnnule))) {
        strcpy(status_reservation, "annule");
    } else {
        strcpy(status_reservation, ""); // Default if no selection
    }

    // Convert num_parking to a string
    char num_parking_str[10];
    sprintf(num_parking_str, "%d", num_parking);

    // Call the backend function to add reservation
    test = ajouter(num_reservation, num_citoyen, num_parking_str, matricule_vehicule, date_reservation, service_reservation, status_reservation);

    // Display feedback based on the result
    if (test == 1) {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Insertion réussie !");
    } else {
        gtk_label_set_text(GTK_LABEL(outputLabel), "Échec de l'insertion.");
    }

    // Optionally, clear input fields after successful insertion
    if (test == 1) {
        gtk_entry_set_text(GTK_ENTRY(inputNumRes), "");
        gtk_entry_set_text(GTK_ENTRY(inputNumCit), "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinNumPark), 0);
        gtk_entry_set_text(GTK_ENTRY(inputMatricule), "");
        gtk_combo_box_set_active(GTK_COMBO_BOX(comboService), -1); // Reset combo box to no selection
    }
}




void on_radioAnnule_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        // Logic when "Annulé" is selected
        printf("Radio button 'Annulé' selected.\n");
    }
}

void on_radioEnAttente_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        // Logic when "En Attente" is selected
        printf("Radio button 'En Attente' selected.\n");
    }
}

void on_radioConfirmer_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        // Logic when "Confirmé" is selected
        printf("Radio button 'Confirmé' selected.\n");
    }
}






// Global variable to store the current status
char current_status_modify[20] = "";

void on_radioConfirmerModify_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(current_status_modify, "confirme");
        printf("Radio button 'Confirmer' toggled: status set to 'confirme'.\n");
    }
}

void on_radioEnAttenteModify_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(current_status_modify, "en_attente");
        printf("Radio button 'En Attente' toggled: status set to 'en_attente'.\n");
    }
}

void on_radioAnnuleModify_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(current_status_modify, "annule");
        printf("Radio button 'Annulé' toggled: status set to 'annule'.\n");
    }
}

void setup_tree_view(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

// Column 1: Num_reservation
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Num_reservation", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 2: Num_citoyen
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Num_citoyen", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 3: Num_parking
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Num_parking", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 4: Matricule_vehicule
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Matricule_vehicule", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 5: Date_reservation
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date_reservation", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 6: Service_reservation
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Service_reservation", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 7: Status_reservation
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Status_reservation", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);
}



void on_Actualiser_clicked(GtkButton *button, gpointer user_data) {
    GtkTreeView *treeview;

    // Find the treeview widget by its name ("tableaures")
    treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "tableaures"));

    if (treeview != NULL) {
        // Setup the tree view columns (if not already done)
        setup_tree_view(treeview);

        // Populate the tree view with data from reservations.txt
        populate_tree_view("reservations.txt", treeview);
    }
}



void on_btn_search_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_search = lookup_widget(GTK_WIDGET(button), "entry_search");
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "tableaures"));

    // Retrieve the search input from the entry field
    const char *search_text = gtk_entry_get_text(GTK_ENTRY(entry_search));
    if (strlen(search_text) == 0) {
        // If the search entry is empty, display all reservations
        populate_tree_view("reservations.txt", treeview);
        return;
    }

    int search_id = atoi(search_text);
    if (search_id <= 0) {
        g_print("Invalid search input: %s\n", search_text);
        return;
    }

    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    Reservation r;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
    }

    gtk_list_store_clear(store);

    f = fopen("reservations.txt", "r");
    if (f == NULL) {
        perror("Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    while (fscanf(f, "%d %d %d %49s %19s %49s %19s\n",
                  &r.num_reservation, &r.num_citoyen, &r.num_parking,
                  r.matricule_vehicule, r.date_reservation,
                  r.service_reservation, r.status_reservation) == 7) {
        if (r.num_reservation == search_id) {
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
    }

    fclose(f);
}

void setup_parking_tree_view(GtkTreeView *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // Column 1: ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 2: Owner
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Owner", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 3: Location
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Location", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 4: Date
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 5: Capacity
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacity", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 6: Price
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Price", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 7: Type
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 8: Vehicle Type
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Vehicle Type", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 9: Size
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Size", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);

    // Column 10: Phone
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Phone", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(treeview, column);
}



void
on_actualiseparking_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkTreeView *treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "treeparcking"));

    // Setup the tree view columns (if not already done)
    setup_parking_tree_view(treeview);

    // Populate the tree view with data from parkings.txt
    populate_parking_tree_view("parkings.txt", treeview);
}


int selected_parking_id = -1; // Global variable to store the selected parking ID

void on_treeparcking_row_activated(GtkTreeView *treeview,
                                   GtkTreePath *path,
                                   GtkTreeViewColumn *column,
                                   gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model(treeview);

    // Check if the path corresponds to a valid row
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &selected_parking_id, -1); // Column 0 contains parking ID
        printf("Selected Parking ID: %d\n", selected_parking_id);
    } else {
        selected_parking_id = -1; // Reset if no valid selection
        printf("No valid row selected.\n");
    }
}




void on_btn_affecter_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry;
    GtkWidget *dialog; // For the popup window
    const char *reservation_id_str;
    int reservation_id;

    // Retrieve the entry widget and get the text
    entry = lookup_widget(GTK_WIDGET(button), "entry_num_res_aff");
    reservation_id_str = gtk_entry_get_text(GTK_ENTRY(entry));
    reservation_id = atoi(reservation_id_str);

    // Validate reservation ID
    if (reservation_id <= 0) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                        "Erreur : ID de réservation invalide.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Ensure a parking is selected
    if (selected_parking_id == -1) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                        "Erreur : Aucun parking sélectionné.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Update the reservation with the new parking ID
    if (update_reservation_parking("reservations.txt", reservation_id, selected_parking_id)) {
        // Update the capacity of the selected parking
        if (update_parking_capacity("parkings.txt", selected_parking_id, 1)) {
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                            GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                            "Affectation réussie :\nParking ID %d assigné à Réservation ID %d.\nCapacité mise à jour.",
                                            selected_parking_id, reservation_id);
        } else {
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
                                            "Affectation réussie, mais échec de la mise à jour de la capacité.");
        }
    } else {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                        "Erreur : Réservation ID %d introuvable.", reservation_id);
    }

    // Show the dialog and destroy it after the user interacts
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


