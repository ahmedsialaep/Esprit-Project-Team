#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reclam.h"
enum{
	RID,
	RCIN,
	RNOM,
	RPRENOM,
	RTYPE,
	RJOUR,
	RMOIS,
	RANNEE,
	RRECLAMATION,
	RSATISFACTION,
	REDUCATION,
	COLUMNS
};
void ajouter_reclam(reclam r){
  FILE *f;
  f=fopen("reclam.txt","a+");
  if(f!=NULL){
    fprintf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,r.type,r.text_reclamation,r.d.jour,r.d.mois,r.d.annee,r.satisfaction,r.education);
	}
	else
		return;
	fclose(f);
}
void supprimer_reclam(char id[20]){
	reclam r;
	FILE *f,*g;
	f=fopen("reclam.txt","r");
	g=fopen("tmp.txt","a+");
	if(f!=NULL && g!=NULL)
	{
	while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,&r.type,r.text_reclamation,&r.d.jour,&r.d.mois,&r.d.annee,&r.satisfaction,&r.education)!=EOF)
	{
        if(strcmp(id,r.id)!=0)
	fprintf(g,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,r.type,r.text_reclamation,r.d.jour,r.d.mois,r.d.annee,r.satisfaction,r.education);
	}
	}
	fclose(f);
	fclose(g);
	remove("reclam.txt");
	rename("tmp.txt","reclam.txt");
}

void modifier_reclam(reclam r){
	reclam r1;
	FILE *f,*g;
	f=fopen("reclam.txt","r");
	g=fopen("tmp.txt","a+");
	if(f!=NULL && g!=NULL)
	{
	while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r1.id,r1.cin,r1.nom,r1.prenom,&r1.type,r1.text_reclamation,&r1.d.jour,&r1.d.mois,&r1.d.annee,&r1.satisfaction,&r1.education)!=EOF)
	   {
	    if(strcmp(r1.id,r.id)!=0)
	     fprintf(g,"%s %s %s %s %d %s %d %d %d %d %d\n",r1.id,r1.cin,r1.nom,r1.prenom,r1.type,r1.text_reclamation,r1.d.jour,r1.d.mois,r1.d.annee,r1.satisfaction,r1.education);
	    else
	    fprintf(g,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,r.type,r.text_reclamation,r.d.jour,r.d.mois,r.d.annee,r.satisfaction,r.education);		
		}
	}
	fclose(f);
	fclose(g);
	remove("reclam.txt");
	rename("tmp.txt","reclam.txt");
}
void recherche_reclam(char cin[20]){
	reclam r1;
	FILE *f,*g;
	f=fopen("reclam.txt","r");
	g=fopen("recherche.txt","a+");
	if(f!=NULL && g!=NULL){
	  while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r1.id,r1.cin,r1.nom,r1.prenom,&r1.type,r1.text_reclamation,&r1.d.jour,&r1.d.mois,&r1.d.annee,&r1.satisfaction,&r1.education)!=EOF)
	  {
	  if(strcmp(cin,r1.cin)==0)
	   fprintf(g,"%s %s %s %s %d %s %d %d %d %d %d\n",r1.id,r1.cin,r1.nom,r1.prenom,r1.type,r1.text_reclamation,r1.d.jour,r1.d.mois,r1.d.annee,r1.satisfaction,r1.education);
				
	  }
	}
	fclose(f);
	fclose(g);

}

void afficher_reclam(GtkWidget *liste, char file[20])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter ;
	GtkListStore *store;
	reclam r;
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);
	if(store==NULL){
		
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("ID",renderer,"text",RID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("CIN",renderer,"text",RCIN,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",RNOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column); 

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Prenom",renderer,"text",RPRENOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
 
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Type",renderer,"text",RTYPE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Jour",renderer,"text",RJOUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Mois",renderer,"text",RMOIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Annee",renderer,"text",RANNEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Reclamation",renderer,"text",RRECLAMATION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("SATISFACTION",renderer,"text",RSATISFACTION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("Education",renderer,"text",REDUCATION,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		 
	}
		 	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);
	f=fopen(file,"r");
	if(f==NULL){return;}
	else
	{
        while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,&r.type,r.text_reclamation,&r.d.jour,&r.d.mois,&r.d.annee,&r.satisfaction,&r.education)!=EOF)
	{
      
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,RID,r.id,RCIN,r.cin,RNOM,r.nom,RPRENOM,r.prenom,RTYPE,r.type,RJOUR,r.d.jour,RMOIS,r.d.mois,RANNEE,r.d.annee,RRECLAMATION,r.text_reclamation,RSATISFACTION,r.satisfaction,REDUCATION,r.education,-1);
		 }
	 fclose(f);
	 gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	 g_object_unref(store);
	}
}
int serviceleplusreclame()
{
	int s=0,s1=0;
	FILE *f;
	reclam r;
	f=fopen("reclam.txt","r");
	if(f!=NULL)
	{
	 while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,&r.type,r.text_reclamation,&r.d.jour,&r.d.mois,&r.d.annee,&r.satisfaction,&r.education)!=EOF)
	{
	if(r.type==0)
	  s++;
        else
	  s1++;
	}
	}
	if(s>s1)
		return 0;
	else
		return 1;
		
}
int existe(char id[20])
{
	FILE *f;
	reclam r;
	f=fopen("reclam.txt","r");
	if(f!=NULL)
	{
	while(fscanf(f,"%s %s %s %s %d %s %d %d %d %d %d\n",r.id,r.cin,r.nom,r.prenom,&r.type,r.text_reclamation,&r.d.jour,&r.d.mois,&r.d.annee,&r.satisfaction,&r.education)!=EOF)
	{
	 if(strcmp(r.id,id)==0)
	  return 1;
	}
	fclose(f);
	}
	return 0;
}







