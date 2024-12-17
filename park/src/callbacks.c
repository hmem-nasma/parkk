#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "parking.h"


 
void
on_buttonCreerCompte_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *windowInscription, *windowLogin ;

windowLogin = lookup_widget(objet_graphique, "windowLogin");
gtk_widget_destroy(windowLogin);
windowInscription = create_windowInscription ();
gtk_widget_show (windowInscription);


}


void
on_buttonLoginInscrire_clicked         (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *windowInscription, *windowLogin ;

windowInscription = lookup_widget(objet_graphique, "windowInscription");
gtk_widget_destroy(windowInscription);
windowLogin = create_windowLogin ();
gtk_widget_show (windowLogin);
}


void
on_buttonInscription_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *windowInscription, *windowLogin ;
    GtkWidget *inputLogin, *inputPassword, *inputNom, *output;
    GtkWidget *radioRole1, *radioRole2;
    char login[110] = "", password[110] = "", nom[110] = "", role[110] = "";
    char messageErreur[256] = "";
    int test;
    
     

    windowInscription = lookup_widget(objet_graphique, "windowInscription");

    // Récupération des widgets
    inputLogin = lookup_widget(objet_graphique, "entryLoginL");
    inputPassword = lookup_widget(objet_graphique, "entryPasswordL");
    inputNom = lookup_widget(objet_graphique, "entryNomL");
    radioRole1 = lookup_widget(objet_graphique, "radioRoleAdminL");
    radioRole2 = lookup_widget(objet_graphique, "radioRoleUserL");
    output = lookup_widget(objet_graphique, "labelResultatUtilisateurL");

    // Récupération des valeurs
    strcpy(login, gtk_entry_get_text(GTK_ENTRY(inputLogin)));
    strcpy(password, gtk_entry_get_text(GTK_ENTRY(inputPassword)));
    strcpy(nom, gtk_entry_get_text(GTK_ENTRY(inputNom)));

    // Déterminer le rôle
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioRole1))) {
        strcpy(role, "Administrateur");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioRole2))) {
        strcpy(role, "Citoyen");
    } else {
        strcat(messageErreur, "Veuillez sélectionner un rôle.\n");
    }

    // Validation des champs
    if (strlen(login) == 0) {
        strcat(messageErreur, "Le champ 'Login' est vide.\n");
    }
    if (strlen(password) == 0) {
        strcat(messageErreur, "Le champ 'Password' est vide.\n");
    }
    if (strlen(nom) == 0) {
        strcat(messageErreur, "Le champ 'Nom' est vide.\n");
    }

    // Affichage des erreurs ou validation
    if (strlen(messageErreur) > 0) {
        gtk_label_set_text(GTK_LABEL(output), messageErreur);
        return;
    }

    // Appel de la fonction d'ajout
    test = Ajout_Utilisateur(login, password, nom, role);

    // Affichage du résultat
    if (test == 1) {
    
     gtk_widget_destroy(windowInscription);
     windowLogin = create_windowLogin ();
     gtk_widget_show (windowLogin);
         
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Insertion non validée (Login déjà existant).");
    }
}


void
on_buttonAuthentification_clicked      (GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *windowMenu, *windowLogin ;
    


    GtkWidget *inputLogin, *inputPassword, *output;
    char login[110] = "", password[110] = "", messageErreur[256] = "";
    int verification; 
      
     windowLogin = lookup_widget(objet_graphique, "windowLogin");
     

    // Récupération des widgets
    inputLogin = lookup_widget(objet_graphique, "entryLoginI");
    inputPassword = lookup_widget(objet_graphique, "entryPasswordI");
    output = lookup_widget(objet_graphique, "labelResultatI");

    // Récupération des valeurs
    strcpy(login, gtk_entry_get_text(GTK_ENTRY(inputLogin)));
    strcpy(password, gtk_entry_get_text(GTK_ENTRY(inputPassword)));

    // Validation des champs
    if (strlen(login) == 0) {
        strcat(messageErreur, "Le champ 'Login' est vide.\n");
    }
    if (strlen(password) == 0) {
        strcat(messageErreur, "Le champ 'Password' est vide.\n");
    }

    // Affichage des erreurs
    if (strlen(messageErreur) > 0) {
        gtk_label_set_text(GTK_LABEL(output), messageErreur);
        return;
    }

    // Appel de la fonction de vérification
    verification = Verifier_Utilisateur(login, password);

    // Affichage du résultat
    if (verification == 1) {
     gtk_widget_destroy(windowLogin);
     windowMenu = create_windowMenu ();
     gtk_widget_show (windowMenu);
   
     
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Login ou mot de passe incorrect.");
    }
}


