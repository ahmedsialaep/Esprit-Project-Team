#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "cruds.h"


//#include "cruds.c"
int choix[]={0,0,0,0};
int s=0;
char idtreeview[10];
void
on_radiobutton_regime_standard_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton));
    s=2;
}


void
on_radiobutton_regime_vegetarien_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton));
    s=1;
}


void
on_checkbutton_sans_sucre_ajouter_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[0]=1;}
}


void
on_checkbutton_sans_sel_ajouter_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[1]=1;}
}


void
on_checkbutton_sans_lactose_ajouter_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[2]=1;}
}


void
on_checkbutton_sans_gluten_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[3]=1;}
}


void
on_button_ajouter_home_clicked         (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	Menu m;
	GtkWidget* id;
	GtkWidget* type;
	GtkWidget* j; 
	GtkWidget* m1; 
	GtkWidget* a;
    GtkWidget* rv;
    GtkWidget* rs;
	GtkWidget* ent;
	GtkWidget* plt;
    GtkWidget* dest;
    GtkWidget* critere;
    GtkWidget* label;

    //GtkWidget* Combobox1;
    int i;
	char texte[100]="";

	int V=1 ;
	GtkWidget *labelid;
	GtkWidget *labeltype;
	//labelid=lookup_widget(objet_graphique,"");

	//labeltype=lookup_widget(objet_graphique,"comboboxentry_type_ajouter");
	id=lookup_widget(objet_graphique,"entry_reference_ajouter");
	type=lookup_widget(objet_graphique,"comboboxentry_type_ajouter");
    //Combobox1=lookup_widget(objet_graphique,"comboboxentry_type_ajouter");

	j=lookup_widget(objet_graphique, "spinbutton_jour_ajouter");
	m1=lookup_widget(objet_graphique, "spinbutton_mois_ajouter");
    a=lookup_widget(objet_graphique, "spinbutton_annee_ajouter");

    
	rv=lookup_widget(objet_graphique, "radiobutton_regime_standard");
	rs=lookup_widget(objet_graphique, "radiobutton_regime_vegetarien");

    ent=lookup_widget(objet_graphique,"entry_entree_ajouter");
    plt=lookup_widget(objet_graphique,"entry_plat_principal_ajouter");
    dest=lookup_widget(objet_graphique,"entry_dessert_ajouter");

    critere=lookup_widget(objet_graphique,"labelcritere");
    

	strcpy(m.id,gtk_entry_get_text(GTK_ENTRY(id)));
	m.date.jour=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (j)) ;
	m.date.mois=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (m1)) ;
    m.date.annee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (a)) ;
   
    if(strcmp("Petit Déjeuner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
        m.type=1;
    else if (strcmp("Déjeuner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
        m.type=2;
    else 
        m.type=3;


    for(i=0;i<4;i++){
        m.critere[i]=choix[i];
    }



	if (s==1) 
		strcpy(m.categorie,"RV") ; 
	else if (s==2)
		strcpy(m.categorie,"RS") ;
 
    strcpy(m.composition.ent,gtk_entry_get_text(GTK_ENTRY(ent) ) );
    strcpy(m.composition.plt,gtk_entry_get_text(GTK_ENTRY(plt) ) );
    strcpy(m.composition.dest,gtk_entry_get_text(GTK_ENTRY(dest) ) );

   // critere_menu(choix,texte);
   // gtk_label_set_text(GTK_LABEL(critere),texte);

	/*if(strcmp(m.id,"")==0){
		gtk_widget_show(idinvalide);
	V=0;
	}
	else {
		gtk_widget_hide(idinvalide);
	}*/
	//if (V==1)
label=lookup_widget(objet_graphique,"label_succes_ajout");
gtk_label_set_text(label,"Menu ajouté avec succés");

	ajouter_menu(m);
        
}

int nn=0;
void
on_button_supprimer_home_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

GtkWidget* id,*label;
char aux[10];
id=lookup_widget(objet_graphique,"combobox_");
label=lookup_widget(objet_graphique,"label_succes_suppression");
strcpy(aux,gtk_combo_box_get_active_text(GTK_COMBO_BOX(id))) ;

printf("%s \n",aux);
supprimer_menu(aux) ;


gtk_label_set_text(label,"Menu supprimé avec succés");
}


void
on_button_afficher_menus_supprimer_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
    GtkWidget* id;
    int i,j;
    char aux[10];
    id=lookup_widget(objet_graphique,"combobox_");
    Menu m[50];
    Menu m1;
    int n;
     //printf("%d", gtk_combo_box_get_active(GTK_COMBO_BOX (id)));
    get_allid(m,&n);
     gtk_combo_box_set_active(GTK_COMBO_BOX(id),n);
    //printf("%d\n", gtk_combo_box_get_wrap_width(GTK_COMBO_BOX (id)));
    if (nn!=0){
        for(j=0;j<nn;j++)
         gtk_combo_box_remove_text(GTK_COMBO_BOX (id),0);
    }
    for (i=0;i< n;i++){
        gtk_combo_box_append_text(GTK_COMBO_BOX (id),_(m[i].id));
    }
     nn=n;
}


void
on_radiobutton_regime_vegetarien_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton));
    s=1;

}


