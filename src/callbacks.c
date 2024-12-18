#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "parking.h"
#include "service.h"
#include "reservation.h"
#include <stdbool.h>
#include <glib.h>

  GtkWidget *windowGestionServices ;


gboolean reset_label_text(gpointer data) {
    GtkWidget *label = GTK_WIDGET(data);
    gtk_label_set_text(GTK_LABEL(label), ""); // Effacer le texte
    return FALSE; // Retourner FALSE pour que le timer ne soit pas réexécuté
}
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


void on_buttonGestionService_clicked(GtkWidget *objet_graphique, gpointer user_data)
{
    GtkWidget *windowMenu, *windowGestionService, *comboboxnum, *treeviewServices , *comboboxservice;
    windowMenu = lookup_widget(objet_graphique, "windowMenu");
    gtk_widget_destroy(windowMenu);
    windowGestionService = create_windowGestionService();
    windowGestionServices = windowGestionService;
    gtk_widget_show(windowGestionService);

    // Récupérer les éléments de l'interface, y compris le TreeView
    comboboxnum = lookup_widget(windowGestionService, "comboboxnum");
    comboboxservice = lookup_widget(windowGestionService, "comboboxservice");
    treeviewServices = lookup_widget(windowGestionService, "treeviewServices");

    // Configurer les colonnes du TreeView
    configurer_treevieww(treeviewServices);

    // Remplir le TreeView avec les services existants dans le fichier
    remplir_treeview_services(treeviewServices);

    // Remplir la combobox avec les numéros de services
    remplir_combobox_services(comboboxnum);
remplir_combobox_services(comboboxservice);
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

void on_ajoutService_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    // Récupération des widgets
    GtkWidget *entry_numservice = lookup_widget(objet_graphique, "entrynum");
    GtkWidget *entry_tarifservice = lookup_widget(objet_graphique, "entrytarif");
    GtkWidget *combobox_typeservice = lookup_widget(objet_graphique, "comboboxentrytype");
    GtkWidget *radio_7_7 = lookup_widget(objet_graphique, "rb7sur7");
    GtkWidget *radio_matin = lookup_widget(objet_graphique, "rbmatin");
    GtkWidget *radio_soir = lookup_widget(objet_graphique, "rbsoir");
    GtkWidget *radio_weekend = lookup_widget(objet_graphique, "rbweekend");
    GtkWidget *spinbutton_duree = lookup_widget(objet_graphique, "spinbutton1");
    GtkWidget *checkbox_voiture = lookup_widget(objet_graphique, "checkvoiture");
    GtkWidget *checkbox_bus = lookup_widget(objet_graphique, "checkbus");
    GtkWidget *checkbox_camion = lookup_widget(objet_graphique, "checkcamion");
    GtkWidget *label_message = lookup_widget(objet_graphique, "labelmessage");

    // Récupérer les valeurs des widgets
    const char *numservice_str = gtk_entry_get_text(GTK_ENTRY(entry_numservice));
    const char *tarifservice_str = gtk_entry_get_text(GTK_ENTRY(entry_tarifservice));
    GtkWidget *entry_type_service = gtk_bin_get_child(GTK_BIN(combobox_typeservice));
    const char *type_service = gtk_entry_get_text(GTK_ENTRY(entry_type_service));

    // === Contrôles de saisie ===
    int numeroService = atoi(numservice_str);
    if (numeroService <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Numéro de service invalide.</span>");
        return;
    }

    float tarifService = atof(tarifservice_str);
    if (tarifService <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Tarif de service invalide.</span>");
        return;
    }

    if (strlen(type_service) == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Type de service vide.</span>");
        return;
    }

    // Vérifier si le numéro ou le type existe déjà
    if (existeService(numeroService, type_service)) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Numéro ou type de service déjà existant.</span>");
        return;
    }

    // Disponibilité
    const char *disponibilite = NULL;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_7_7))) {
        disponibilite = "7/7";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_matin))) {
        disponibilite = "Matin";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_soir))) {
        disponibilite = "Soir";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_weekend))) {
        disponibilite = "Weekend";
    }

    if (disponibilite == NULL) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Disponibilité non sélectionnée.</span>");
        return;
    }

    // Véhicules concernés
    char vehicule_concerne[200] = "";
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_voiture))) {
        strcat(vehicule_concerne, "Voiture, ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_bus))) {
        strcat(vehicule_concerne, "Bus, ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_camion))) {
        strcat(vehicule_concerne, "Camion, ");
    }
    if (strlen(vehicule_concerne) == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Aucun véhicule sélectionné.</span>");
        return;
    }
    size_t len = strlen(vehicule_concerne);
    if (len > 2) vehicule_concerne[len - 2] = '\0';

    const int duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_duree));

    // Remplir la structure Service
    Service service;
    service.numeroService = numeroService;
    strcpy(service.typeService, type_service);
    strcpy(service.disponibilite, disponibilite);
    strcpy(service.vehiculeconcerne, vehicule_concerne);
    service.tarifService = tarifService;
    service.dureeEstimee = duree;

    // Ajouter au fichier
    const bool success = ajouterService(service);

    GtkWidget *comboboxnum = lookup_widget(objet_graphique, "comboboxnum");

    GtkWidget *comboboxservice = lookup_widget(objet_graphique, "comboboxservice");
    if (success) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='green'>Service ajouté avec succès!</span>");
 gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxnum), type_service); 
 gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxservice), type_service); 
        // === Mise à jour du TreeView ===
        GtkWidget *treeview = lookup_widget(objet_graphique, "treeviewServices");
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, service.numeroService,
                           1, service.typeService,
                           2, service.disponibilite,
                           3, service.tarifService,
                           4, service.dureeEstimee,
                           5, service.vehiculeconcerne,
                           -1);

        // === Réinitialisation du formulaire ===
        gtk_entry_set_text(GTK_ENTRY(entry_numservice), "");
        gtk_entry_set_text(GTK_ENTRY(entry_tarifservice), "");
        gtk_entry_set_text(GTK_ENTRY(entry_type_service), "");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_7_7), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_matin), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_soir), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_weekend), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_voiture), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_bus), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_camion), FALSE);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_duree), 0);
        gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_typeservice), -1);
    } else {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur lors de l'ajout du service.</span>");
    }
 g_timeout_add(5000, reset_label_text, label_message);
}
void on_modifierService_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    // Récupération des widgets
    GtkWidget *entry_numservice = lookup_widget(objet_graphique, "entrynumU");
    GtkWidget *entry_tarifservice = lookup_widget(objet_graphique, "entrytarifU");
    GtkWidget *combobox_typeservice = lookup_widget(objet_graphique, "comboboxentrytypeU");
    GtkWidget *radio_7_7 = lookup_widget(objet_graphique, "rb7sur7U");
    GtkWidget *radio_matin = lookup_widget(objet_graphique, "rbmatinU");
    GtkWidget *radio_soir = lookup_widget(objet_graphique, "rbsoirU");
    GtkWidget *radio_weekend = lookup_widget(objet_graphique, "rbweekendU");
    GtkWidget *spinbutton_duree = lookup_widget(objet_graphique, "spinbuttonU");
    GtkWidget *checkbox_voiture = lookup_widget(objet_graphique, "checkV");
    GtkWidget *checkbox_bus = lookup_widget(objet_graphique, "checkB");
    GtkWidget *checkbox_camion = lookup_widget(objet_graphique, "checkC");
    GtkWidget *label_message = lookup_widget(objet_graphique, "labelmessageU");
    GtkWidget *treeview = lookup_widget(objet_graphique, "treeviewServices");

    // === Récupérer les valeurs des widgets ===
    const char *numservice_str = gtk_entry_get_text(GTK_ENTRY(entry_numservice));
    const char *tarifservice_str = gtk_entry_get_text(GTK_ENTRY(entry_tarifservice));
    GtkWidget *entry_type_service = gtk_bin_get_child(GTK_BIN(combobox_typeservice));
    const char *type_service = gtk_entry_get_text(GTK_ENTRY(entry_type_service));

    // === Contrôle de saisie ===
    int numeroService = atoi(numservice_str);
    if (numeroService <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Numéro de service invalide.</span>");
        return;
    }

    float tarifService = atof(tarifservice_str);
    if (tarifService <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Tarif de service invalide.</span>");
        return;
    }

    if (strlen(type_service) == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Type de service vide.</span>");
        return;
    }

    // Disponibilité
    const char *disponibilite = NULL;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_7_7))) {
        disponibilite = "7/7";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_matin))) {
        disponibilite = "Matin";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_soir))) {
        disponibilite = "Soir";
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_weekend))) {
        disponibilite = "Weekend";
    } else {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Disponibilité non sélectionnée.</span>");
        return;
    }

    // Véhicules concernés
    char vehicule_concerne[200] = "";
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_voiture))) {
        strcat(vehicule_concerne, "Voiture, ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_bus))) {
        strcat(vehicule_concerne, "Bus, ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_camion))) {
        strcat(vehicule_concerne, "Camion, ");
    }
    if (strlen(vehicule_concerne) == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Aucun véhicule sélectionné.</span>");
        return;
    }
    size_t len = strlen(vehicule_concerne);
    if (len > 2) vehicule_concerne[len - 2] = '\0';

    int duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_duree));
    if (duree <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Durée estimée invalide.</span>");
        return;
    }

    // === Remplir la structure Service ===
    Service service;
    service.numeroService = numeroService;
    strcpy(service.typeService, type_service);
    strcpy(service.disponibilite, disponibilite);
    strcpy(service.vehiculeconcerne, vehicule_concerne);
    service.tarifService = tarifService;
    service.dureeEstimee = duree;

    // === Modifier le service dans le fichier ===
    const bool success = modifierService(service);

    if (success) {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='green'>Service modifié avec succès!</span>");

        // === Mise à jour du TreeView ===
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
        GtkTreeIter iter;
        gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter);

        // Parcourir le TreeView pour mettre à jour l'entrée
        while (valid) {
            int num_service_tree;
            gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &num_service_tree, -1);

            if (num_service_tree == service.numeroService) {
                gtk_list_store_set(store, &iter,
                                   1, service.typeService,
                                   2, service.disponibilite,
                                   3, service.tarifService,
                                   4, service.dureeEstimee,
                                   5, service.vehiculeconcerne,
                                   -1);
                break;
            }
            valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
        }
    } else {
        gtk_label_set_markup(GTK_LABEL(label_message), "<span foreground='red'>Erreur : Service non trouvé.</span>");
    }

    // === Réinitialiser le formulaire ===
    gtk_entry_set_text(GTK_ENTRY(entry_numservice), "");
    gtk_entry_set_text(GTK_ENTRY(entry_tarifservice), "");
    gtk_entry_set_text(GTK_ENTRY(entry_type_service), "");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_7_7), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_matin), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_soir), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_weekend), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_voiture), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_bus), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_camion), FALSE);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_duree), 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_typeservice), -1);

    // Réinitialiser le label après 5 secondes
    g_timeout_add(5000, reset_label_text, label_message);
}

