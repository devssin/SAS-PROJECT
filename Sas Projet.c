#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int produitId = 1; // Initialisation de Id du produit pour Auto-incrementations

//Declaration de structure produit
typedef struct {
	int id;
	char * nom;
	int qte;
	float prix;
	
}Produit;


//Declaraction de structure achat
typedef struct {
	char * nom;
	float prix_tcc;
	struct tm dateAchat;
} Achat;

//Ajouter un nouveau produit
void ajouterProduit(Produit * prod, int size){
	char nom1[50], nom2[50];
	printf("=================== Ajouter un nouveau produit: ==================\n\n");
	prod[size].id = produitId;
	prod[size].nom = malloc(100 * sizeof(char));
	printf("Nom du produit => ");
	scanf("%s %s", nom1,nom2);
	strcat(nom1, " ");
	strcat(nom1,nom2);
	strcpy(prod[size].nom,nom1);
	printf("Quanite du produit => ");
	scanf("%d",&prod[size].qte);
	printf("Prix du produit => ");
	scanf("%f",&prod[size].prix);
	produitId++;
	printf("Ajout termine avec succee \n");
	getch();
}

//Fonction pour lister les produits
void listProduits(Produit *prod, int size){
	int i;
	printf("=================== Liste des produits (%d) ==================\n\n", size);
	for(i =0; i < size; i++){
		printf("              Produit %d id(%d)\n ",i+1 , prod[i].id);
		printf("Nom => %s\n", prod[i].nom);
		printf("Prix => %.2f DH\n", prod[i].prix);
		printf("Prix TCC => %.2f DH\n", prod[i].prix + (prod[i].prix * 0.15));
		printf("==============================\n");
	}
	
}

//Fonction pour ajouter plusieurs produits
void ajouterPlusieurProduits(Produit * prod,int size,int newSize){
	int i;
	char nom1[50], nom2[50];

	for(i= size; i < newSize + size ; i++){
		prod[i].id = produitId;
		prod[i].nom = malloc(100 * sizeof(char));
		printf("Nom du produit => ");
		scanf("%s %s", nom1,nom2);
		strcat(nom1, " ");
		strcat(nom1,nom2);
		strcat(prod[i].nom, nom1);
		printf("Quanite du produit => ");
		scanf("%d",&prod[i].qte);
		printf("Prix du produit => ");
		scanf("%f",&prod[i].prix);
		produitId++;
		printf("=================================================\n\n");
	}
	printf("%d Produits sont ajoute dans le stock \n");
	getch();
	
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

/*Fonction sous-menu pour afficher la liste des produits 
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
			//Trier les produit selon l'ordre alphabitique
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
			break;
			
		case 2: 
			//Trier le programe selon le prix 
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
			break;
	}
	
	
}

//Fonction pour rechercher les produits par quantite
void searchByQuantity(Produit * prod, int size){
	int count = 0;
	Produit existedProducts[size];
	int i,qte;
	printf("Donner la quantite => ");
	scanf("%d",&qte);
	for(i = 0; i < size ; i++){
		if(qte == prod[i].qte){
			existedProducts[count] = prod[i];
			count++;
		}
	}
	if(count == 0){
		printf("Aucun produit existe de cette quantite \n");
		return;				
	}
	
	listProduits(existedProducts, count);
	getch();
} 

// La fonction pour rechercher un produit par son Id
void searchById(Produit * prod,int size){
	int id; 
	printf("Donner l'Id du produit => ");
	scanf("%d",&id);
	int exists = findById(prod,size,id);
	if(exists == -1){
		printf("Ce produit n'exist pas dans le stock: \n");
	}else{
		printf("Id => %d\n", prod[exists].id);
		printf("Nom => %s\n", prod[exists].nom);
		printf("Quantite => %d\n", prod[exists].qte);
		printf("Prix => %.2f DH\n", prod[exists].prix);
		printf("==============================\n");
	}
}

// Fonction pour Trouver le produit par Id
int findById(Produit * prod, int size,int id  ){
	int i = 0;
	for(i = 0; i < size ; i++){
		if(prod[i].id == id)
			return i;
	}
	return -1;
}

//Sous-Menu pour rechercher le produit selon le choix d'utilisateur
void subMenuSearch(Produit * prod, int size){
	int choix;
	do{
		printf("Donner la maniere de recherche: \n");
		printf("1- Par id: \t 2- Par quantite: \n");
		scanf("%d",&choix);
		if(choix != 1 && choix != 2){
			printf("Choix invalide \n");
		}
	}while(choix != 1 && choix != 2);
	
	switch(choix){
		case 1 :
			searchById(prod, size);
			getch();
			break;
		case 2 : 
			searchByQuantity(prod,size);
			getch();
			break;
	}	
	
}

//Fonction pour Acheter un produit par Id
void acheterProduit(Produit * prod, int size,Achat * bonne, int size2){
	if(size == 0){
		printf("Le stock est vide , Ajouter des produit \n");
		getch();
		return;
	}
	
	/*
		L'appel à time(NULL) renvoie le temps calendaire actuel (secondes depuis le 1er janvier 1970).	
	*/
	time_t today = time(NULL);
	int id,quantity; 
	printf("Donner l'Id du produit => ");
	scanf("%d",&id);
	int exists = findById(prod,size,id);
	if(exists == -1){
		printf("Ce produit n'exist pas dans le stock: \n");
	}else{
		printf("Nom => %s\n", prod[exists].nom);
		printf("Quantite => %d\n", prod[exists].qte);
		printf("Prix => %.2f DH\n", prod[exists].prix);
		printf("Prix (TCC) => %.2f DH\n", prod[exists].prix + (prod[exists].prix * 0.15));
		printf("==============================\n");
		printf("Donner la quanitite que vous voulez acheter ");
		scanf("%d",&quantity);
		if(quantity >= prod[exists].qte){
			printf("Quantite insufisante !!!! \n");
		}else{
			printf("Debut d'achat\n");
			strcpy(bonne[size2].nom,prod[exists].nom);
			bonne[size2].prix_tcc = (prod[exists].prix + (prod[exists].prix * 0.15)) * quantity;
			bonne[size2].dateAchat = *localtime(&today);
			prod[exists].qte -= quantity;
			printf("Vous avez acheter %d pieces du produit : %s %s \n", quantity, prod[exists].nom, prod[exists]);
			printf("Prix TCC => %.2f \t Date d'achat %02d-%02d-%d %02d:%02d:%02d \n", bonne[size2].prix_tcc,bonne[size2].dateAchat.tm_mday, bonne[size2].dateAchat.tm_mon + 1, bonne[size2].dateAchat.tm_year +1900, bonne[size2].dateAchat.tm_hour, bonne[size2].dateAchat.tm_min, bonne[size2].dateAchat.tm_sec);
		}
	}
}