void
on_radiobutton_regime_standard_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton));
    s=2;
}


void
on_checkbutton_sans_sucre_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
    {choix[0]=1;}
}


void
on_checkbutton_sans_sel_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[1]=1;}
}


void
on_checkbutton_sans_lactose_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[2]=1;}
}


void
on_checkbutton_sans_gluten_modifier_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
    {choix[3]=1;}
}


void
on_button_modifier_home_clicked        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
Menu m;
	GtkWidget* id;
	GtkWidget* type;
	GtkWidget* cal;
    GtkWidget* rv;
    GtkWidget* rs;
	GtkWidget* ent;
	GtkWidget* plt;
    GtkWidget* dest;
    GtkWidget* critere;
int j,m1,a;
    int i;
  GtkWidget *liste;
	GtkWidget *labelid;
	GtkWidget *labeltype;
	
    id=lookup_widget(objet_graphique,"combobox_reference_modifier");
	type=lookup_widget(objet_graphique,"comboboxentry_type_modifier");
	rv=lookup_widget(objet_graphique, "radiobutton_regime_standard_modifier");
	rs=lookup_widget(objet_graphique,"radiobutton_regime_vegetarien_modifier");
    ent=lookup_widget(objet_graphique,"entry_entree_modifier");
    plt=lookup_widget(objet_graphique,"entry_plat_principal_modifier");
    dest=lookup_widget(objet_graphique,"entry_dessert_modifier");
    critere=lookup_widget(objet_graphique,"label25");
    cal=lookup_widget(objet_graphique,"calendar_modifier");
    gtk_calendar_get_date (GTK_CALENDAR(cal),
                       &j,
                       &m1,
                       &a);
     if(strcmp("Petit Déjeuner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
        m.type=1;
    else if (strcmp("Déjeuner",gtk_combo_box_get_active_text(GTK_COMBO_BOX(type)))==0)
        m.type=2;
    else 
        m.type=3;

  for(i=0;i<4;i++){
        m.critere[i]=choix[i];
    }
if (s==1) 
		strcpy(m.categorie,"RV") ; 
	else if (s==2)
		strcpy(m.categorie,"RS") ;

    strcpy(m.id,gtk_combo_box_get_active_text(GTK_COMBO_BOX(id))) ;

    m.date.jour=j;
    m.date.mois=m1;
    m.date.annee=a;
printf("%d %d %d\n",j,m1,a);

strcpy(m.composition.ent,gtk_entry_get_text(GTK_ENTRY(ent) ) );
strcpy(m.composition.plt,gtk_entry_get_text(GTK_ENTRY(plt) ) );
strcpy(m.composition.dest,gtk_entry_get_text(GTK_ENTRY(dest) ) );

modifier(m);
 
    /*liste=lookup_widget(objet_graphique,"treeview1");
    afficher_menus(liste);*/
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void
on_button_afficher_menu_modifier_clicked (GtkWidget      *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget* id;
    int i,j;
    char aux[10];
    id=lookup_widget(objet_graphique,"combobox_reference_modifier");
    Menu m[50];
    Menu m1;
    int n;
     //printf("%d", gtk_combo_box_get_active(GTK_COMBO_BOX (id)));
    get_allid(m,&n);
     gtk_combo_box_set_active(GTK_COMBO_BOX(id),n);
    //printf("%d\n", gtk_combo_box_get_wrap_width(GTK_COMBO_BOX (id)));
    if (nn!=0){
        for(j=0;j<nn;j++)
         gtk_combo_box_remove_text(GTK_COMBO_BOX (id),0);
    }
    for (i=0;i< n;i++){
        gtk_combo_box_append_text(GTK_COMBO_BOX (id),_(m[i].id));
    }
     nn=n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void
on_button_cherhcer_home_clicked        (GtkWidget     *objet_graphique,
                                        gpointer         user_data)
{


GtkWidget *liste;
Menu m;
char mois_string[20];
char type_string[20];
char regime_string[20];
char id[20];
char datejour[5];
char datejour2[5];


GtkWidget *ref;
GtkWidget *type;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *regime;
GtkWidget *annee;
GtkWidget *categorie;
GtkWidget *entree;
GtkWidget *pltp;
GtkWidget *dessert;
GtkWidget *crit1;
GtkWidget *crit2;
GtkWidget *crit3;
GtkWidget *crit4;

		GtkWidget* idm;
		GtkWidget *labelShow;
                GtkWidget* label;

		
		int X ; 
		char aux[50] ; 
		idm=lookup_widget(objet_graphique,"entry_reference_chercher");
                label=lookup_widget(objet_graphique,"label_menu_introubale");
		strcpy(aux,gtk_entry_get_text(GTK_ENTRY(idm))) ;
		X=chercher(aux) ; 
		if (X==0)	
                gtk_label_set_text(label,"Menu introuvable");
                else	
                gtk_label_set_text(label,"Menu existant");


FILE *f;
printf("1\n");
f= fopen("men.txt","r");
printf("2\n");
if(f != NULL){
while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF){
if(strcmp(m.id,aux) == 0){
        GtkWidget *uno;
     GtkNotebook *notebook1;
  uno = create_affichage_uno();
  gtk_widget_show (uno);
printf("3\n");
if (m.type==1){
                strcpy(type_string,"petit déjeuner");
            }else if (m.type==2){
                strcpy(type_string,"dejeuner");
            }else {
                strcpy(type_string,"dinner");
            }
printf("4\n");
type = lookup_widget(uno, "type_uno");
gtk_label_set_text(GTK_LABEL(type),type_string);
printf("5\n");
jour = lookup_widget(uno, "jour_uno");
snprintf(datejour2, 5, "%d", m.date.jour );
gtk_label_set_text(GTK_LABEL(jour),datejour2);

printf("6\n");
switch(m.date.mois) {
                              case 1: strcpy(mois_string,"Janvier"); break;
                              case 2: strcpy(mois_string,"Février"); break;
                              case 3: strcpy(mois_string,"Mars"); break;
                              case 4: strcpy(mois_string,"Avril"); break;
                              case 5: strcpy(mois_string,"Mai"); break;
                              case 6: strcpy(mois_string,"Juin"); break;
                              case 7: strcpy(mois_string,"Juillet"); break;
                              case 8: strcpy(mois_string,"Août"); break;
                              case 9: strcpy(mois_string,"Septembre"); break; 
                              case 10: strcpy(mois_string,"Octobre"); break; 
                              case 11: strcpy(mois_string,"Novembre"); break; 
                              case 12: strcpy(mois_string,"Décembre"); break; 
                            }

mois = lookup_widget(uno, "mois_uno");
gtk_label_set_text(GTK_LABEL(mois),mois_string);

snprintf(datejour, 5, "%d", m.date.annee );
gtk_label_set_text(GTK_LABEL(jour),datejour);

annee = lookup_widget(uno, "annee_uno");
gtk_label_set_text(GTK_LABEL(annee),datejour);

regime = lookup_widget(uno, "regime_uno");
gtk_label_set_text(GTK_LABEL(regime),m.categorie);

entree= lookup_widget(uno, "entree_uno");
gtk_label_set_text(GTK_LABEL(entree),m.composition.ent);

pltp= lookup_widget(uno, "plt_uno");
gtk_label_set_text(GTK_LABEL(pltp),m.composition.plt);

dessert= lookup_widget(uno, "dessert_uno");
gtk_label_set_text(GTK_LABEL(dessert),m.composition.dest);

crit1= lookup_widget(uno, "lcrit1");
if(m.critere[0]==0){
gtk_label_set_text(GTK_LABEL(crit1),"*");}
if(m.critere[0]==1){
gtk_label_set_text(GTK_LABEL(crit1),"✓");}

crit2= lookup_widget(uno, "lcrit2");
if(m.critere[1]==0){
gtk_label_set_text(GTK_LABEL(crit2),"*");}
if(m.critere[1]==1){
gtk_label_set_text(GTK_LABEL(crit2),"✓");}

crit3= lookup_widget(uno, "lcrit3");
if(m.critere[2]==0){
gtk_label_set_text(GTK_LABEL(crit3),"*");}
if(m.critere[2]==1){
gtk_label_set_text(GTK_LABEL(crit3),"✓");}

crit4= lookup_widget(uno, "lcrit4");
if(m.critere[3]==0){
gtk_label_set_text(GTK_LABEL(crit4),"*");}
if(m.critere[3]==1){
gtk_label_set_text(GTK_LABEL(crit4),"✓");}
}
}
}
fclose(f);

}
void
on_button_ajouter_affichage_clicked    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
       GtkWidget *home;
       GtkNotebook *notebook1;
  home = create_home();
  gtk_widget_show (home);
 /* notebook1=lookup_widget(objet_graphique,"notebook1");
 gtk_notebook_set_current_page(GtkNotebook *notebook,2);*/
}


void
on_button_supprimer_affichage_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *uno;
     GtkNotebook *notebook1;
  uno = create_affichage_uno();
  gtk_widget_show (uno);
char mois_string[20];
char type_string[20];
char regime_string[20];
char id[20];
char datejour[5];
char datejour2[5];
GtkWidget *ref;
GtkWidget *type;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *regime;
GtkWidget *annee;
GtkWidget *categorie;
GtkWidget *entree;
GtkWidget *pltp;
GtkWidget *dessert;
GtkWidget *crit1;
GtkWidget *crit2;
GtkWidget *crit3;
GtkWidget *crit4;
Menu m;

FILE *f;
f= fopen("men.txt","r");

if(f != NULL){
while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF){
if(strcmp(idtreeview,m.id) == 0){
printf("199\n");
if (m.type==1){
                strcpy(type_string,"petit déjeuner");
            }else if (m.type==2){
                strcpy(type_string,"dejeuner");
            }else {
                strcpy(type_string,"dinner");
            }
printf("4\n");
type = lookup_widget(uno, "type_uno");
gtk_label_set_text(GTK_LABEL(type),type_string);
printf("5\n");
jour = lookup_widget(uno, "jour_uno");
snprintf(datejour2, 5, "%d", m.date.jour );
gtk_label_set_text(GTK_LABEL(jour),datejour2);

printf("6\n");
switch(m.date.mois) {
                              case 1: strcpy(mois_string,"Janvier"); break;
                              case 2: strcpy(mois_string,"Février"); break;
                              case 3: strcpy(mois_string,"Mars"); break;
                              case 4: strcpy(mois_string,"Avril"); break;
                              case 5: strcpy(mois_string,"Mai"); break;
                              case 6: strcpy(mois_string,"Juin"); break;
                              case 7: strcpy(mois_string,"Juillet"); break;
                              case 8: strcpy(mois_string,"Août"); break;
                              case 9: strcpy(mois_string,"Septembre"); break; 
                              case 10: strcpy(mois_string,"Octobre"); break; 
                              case 11: strcpy(mois_string,"Novembre"); break; 
                              case 12: strcpy(mois_string,"Décembre"); break; 
                            }

mois = lookup_widget(uno, "mois_uno");
gtk_label_set_text(GTK_LABEL(mois),mois_string);

snprintf(datejour, 5, "%d", m.date.annee );
gtk_label_set_text(GTK_LABEL(jour),datejour);

annee = lookup_widget(uno, "annee_uno");
gtk_label_set_text(GTK_LABEL(annee),datejour);

regime = lookup_widget(uno, "regime_uno");
gtk_label_set_text(GTK_LABEL(regime),m.categorie);

entree= lookup_widget(uno, "entree_uno");
gtk_label_set_text(GTK_LABEL(entree),m.composition.ent);

pltp= lookup_widget(uno, "plt_uno");
gtk_label_set_text(GTK_LABEL(pltp),m.composition.plt);

dessert= lookup_widget(uno, "dessert_uno");
gtk_label_set_text(GTK_LABEL(dessert),m.composition.dest);

crit1= lookup_widget(uno, "lcrit1");
if(m.critere[0]==0){
gtk_label_set_text(GTK_LABEL(crit1),"*");}
if(m.critere[0]==1){
gtk_label_set_text(GTK_LABEL(crit1),"✓");}

crit2= lookup_widget(uno, "lcrit2");
if(m.critere[1]==0){
gtk_label_set_text(GTK_LABEL(crit2),"*");}
if(m.critere[1]==1){
gtk_label_set_text(GTK_LABEL(crit2),"✓");}

crit3= lookup_widget(uno, "lcrit3");
if(m.critere[2]==0){
gtk_label_set_text(GTK_LABEL(crit3),"*");}
if(m.critere[2]==1){
gtk_label_set_text(GTK_LABEL(crit3),"✓");}

crit4= lookup_widget(uno, "lcrit4");
if(m.critere[3]==0){
gtk_label_set_text(GTK_LABEL(crit4),"*");}
if(m.critere[3]==1){
gtk_label_set_text(GTK_LABEL(crit4),"✓");}
}
}
}
fclose(f);
}

