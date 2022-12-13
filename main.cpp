#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
// Initialisation des donneés 
typedef struct {
	int j;
	int m;
	int y;
}date;
typedef struct{
	char titre_mag [100];
	char name_auth [20];
	date date_realise;
	char description [100];
	int rate ;
}mag;
typedef struct{
	char titre_liv[100];
	char name_auth [20];
	date date_realise;
	char description [100];
	int rate ;
}liv;
typedef struct {
	int code ;
	char loc [10];
	int nbre;
	mag magazine ;
	liv livre;
	int dispo;
	char  type [100] ;
}biblio;
typedef struct {
	char nom [100];
	int id;
	char statut [10];
	int nbr_doc;
	date date_louer;
	date date_retour;
	int taxe ;

}fiche;

// Functions 

date saisie_date(){
    date d ;
    do{
        printf("Mois : ");
        scanf("%d",&d.m);
    }while(d.m<0 ||  d.m>12);
    do{
        printf("Annee : ");
        scanf("%d",&d.y);
    }while(d.y>2022 || d.y<1000);
    do{
        printf("Jour : ");
        scanf("%d",&d.j);
    }while(d.j<0 || d.j>31);
    return d;

}
liv  saisie_liv(){
	biblio b;
	printf("Donner le titre de livre : ");
	scanf("%s",&b.livre.titre_liv);
	printf("Donner le Nom d'auteur' de livre : ");
	scanf("%s",&b.livre.name_auth);
	printf("Donner date de realisation de livre : ");
	b.livre.date_realise=saisie_date();
	printf("Donner le rate de cette livre : ");
	scanf("%d",&b.livre.rate);
	return b.livre;
}
mag saisie_mag(){
	biblio b;
	printf("Donner le titre de magazine : ");
	scanf("%s",&b.magazine.titre_mag);
	printf("Donner le Nom d'auteur' de magazine : ");
	scanf("%s",&b.magazine.name_auth);
	printf("Donner date de realisation de magazine : \n");
	b.magazine.date_realise=saisie_date();
	printf("Donner le rate de cette magazine : ");
	scanf("%d",&b.magazine.rate);
	return b.magazine;
}


int saisie(){
	int n;
	printf("Donner les nombre de document que vous voulez l'ajouter : ");
	do{
	    scanf("%d",&n);
	}while(n==0);
	return n;

}
int saisiek(){
	int k;
	printf("Donner les nombre des personne : ");
	do{
	    scanf("%d",&k);
	}while(k==0);
	return k;

}
int verif_code(biblio b[],int x,int i){
    for(int j=0;j<i;j++){
        if(b[j].code==x){
            return 0;
        }
    }
    return 1 ;
}
biblio saisie_b(biblio t[],int i){
	biblio b;
    printf("Donner 	Code : ");
    scanf("%d",&b.code);
    while(verif_code(t,b.code,i)==0){
        printf("Erreur ! Cette code est deja utulise !!  Donner Code : ");
        scanf("%d",&b.code);
    }
    printf("Donner La location de cette document : ");
	scanf("%s",&b.loc);
	printf("Donner un nombre exemplaire : ");
	scanf("%d",&b.nbre);
	do{
        printf("Donner le type de document que vous voulez  l'ajouter : ");
        scanf("%s",&b.type);
    }while(strcmp(b.type,"livre")==1 && strcmp(b.type,"magazine")==1);
    if(strcmp(b.type,"livre")==0){
		b.livre=saisie_liv();
	}else{
		b.magazine=saisie_mag();
	}
	return b;
}
void saisie_tab(int n,biblio t[100]){
	for(int i=0;i<n;i++){
		t[i]=saisie_b(t,i);

	}
}
int verif(fiche f[],int x,int i){
	for(int j=0;j<i;j++){
		if(x==f[j].id){
			return 0;
		}
	}
	return 1;
}
fiche saisie_f(fiche f[],int i){
	fiche f2;
	printf("Donner Votre Nom : ");
	scanf("%s",&f2.nom);
	printf("Donner Votre Id : ");
	scanf("%d",&f2.id);
	while(verif(f,f2.id,i)!=1){
		printf("Erreur ! Cette Id est deja saisie Verifier Votre Id : ");
		scanf("%d",&f2.id);
	}
	do{
		printf("Donner Votre Statut : ");
		scanf("%s",&f2.statut);
	}while(strcmp(f2.statut,"etudiant")==1 && strcmp(f2.statut,"enseignent")==1 && strcmp(f2.statut,"administration")==1 );
	return f2;
}
void saisie_tab2(int n,fiche f[100]){
	for(int i=0;i<n;i++){
		f[i]=saisie_f(f,i);
		
	}
}