//Fonction Pour Afficher l'etat de stock
void etatDeStock(Produit * prod, int size){
	int count = 0;
	Produit  existedProducts[size];
	if(size == 0){
		printf("Le stock est vide , Ajouter des produit \n");
		getch();
		return;
	}
	int i,qte;
	for(i = 0; i < size ; i++){
		if(prod[i].qte < 3){
			existedProducts[count] = prod[i];
			count++;
		}
	}
	if(count == 0){
		printf("Tous les produits ont la quantite superieur de 3\n");
					
	}else{
		printf("Les produits dont la quantite est inferieur de 3 \n");
		listProduits(existedProducts, count);
	}
	getch();
}


//Fonction Pour Alimenter le stock
void alimenterLeStock(Produit * prod, int size){
	if(size == 0){
		printf("Le stock est vide , Ajouter des produit \n");
		getch();
		return;
	}
	int id,quantity; 
	printf("Donner l'Id du produit => ");
	scanf("%d",&id);
	int exists = findById(prod,size,id);
	if(exists == -1){
		printf("Ce produit n'exist pas dans le stock: \n");
	}else{
		printf("Nom => %s\n", prod[exists].nom);
		printf("Quantite => %d\n", prod[exists].qte);
		printf("Prix => %.2f DH\n", prod[exists].prix);
		printf("Prix (TCC) => %.2f DH\n", prod[exists].prix + (prod[exists].prix * 0.15));
		printf("==============================\n");
		printf("Donner la quanitite que vous voulez ajouter ");
		scanf("%d",&quantity);
		prod[exists].qte += quantity;
		printf("Vous avez ajouter %d pieces au produit : %s %s \n", quantity, prod[exists].nom, prod[exists]);
		
		
	}	
}