void
on_buttonGestionParkihg_clicked        (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,*windowGestionParking;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
  windowGestionParking = create_windowGestionParking ();
  gtk_widget_show (windowGestionParking);
}


void
on_buttonGestionReservation_clicked    (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,*windowGestionReservation;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
  windowGestionReservation = create_windowGestionReservation ();
  gtk_widget_show (windowGestionReservation);
}


void
on_buttonGestionService_clicked        (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,*windowGestionService;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
 windowGestionService = create_windowGestionService ();
  gtk_widget_show (windowGestionService);
}


void
on_buttonGestionAgent_clicked          (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu, *windowGestionAgent;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
  windowGestionAgent = create_windowGestionAgent ();
  gtk_widget_show (windowGestionAgent);
}


void
on_buttonGestionCitoyen_clicked        (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu, *windowGestionCitoyen;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
 windowGestionCitoyen = create_windowGestionCitoyen ();
  gtk_widget_show (windowGestionCitoyen);
}


void
on_buttonGestionReclamation_clicked    (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,*windowGestionReclamation ;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
 windowGestionReclamation = create_windowGestionReclamation ();
  gtk_widget_show (windowGestionReclamation);
}


void
on_buttonQuitterMenu_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu;
 windowMenu = lookup_widget(objet_graphique, "windowMenu");
 gtk_widget_destroy(windowMenu);
}


void
on_buttonAjouterParking_clicked        (GtkWidget *objet_graphique, gpointer user_data)
{
     GtkWidget *inputNom, *inputPrix, *inputAdresse, *output;
    GtkWidget *checkSeurite1, *checkSeurite2;
    GtkWidget *spinJour, *spinMois, *spinAnnee, *spinNumero, *spinCapacite;
    GtkWidget *radioSecteur1, *radioSecteur2;
    char nom[110] = "", adresse[110] = "", securite[500] = "", secteur[110] = "", agent[110] = "Absent";
    int test, numero, capacite, jour, mois, annee;
    float prix;
    char messageErreur[256] = "";

    // Récupération des widgets
    spinNumero = lookup_widget(objet_graphique, "spinNumeroPJ");
    inputNom = lookup_widget(objet_graphique, "entryNomPJ");
    spinCapacite = lookup_widget(objet_graphique, "spinCapacitePJ");
    inputPrix = lookup_widget(objet_graphique, "entryPrixPJ");
    spinJour = lookup_widget(objet_graphique, "spinJourPJ");
    spinMois = lookup_widget(objet_graphique, "spinMoisPJ");
    spinAnnee = lookup_widget(objet_graphique, "spinAnneePJ");
    inputAdresse = lookup_widget(objet_graphique, "entryAdressePJ");
    checkSeurite1 = lookup_widget(objet_graphique, "checkSecuritePJ1");
    checkSeurite2 = lookup_widget(objet_graphique, "checkSecuritePJ2");
    radioSecteur1 = lookup_widget(objet_graphique, "radioSecteurPJ1");
    radioSecteur2 = lookup_widget(objet_graphique, "radioSecteurPJ2");
    output = lookup_widget(objet_graphique, "labelResultatPJ");

    // Récupération des valeurs
    strcpy(nom, gtk_entry_get_text(GTK_ENTRY(inputNom)));
    strcpy(adresse, gtk_entry_get_text(GTK_ENTRY(inputAdresse)));
    prix = atof(gtk_entry_get_text(GTK_ENTRY(inputPrix)));
    numero = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinNumero));
    capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinCapacite));

    // Récupérer la date
    jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinJour));
    mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinMois));
    annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinAnnee));

    // Déterminer le secteur
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioSecteur1))) {
        strcpy(secteur, "Prive");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioSecteur2))) {
        strcpy(secteur, "Publique");
    } else {
        strcat(messageErreur, "Veuillez sélectionner un secteur.\n");
    }

    // Ajouter la sécurité
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkSeurite1))) {
    if (strlen(securite) > 0) {
        strcat(securite, "/");
    }
    strcat(securite, "camira");
   }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkSeurite2))) {
    if (strlen(securite) > 0) {
        strcat(securite, "/");
    }
    strcat(securite, "gardien");
  }
    if (strlen(securite) == 0) {
        strcat(messageErreur, "Veuillez sélectionner une sécurité.\n");
    }

    // Validation de la date
    if ((jour <= 0 || mois <= 0 || mois > 12 || annee <= 0) ||
        (mois == 2 && jour > 29) || 
        ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30)) {
        strcat(messageErreur, "La date est invalide.\n");
    }

    // Vérification des champs
    if (strlen(nom) == 0) {
        strcat(messageErreur, "Le champ 'Nom' est vide.\n");
    }
    if (strlen(adresse) == 0) {
        strcat(messageErreur, "Le champ 'Adresse' est vide.\n");
    }
    if (prix <= 0) {
        strcat(messageErreur, "Le champ 'Prix' est invalide.\n");
    }
    if (numero <= 0) {
        strcat(messageErreur, "Le numéro est invalide.\n");
    }
    if (capacite <= 0) {
        strcat(messageErreur, "La capacité est invalide.\n");
    }

    // Affichage des erreurs ou validation
    if (strlen(messageErreur) > 0) {
        gtk_label_set_text(GTK_LABEL(output), messageErreur);
        return;
    }

    // Appel de la fonction d'ajout
    test = Ajout_Parking(numero, nom, capacite, prix, jour, mois, annee, adresse, securite, secteur, agent);

    // Affichage du résultat
    if (test == 1) {
        gtk_label_set_text(GTK_LABEL(output), "Insertion validée.");
        
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Insertion non validée (Numéro ou Nom déjà existant).");
    }
}