void affiche(){
    printf("------------------------------------------------Menu------------------------------------------------------------\n");
	printf("1) Louer Un Document\n");
	printf("2) Retour Un Document\n");
	printf("3) Mise a jour d'un Document\n");
	printf("4) Configuration de Biblio \n");
	printf("5) Affichage de contenu \n");
	printf("0) Pour sortir \n\n");
	
}
int choix(){
	int choix;
	printf("Choisir un commande : ");
	scanf("%d",&choix);
	return choix;
}
int search(biblio t[100],int code,int n){
	int i=0;
	while(i<n && t[i].code!=code){
		i++;
	}
	return i;
}
int search_id(fiche t[100],int id,int n){
	int i=0;
	while(i<n && t[i].id!=id){
		i++;
	}
	return i;
}
void verif_date(fiche f[100],int i,int k){
	int j=f[i].date_louer.j;
	int m=f[i].date_louer.m;
	int y=f[i].date_louer.y;
	if(j+k>31 && (m==1 || m==3||m==5 || m==7 || m==8 || m==12 || m==10)){
		j=(j+k)-31;
		if(m==12){
			m=1;
		}
		else{
		    m+=1;
		}
	}else if(j+k>30 &&(m==4 || m==6||m==9 || m==11 )){
		j=(j+15)-31;
		m+=1;
	}else if (m==2 && (j+k>28 || j+k>29)){
		if(y%4==0){
			if(j+k>29){
				j=j+k-29;
				m+1;
			}else{
				j=j+k-28;
				m+1;
			}
		}
	}else{
		j=j+k;
	}
	f[i].date_retour.j=j;
	f[i].date_retour.m=m;
	f[i].date_retour.y=y;


}
void affiche_data(char ch[],char ch1[],int j,int m,int y,char ch2[] ){
	if(strcmp(ch2,"livre")==0){
		printf("Vous avez Louer la document %s . Votre date de retour est %d / %d / %d",ch,j,m,y);
	}
	else{
		printf("Vous avez Louer la document %s . Votre date de retour est %d / %d / %d",ch1,j,m,y);
	}
}
void louer(biblio t[100],fiche f[100],int n,int k){
	int code,id;
	SYSTEMTIME time;
	GetSystemTime(&time);
	do{
		printf("Donner Le code de document que vous vouler louer : \n ");
	scanf("%d",&code);
	}while(verif_code(t,code,n));
	do{
	printf("Donner Votre Id : ");
	scanf("%d",&id);	
	}while(verif(f,id,n));
	int i=search(t,code,n);
	int j=search_id(f,id,k);
	if(t[i].dispo==0 && t[i].nbre==0){
		printf("Ces document sont deja louer !\n ");
	}else{
		t[i].nbre--;
		if(t[i].nbre==0){
			t[i].dispo=0;
		}
		f[i].nbr_doc++;
		f[i].date_louer.j=time.wDay;
		f[i].date_louer.m=time.wMonth;
		f[i].date_louer.y=time.wYear;
		if(strcmp(f[i].statut,"etudiant")==0){
			verif_date(f,i,15);
			affiche_data(t[i].livre.titre_liv,t[i].magazine.titre_mag,f[i].date_retour.j,f[i].date_retour.m,f[i].date_retour.y,t[i].type);
		}else if( strcmp(f[i].statut,"enseignent")==0){
			verif_date(f,i,10);
			affiche_data(t[i].livre.titre_liv,t[i].magazine.titre_mag,f[i].date_retour.j,f[i].date_retour.m,f[i].date_retour.y,t[i].type);
		}
		printf("Louer avec succes ! \n");

	}


}
void retour(biblio t[100],fiche f[100],int n,int k){
	int code,id;
	SYSTEMTIME time;
	GetSystemTime(&time);
	do{
		printf("Donner Le code de document que vous avez deja louer : \n");
	scanf("%d",&code);
	}while(verif_code(t,code,n));
	do{
	printf("Donner Votre Id : ");
	scanf("%d",&id);	
	}while(verif(f,id,n));
	int i=search_id(f,i,k);
	int j=search(t,code,n);
	if(t[j].dispo==1 && f[i].nbr_doc==0){
		printf("Verifier Votre donnees ! Vous n'avez pas loue cette  livre\n ");
	}else{
	
	if((f[i].date_retour.j>time.wDay) && (f[i].date_retour.m>time.wMonth)){
		f[i].taxe+=1;;
	}
	f[i].nbr_doc--;
	int j=search(t,code,n);
	t[i].dispo=1;
	t[i].nbre++;
	printf("Retour Avec Succes !\n");
}
}
void aff_mis(){
	printf("-------------------------------------------------Mise a jour ----------------------------------------------------------\n");
	printf("1) Pour Ajouter un livre/magazine\n");
	printf("2) Pour Modifier la quantite d'un document un livre/magazine\n");
	printf("3) Pour Modifier la disponibilité d'un document'\n");
	printf("4) Pour Supprimer un document \n");
	printf("0) Pour Sortir \n\n");
}
void supp(biblio t[100],int n ,int i){
	for(int j=i;j<n-1;i++){
		for(int k=j+1;k<n;k++){
			t[j]=t[k];
		}
	}
	
}
void mise_jour(biblio t[100],int *n,fiche f[100],int k){
	int id;
	do{
		printf("Donner Votre Id : ");
	scanf("%d",&id);
	}while(verif(f,id,k));
	
	int i=search_id(f,id,k);
	if(strcmp(f[i].statut,"etudiant")==0 ||strcmp(f[i].statut,"enseignent")==0  ){
		printf("Erreur ! Vous n'avez pas la permetion pour les modification ; \n");
	}else{
		aff_mis();
		int c,i,code;
		biblio e ;
		do{
		do{
		   c=choix();
		}while(c!=1 && c!=2 && c!=3 && c!=4 && c!=5 &&  c!=0);
		switch (c){
			case 1:
				t[*n]=saisie_b(t,*n);
				*n=*n+1;
				break;
			case 2 :
				int q,code;
				printf("Donner La quantite que vous voulez l'ajouter :");
				scanf("%d",&q);
				do{
					printf("Donner code de Document  : ");
					scanf("%d",&code);
				}while(verif_code(t,code,*n));
				i=search(t,code,*n);
				t[i].nbre+=q;
				break;
			case 3 :
				code;
				do{
				    printf("Donner code de Document que vous voulez modifier sa disponibilite : ");
				    scanf("%d",&code);	
				}while(verif_code(t,code,*n));
				
				i=search(t,code,*n);
				if(t[i].dispo==0){
					t[i].dispo=1;
				}else{
					t[i].dispo=0;
				}
				break;
			case 4:
				code;
				do{
					printf("Donner code de Document pour le supprimer : ");
					scanf("%d",&code);
				}while(verif_code(t,code,*n));
				i=search(t,code,*n);
				supp(t,*n,i);
				*n=*n-1;
				break;
            default :
                break;

		}
		aff_mis();
			
		}while(c!=0);
		
	}
}
void affiche_personel(fiche f[],int k){
	for(int i=0;i<k;i++){
		printf("Nom : %s , Id : %d , Statut : %s\n",f[i].nom,f[i].id,f[i].statut);
	}
}
void aff_conf(){
	printf("1) Pour ajouter des personnes \n");
	printf("2) Pour afficher liste des personnes \n");
	printf("0) Pour sortir ");
}
void configuration(fiche f[],int *k){
	int id;
	int c ;
	aff_conf();
	do{
		printf("Donner Votre Id : ");
	scanf("%d",&id);
	}while(verif(f,id,*k));
	int i=search_id(f,id,*k);
	if(strcmp(f[i].statut,"etudiant")==0 ||strcmp(f[i].statut,"enseignent")==0  ){
		printf("Erreur ! Vous n'avez pas la permetion pour les modification ; \n");
	}else{
	do{
		do{
		   c=choix();
		}while(c!=1 && c!=2 &&  c!=0);
		switch (c){
			case 1 :
				f[*k]=saisie_f(f,*k);
				*k=*k+1;
				break;
			case 2:
				affiche_personel(f,*k);
				break;
		}
		aff_conf();
		}while(c!=0);}
		
}
void affichage_cont(biblio t[100],int n){
	for(int i=0;i<n;i++){
		if(strcmp(t[i].type,"livre")==0){
			printf("Titre De Livre %s , Quantite  %d , Autheur : %s , Etat : ",t[i].livre.titre_liv,t[i].nbre,t[i].livre.name_auth);
		}else if(strcmp(t[i].type,"magazine ")==0){
			printf("Titre De Magazine : %s , Quantite  %d , Autheur : %s , Etat : ",t[i].magazine.titre_mag,t[i].nbre,t[i].magazine.name_auth);
		}
		if(t[i].dispo==0 && t[i].nbre!=0){
			printf(" N'est pas diponible pour le moument !\n");
		}else{
			printf(" Diponible!\n");
		}
	}
}
void moderation(int c,biblio t[100],fiche f[100],int *n,int *k){
	switch (c){
		case 0:
			break ;
		case 1:
			louer(t,f,*n,*k);
			break;
		case 2:
			retour(t,f,*n,*k);
			break;
		case 3 :
			mise_jour(t,n,f,*k);
			break;
		case 4:
		    configuration(f,k);
		    break;
		case 5:
			affichage_cont(t,*n);
			break;
	}
}

//main 

int main(){
	int n=saisie();
	int k=saisiek();
	biblio tab[100];
	fiche tab2[100];
	saisie_tab(n,tab);
	saisie_tab2(k,tab2);
	affiche();
	int c;
	do{
		do{
		   c=choix();
	}while(c!=1 && c!=2 && c!=3 && c!=4  && c!=5  && c!=0);
	moderation(c,tab,tab2,&n,&k);
	affiche();
	}while(c!=0);
}

