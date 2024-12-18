#include <gtk/gtk.h>


 

void
on_buttonCreerCompte_clicked           (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonLoginInscrire_clicked         (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonInscription_clicked           (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonAuthentification_clicked      (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionParkihg_clicked        (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionReservation_clicked    (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionService_clicked        (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionAgent_clicked          (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionCitoyen_clicked        (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonGestionReclamation_clicked    (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonQuitterMenu_clicked           (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonAjouterParking_clicked        (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonMenuPJ_clicked                (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonModifierParking_clicked       (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonRecupererPM_clicked           (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonMenuPM_clicked                (GtkWidget *objet_graphique, gpointer user_data);

 

void
on_buttonMenuPCH_clicked               (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonParkingTrier_clicked          (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonParkingAvecAgent_clicked      (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonParkingSansAgent_clicked      (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonActualiserLPS_clicked         (GtkWidget *objet_graphique, gpointer user_data);
void
on_buttonSupprimerPS_clicked           (GtkWidget *objet_graphique, gpointer user_data);

 

void
on_buttonActualiserAffAg_clicked       (GtkWidget *objet_graphique, gpointer user_data);

void
on_buttonAffecterAgent_clicked         (GtkWidget *objet_graphique, gpointer user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview, GtkTreePath     *path, GtkTreeViewColumn *column, gpointer         user_data);

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
void
on_ajoutService_clicked                (GtkWidget *objet_graphique,gpointer user_data);

void
on_modifierService_clicked             (GtkWidget *objet_graphique,gpointer user_data);

void
on_supprimerService_clicked            (GtkWidget *objet_graphique, gpointer user_data);

void
onValiderSupprier_clicked              (GtkWidget       *objet_graphique, gpointer         user_data);

void
on_CancelSupprimer_clicked             (GtkWidget       *objet_graphique, gpointer         user_data);

void
on_Menu_clicked                        (GtkWidget *objet_graphique, gpointer         user_data);
gboolean reset_label_text(gpointer data);

void
on_treeviewServices_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void on_Rechercher_clicked(GtkWidget *objet_graphique, gpointer user_data) ;

void on_Affecter_clicked(GtkWidget *objet_graphique, gpointer user_data);