void
on_button_modifier_affichage_clicked   (GtkWidget       *objet_graphique,/*le bouttons qui affichs sur treeview*/
                                        gpointer         user_data)
{
    GtkWidget *liste;
    liste=lookup_widget(objet_graphique,"treeview1");
    afficher_menus(liste);
}


gboolean
on_combobox_reference_modifier_button_press_event
                                        (GtkWidget       *objet_graphique,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

     GtkWidget* id;
    int i,j;
    id=lookup_widget(objet_graphique,"combobox_");

    Menu m[50];
    int n;
    get_allid(m,&n);
    printf("%d\n", gtk_combo_box_get_wrap_width(GTK_COMBO_BOX (id)));
    

    if (n!=0){
        for(j=0;j<nn;j++)
         gtk_combo_box_remove_text(GTK_COMBO_BOX (id),0);
    }
   
    

    for (i=0;i< n;i++){
        gtk_combo_box_append_text(GTK_COMBO_BOX (id),_(m[i].id));
    }
  nn=n;

  return FALSE;
}


gboolean
on_combobox__key_press_event           (GtkWidget       *objet_graphique,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
    GtkWidget* id;
    int i,j;
    id=lookup_widget(objet_graphique,"combobox_");

    Menu m[50];
    int n;
    get_allid(m,&n);
    printf("%d\n", gtk_combo_box_get_wrap_width(GTK_COMBO_BOX (id)));
    

    if (n!=0){
        for(j=0;j<2;j++)
         gtk_combo_box_remove_text(GTK_COMBO_BOX (id),0);
    }
   
    

    for (i=0;i< n;i++){
        gtk_combo_box_append_text(GTK_COMBO_BOX (id),_(m[i].id));
    }
  nn=n;

  return FALSE;
}