void
on_supprimerService_clicked            (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *Supprimer;
  Supprimer = create_Supprimer();
  gtk_widget_show (Supprimer);
}

void onValiderSupprier_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    // Récupération des widgets nécessaires
    GtkWidget *comboboxnum = lookup_widget(windowGestionServices, "comboboxnum");
    GtkWidget *labelsupprimer = lookup_widget(windowGestionServices, "labelsupprimer");

    if (comboboxnum == NULL || labelsupprimer == NULL) {
        g_print("Erreur : Widgets non trouvés.\n");
        return;
    }

    // Récupérer le texte sélectionné dans le combobox
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(comboboxnum));
    gchar *type_service = NULL;

    if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(comboboxnum), &iter)) {
        gtk_tree_model_get(model, &iter, 0, &type_service, -1); // Colonne 0 pour le texte
    } else {
        gtk_label_set_markup(GTK_LABEL(labelsupprimer), "<span foreground='red'>Veuillez sélectionner un service à supprimer.</span>");
        g_timeout_add(5000, reset_label_text, labelsupprimer); // Réinitialiser après 5 secondes
        return;
    }

    if (type_service == NULL || strlen(type_service) == 0) {
        gtk_label_set_markup(GTK_LABEL(labelsupprimer), "<span foreground='red'>Aucune sélection valide détectée.</span>");
        g_timeout_add(5000, reset_label_text, labelsupprimer); // Réinitialiser après 5 secondes
        return;
    }

    // Recherche du service correspondant
    Service *service = chercherServiceParType(type_service);

    if (service == NULL) {
        gtk_label_set_markup(GTK_LABEL(labelsupprimer), "<span foreground='red'>Ce service n'existe pas.</span>");
        g_timeout_add(5000, reset_label_text, labelsupprimer); // Réinitialiser après 5 secondes
        g_free(type_service); // Libérer la mémoire
        return;
    }

    GtkWidget *comboboxservice = lookup_widget(windowGestionServices, "comboboxservice");
    
    // Suppression du service
    bool success = supprimerService(&service->numeroService);
    free(service); // Libérer la mémoire allouée pour le service

    // Affichage du résultat dans le label
    if (success) {
        gtk_label_set_markup(GTK_LABEL(labelsupprimer), "<span foreground='green'>Service supprimé avec succès !</span>");
        supprimer_element_combobox(comboboxservice, type_service);
        
        // Supprimer l'élément du combobox
        GtkListStore *list_store = GTK_LIST_STORE(model);
        gtk_list_store_remove(list_store, &iter); // Supprime l'élément sélectionné
        
        // Désélectionner explicitement tout élément actif
        gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxnum), -1); // Aucun élément actif

        // Rafraîchir le modèle du combobox pour s'assurer de la mise à jour visuelle
        gtk_widget_queue_draw(comboboxnum); // Force le rafraîchissement de l'affichage

        // === Mise à jour du TreeView ===
        GtkWidget *treeview = lookup_widget(windowGestionServices, "treeviewServices");
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

        // Recherche et suppression du service dans le TreeView
        GtkTreeIter tree_iter;
        gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &tree_iter);
        while (valid) {
            gchar *service_type;
            gtk_tree_model_get(GTK_TREE_MODEL(store), &tree_iter, 1, &service_type, -1);

            if (service_type != NULL && g_strcmp0(service_type, type_service) == 0) {
                gtk_list_store_remove(store, &tree_iter); // Supprimer le service du TreeView
                g_free(service_type); // Libérer la mémoire
                break;
            }

            g_free(service_type);
            valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &tree_iter);
        }

        // Rafraîchir le TreeView pour afficher les changements
        gtk_widget_queue_draw(treeview); // Forcer le rafraîchissement du TreeView
    } else {
        gtk_label_set_markup(GTK_LABEL(labelsupprimer), "<span foreground='red'>Erreur lors de la suppression du service.</span>");
    }

    // Réinitialiser le texte du label après 5 secondes
    g_timeout_add(5000, reset_label_text, labelsupprimer);

    // Libérer les ressources
    g_free(type_service);

    // Optionnel : détruire la fenêtre de suppression (si nécessaire)
    GtkWidget *Supprimer = lookup_widget(objet_graphique, "Supprimer");
    if (Supprimer != NULL) {
        gtk_widget_destroy(Supprimer);
    }
}