void
on_buttonMenuPJ_clicked                (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,* windowGestionParking;
  windowGestionParking = lookup_widget(objet_graphique, "windowGestionParking");
 gtk_widget_destroy(windowGestionParking);
  windowMenu = create_windowMenu ();
  gtk_widget_show (windowMenu);
}


void
on_buttonModifierParking_clicked       (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *spinNumero, *inputNom, *spinCapacite, *inputPrix;
    GtkWidget *spinJour, *spinMois, *spinAnnee, *inputAdresse;
    GtkWidget *checkSecurite1, *checkSecurite2, *radioSecteur1, *radioSecteur2;
    GtkWidget *output;

    char nom[110] = "", adresse[110] = "", securite[500] = "", secteur[110] = "";
    char messageErreur[256] = "";
    int numero, capacite, jour, mois, annee;
    float prix;

    // Récupération des widgets
    spinNumero = lookup_widget(objet_graphique, "spinNumeroPM");
    inputNom = lookup_widget(objet_graphique, "entryNomPM");
    spinCapacite = lookup_widget(objet_graphique, "spinCapacitePM");
    inputPrix = lookup_widget(objet_graphique, "entryPrixPM");
    spinJour = lookup_widget(objet_graphique, "spinJourPM");
    spinMois = lookup_widget(objet_graphique, "spinMoisPM");
    spinAnnee = lookup_widget(objet_graphique, "spinAnneePM");
    inputAdresse = lookup_widget(objet_graphique, "entryAdressePM");
    checkSecurite1 = lookup_widget(objet_graphique, "checkSecuritePM1");
    checkSecurite2 = lookup_widget(objet_graphique, "checkSecuritePM2");
    radioSecteur1 = lookup_widget(objet_graphique, "radioSecteurPM1");
    radioSecteur2 = lookup_widget(objet_graphique, "radioSecteurPM2");
    output = lookup_widget(objet_graphique, "labelResultatPM");

    // Récupération des données
    numero = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinNumero));
    strncpy(nom, gtk_entry_get_text(GTK_ENTRY(inputNom)), sizeof(nom) - 1);
    nom[sizeof(nom) - 1] = '\0';
    capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinCapacite));
    prix = atof(gtk_entry_get_text(GTK_ENTRY(inputPrix)));
    jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinJour));
    mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinMois));
    annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinAnnee));
    strncpy(adresse, gtk_entry_get_text(GTK_ENTRY(inputAdresse)), sizeof(adresse) - 1);
    adresse[sizeof(adresse) - 1] = '\0';

    // Construction de la chaîne pour la sécurité
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkSecurite1))) {
        strcat(securite, "camira");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkSecurite2))) {
        if (strlen(securite) > 0) {
            strcat(securite, "/");
        }
        strcat(securite, "gardien");
    }

    if (strlen(securite) == 0) {
        strcat(messageErreur, "Veuillez sélectionner une sécurité.\n");
    }

    // Détermination du secteur
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioSecteur1))) {
        strcpy(secteur, "Prive");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioSecteur2))) {
        strcpy(secteur, "Publique");
    } else {
        strcat(messageErreur, "Veuillez sélectionner un secteur.\n");
    }

    // Validation de la date
    if ((jour <= 0 || mois <= 0 || mois > 12 || annee <= 0) ||
        (mois == 2 && jour > 29) || 
        ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30)) {
        strcat(messageErreur, "La date est invalide.\n");
    }

    // Validation des autres champs
    if (strlen(nom) == 0) {
        strcat(messageErreur, "Le champ 'Nom' est vide.\n");
    }
    if (strlen(adresse) == 0) {
        strcat(messageErreur, "Le champ 'Adresse' est vide.\n");
    }
    if (prix <= 0) {
        strcat(messageErreur, "Le champ 'Prix' est invalide.\n");
    }
    if (numero <= 0) {
        strcat(messageErreur, "Le numéro est invalide.\n");
    }
    if (capacite <= 0) {
        strcat(messageErreur, "La capacité est invalide.\n");
    }

    // Affichage des erreurs ou modification
    if (strlen(messageErreur) > 0) {
        gtk_label_set_text(GTK_LABEL(output), messageErreur);
        return;
    }

    // Appel à la fonction de modification
    if (Modifier_Parking(numero, nom, capacite, prix, jour, mois, annee, adresse, securite, secteur)) {
        gtk_label_set_text(GTK_LABEL(output), "Parking modifié avec succès !");
        
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Parking introuvable ou problème de modification.");
    }
}