gboolean
on_combobox_reference_modifier_key_press_event
                                        (GtkWidget       *objet_graphique,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
 GtkWidget* id;
    int i,j;
    id=lookup_widget(objet_graphique,"combobox_reference_modifier");

    Menu m[50];
    int n;
    get_allid(m,&n);
    printf("%d\n", gtk_combo_box_get_wrap_width(GTK_COMBO_BOX (id)));
    

    if (n!=0){
        for(j=0;j<2;j++)
         gtk_combo_box_remove_text(GTK_COMBO_BOX (id),0);
    }
   
    

    for (i=0;i< n;i++){
        gtk_combo_box_append_text(GTK_COMBO_BOX (id),_(m[i].id));
    }
  nn=n;
  return FALSE;
}


void
on_dash_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{


}


void
on_dashbord_clicked                    (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
    int j1,j2,j3,j4,type1,type2,type3,type4;
    char j11[10],j22[10],j33[10],j44[10],type11[10],type22[10],type33[10],type44[10];

    GtkWidget *dashboard,*labelj1,*labelj2,*labelj3,*labelj4,*cal,*labelt1,*labelt2,*labelt3,*labelt4;
    dashboard = create_window_dashboard();
    gtk_widget_show (dashboard);

    labelt1=lookup_widget(dashboard,"t1");
    labelt2=lookup_widget(dashboard,"t2");
    labelt3=lookup_widget(dashboard,"t3");
    labelt4=lookup_widget(dashboard,"t4");

    labelj1=lookup_widget(dashboard,"j1");
    labelj2=lookup_widget(dashboard,"j2");
    labelj3=lookup_widget(dashboard,"j3");
    labelj4=lookup_widget(dashboard,"j4");
  
    calcul(&j1,&j2,&j3,&j4,&type1,&type2,&type3,&type4);
    printf ("%d %d %d %d %d %d %d %d\n",j1,j2,j3,j4,type1,type2,type3,type4);
    char jour[10]="jour°";
    char test[20];

    char t[15];
    if(type1==1){
        strcpy(t,"petit déjeuner");
    }else if(type1==2){
        strcpy(t,"déjeuner");
    }else{
        strcpy(t,"dinner");
    }

    snprintf(test,sizeof(test),"%d",j1);
    strcat(jour,test);
    gtk_label_set_text(labelj1,jour);
    gtk_label_set_text(labelt1,t);



    if(type2==1){
        strcpy(t,"petit déjeuner");
    }else if(type2==2){
        strcpy(t,"déjeuner");
    }else{
        strcpy(t,"dinner");
    }
   char jour2[10]="jour°";
   snprintf(test,sizeof(test),"%d",j2);
   strcat(jour2,test);
   gtk_label_set_text(labelj2,jour2);
   gtk_label_set_text(labelt2,t);



    if(type3==1){
        strcpy(t,"petit déjeuner");
    }else if(type3==2){
        strcpy(t,"déjeuner");
    }else{
        strcpy(t,"dinner");
    }
   char jour3[10]="jour°";
   snprintf(test,sizeof(test),"%d",j3);
   strcat(jour3,test);
   gtk_label_set_text(labelj3,jour3);
   gtk_label_set_text(labelt3,t);


    if(type4==1){
        strcpy(t,"petit déjeuner");
    }else if(type4==2){
        strcpy(t,"déjeuner");
    }else{
        strcpy(t,"dinner");
    }
   char jour4[10]="jour°";
   snprintf(test,sizeof(test),"%d",j4);
   strcat(jour4,test);
   gtk_label_set_text(labelj4,jour4);
   gtk_label_set_text(labelt4,t);

}


