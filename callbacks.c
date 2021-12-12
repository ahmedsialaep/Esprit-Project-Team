#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "stock.h"


void
on_button4_ref_home_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *treeview1, *ref_tree;


ref_tree=lookup_widget(objet_graphique,"window_prod_home");

gtk_widget_destroy(ref_tree);
ref_tree=lookup_widget(objet_graphique,"window_prod_home");
ref_tree=create_window_prod_home();

gtk_widget_show(ref_tree);

treeview1=lookup_widget(ref_tree,"treeview1_home_list");

Display_Stock(treeview1,"stock.txt");
}


void
on_button5_search_prod_clicked              (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *windowAuth;
windowAuth=create_window_search_prod();
gtk_widget_show (windowAuth);
}


void
on_button2_add_prod_clicked                (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
stock p;

GtkWidget *input1,*input2,*input3,*input4,*input5,*input6,*input7,*input8;
GtkWidget *interface;
interface=lookup_widget(objet_graphique, "window_prod_home");

input1=lookup_widget(objet_graphique,"entry1_add_prod");
input2=lookup_widget(objet_graphique,"entry2_add_prod"); 
input3=lookup_widget ( objet_graphique,"entry3_add_prod" );
input4=lookup_widget(objet_graphique,"spinbutton9_add_prod"); 
input5=lookup_widget(objet_graphique,"spinbutton2_add_prod");
input6=lookup_widget(objet_graphique,"spinbutton3_add_prod");
input7=lookup_widget(objet_graphique,"spinbutton4_add_prod");
input8=lookup_widget(objet_graphique,"entry4_add_prod");

strcpy(p.identifiant,gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(p.nom,gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(p.prix,gtk_entry_get_text(GTK_ENTRY(input3))); 
p.quantite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input4));
p.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5));
p.date.moins=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input6));
p.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input7));
strcpy(p.place,gtk_entry_get_text(GTK_ENTRY(input8)));

Add_Product(p);

}


void
on_button3_disp_out_prod_clicked                 (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *w1; GtkWidget *treeview3;
w1=lookup_widget(objet_graphique,"window_prod_home"); 

gtk_widget_show(w1);


treeview3=lookup_widget(w1,"treeview3_show_out");

Display_Stock(treeview3,"rupture.txt");
}


void
on_treeview1_home_list_row_activated             (GtkTreeView *treeview1_home_list,GtkTreePath *path, GtkTreeViewColumn *column, gpointer    user_data)
{
GtkTreeIter iter; gchar *identifiant;GtkWidget *msgInfo;
stock p;

GtkTreeModel *model = gtk_tree_view_get_model(treeview1_home_list);
if (gtk_tree_model_get_iter(model, &iter, path)) {
gtk_tree_model_get (GTK_LIST_STORE(model), &iter, 0, &identifiant,-1);

strcpy(p.identifiant,identifiant);


delete_Product(p,"stock.txt");
Display_Stock(treeview1_home_list,"stock.txt");
msgInfo=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Product succesfully deleted");
	switch(gtk_dialog_run(GTK_DIALOG(msgInfo)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(msgInfo);
	break;
	}
}
}


void
on_button6_search_prod_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
int v;
char id[20],date_achat[40],quantite[20];
GtkWidget *txt1, *txt2, *txt3, *txt4, *txt5, *txt6;
GtkWidget *iden,*dialog;

iden=lookup_widget(objet_graphique,"entry5_search_prod"); 
strcpy(id,gtk_entry_get_text(GTK_ENTRY(iden)));
txt1=lookup_widget(objet_graphique,"label5_search_prod");
txt2=lookup_widget(objet_graphique,"label6_search_prod");
txt3=lookup_widget(objet_graphique,"label7_search_prod");
txt4=lookup_widget(objet_graphique,"label8_search_prod");
txt5=lookup_widget(objet_graphique,"checkbutton1_stockA");
txt6=lookup_widget(objet_graphique,"checkbutton2_stockB");

stock p=search_product(id,"stock.txt",&v);

if (v==-1){
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Incorrect ID");
switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}
}
else {
gtk_label_set_text(GTK_LABEL(txt1),p.nom);
gtk_label_set_text(GTK_LABEL(txt2),p.prix);
sprintf(quantite,"%d",p.quantite);
sprintf(date_achat,"%d/%d/%d",p.date.jour,p.date.moins,p.date.annee);
gtk_label_set_text(GTK_LABEL(txt3),quantite);
gtk_label_set_text(GTK_LABEL(txt4),date_achat);
if(strcmp(p.place,"StockA")==0)
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(txt5),TRUE);
else
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(txt6),TRUE);

}
}