void
on_buttonRecupererPM_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *spinNumero, *inputNom, *inputPrix, *inputAdresse;
    GtkWidget *checkSeurite1, *checkSeurite2;
    GtkWidget *spinJour, *spinMois, *spinAnnee, *spinCapacite;
    GtkWidget *radioSecteur1, *radioSecteur2;
    GtkWidget *output;

    char nom[110] = "", adresse[110] = "", securite[110] = "", secteur[110] = "";
    int numero, capacite, jour, mois, annee;
    float prix;

    spinNumero = lookup_widget(objet_graphique, "spinNumeroPM");
    inputNom = lookup_widget(objet_graphique, "entryNomPM");
    spinCapacite = lookup_widget(objet_graphique, "spinCapacitePM");
    inputPrix = lookup_widget(objet_graphique, "entryPrixPM");
    spinJour = lookup_widget(objet_graphique, "spinJourPM");
    spinMois = lookup_widget(objet_graphique, "spinMoisPJ");
    spinAnnee = lookup_widget(objet_graphique, "spinAnneePM");
    inputAdresse = lookup_widget(objet_graphique, "entryAdressePM");
    checkSeurite1 = lookup_widget(objet_graphique, "checkSecuritePM1");
    checkSeurite2 = lookup_widget(objet_graphique, "checkSecuritePM2");
    radioSecteur1 = lookup_widget(objet_graphique, "radioSecteurPM1");
    radioSecteur2 = lookup_widget(objet_graphique, "radioSecteurPM2");
    output = lookup_widget(objet_graphique, "labelResultatPM");

    numero = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinNumero));

    if (Rechercher_Parking(numero, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur)) {
        gtk_entry_set_text(GTK_ENTRY(inputNom), nom);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinCapacite), capacite);
        char *prix_str = g_strdup_printf("%.2f", prix);
        gtk_entry_set_text(GTK_ENTRY(inputPrix), prix_str);
        g_free(prix_str);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinJour), jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinMois), mois);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinAnnee), annee);
        gtk_entry_set_text(GTK_ENTRY(inputAdresse), adresse);

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkSeurite1),strstr(securite, "camira") != NULL);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkSeurite2),strstr(securite, "gardien") != NULL);
        
        if(strcmp(secteur, "Prive")==0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioSecteur1),TRUE);
         else if(strcmp(secteur, "Publique") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioSecteur2), TRUE);

        gtk_label_set_text(GTK_LABEL(output), "Parking trouvé et informations chargées.");
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Parking introuvable.");
    }
}