void
on_CancelSupprimer_clicked             (GtkWidget *objet_graphique, gpointer  user_data)
{
GtkWidget *Supprimer ;
 Supprimer = lookup_widget(objet_graphique, "Supprimer");
 gtk_widget_destroy(Supprimer);
}


void
on_Menu_clicked                        (GtkWidget *objet_graphique, gpointer         user_data)
{
 GtkWidget *windowMenu,*windowGestionService;
 windowGestionService = lookup_widget(objet_graphique, "windowGestionService");
 gtk_widget_destroy(windowGestionService);
 windowMenu = create_windowMenu();
  gtk_widget_show (windowMenu);
}
void on_treeviewServices_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
  GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    // Objets de formulaire
    GtkWidget *entry_numservice = lookup_widget(GTK_WIDGET(treeview), "entrynumU");
    GtkWidget *entry_tarifservice = lookup_widget(GTK_WIDGET(treeview), "entrytarifU");
    GtkWidget *combobox_typeservice = lookup_widget(GTK_WIDGET(treeview), "comboboxentrytypeU");
    GtkWidget *radio_7_7 = lookup_widget(GTK_WIDGET(treeview), "rb7sur7U");
    GtkWidget *radio_matin = lookup_widget(GTK_WIDGET(treeview), "rbmatinU");
    GtkWidget *radio_soir = lookup_widget(GTK_WIDGET(treeview), "rbsoirU");
    GtkWidget *radio_weekend = lookup_widget(GTK_WIDGET(treeview), "rbweekendU");
    GtkWidget *spinbutton_duree = lookup_widget(GTK_WIDGET(treeview), "spinbuttonU");
    GtkWidget *checkbox_voiture = lookup_widget(GTK_WIDGET(treeview), "checkV");
    GtkWidget *checkbox_bus = lookup_widget(GTK_WIDGET(treeview), "checkB");
    GtkWidget *checkbox_camion = lookup_widget(GTK_WIDGET(treeview), "checkC");

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        int numeroService;
        char *typeService;
        char *disponibilite;
        float tarifService;
        int dureeEstimee;
        char *vehiculeConcerne;

        // Extraire les valeurs des colonnes
        gtk_tree_model_get(model, &iter,
                           0, &numeroService,
                           1, &typeService,
                           2, &disponibilite,
                           3, &tarifService,
                           4, &dureeEstimee,
                           5, &vehiculeConcerne,
                           -1);

        // === Remplissage des champs ===

        // 1. Remplir l'entrée du numéro de service
        char buffer_num[20];
        sprintf(buffer_num, "%d", numeroService);
        gtk_entry_set_text(GTK_ENTRY(entry_numservice), buffer_num);

        // 2. Remplir le type de service dans la combobox avec conversion UTF-8
        char *typeService_utf8 = convertir_en_utf8(typeService);
        GtkWidget *entry_type_service = gtk_bin_get_child(GTK_BIN(combobox_typeservice));
        gtk_entry_set_text(GTK_ENTRY(entry_type_service), typeService_utf8);
        g_free(typeService_utf8);

        // 3. Remplir la disponibilité (radio buttons)
        if (strcmp(disponibilite, "7/7") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_7_7), TRUE);
        } else if (strcmp(disponibilite, "Matin") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_matin), TRUE);
        } else if (strcmp(disponibilite, "Soir") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_soir), TRUE);
        } else if (strcmp(disponibilite, "Weekend") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_weekend), TRUE);
        }

        // 4. Remplir le tarif
        char buffer_tarif[20];
        sprintf(buffer_tarif, "%.2f", tarifService);
        gtk_entry_set_text(GTK_ENTRY(entry_tarifservice), buffer_tarif);

        // 5. Remplir la durée estimée
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton_duree), dureeEstimee);

        // 6. Remplir les cases à cocher des véhicules concernés
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_voiture), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_bus), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_camion), FALSE);

        if (strstr(vehiculeConcerne, "Voiture") != NULL) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_voiture), TRUE);
        }
        if (strstr(vehiculeConcerne, "Bus") != NULL) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_bus), TRUE);
        }
        if (strstr(vehiculeConcerne, "Camion") != NULL) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox_camion), TRUE);
        }

        // Libération de la mémoire allouée par `gtk_tree_model_get`
        g_free(typeService);
        g_free(disponibilite);
        g_free(vehiculeConcerne);
    }


}

