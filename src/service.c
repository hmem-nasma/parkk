#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
#include "reservation.h"
#include <stdbool.h>

#define FICHIER "Service.txt"
#define FICHIER_RESERVATION "reservation.txt"


void sauvegarderService(Service service, FILE *fichier) {
    fprintf(fichier, "%d \"%s\" \"%s\" %.2f %d \"%s\"\n",
            service.numeroService,
            service.typeService,
            service.disponibilite,
            service.tarifService,
            service.dureeEstimee,
	    service.vehiculeconcerne
              );
}

bool ajouterService(Service service) {
    FILE *fichier = fopen(FICHIER, "a");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier pour l'écriture.");
        return false;
    }
    sauvegarderService(service, fichier);
    fclose(fichier);
    return true;
}
Service* chercherServiceParType(const char* typeService) {
    FILE *fichier = fopen(FICHIER, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s pour la lecture.\n", FICHIER);
        return NULL;
    }

    Service *service = malloc(sizeof(Service));
    if (service == NULL) {
        printf("Erreur : allocation mémoire échouée.\n");
        fclose(fichier);
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), fichier)) {
        sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %f %d \"%[^\"]\"",
               &service->numeroService,
               service->typeService,
               service->disponibilite,
               &service->tarifService,
               &service->dureeEstimee,
               service->vehiculeconcerne);

        // Comparer le type de service
        if (strcmp(service->typeService, typeService) == 0) {
            fclose(fichier);
            return service;
        }
    }

    fclose(fichier);
    free(service);
    return NULL;
}

char* convertir_en_utf8(const char *input) {
    GError *error = NULL;
    char *utf8_str = g_convert(input, -1, "UTF-8", "ISO-8859-1", NULL, NULL, &error);

    if (error) {
        g_warning("Erreur de conversion en UTF-8 : %s", error->message);
        g_error_free(error);
        return g_strdup(input); // Retourner la chaîne originale en cas d'erreur
    }
    return utf8_str;
}
bool modifierService(Service service) {
    FILE *fichier = fopen(FICHIER, "r");
    FILE *tempFichier = fopen("TempService.txt", "w");
    if (fichier == NULL || tempFichier == NULL) {
        printf("Erreur d'ouverture du fichier.");
        return false;
    }

    Service tempService;
    char line[256];
    int trouve = 0;
    while (fgets(line, sizeof(line), fichier)) {
        sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %f %d \"%[^\"]\"",
               &tempService.numeroService,
               tempService.typeService,
               tempService.disponibilite,
               &tempService.tarifService,
               &tempService.dureeEstimee,
		tempService.vehiculeconcerne	);

        if (tempService.numeroService == service.numeroService) {
            sauvegarderService(service, tempFichier);
            trouve = 1;
        } else {
            sauvegarderService(tempService, tempFichier);
        }
    }

    fclose(fichier);
    fclose(tempFichier);
    remove(FICHIER);
    rename("TempService.txt", FICHIER);

    if (!trouve) {
       return false;
    }
return true;
}
void remplir_combobox_services(GtkWidget *combobox) {
    FILE *file = fopen("Service.txt", "r");
    if (file == NULL) {
        g_print("Erreur : impossible d'ouvrir le fichier service.txt\n");
        return;
    }

    gchar line[256];
    while (fgets(line, sizeof(line), file)) {
        // Extraire le type de service (2ème élément de la ligne)
        gchar *token = strtok(line, " "); // Premier token : numéro de service
        if (token != NULL) {
            token = strtok(NULL, "\""); // Avancer jusqu'à l'ouverture du guillemet
            if (token != NULL) {
                // Ajouter le type au combobox
                gtk_combo_box_append_text(GTK_COMBO_BOX(combobox), token);
            }
        }
    }

    fclose(file);
}
void supprimer_element_combobox(GtkWidget *combobox, const char *valeur) {
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combobox));
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter_first(model, &iter)) { // Parcourir les éléments
        do {
            gchar *text;
            gtk_tree_model_get(model, &iter, 0, &text, -1); // Obtenir la valeur

            if (g_strcmp0(text, valeur) == 0) { // Comparer avec la valeur cible
                GtkListStore *list_store = GTK_LIST_STORE(model);
                gtk_list_store_remove(list_store, &iter); // Supprimer l'élément
                g_free(text);
                return; // Quitter une fois l'élément supprimé
            }

            g_free(text); // Libérer la mémoire de la valeur récupérée
        } while (gtk_tree_model_iter_next(model, &iter));
    }

    g_print("Élément '%s' introuvable dans le combobox.\n", valeur);
}
void remplir_treeview_services(GtkWidget *treeview)
{
    // Créez un modèle GtkListStore avec une colonne supplémentaire pour "vehiculeconcerne"
    GtkListStore *store = gtk_list_store_new(6,  // 6 colonnes pour 6 attributs
                                              G_TYPE_INT,    // colonne 1 : numeroService
                                              G_TYPE_STRING, // colonne 2 : typeService
                                              G_TYPE_STRING, // colonne 3 : disponibilite
                                              G_TYPE_FLOAT,  // colonne 4 : tarifService
                                              G_TYPE_INT,    // colonne 5 : dureeEstimee
                                              G_TYPE_STRING); // colonne 6 : vehiculeconcerne

    // Ouvrir le fichier pour lire les services
    FILE *fichier = fopen("Service.txt", "r");
    if (fichier == NULL) {
        g_print("Erreur d'ouverture du fichier Service.txt\n");
        return;
    }

    Service tempService;
    char line[256];
    while (fgets(line, sizeof(line), fichier)) {
        // Lire et parser chaque ligne
        sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %f %d \"%[^\"]\"",
               &tempService.numeroService,
               tempService.typeService,
               tempService.disponibilite,
               &tempService.tarifService,
               &tempService.dureeEstimee,
               tempService.vehiculeconcerne);

        // Ajouter les données dans le GtkListStore
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, tempService.numeroService,
                           1, tempService.typeService,
                           2, tempService.disponibilite,
                           3, tempService.tarifService,
                           4, tempService.dureeEstimee,
                           5, tempService.vehiculeconcerne,
                           -1);
    }

    fclose(fichier);

    // Associer le modèle de données au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Libérer le modèle lorsque le TreeView n'est plus nécessaire
    g_object_unref(store);
}