void
on_buttonMenuPM_clicked                (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,* windowGestionParking;
  windowGestionParking = lookup_widget(objet_graphique, "windowGestionParking");
 gtk_widget_destroy(windowGestionParking);
  windowMenu = create_windowMenu ();
  gtk_widget_show (windowMenu);
}


void configurer_treeview(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

      // Supprimer toutes les colonnes existantes
       gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), NULL);
      while (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) != NULL) {
        gtk_tree_view_remove_column(GTK_TREE_VIEW(treeview), gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0));}

    // Colonne 1 : Numéro
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Numéro", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 2 : Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 3 : Capacité
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 4 : Prix
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 5 : Date
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 6 : Adresse
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 7 : Sécurité
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sécurité", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 8 : Secteur
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Secteur", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 9 : Agent
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Agent", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}

 



 

void
on_buttonMenuPCH_clicked               (GtkWidget *objet_graphique, gpointer user_data)
{
 GtkWidget *windowMenu,* windowGestionParking;
  windowGestionParking = lookup_widget(objet_graphique, "windowGestionParking");
 gtk_widget_destroy(windowGestionParking);
  windowMenu = create_windowMenu ();
  gtk_widget_show (windowMenu);
}



void remplir_treeview_Trier_Capacite(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *fichier = fopen("Parking.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Créer un modèle GtkListStore
    store = gtk_list_store_new(9, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    int numero, capacite, jour, mois, annee;
    float prix;
    char nom[110], adresse[500], securite[50], secteur[50], agent[100], date[20];

    while (fscanf(fichier, "%d,%109[^,],%d,%f,%d,%d,%d,%499[^,],%499[^,],%49[^,],%99s\n",
                  &numero, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur, agent) == 11) {
        snprintf(date, sizeof(date), "%02d/%02d/%04d", jour, mois, annee);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, numero,
                           1, nom,
                           2, capacite,
                           3, prix,
                           4, date,
                           5, adresse,
                           6, securite,
                           7, secteur,
                           8, agent,
                           -1);
    }

    fclose(fichier);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Décrémenter le compteur de référence du modèle
    g_object_unref(store);

    // Set default sorting by "Capacité" (column index 2)
    GtkTreeSortable *sortable = GTK_TREE_SORTABLE(store);
    gtk_tree_sortable_set_sort_column_id(sortable, 2, GTK_SORT_ASCENDING);
}


void
on_buttonParkingTrier_clicked          (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *treeview;

    // Récupérer le TreeView
    treeview = lookup_widget(objet_graphique, "treeview1");

    // Configurer le TreeView
    configurer_treeview(treeview);

    // Remplir le TreeView avec les données
    remplir_treeview_Trier_Capacite(treeview); 
}


void remplir_treeview_Avec_Agent(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *fichier = fopen("Parking.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Créer un modèle GtkListStore
    store = gtk_list_store_new(9, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    int numero, capacite, jour, mois, annee;
    float prix;
    char nom[110], adresse[500], securite[50], secteur[50], agent[100], date[20]; // Added agent and date

    while (fscanf(fichier, "%d,%109[^,],%d,%f,%d,%d,%d,%499[^,],%499[^,],%49[^,],%99s\n",
                  &numero, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur, agent) == 11) {
        // Skip rows where the agent is "Absent"
        if (strcmp(agent, "Absent") == 0) {
            continue;
        }

        // Combine jour, mois, annee into a single date string
        snprintf(date, sizeof(date), "%02d/%02d/%04d", jour, mois, annee);

        // Ajouter une ligne au modèle
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, numero,
                           1, nom,
                           2, capacite,
                           3, prix,
                           4, date,  // Set the combined date string
                           5, adresse,
                           6, securite,
                           7, secteur,
                           8, agent,  // Set the agent string
                           -1);
    }

    fclose(fichier);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Décrémenter le compteur de référence du modèle
    g_object_unref(store);
}


void
on_buttonParkingAvecAgent_clicked      (GtkWidget *objet_graphique, gpointer user_data)
{
     GtkWidget *treeview;

    // Récupérer le TreeView
    treeview = lookup_widget(objet_graphique, "treeview1");

    // Configurer le TreeView
    configurer_treeview(treeview);

    // Remplir le TreeView avec les données
    remplir_treeview_Avec_Agent(treeview); 
}


void remplir_treeview_Sans_Agent(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *fichier = fopen("Parking.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Créer un modèle GtkListStore
    store = gtk_list_store_new(9, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_FLOAT,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    int numero, capacite, jour, mois, annee;
    float prix;
    char nom[110], adresse[500], securite[50], secteur[50], agent[100], date[20]; // Added agent and date

    while (fscanf(fichier, "%d,%109[^,],%d,%f,%d,%d,%d,%499[^,],%499[^,],%49[^,],%99s\n",
                  &numero, nom, &capacite, &prix, &jour, &mois, &annee, adresse, securite, secteur, agent) == 11) {
        // Skip rows where the agent is "Absent"
        if (strcmp(agent, "Absent") != 0) {
            continue;
        }

        // Combine jour, mois, annee into a single date string
        snprintf(date, sizeof(date), "%02d/%02d/%04d", jour, mois, annee);

        // Ajouter une ligne au modèle
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, numero,
                           1, nom,
                           2, capacite,
                           3, prix,
                           4, date,  // Set the combined date string
                           5, adresse,
                           6, securite,
                           7, secteur,
                           8, agent,  // Set the agent string
                           -1);
    }

    fclose(fichier);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Décrémenter le compteur de référence du modèle
    g_object_unref(store);
}
 

void
on_buttonParkingSansAgent_clicked      (GtkWidget *objet_graphique, gpointer user_data)
{
  GtkWidget *treeview;

    // Récupérer le TreeView
    treeview = lookup_widget(objet_graphique, "treeview1");

    // Configurer le TreeView
    configurer_treeview(treeview);

    // Remplir le TreeView avec les données
    remplir_treeview_Sans_Agent(treeview); 
}


void
on_buttonActualiserLPS_clicked         (GtkWidget *objet_graphique, gpointer user_data)
{
   GtkWidget *comboAgent;
    int i;
    char noms[100][110]; // Assuming max of 100 parking names
    int count;

    comboAgent = lookup_widget(objet_graphique, "comboboxParkingPS");
    if (comboAgent == NULL) {
        g_print("Erreur : le widget comboAgent est introuvable.\n");
        return;
    }

    // Clear the existing items in the combo box
    gtk_combo_box_remove_text(GTK_COMBO_BOX(comboAgent), 0);

    // Retrieve parking names from the function
    count = Rechercher_Noms_Parking(noms, 100);
    if (count == -1) {
        g_print("Erreur : impossible d'ouvrir le fichier Parking.txt.\n");
        return;
    }

    // Add the names to the combo box
    for (i = 0; i < count; i++) {
        if (noms[i][0] != '\0') { // Ensure that the name is valid
            gtk_combo_box_append_text(GTK_COMBO_BOX(comboAgent), noms[i]);
        } else {
            g_print("Erreur : nom invalide pour l'élément %d.\n", i);
        }
    }

    // Set the first item as active (optional)
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboAgent), 0);
}


 


void
on_buttonSupprimerPS_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *comboAgent;
    GtkWidget *output;
    const char *selected_parking;
    char noms[100][110];
    int i, count;

     output = lookup_widget(objet_graphique, "labelResultatSP");
    comboAgent = lookup_widget(objet_graphique, "comboboxParkingPS");
    if (comboAgent == NULL) {
        g_print("Erreur : le widget comboAgent est introuvable.\n");
        return;
    }

    // Récupérer le texte sélectionné dans la combobox
    selected_parking = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboAgent));
    if (selected_parking == NULL) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : aucun parking sélectionné");
        return;
    }

    // Supprimer le parking sélectionné du fichier
       
      if (Supprimer_Parking(selected_parking) == 0) {
        gtk_label_set_text(GTK_LABEL(output), "Parking  a été supprimé  avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Parking n'a pas pu être supprimé..");
    }


    // Rafraîchir les données dans la ComboBox
    gtk_combo_box_remove_text(GTK_COMBO_BOX(comboAgent), 0);

    // Recharger les noms des parkings
    count = Rechercher_Noms_Parking(noms, 100);
    if (count == -1) {
        g_print("Erreur : impossible d'ouvrir le fichier Parking.txt.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(comboAgent), noms[i]);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(comboAgent), 0);
}


 
 void configurer_treeview_Sans_agents(GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    // Supprimer toutes les colonnes existantes
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), NULL);
    while (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) != NULL) {
        gtk_tree_view_remove_column(GTK_TREE_VIEW(treeview), gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0));
    }

    // Colonne 1 : ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 2 : Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Colonne 3 : Etat
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
}

 void remplir_treeview_Sans_agents(GtkWidget *treeview) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *fichier = fopen("Agent.txt", "r");

    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Créer un modèle GtkListStore
    store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING); // ID, Nom, Etat

    char id[20], nom[110], etat[10];

    while (fscanf(fichier, "%19[^,],%109[^,],%9s\n", id, nom, etat) == 3) {
        // Si l'état de l'agent est "0" (Présent)
        if (strcmp(etat, "0") == 0) {
            // Ajouter une ligne au modèle
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, id,      // ID
                               1, nom,     // Nom
                               2, etat,    // Etat
                               -1);
        }
    }

    fclose(fichier);

    // Associer le modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Décrémenter le compteur de référence du modèle
    g_object_unref(store);
}