void
on_button_afficher_menus_ajouter_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *window_affichage;
 GtkNotebook *notebook1;
 window_affichage = create_window_affichage();
 gtk_widget_show (window_affichage);
}


void
on_button_afficher_menu__chercher_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
    GtkWidget *window_affichage;
    GtkNotebook *notebook1;
    window_affichage = create_window_affichage();
    gtk_widget_show (window_affichage);
}





void
on_button_siwar_afficher_clicked       (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
     GtkWidget *uno;
     GtkNotebook *notebook1;
  uno = create_affichage_uno();
  gtk_widget_show (uno);

}


void
on_affichage_siwar_menus_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
     GtkWidget *affichage;
     GtkNotebook *notebook1;
  affichage = create_window_affichage();
  gtk_widget_show (affichage);
}


void
on_revealbutton_clicked                (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
Menu m ;
char mois_string[20];
char type_string[20];
char regime_string[20];
char id[20];
char datejour[5];
char datejour2[5];
GtkWidget *ref;
GtkWidget *type;
GtkWidget *jour;
GtkWidget *mois;
GtkWidget *regime;
GtkWidget *annee;
GtkWidget *categorie;
GtkWidget *entree;
GtkWidget *pltp;
GtkWidget *dessert;
GtkWidget *crit1;
GtkWidget *crit2;
GtkWidget *crit3;
GtkWidget *crit4;
ref =lookup_widget(objet_graphique,"combobox_reference_modifier");  
strcpy(id,gtk_combo_box_get_active_text(GTK_COMBO_BOX(ref))) ;


FILE *f;
printf("1\n");
f= fopen("men.txt","r");
printf("2\n");
if(f != NULL){
while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF){
if(strcmp(m.id,id) == 0){

printf("3\n");
if (m.type==1){
                strcpy(type_string,"petit déjeuner");
            }else if (m.type==2){
                strcpy(type_string,"dejeuner");
            }else {
                strcpy(type_string,"dinner");
            }
printf("4\n");
type = lookup_widget(objet_graphique, "type_uno");
gtk_label_set_text(GTK_LABEL(type),type_string);
printf("5\n");
jour = lookup_widget(objet_graphique, "jour_uno");
snprintf(datejour2, 5, "%d", m.date.jour );
gtk_label_set_text(GTK_LABEL(jour),datejour2);

printf("6\n");
switch(m.date.mois) {
                              case 1: strcpy(mois_string,"Janvier"); break;
                              case 2: strcpy(mois_string,"Février"); break;
                              case 3: strcpy(mois_string,"Mars"); break;
                              case 4: strcpy(mois_string,"Avril"); break;
                              case 5: strcpy(mois_string,"Mai"); break;
                              case 6: strcpy(mois_string,"Juin"); break;
                              case 7: strcpy(mois_string,"Juillet"); break;
                              case 8: strcpy(mois_string,"Août"); break;
                              case 9: strcpy(mois_string,"Septembre"); break; 
                              case 10: strcpy(mois_string,"Octobre"); break; 
                              case 11: strcpy(mois_string,"Novembre"); break; 
                              case 12: strcpy(mois_string,"Décembre"); break; 
                            }

mois = lookup_widget(objet_graphique, "mois_uno");
gtk_label_set_text(GTK_LABEL(mois),mois_string);

snprintf(datejour, 5, "%d", m.date.annee );
gtk_label_set_text(GTK_LABEL(jour),datejour);

annee = lookup_widget(objet_graphique, "annee_uno");
gtk_label_set_text(GTK_LABEL(annee),datejour);

regime = lookup_widget(objet_graphique, "regime_uno");
gtk_label_set_text(GTK_LABEL(regime),m.categorie);

entree= lookup_widget(objet_graphique, "entree_uno");
gtk_label_set_text(GTK_LABEL(entree),m.composition.ent);

pltp= lookup_widget(objet_graphique, "plt_uno");
gtk_label_set_text(GTK_LABEL(pltp),m.composition.plt);

dessert= lookup_widget(objet_graphique, "dessert_uno");
gtk_label_set_text(GTK_LABEL(dessert),m.composition.dest);

crit1= lookup_widget(objet_graphique, "lcrit1");
if(m.critere[0]==0){
gtk_label_set_text(GTK_LABEL(crit1),"*");}
if(m.critere[0]==1){
gtk_label_set_text(GTK_LABEL(crit1),"✓");}

crit2= lookup_widget(objet_graphique, "lcrit2");
if(m.critere[1]==0){
gtk_label_set_text(GTK_LABEL(crit2),"*");}
if(m.critere[1]==1){
gtk_label_set_text(GTK_LABEL(crit2),"✓");}

crit3= lookup_widget(objet_graphique, "lcrit3");
if(m.critere[2]==0){
gtk_label_set_text(GTK_LABEL(crit3),"*");}
if(m.critere[2]==1){
gtk_label_set_text(GTK_LABEL(crit3),"✓");}

crit4= lookup_widget(objet_graphique, "lcrit4");
if(m.critere[3]==0){
gtk_label_set_text(GTK_LABEL(crit4),"*");}
if(m.critere[3]==1){
gtk_label_set_text(GTK_LABEL(crit4),"✓");}
}
}
}
fclose(f);

}


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data,
                                        GtkWidget       *objet_graphique)
{
    GtkTreeSelection *selection1;
    gchar *id;
    
    GtkTreeModel     *model;
    GtkTreeIter iter;
    GtkWidget *p=lookup_widget(affichage,"treeview1");
    selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(p));
    if (gtk_tree_selection_get_selected(selection1, &model, &iter))
    {
        gtk_tree_model_get (model,&iter,0,&id,-1);
    }
    strcpy(idtreeview,id);
}