void on_Rechercher_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    // Récupérer le widget de l'entry pour la recherche
    GtkWidget *entry_recherche = lookup_widget(objet_graphique, "entry_recherche");
    const gchar *search_text = gtk_entry_get_text(GTK_ENTRY(entry_recherche));

    if (search_text == NULL || strlen(search_text) == 0) {
        g_print("Erreur : Aucun texte de recherche.\n");
        return;
    }

    // Récupérer le TreeView et son modèle
    GtkWidget *treeview = lookup_widget(objet_graphique, "treeviewServices");
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkTreeIter iter;
    gboolean valid_iter;

    // Boucle pour parcourir les éléments du TreeView
    valid_iter = gtk_tree_model_get_iter_first(model, &iter);
    gboolean service_found = FALSE;

    while (valid_iter) {
        gchar *type_service = NULL;

        // Extraire le "typeService" de la ligne courante
        gtk_tree_model_get(model, &iter, 1, &type_service, -1);

        if (type_service != NULL && strstr(type_service, search_text) != NULL) {
            service_found = TRUE;

            // Afficher le résultat trouvé (facultatif)
            g_print("Service trouvé: %s\n", type_service);

            // Optionnel : mettre en surbrillance ou sélectionner la ligne correspondante dans le TreeView
            GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
            gtk_tree_selection_select_iter(selection, &iter);
        }

        // Libérer la mémoire allouée pour type_service
        g_free(type_service);

        // Passer à l'élément suivant
        valid_iter = gtk_tree_model_iter_next(model, &iter);
    }

    // Message de résultat
    GtkWidget *label_result = lookup_widget(objet_graphique, "label_resultat1");
    if (service_found) {
        gtk_label_set_markup(GTK_LABEL(label_result), "<span foreground='green'>Service trouvé!</span>");
    } else {
        gtk_label_set_markup(GTK_LABEL(label_result), "<span foreground='red'>Aucun service trouvé.</span>");
    }

    // Optionnel : réinitialiser après 5 secondes
    g_timeout_add(5000, reset_label_text, label_result);
}