void
on_buttonActualiserAffAg_clicked       (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *comboAgent, *comboParking;
    int i,j;
    char ids[100][110],noms[100][110]; // Assuming max of 100 parking names
    int countA, countP;

    comboAgent = lookup_widget(objet_graphique, "comboboxAgentLAffAg");
    comboParking = lookup_widget(objet_graphique, "comboboxParkingLAffAg");
    if (comboAgent == NULL) {
        g_print("Erreur : le widget comboAgent est introuvable.\n");
        return;
    }
      if (comboParking == NULL) {
        g_print("Erreur : le widget comboParking est introuvable.\n");
        return;
    }

    // Clear the existing items in the combo box
    gtk_combo_box_remove_text(GTK_COMBO_BOX(comboAgent), 0);
    gtk_combo_box_remove_text(GTK_COMBO_BOX(comboParking), 0);

    // Retrieve parking names from the function
    countA =  Rechercher_ID_Agents(ids, 100);
    if (countA == -1) {
        g_print("Erreur : impossible d'ouvrir le fichier Agent.txt.\n");
        return;
    }

      countP =  Rechercher_Parkings_Sans_Agent(noms, 100);
    if (countP == -1) {
        g_print("Erreur : impossible d'ouvrir le fichier Parking.txt.\n");
        return;
    }

    // Add the names to the combo box
    for (i = 0; i < countA; i++) {
        if (ids[i][0] != '\0') { // Ensure that the name is valid
            gtk_combo_box_append_text(GTK_COMBO_BOX(comboAgent), ids[i]);
        } else {
            g_print("Erreur : nom invalide pour l'élément %d.\n", i);
        }
    }
   
       for (j = 0; j < countP; j++) {
        if (noms[j][0] != '\0') { // Ensure that the name is valid
            gtk_combo_box_append_text(GTK_COMBO_BOX(comboParking), noms[j]);
        } else {
            g_print("Erreur : nom invalide pour l'élément %d.\n", j);
        }
    }

    // Set the first item as active (optional)
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboAgent), 0);
  // Set the first item as active (optional)
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboParking), 0);




    GtkWidget *treeview;

    // Récupérer le TreeView
    treeview = lookup_widget(objet_graphique, "treeview2");

    // Configurer le TreeView
     configurer_treeview_Sans_agents(treeview);

    // Remplir le TreeView avec les données
    remplir_treeview_Sans_agents(treeview);  
}