void
on_verif_id_prod_clicked                    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
int v;
char id[20];
GtkWidget *txt1, *txt2, *txt3, *txt4a,*txt4b,*txt4c, *txt5, *txt6, *txt7;
GtkWidget *iden,*dialog;

iden=lookup_widget(objet_graphique,"repl1"); 
strcpy(id,gtk_entry_get_text(GTK_ENTRY(iden)));
txt1=lookup_widget(objet_graphique,"repl2");
txt2=lookup_widget(objet_graphique,"repl3");
txt3=lookup_widget(objet_graphique,"spinbutton5_mod_prod");
txt4a=lookup_widget(objet_graphique,"spinbutton6_mod_prod");
txt4b=lookup_widget(objet_graphique,"spinbutton7_mod_prod");
txt4c=lookup_widget(objet_graphique,"spinbutton8_mod_prod");
txt5=lookup_widget(objet_graphique,"stockA");
txt6=lookup_widget(objet_graphique,"stockB");
txt7=lookup_widget(objet_graphique,"entry24_mod_prod");


stock p=search_product(id,"stock.txt",&v);

if (v==-1){
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Incorrect ID");
switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}
}
else {

gtk_entry_set_text(GTK_ENTRY(txt1),p.nom);
gtk_entry_set_text(GTK_ENTRY(txt1),p.nom);
gtk_entry_set_text(GTK_ENTRY(txt2),p.prix);
gtk_spin_button_set_value(txt3,p.quantite);
gtk_spin_button_set_value(txt4a,p.date.jour);
gtk_spin_button_set_value(txt4b,p.date.moins);
gtk_spin_button_set_value(txt4c,p.date.annee);
if(strcmp(p.place,"StockA")==0)
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(txt5),TRUE);
else
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(txt6),TRUE);
gtk_entry_set_text(GTK_ENTRY(txt7),id);
}
}



void
on_button9_mod_prod_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
stock p;
GtkWidget *txt1, *txt2, *txt3, *txt4a,*txt4b,*txt4c, *txt5, *txt6;
GtkWidget *iden,*dialog;

iden=lookup_widget(objet_graphique,"entry24_mod_prod");
txt1=lookup_widget(objet_graphique,"repl2");
txt2=lookup_widget(objet_graphique,"repl3");
txt3=lookup_widget(objet_graphique,"spinbutton5_mod_prod");
txt4a=lookup_widget(objet_graphique,"spinbutton6_mod_prod");
txt4b=lookup_widget(objet_graphique,"spinbutton7_mod_prod");
txt4c=lookup_widget(objet_graphique,"spinbutton8_mod_prod");
txt5=lookup_widget(objet_graphique,"stockA");
txt6=lookup_widget(objet_graphique,"stockB");


strcpy(p.identifiant,gtk_entry_get_text(GTK_ENTRY(iden)));
strcpy(p.nom,gtk_entry_get_text(GTK_ENTRY(txt1)));
strcpy(p.prix,gtk_entry_get_text(GTK_ENTRY(txt2)));
p.quantite=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(txt3));
p.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(txt4a));
p.date.moins=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(txt4b));
p.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(txt4c));
strcpy(p.place,gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(txt5))==1?"StockA":"StockB");
modifier(p,"stock.txt");
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Product Succesfully Modified");
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}
}



