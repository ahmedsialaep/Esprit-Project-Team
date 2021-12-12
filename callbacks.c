#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "reclam.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"


void on_button1_recherche_clicked (GtkWidget *objet_graphique ,gpointer user_data)
{
GtkWidget *cin,*treeview_reclam;
char cin1[20];
cin=lookup_widget(objet_graphique,"entry1_recherche");	treeview_reclam=lookup_widget(objet_graphique,"treeview_reclam");
strcpy(cin1,gtk_entry_get_text(GTK_ENTRY(cin)));
if(strcmp(cin1,"")!=0)
  {
   recherche_reclam(cin1);
   afficher_reclam(treeview_reclam,"recherche.txt");
   remove("recherche.txt");
  }
else
   afficher_reclam(treeview_reclam,"reclam.txt");
}

void on_button2_ajout_rec_clicked (GtkWidget *objet_graphique ,gpointer user_data)
{
GtkWidget *window_afficher,*window_gestion,*treeview_reclam;

window_afficher=lookup_widget(objet_graphique,"window_afficher");
window_gestion=lookup_widget(objet_graphique,"window_gestion");
gtk_widget_destroy(window_afficher);
window_gestion=create_window_gestion();
gtk_widget_show(window_gestion);
}

void on_button3_modif_rec_clicked (GtkWidget *objet_graphique,gpointer         user_data)
{

GtkWidget *window_gestion,*window_afficher;
GtkTreeModel     *model;
GtkTreeSelection *selection;
GtkTreeIter iter;
GtkWidget* treeview;
	
	
gchar* id;
gchar* cin;
gchar* nom;
gchar* prenom;
gchar* text;
gint satisfaction;
gint education;
gint jour;
gint mois;
gint annee;
gint type;

window_afficher=lookup_widget(objet_graphique,"window_afficher");
treeview=lookup_widget(window_afficher,"treeview_reclam");
selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
if (gtk_tree_selection_get_selected(selection, &model, &iter))
   {
    gtk_tree_model_get (model,&iter,0,&id,1,&cin,2,&nom,3,&prenom,4,&type,5,&jour,6,&mois,7,&annee,8,&text,9,&satisfaction,10,&education,-1);
    gtk_widget_destroy(window_afficher);
		         window_gestion=lookup_widget(objet_graphique,"window_gestion");
window_gestion=create_window_gestion();
gtk_widget_show(window_gestion);
	        gtk_entry_set_text(GTK_ENTRY(lookup_widget(window_gestion,"entry2_id_rec")),id);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(window_gestion,"entry3_cin_rec")),cin);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(window_gestion,"entry4_nom_rec")),nom);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(window_gestion,"entry5_prenom_rec")),prenom);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(window_gestion,"entry6_text_rec")),text);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(window_gestion,"spinbutton1_jour")),jour);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(window_gestion,"spinbutton2_mois")),mois);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(window_gestion,"spinbutton3_annee")),annee);
		gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(window_gestion,"combobox_rec")),type);

	}
}

void on_button4_supp_rec_clicked (GtkWidget *objet_graphique,gpointer         user_data)
{
GtkWidget *window_gestion,*window_afficher;
GtkTreeModel  *model;
GtkTreeSelection *selection;
GtkTreeIter iter;
GtkWidget* treeview;
		
gchar* id;
		window_afficher=lookup_widget(objet_graphique,"window_afficher");
treeview=lookup_widget(window_afficher,"treeview_reclam");
selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
   gtk_tree_model_get (model,&iter,0,&id,-1);
   supprimer_reclam(id);
   afficher_reclam(treeview,"reclam.txt");
		
  }
}

int x,y;
void on_radiobutton1_satisfait_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
 if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
    x=0;
}


void on_radiobutton2_non_satisfait_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
    x=1;
}


void on_checkbutton1_prep_toggled (GtkToggleButton *togglebutton, gpointer     user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
    y=0;
}


void on_checkbutton2_cycle_ing_toggled (GtkToggleButton *togglebutton,
gpointer user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
    y=1;
}


void on_checkbutton3_business_toggled (GtkToggleButton *togglebutton,
gpointer user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
    y=2;
}


void on_button6_ajouter_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
reclam r;
GtkWidget *id,*cin,*nom,*prenom,*type,*text_reclamation,*jour,*mois,*annee;

