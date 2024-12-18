#include <gtk/gtk.h>


void
on_button_supprimer_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_ajouter_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_display_reservations                (GtkButton       *button,
                                        gpointer         user_data);

void
on_display_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_radioAnnule_toggled                 (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioEnAttente_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioConfirmer_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioConfirmerModify_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioEnAttenteModify_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radioAnnuleModify_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Actualiser_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_search_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_actualiseparking_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeparcking_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_affecter_clicked                (GtkButton       *button,
                                        gpointer         user_data);
