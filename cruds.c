
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "cruds.h"
#include<gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>



enum{
    Eid,
    Etype,
    Edatej,
    Edatem,
    Edatea,
    Ecat,
    Ecompe,
    Ecompp,
    Ecomd,
    Ecrit1,
    Ecrit2,
    Ecrit3,
    Ecrit4,
    COLUMNS,
};


/*ajouter*/
void ajouter_menu(Menu m )
{
    FILE* f;

    f=fopen("men.txt","a");
    fprintf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,m.type,m.date.jour,m.date.mois,m.date.annee,m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,m.critere[0],m.critere[1],m.critere[2],m.critere[3]);
    fclose(f);
}

void get_allid(Menu m[50],int *n){
 
    FILE* f;
    int i=0;
    f=fopen("men.txt","r");

    if (f!=NULL){
        while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n",m[i].id,&(m[i].type),&m[i].date.jour,&m[i].date.mois,&m[i].date.annee,m[i].categorie,m[i].composition.ent,m[i].composition.plt,m[i].composition.dest,&(m[i].critere[0]),&m[i].critere[1],&(m[i].critere[2]),&(m[i].critere[3]))!=EOF){
             i++;
    }
    }
    *n=i;
    fclose(f);
}

/*supprimer*/

void supprimer_menu(char id[20]){
    FILE *f=NULL;
    FILE *g=NULL;
    Menu m;
    f=fopen("men.txt","r");
    g=fopen("men2.txt","a");
    if(f==NULL || g==NULL)
        return;
    else{
        while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF)
    {
        if (strcmp(id,m.id)!=0 ){fprintf(g,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n",m.id,m.type,m.date.jour,m.date.mois,m.date.annee,m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,m.critere[0],m.critere[1],m.critere[2],m.critere[3]);}
    }
    fclose(f);
    fclose(g);
    remove("men.txt");
    rename("men2.txt","men.txt");
    }
};

	/*modifier*/
	void modifier(Menu m2)
{
	Menu m;
	FILE *f, *g;
    printf("2\n");
	f=fopen("men.txt","r");
	g=fopen("men2.txt","a");
	if (f!=NULL && g!=NULL) {
        printf("3\n");
		while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF)
			{ if(strcmp(m.id,m2.id)==0){
                 printf("4\n");
				fprintf(g,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n",m2.id,m2.type,m2.date.jour,m2.date.mois,m2.date.annee,m2.categorie,m2.composition.ent,m2.composition.plt,m2.composition.dest,m2.critere[0],m2.critere[1],m2.critere[2],m2.critere[3]);}
			else{
                printf("5\n");
				fprintf(g,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n",m.id,m.type,m.date.jour,m.date.mois,m.date.annee,m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,m.critere[0],m.critere[1],m.critere[2],m.critere[3]);}
			}
		}
	fclose(f);
	fclose(g);
	remove("men.txt");
	rename("men2.txt","men.txt");
}

/* rechercher*/

int chercher(char id[]){
Menu m ;
FILE *f;
f= fopen("men.txt","r");
if(f != NULL){
while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n", m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF){
if(strcmp(m.id,id) == 0){
return 1;}}}
fclose(f);
return 0;
}



void afficher_menus(GtkWidget *liste){  //pointeur 3la treeview de type gtkwidget
    
    GtkCellRenderer *renderer; //render ta3tik l fourma mta3 treeview eli hiya espace bidha
    GtkTreeViewColumn *column; //inti f ena colonne
    GtkTreeIter iter; // iter : enti f ena star
    GtkListStore *store; //store : il garde l fourma mta3 treeview yani chnowa type mta3 colonne w fourmetha ya3ni type et nom de colonne
   /* char id[50]; // declaration des variables
    char type[50];
    int date_j;
    int date_m;
    int date_a;
    char cat[50];
    char comp_ent[50];
    char comp_plt[50];
    char comp_des[50];
    int critere[4];*/
    Menu m;
    char type[20];

    char *typee[]={"petit dejeuner","dejeuner","dinner"};

    FILE *f;
    store = NULL; 
    store = gtk_tree_view_get_model(liste); //ta5ou fourma mta3 liste view

    if(store == NULL){ 
        renderer = gtk_cell_renderer_text_new(); // les 3 lignes : i7adhroulek co
        column = gtk_tree_view_column_new_with_attributes("Référence",renderer,"text",Eid,NULL);// ref esm colonne
        //render : type de sortie et affichage Eid : ye7sblek nti f ena ligne
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column); //tlasa9 colonne l colonne

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Type ",renderer,"text",Etype,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Jour ",renderer,"text",Edatej,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Mois ",renderer,"text",Edatem,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année",renderer,"text",Edatea,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Catégorie",renderer,"text",Ecat,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Entrée",renderer,"text",Ecompe,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Plat Principal",renderer,"text",Ecompp,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Dessert",renderer,"text",Ecomd,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Critère",renderer,"text",Ecrit1,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Critère",renderer,"text",Ecrit2,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Critère",renderer,"text",Ecrit3,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Critère",renderer,"text",Ecrit4,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
    }
    store = gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
    //9adech andek mn colonnes w w ta3tik type de la variable l f colonne 
    f = fopen("men.txt","r"); // tawa mech n3amer e treeview donc 7alit l fichier 
    if(f == NULL){
            return;
    }
    else{
        while(fscanf(f,"%s %d %d %d %d %s %s %s %s %d %d %d %d\n",m.id,&(m.type),&(m.date.jour),&(m.date.mois),&(m.date.annee),m.categorie,m.composition.ent,m.composition.plt,m.composition.dest,&(m.critere[0]),&(m.critere[1]),&(m.critere[2]),&(m.critere[3]))!=EOF){
            if (m.type==1){
                strcpy(type,"petit déjeuner");
            }else if (m.type==2){
                strcpy(type,"dejeuner");
            }else {
                strcpy(type,"dinner");
            }
            gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,Eid,m.id,Etype,type,Edatej,m.date.jour,Edatem,m.date.mois,Edatea,m.date.annee,Ecat,m.categorie,Ecompe,m.composition.ent,Ecompp,m.composition.plt,Ecomd,m.composition.dest,Ecrit1,m.critere[0],Ecrit2,m.critere[1],Ecrit3,m.critere[2],Ecrit4,m.critere[3],-1);
                    
        }
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
        g_object_unref(store);
        fclose(f);
        }
}

/*afficher*/

void afficher_menus2(GtkWidget *liste){  //pointeur 3la treeview de type gtkwidget
    
    GtkCellRenderer *renderer; //render ta3tik l fourma mta3 treeview eli hiya espace bidha
    GtkTreeViewColumn *column; //inti f ena colonne
    GtkTreeIter iter; // iter : enti f ena star
    GtkListStore *store; //store : il garde l fourma mta3 treeview yani chnowa type mta3 colonne w fourmetha ya3ni type et nom de colonne

    char id[50]; // declaration des variables
    char type[50];
    int date_j;
    int date_m;
    int date_a;
    char cat[50];
    char comp_ent[50];
    char comp_plt[50];
    char comp_des[50];
    int critere[4];

    FILE *f;
    store = NULL; 
    store = gtk_tree_view_get_model(liste); //ta5ou fourma mta3 liste view

    if(store == NULL){ 
        renderer = gtk_cell_renderer_text_new(); // les 3 lignes : i7adhroulek co
        column = gtk_tree_view_column_new_with_attributes("Référence",renderer,"text",Eid,NULL);// ref esm colonne
//render : type de sortie et affichage Eid : ye7sblek nti f ena ligne
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column); //tlasa9 colonne l colonne

       /* renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Type ",renderer,"text",Etype,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Jour ",renderer,"text",Edatej,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(" Mois ",renderer,"text",Edatem,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année",renderer,"text",Edatea,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Catégorie",renderer,"text",Ecat,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


            renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Entrée",renderer,"text",Ecompe,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Plat Principal",renderer,"text",Ecompp,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Dessert",renderer,"text",Ecomd,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Critère",renderer,"text",Ecrit,NULL);
        column = gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);*/


    }
    store = gtk_list_store_new(COLUMNS,G_TYPE_STRING);
    
    gtk_list_store_append(store,&iter);
     gtk_list_store_set(store,&iter,Eid,"55",-1);
    //9adech andek mn colonnes w w ta3tik type de la variable l f colonne 
    
    
       /* f = fopen("menu.txt","r"); // tawa mech n3amer e treeview donc 7alit l fichier 
    if(f == NULL){
            return;
        }
    else{
            while(fscanf(f,"%s %s %d %d %d %s %s %s %s %s\n",id,type,date_j,date_m,date_a,cat,comp_ent,comp_plt,comp_des,critere[0],critere[1],critere[2],critere[3]) != EOF){ 
        
            gtk_list_store_append(store,&iter);
                    gtk_list_store_set(store,&iter,Eid,id,Etype,&type,Edatej,&date_j,Edatem,&date_m,Edatea,&date_a,Ecat,&cat,Ecompe,&comp_ent,Ecompp,&comp_plt,Ecomd,&comp_des,Ecrit1,critere[0],Ecrit2,critere[1],Ecrit3,critere[2],Ecrit4,critere[3],-1);
                    
            }
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
        g_object_unref(store);
            fclose(f);
        }*/
    
}




int calculmin(float tab[], int deb){
    int min =deb;
    int i;
    for(i=deb;i<(21+deb);i++){
        if (tab[i]<tab[min])
            min=i;
    }
    return min;
}
void calcul(int*j1,int*j2,int*j3,int*j4,int*type1,int*type2,int*type3,int*type4){
int pos1,pos2,pos3,pos4,i=0;
int tab1[100];
int tab2[100];
float tab3[100];
FILE *f;
int j,type;
float dechet;
  
f = fopen("dechets.txt","r");
if(f != NULL){
while(fscanf(f,"%d %d %f\n", &j,&type,&dechet) != EOF){

tab1[i]=j; tab2[i]=type; tab3[i]=dechet;
i++; }}

fclose(f);

 pos1=calculmin(tab3,0);

 *j1=tab1[pos1];*type1=tab2[pos1];
 pos2=calculmin(tab3,21);*j2=tab1[pos2];*type2=tab2[pos2];
 pos3=calculmin(tab3,42);*j3=tab3[pos3];*type3=tab2[pos3];
 pos4=calculmin(tab3,63);*j4=tab1[pos4];*type4=tab2[pos4];
 printf("%d %d\n",*j1,*type1);
}