id=lookup_widget(objet_graphique,"entry2_id_rec");
cin=lookup_widget(objet_graphique,"entry3_cin_rec");
nom=lookup_widget(objet_graphique,"entry4_nom_rec");
prenom=lookup_widget(objet_graphique,"entry5_prenom_rec");
type=lookup_widget(objet_graphique,"combobox_rec");
text_reclamation=lookup_widget(objet_graphique,"entry6_text_rec");
jour=lookup_widget(objet_graphique,"spinbutton1_jour");
mois=lookup_widget(objet_graphique,"spinbutton2_mois");
annee=lookup_widget(objet_graphique,"spinbutton3_annee");
strcpy(r.id,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(r.cin,gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(r.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(r.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(r.text_reclamation,gtk_entry_get_text(GTK_ENTRY(text_reclamation)));
r.d.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
r.d.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
r.d.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
if(strcmp("Service hebergement" ,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
   r.type=0;
else
   r.type=1;
   r.satisfaction=x;
   r.education=y;
if(existe(r.id)==0)
  {	
   ajouter_reclam(r);
   GtkWidget *dialog_ok_aj;
   dialog_ok_aj=create_dialog_ok_aj() ;
   gtk_widget_show(dialog_ok_aj) ;
  }
else
  {
  GtkWidget *dialog_pb_aj;
  dialog_pb_aj=create_dialog_pb_aj() ;
  gtk_widget_show(dialog_pb_aj) ;
  }
}


void on_button7_modifier_clicked (GtkWidget *objet_graphique,gpointer user_data)
{
reclam r;
int ex=1;
GtkWidget *id,*cin,*nom,*prenom,*type,*text_reclamation,*jour,*mois,*annee;

id=lookup_widget(objet_graphique,"entry2_id_rec");
cin=lookup_widget(objet_graphique,"entry3_cin_rec");
nom=lookup_widget(objet_graphique,"entry4_nom_rec");
prenom=lookup_widget(objet_graphique,"entry5_prenom_rec");
type=lookup_widget(objet_graphique,"combobox_rec");
text_reclamation=lookup_widget(objet_graphique,"entry6_text_rec");
jour=lookup_widget(objet_graphique,"spinbutton1_jour");
mois=lookup_widget(objet_graphique,"spinbutton2_mois");
annee=lookup_widget(objet_graphique,"spinbutton3_annee");
strcpy(r.id,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(r.cin,gtk_entry_get_text(GTK_ENTRY(cin)));
strcpy(r.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
strcpy(r.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
strcpy(r.text_reclamation,gtk_entry_get_text(GTK_ENTRY(text_reclamation)));
r.d.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
r.d.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
r.d.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
if(strcmp("Service hebergement",gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
  r.type=0;
else
  r.type=1;
  r.satisfaction=x;
  r.education=y;
  ex=existe(r.id);
if(ex==1)
  {
  modifier_reclam(r);
  GtkWidget *dialog_ok_modif;
  dialog_ok_modif=create_dialog_ok_modif() ;
  gtk_widget_show(dialog_ok_modif) ;
  }
else
  {
  GtkWidget *dialog_pb_modif;
  dialog_pb_modif=create_dialog_pb_modif() ;
  gtk_widget_show(dialog_pb_modif) ;
  }
}


void on_button8_afficher_clicked (GtkWidget *objet_graphique,gpointer user_data)
{
GtkWidget *window_afficher,*window_gestion,*treeview_reclam;

window_afficher=lookup_widget(objet_graphique,"window_afficher");
window_gestion=lookup_widget(objet_graphique,"window_gestion");
gtk_widget_destroy(window_gestion);
window_afficher=create_window_afficher();
gtk_widget_show(window_afficher);
treeview_reclam=lookup_widget(window_afficher,"treeview_reclam");
afficher_reclam(treeview_reclam,"reclam.txt");
}


void on_closebutton1_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
gtk_widget_destroy(lookup_widget(objet_graphique,"dialog_ok_aj"));
}


void on_closebutton2_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
gtk_widget_destroy(lookup_widget(objet_graphique,"dialog_pb_aj"));
}


void on_closebutton3_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
gtk_widget_destroy(lookup_widget(objet_graphique,"dialog_ok_modif"));
}


void on_closebutton4_clicked (GtkWidget *objet_graphique, gpointer user_data)
{
gtk_widget_destroy(lookup_widget(objet_graphique,"dialog_pb_modif"));
}