void on_Affecter_clicked(GtkWidget *objet_graphique, gpointer user_data) {
   
    GtkWidget *entry_reservation = lookup_widget(objet_graphique, "entry4");
    GtkWidget *combobox_service = lookup_widget(objet_graphique, "comboboxservice");
    GtkWidget *label_message = lookup_widget(objet_graphique, "labelaffecter");


    const char *reservation_id_str = gtk_entry_get_text(GTK_ENTRY(entry_reservation));

    // Obtenir le texte sélectionné dans la combobox
    GtkWidget *entry_combobox = gtk_bin_get_child(GTK_BIN(combobox_service));
    const char *service_reservation = gtk_entry_get_text(GTK_ENTRY(entry_combobox));

    // Vérification de saisie vide
    if (strlen(reservation_id_str) == 0 || strlen(service_reservation) == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), 
            "<span foreground='red'>Veuillez remplir tous les champs!</span>");
        return;
    }

    // Conversion de l'ID en entier
    int id_reservation = atoi(reservation_id_str);
    if (id_reservation <= 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), 
            "<span foreground='red'>ID réservation invalide!</span>");
        return;
    }

    // Variables pour la gestion du fichier
    FILE *fichier = fopen("reservations.txt", "r");
    FILE *tempFichier = fopen("TempReservations.txt", "w");
    if (fichier == NULL || tempFichier == NULL) {
        gtk_label_set_markup(GTK_LABEL(label_message), 
            "<span foreground='red'>Erreur d'ouverture du fichier!</span>");
        return;
    }

    Reservation tempReservation;
    int trouve = 0;
    char line[256];

    // Lecture et modification du fichier
    while (fgets(line, sizeof(line), fichier)) {
        if (sscanf(line, "%d %d %d %49s %19s %49s %19s",
                   &tempReservation.num_reservation,
                   &tempReservation.num_citoyen,
                   &tempReservation.num_parking,
                   tempReservation.matricule_vehicule,
                   tempReservation.date_reservation,
                   tempReservation.service_reservation,
                   tempReservation.status_reservation) == 7) {

            if (tempReservation.num_reservation == id_reservation) {
                if (strcmp(tempReservation.service_reservation, "0") != 0) {
                    // Service déjà affecté
                    gtk_label_set_markup(GTK_LABEL(label_message), 
                        "<span foreground='red'>Un service est déjà affecté à cette réservation!</span>");
                    trouve = -1; // Marquer comme erreur
                } else {
                    // Affecter le nouveau service
                    strncpy(tempReservation.service_reservation, service_reservation, 
                            sizeof(tempReservation.service_reservation) - 1);
                    tempReservation.service_reservation[sizeof(tempReservation.service_reservation) - 1] = '\0';
                    trouve = 1;
                }
            }
            // Réécrire dans le fichier temporaire
            fprintf(tempFichier, "%d %d %d %s %s %s %s\n",
                    tempReservation.num_reservation,
                    tempReservation.num_citoyen,
                    tempReservation.num_parking,
                    tempReservation.matricule_vehicule,
                    tempReservation.date_reservation,
                    tempReservation.service_reservation,
                    tempReservation.status_reservation);
        }
    }

    // Fermeture des fichiers
    fclose(fichier);
    fclose(tempFichier);

    // Remplacer le fichier original par le fichier temporaire
    if (trouve == 1) {
        remove("reservations.txt");
        rename("TempReservations.txt", "reservations.txt");
        gtk_label_set_markup(GTK_LABEL(label_message), 
            "<span foreground='green'>Service affecté avec succès!</span>");
    } else if (trouve == 0) {
        gtk_label_set_markup(GTK_LABEL(label_message), 
            "<span foreground='red'>Réservation introuvable!</span>");
        remove("TempReservations.txt");
    } else {
        remove("TempReservations.txt"); // Supprimer si erreur
    }
}

