#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int produitId = 1; // Initialisation de Id du produit pour Auto incrementations


//Declaration de structure produit
typedef struct {
	int id;
	char * nom;
	int qte;
	float prix;
	
}Produit;

//Ajouter un nouveau produit
void ajouterProduit(Produit * prod, int size){
	
	
	
	printf("=================== Ajouter un nouveau produit: ==================\n\n");

	prod[size].id = produitId;
	
	prod[size].nom = malloc(40 * sizeof(char));
	printf("Nom du produit => ");
	scanf("%s",prod[size].nom);
	printf("Quanite du produit => ");
	scanf("%d",&prod[size].qte);
	printf("Prix du produit => ");
	scanf("%f",&prod[size].prix);
	
	produitId++;
	printf("Ajout termine avec succee \n");
	
	

	getch();
}


void listProduits(Produit *prod, int size){
	int i;
	printf("=================== Liste des produits (%d) ==================\n\n", size);
	for(i =0; i < size; i++){
		printf("              Produit %d\n",i+1);
		printf("Id => %d\n", prod[i].id);
		printf("Nom => %s\n", prod[i].nom);
		printf("Quantite => %d\n", prod[i].qte);
		printf("Prix => %f\n", prod[i].prix);
		printf("==============================\n");
	}
	getch();
}

//Fonction pour ajouter plusieurs produits
void ajouterPlusieurProduits(Produit * prod,int size,int newSize){
	int i;
	for(i= size; i < newSize + size ; i++){
		prod[i].id = produitId;
		prod[i].nom = malloc(40 * sizeof(char));
		printf("Nom du produit => ");
		scanf("%s",prod[i].nom);
		printf("Quanite du produit => ");
		scanf("%d",&prod[i].qte);
		printf("Prix du produit => ");
		scanf("%f",&prod[i].prix);
		produitId++;
		printf("=================================================\n\n");
	}
	
	
}
//Fonction pour afficher le menu principal
int menu(){
	int op;
	printf("==================== Gestion de Pharmacie ========================\n");
	printf("1- Ajouter un nouveau prodouit: \t 2- Ajouter plusieur produits:\n");
	printf("3- Consulter la liste des produit: \t 4-:Acheter un produit: \n");
	printf("5- Rechercher un produit: \t\t 6- Etat de stock:\n");
	printf("7- Alimenter le stock: \t\t\t 8- Suprimer un produit: \n");
	printf("9- Static de vente: \t\t\t 10- Quitter le programme: \n");
	printf("======================================================================\n");
	printf("\nVeuillez Choisir un operation: => ");
	scanf("%d", &op);
	return op; 
}

/*Fonction pour Afficher le sous-menu pour afficher la liste des produits 
	selon l'ordre choisi par l'utilisateur */
void subMenuList (Produit * prod, int size){
	
	int choix,i,j;
	do{
		printf("Donner la maniere d'affichage \n");
		printf("1- Selon l'ordre alphabetique  croissant du nom: \t 2- Selon l'ordre  decroissant du prix. \n");
		scanf("%d",&choix);
		if(choix != 1 && choix != 2){
			printf("Choix invalide \n");

		}
	}while(choix != 1 && choix != 2);
	switch(choix){
		case 1: 
			for(i = 0; i < size; i++){
				for(j = 0; j < size -1; j++){
					if(strcmp(prod[j].nom, prod[j+1].nom) == 1){
						Produit temp = prod[j];
						prod[j] = prod[j+1];
						prod[j+1] = temp;
					}
				}
				
			}
			listProduits(prod,size);
		case 2: 
			for(i = 0; i < size; i++){
				for(j = 0; j < size -1; j++){
					if(prod[j].prix < prod[j + 1].prix){
						Produit temp = prod[j];
						prod[j] = prod[j+1];
						prod[j+1] = temp;
					}
				}
				
			}
			listProduits(prod,size);
		
		default : 
			printf("Choix invalide ");
			getch();
	}
	
}

void searchById(Produit * prod,int size){
	int id; 
	printf("Donner l'Id du produit => ");
	scanf("%d",&id);
	int exists = findById(prod,size,id);
	if(exists == 0){
		printf("Ce produit n'exist pas dans le stock: \n");
	}else{
		printf("Id => %d\n", prod[exists].id);
		printf("Nom => %s\n", prod[exists].nom);
		printf("Quantite => %d\n", prod[exists].qte);
		printf("Prix => %f\n", prod[exists].prix);
		printf("==============================\n");
	}
}

// Fonction pour rechercher le produit par Id
int findById(Produit * prod, int size,int id  ){
	int i = 0;
	for(i = 0; i < size ; i++){
		if(prod[i].id == id)
			return i;
	}
	
	return 0;
}

int main(){
	
	int nouveauTaille ;
	int taille = 0;
	Produit * produits ;
	while(1){
		system("cls");
		int operation = menu();
		int close = 0;
		system("cls");
		switch(operation){
			
			case 1:
				produits = realloc(produits , (taille + 1) * sizeof(Produit) );
				ajouterProduit(produits,taille);
				taille ++;
				break;
			case 2:
				
				printf("Donner la nombre de produit a ajouter: ");
				scanf("%d",&nouveauTaille);
				
				produits = realloc(produits , (taille + nouveauTaille) * sizeof(Produit) );
				ajouterPlusieurProduits(produits, taille, nouveauTaille);
				taille += nouveauTaille;
				break;
			case 3:
				subMenuList(produits, taille);
				break;
			case 4:
				printf("Acheter un produit: \n");
				getch();
				break;
			case 5: 
				printf("Rechercher un produit: \n");
				searchById(produits, taille);
				
				
				getch();
				break;
			case 6:
				printf("Etat de stock: \n");
				getch();
				break;
			case 7:
				printf("Alimenter le stock: \n");
				getch();
				break;
			case 8:
				printf("Suprimer un produit: \n");
				getch();
				break;
			case 9: 
				printf("Statistic de vent: \n");
				getch();
				break;
			case 10:
				close = 1;
				break;
			default: 
				printf("Choix invalide: Recommancer\n");
				getch();
				break;
		}	
		
		if(close == 1){
			printf("\nAu revoir:");
			break;
		}
	}
}
