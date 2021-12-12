#include<stdio.h>
#include<string.h>
#include"stock.h"
#include<stdio.h>
#include<gtk/gtk.h>
enum{
IDEN,
NOM,
PRICE,
QUANT,
DATE,
PLACE,
COLUMNS
};
void verif_empty(stock p){
FILE *f=fopen("stock.txt","r");
if (f!=NULL){
FILE *g=fopen("rupture.txt","a+");
while(fscanf(f,"%s %s %s %d %d %d %d %s\n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place) !=EOF){
if (p.quantite==0){
fprintf(g,"%s %s %s %d %d %d %d %s \n",p.identifiant,p.nom,p.prix,p.quantite,p.date.jour,p.date.moins,p.date.annee,p.place); 
}
}
fclose(g);}
fclose(f);
}

void Add_Product(stock p1){
GtkWidget *dialog;
stock p;
int c=0;
FILE *f=fopen("stock.txt","a+");
gpointer user_data;
if(f!=NULL){
while(fscanf(f,"%s %s %s %d %d %d %d %s\n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place) !=EOF){
if (strcmp(p.identifiant,p1.identifiant)==0){
c++;
}
}
if (c!=0){
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"ID Exist already !!");
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}}
else if (c==0){
fprintf(f,"%s %s %s %d %d %d %d %s \n",p1.identifiant,p1.nom,p1.prix,p1.quantite,p1.date.jour,p1.date.moins,p1.date.annee,p1.place);
dialog=gtk_message_dialog_new(GTK_WINDOW(user_data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Product Succesfully Added :D");
	switch(gtk_dialog_run(GTK_DIALOG(dialog)))
	{
	case GTK_RESPONSE_OK:
	gtk_widget_destroy(dialog);
	break;
	}}
fclose(f);
}
verif_empty(p);
}


void Display_Stock(GtkWidget *list,char *filename){
stock p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar quantite[40];gchar date_achat[40];store=NULL;


FILE *f;

store=gtk_tree_view_get_model(list); 
if (store==NULL){

renderer = gtk_cell_renderer_text_new ();    
column = gtk_tree_view_column_new_with_attributes(" identifiant", renderer, "text" ,IDEN, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);  
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" nom", renderer, "text",NOM, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" prix", renderer, "text",PRICE, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" quantite", renderer, "text",QUANT, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" date_achat", renderer, "text",DATE, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" place", renderer, "text",PLACE, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);


store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING);

f = fopen(filename, "r");

if (f==NULL)

{

return;

}

else

{ f = fopen(filename, "a+");

while(fscanf(f,"%s %s %s %d %d %d %d %s\n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place) !=EOF)

{

sprintf(date_achat,"%d/%d/%d",p.date.jour,p.date.moins,p.date.annee);
sprintf(quantite,"%d",p.quantite);
gtk_list_store_append (store, &iter); //est l'itérateur parent. IL est utiLisé pour ajouter une Ligne enfant à une Ligne d'un GtkTreeStore,

gtk_list_store_set (store, &iter, IDEN, p.identifiant, NOM, p.nom, PRICE, p.prix,QUANT,quantite,DATE,date_achat,PLACE,p.place, -1);

}

fclose(f);

gtk_tree_view_set_model (GTK_TREE_VIEW (list), GTK_TREE_MODEL (store));
g_object_unref (store);}
}
}

void vider(GtkWidget *list){

GtkCellRenderer *renderer;

GtkTreeViewColumn *column;

GtkTreeIter iter;

GtkListStore *store;

char identifiant[20]; char nom[20]; ; char prix[20] ;int quantite; char date_achat[30]; char place[20];store=NULL;

FILE *f;

store=gtk_tree_view_get_model(list); 
if (store==NULL){

renderer = gtk_cell_renderer_text_new ();}}



void delete_Product(stock p1,char *filename){
stock p;

FILE *f, *g;
f=fopen(filename,"r");
g=fopen("dump.txt","w");
if(f!=NULL && g!=NULL){
	while(fscanf(f,"%s %s %s %d %d %d %d %s \n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place)!=EOF)
	{
		if(strcmp(p1.identifiant,p.identifiant)!=0)
			fprintf(g,"%s %s %s %d %d %d %d %s \n",p.identifiant,p.nom,p.prix,p.quantite,p.date.jour,p.date.moins,p.date.annee,p.place);
	}
	fclose(f);
	fclose(g);
remove(filename);
rename("dump.txt",filename);
}
}

stock search_product(char iden[],char *filename,int *v){
stock p, p1;
FILE *f;
*v=1;
f=fopen(filename,"r");
if(f!=NULL){
	while(fscanf(f,"%s %s %s %d %d %d %d %s\n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place)!=EOF)
	{
		if(strcmp(p.identifiant,iden)==0)
			return p;
	}
	fclose(f);
}
*v=-1;
return p1;
}

void modifier(stock b,char *fichier)
{
    FILE *f1;
    FILE *f2;
    stock a;
    f1=fopen(fichier,"r");
    f2=fopen("dump.txt","w");
    if(f1==NULL && f2==NULL){
    return;}
    else{
    while(fscanf(f1,"%s %s %s %d %d %d %d %s \n",a.identifiant,a.nom,a.prix,&a.quantite,&a.date.jour,&a.date.moins,&a.date.annee,a.place)!=EOF)
    {
        if(strcmp(b.identifiant,a.identifiant)!=0)
          fprintf(f2,"%s %s %s %d %d %d %d %s \n",a.identifiant,a.nom,a.prix,a.quantite,a.date.jour,a.date.moins,a.date.annee,a.place);
        else
          fprintf(f2,"%s %s %s %d %d %d %d %s \n",b.identifiant,b.nom,b.prix,b.quantite,b.date.jour,b.date.moins,b.date.annee,b.place);
    }
    fclose(f1);
    fclose(f2);
    remove(fichier);
    rename("dump.txt",fichier);
       
}
verif_empty(b);
if (b.quantite!=0){
delete_Product(b,"rupture.txt");
}
}


void Display_out_Stock(GtkWidget *list,char *filename){
stock p;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
gchar date_achat[40];store=NULL;


FILE *f;

store=gtk_tree_view_get_model(list); 
if (store==NULL){

renderer = gtk_cell_renderer_text_new ();    
column = gtk_tree_view_column_new_with_attributes(" identifiant", renderer, "text" ,IDEN, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);  
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" nom", renderer, "text",NOM, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);


renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" date_achat", renderer, "text",DATE, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);

renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes(" place", renderer, "text",PLACE, NULL); 
gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
gtk_tree_view_column_set_expand(column,TRUE);


store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

f = fopen(filename, "r");

if (f==NULL)

{

return;

}

else

{ f = fopen(filename, "a+");

while(fscanf(f,"%s %s %s %d %d %d %d %s\n",p.identifiant,p.nom,p.prix,&p.quantite,&p.date.jour,&p.date.moins,&p.date.annee,p.place) !=EOF)

{
if (p.quantite==0){
sprintf(date_achat,"%d/%d/%d",p.date.jour,p.date.moins,p.date.annee);


gtk_list_store_append (store, &iter); //est l'itérateur parent. IL est utiLisé pour ajouter une Ligne enfant à une Ligne d'un GtkTreeStore,

gtk_list_store_set (store, &iter, IDEN, p.identifiant, NOM, p.nom, PRICE, p.prix,DATE,date_achat,PLACE,p.place, -1);}

else 
break;
fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (list), GTK_TREE_MODEL (store));
g_object_unref (store);}
}
}
}
