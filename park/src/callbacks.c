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
        strcpy(role, "Agent");
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