//Fonction pour suprimer un produit par Id
void suprimerProduit(Produit * prod, int size){
	if(size == 0){
		printf("Le stock est vide , Ajouter des produit \n");
		getch();
		return;
	}
	int id,i,confirmer; 
	printf("Donner l'Id du produit => ");
	scanf("%d",&id);
	int exists = findById(prod,size,id);
	if(exists == -1){
		printf("Ce produit n'exist pas dans le stock: \n");
	}else{
		printf("Nom => %s\n", prod[exists].nom);
		printf("Quantite => %d\n", prod[exists].qte);
		printf("Prix => %.2f DH\n", prod[exists].prix);
		printf("==============================\n");
		do{
			printf("Appuillez sur 1 pour confirmer la supression : \n");
			scanf("%d",&confirmer);	
		}while(confirmer != 1);
		for(i = exists; i < size; i++){
			prod[i] = prod[i+1];
		}
		printf("Supression Termine\n");
	}
}


//Fonction Pour Calculer Le total des prix 
float totalPrix(Achat *bonne, int size){
	int i;
	float  somme = 0;
	for(i =0; i <size; i++){
		somme += bonne[i].prix_tcc;
	}
	return somme;
}

//Fonction Pour Calculer la moyenne des prix 
float moyennePrix(Achat *bonne, int size){
	return totalPrix(bonne, size) / size;
}

//Fonction Pour Afficher Le minimum des prix vendus dans la journee courante
void minPrix(Achat * bonne, int size){
	int i;
	Achat min = bonne[0];
	for(i = 0; i <size; i++){
		if(bonne[i].prix_tcc < min.prix_tcc )
			min = bonne[i];
	}
	
	printf("le Min des prix des produits vendus en  %02d-%02d-%d: \n",min.dateAchat.tm_mday, min.dateAchat.tm_mon + 1, min.dateAchat.tm_year +1900);
	printf("%s => %.2f",min.nom,min.prix_tcc );
	
}


//Fonction Pour Afficher le maximum des prix vendus dans la journee courante
void maxPrix(Achat * bonne, int size){
	int i;
	Achat max = bonne[0];
	for(i = 0; i <size; i++){
		if(bonne[i].prix_tcc > max.prix_tcc )
			max = bonne[i];
	}
	
	printf("le max des prix des produits vendus en  %02d-%02d-%d: \n",max.dateAchat.tm_mday, max.dateAchat.tm_mon + 1, max.dateAchat.tm_year +1900);
	printf("%s => %.2f",max.nom,max.prix_tcc );
	
}


//Fonction Pour Afficher les stqtistiques de vente dans la journee courante
void staticDeVente(Achat *bonne, int size){
	if(size == 0){
		printf("Le stock est vide , Ajouter des produit \n");
		getch();
		return;
	}
	int op;
	printf("1- Afficher le total des prix des produits vendus en journee courante \n");
	printf("2- Afficher la moyenne des prix des produits vendus en journée courante\n");
	printf("3- Afficher le Max des prix des produits vendus en journée courante\n");
	printf("4- Afficher le Min des prix des produits vendus en journée courante\n");
	scanf("%d",&op);
	switch(op){
		case 1: 
			printf("Total => %.2f DH TTC", totalPrix(bonne, size));
			break;
		case 2:
			printf("Moyenne => %.2f DH TTC",moyennePrix(bonne, size));
			break;
		case 3:
			maxPrix(bonne,size);
			break;
		case 4:
			minPrix(bonne,size);
			break;
	}
}



int main(){
	int nouveauTaille ;
	int taille = 0,taille2 =0;
	Produit * produits ;
	Achat * bonneAchat;
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
				getch();
				break;
			case 4:
				printf("Acheter un produit: \n");
			 	Achat * bonneAchat = realloc( bonneAchat,(taille2 + 1) * sizeof(Achat));
				acheterProduit(produits, taille,bonneAchat, taille2);
				taille2++;
				getch();
				break;
			case 5: 
				printf("Rechercher un produit: \n");
				subMenuSearch(produits, taille);
				break;
			case 6:
				printf("Etat de stock: \n");
				etatDeStock(produits,taille);
				break;
			case 7:
				printf("Alimenter le stock: \n");
				alimenterLeStock(produits, taille);
				getch();
				break;
			case 8:
				printf("Suprimer un produit: \n");
				if(taille == 0){
					printf("Le stock est vide , Ajouter des produit \n");
					getch();
				}else{
					suprimerProduit(produits, taille);
					taille--;
					getch();
				}
				break;
			case 9: 
				printf("Statistic de vente: \n");
				staticDeVente(bonneAchat, taille2);
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