void
on_buttonAffecterAgent_clicked         (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *comboAgent, *comboParking, *output;
    char *selected_agent, *selected_parking;

    output = lookup_widget(objet_graphique, "labelResultatAffAg");
    comboParking = lookup_widget(objet_graphique, "comboboxParkingLAffAg");
    comboAgent = lookup_widget(objet_graphique, "comboboxAgentLAffAg");

    if (comboAgent == NULL || comboParking == NULL) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Combobox introuvable");
        return;
    }

    selected_agent = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboAgent));
    selected_parking = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboParking));

    if (selected_agent == NULL || selected_parking == NULL) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Sélection manquante");
        return;
    }

    int result = affectAgent(selected_parking, selected_agent);
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(output), "Agent affecté avec succès !");
    } else if (result == 0) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Parking ou Agent introuvable");
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Problème interne");
    }

    g_free(selected_agent);
    g_free(selected_parking);

    // Recharge des données dans les comboboxes
 gtk_combo_box_remove_text(GTK_COMBO_BOX(comboAgent), 0);
   gtk_combo_box_remove_text(GTK_COMBO_BOX(comboParking), 0);
}


 

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
  GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    // Widgets pour le formulaire
    GtkWidget *inputNumero = lookup_widget(GTK_WIDGET(treeview), "spinNumeroPM");
    GtkWidget *inputNom = lookup_widget(GTK_WIDGET(treeview), "entryNomPM");
    GtkWidget *spinCapacite = lookup_widget(GTK_WIDGET(treeview), "spinCapacitePM");
    GtkWidget *inputPrix = lookup_widget(GTK_WIDGET(treeview), "entryPrixPM");
    GtkWidget *spinJour = lookup_widget(GTK_WIDGET(treeview), "spinJourPM");
    GtkWidget *spinMois = lookup_widget(GTK_WIDGET(treeview), "spinMoisPM");
    GtkWidget *spinAnnee = lookup_widget(GTK_WIDGET(treeview), "spinAnneePM");
    GtkWidget *inputAdresse = lookup_widget(GTK_WIDGET(treeview), "entryAdressePM");
    GtkWidget *checkSeurite1 = lookup_widget(GTK_WIDGET(treeview), "checkSecuritePM1");
    GtkWidget *checkSeurite2 = lookup_widget(GTK_WIDGET(treeview), "checkSecuritePM2");
    GtkWidget *radioSecteur1 = lookup_widget(GTK_WIDGET(treeview), "radioSecteurPM1");
    GtkWidget *radioSecteur2 = lookup_widget(GTK_WIDGET(treeview), "radioSecteurPM2");
    
    // Label pour indiquer que le formulaire est chargé
    GtkWidget *labelGModifierParking = lookup_widget(GTK_WIDGET(treeview), "labelGModifierParking");

    // Assurez-vous que le label existe
    if (!inputNumero || !inputNom || !spinCapacite || !inputPrix || !spinJour || !spinMois || !spinAnnee ||
        !inputAdresse || !checkSeurite1 || !checkSeurite2 || !radioSecteur1 || !radioSecteur2 || !labelGModifierParking) {
        g_print("Un ou plusieurs widgets sont introuvables\n");
        return;
    }

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int numero = 0, capacite = 0;
        float prix = 0.0f;
        char *nom = NULL, *adresse = NULL, *securite = NULL, *secteur = NULL, *date = NULL;

        // Récupérer les données de la ligne sélectionnée
        gtk_tree_model_get(model, &iter,
                           0, &numero,
                           1, &nom,
                           2, &capacite,
                           3, &prix,
                           4, &date, // Date formatée "JJ/MM/AAAA"
                           5, &adresse,
                           6, &securite,
                           7, &secteur,
                           -1);

        // === Remplir les champs ===

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(inputNumero), numero);
        gtk_entry_set_text(GTK_ENTRY(inputNom), nom ? nom : "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinCapacite), capacite);

        // Remplir le prix
        char buffer_prix[20];
        snprintf(buffer_prix, sizeof(buffer_prix), "%.2f", prix);
        gtk_entry_set_text(GTK_ENTRY(inputPrix), buffer_prix);

        // Remplir les champs de date
        if (date) {
            int jour = 0, mois = 0, annee = 0;
            if (sscanf(date, "%2d/%2d/%4d", &jour, &mois, &annee) == 3) {
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinJour), jour);
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinMois), mois);
                gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinAnnee), annee);
            } else {
                g_print("Format de date invalide : %s\n", date);
            }
        }

        // Remplir l'adresse
        gtk_entry_set_text(GTK_ENTRY(inputAdresse), adresse ? adresse : "");

        // Remplir les cases à cocher pour la sécurité
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkSeurite1),
                                     securite && strstr(securite, "camira") != NULL);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkSeurite2),
                                     securite && strstr(securite, "gardien") != NULL);

        // Remplir les boutons radio pour le secteur
        if (secteur && strcmp(secteur, "Prive") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioSecteur1), TRUE);
        } else if (secteur && strcmp(secteur, "Publique") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioSecteur2), TRUE);
        }

        // Afficher le label après avoir chargé les données
        gtk_widget_show(labelGModifierParking);

        // Libérer la mémoire des chaînes allouées dynamiquement
        if (nom) g_free(nom);
        if (adresse) g_free(adresse);
        if (securite) g_free(securite);
        if (secteur) g_free(secteur);
        if (date) g_free(date);
    }
}