void configurer_treevieww(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // Créer le modèle de données pour le TreeView
    GtkListStore *store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Créer la première colonne "Numéro"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Numéro de Service");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 0); // Lier au champ 0 (numéroService)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // Créer la colonne "Type"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Type de Service");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 1); // Lier au champ 1 (typeService)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // Créer la colonne "Disponibilité"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Disponibilité");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 2); // Lier au champ 2 (disponibilite)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // Créer la colonne "Tarif"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Tarif");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 3); // Lier au champ 3 (tarifService)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // Créer la colonne "Durée"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Durée Estimée");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 4); // Lier au champ 4 (dureeEstimee)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // Créer la colonne "Véhicule Concerné"
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_set_title(column, "Véhicule Concerné");
    gtk_tree_view_column_add_attribute(column, renderer, "text", 5); // Lier au champ 5 (vehiculeconcerne)
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Ajouter les données au modèle (ici vous ajoutez des éléments manuellement ou à partir de votre fichier)
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, 123,                // numéro de service
                       1, "Lavage Complet",    // type de service
                       2, "7/7",               // disponibilité
                       3, 50.0,                // tarif
                       4, 30,                  // durée estimée
                       5, "Voiture, Bus",      // véhicules concernés
                       -1);
}

bool supprimerService(int *numeroService) {
    FILE *fichier = fopen(FICHIER, "r");
    FILE *tempFichier = fopen("TempService.txt", "w");
    if (fichier == NULL || tempFichier == NULL) {
        perror("Erreur d'ouverture du fichier.");
        return false;
    }

    Service tempService;
    char line[256];
    int trouve = 0;

    while (fgets(line, sizeof(line), fichier)) {
        // Lire chaque ligne et remplir la structure temporaire
        sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %f %d \"%[^\"]\"",
               &tempService.numeroService,
               tempService.typeService,
               tempService.disponibilite,
               &tempService.tarifService,
               &tempService.dureeEstimee,
               tempService.vehiculeconcerne);

        // Comparer le numéro de service
        if (tempService.numeroService == *numeroService) {
            trouve = 1; // Service trouvé, on ne l'écrit pas dans le fichier temporaire
        } else {
            sauvegarderService(tempService, tempFichier); // Sauvegarder les autres services
        }
    }

    fclose(fichier);
    fclose(tempFichier);

    // Remplacer l'ancien fichier par le nouveau
    if (remove(FICHIER) != 0) {
        perror("Erreur lors de la suppression du fichier original.");
        return false;
    }

    if (rename("TempService.txt", FICHIER) != 0) {
        perror("Erreur lors du renommage du fichier temporaire.");
        return false;
    }

    // Si le service n'a pas été trouvé
    if (!trouve) {
        fprintf(stderr, "Service avec le numéro %d introuvable.\n", *numeroService);
        return false;
    }

    printf("Service avec le numéro %d supprimé avec succès.\n", *numeroService);
    return true;
}

void listerServices() {
    FILE *fichier = fopen(FICHIER, "r");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier.");
        return;
    }

    Service service;
    char line[256];
    printf("Liste des services :\n");
    printf("N° Service | Type | Disponibilité | Tarif | Durée\n");
    while (fgets(line, sizeof(line), fichier)) {
        sscanf(line, "%d \"%[^\"]\" \"%[^\"]\" %f %d",
               &service.numeroService,
               service.typeService,
               service.disponibilite,
               &service.tarifService,
               &service.dureeEstimee);
        printf("%d | %s | %s | %.2f | %d\n",
               service.numeroService,
               service.typeService,
               service.disponibilite,
               service.tarifService,
               service.dureeEstimee);
    }
    fclose(fichier);
}
bool existeService(int numeroService, const char *typeService) {
    FILE *file = fopen("Service.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier Service.txt\n");
        return false;
    }

    int num;
    char type[50], disponibilite[20], vehicules[200];
    float tarif;
    int duree;

    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" %f %d \"%[^\"]\"\n", &num, type, disponibilite, &tarif, &duree, vehicules) != EOF) {
        if (num == numeroService || strcmp(type, typeService) == 0) {
            fclose(file);
            return true;  // Le numéro ou le type existe déjà
        }
    }

    fclose(file);
    return false;  // Pas trouvé
}


