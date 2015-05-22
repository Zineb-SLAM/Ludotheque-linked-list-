#include "tp3.h"



int main()	
{
	int choix=0;
	List * list= (List*)malloc (sizeof( List));
	int i;
	initialize(list);
	while (choix != 8){
		printf(" 1- ajouter un nombre en début de liste \n 2- ajouter un nombre en fin de liste \n 3- ajouter un nombre à une certaine position dans la liste \n 4- supprimer un nombre d’une certaine position de la liste \n 5- trier la liste par ordre croissant \n 6- afficher la liste \n 7- détruire la liste toute entière \n 8- quitter \n 9- Somme \n Votre choix : ");
		scanf("%d",&choix);
	switch(choix){
		char nombre[30];
	case 8:
			printf("Au revoir\n");
			break;
	case 1:
			printf("Entrez nombre :  ");
			fflush(stdin);
			scanf("%s",nombre);
			if (list->head==NULL)
				insert_empty_list(list,nombre);
			else
				insert_begining_list(list,nombre);		
			break;
	case 2:
			printf("Entrez nombre :  ");
			fflush(stdin);
			scanf("%s",nombre);
			insert_end_list(list,nombre);
			break;
	case 3:			
			printf("Entrez position:  ");
			scanf("%d",&i);
			printf("\n Entrez nombre :  ");
			fflush(stdin);
			scanf("%s",nombre);
			insert_after_position(list,nombre,i);
			break;
		
	case 4:		
			
			printf("Entrez position:  ");
			scanf("%d",&i);			
			fflush(stdin);		
			delete_data(list,i);
			break;
	
	case 5:
			sort(list);
			break;
	case 6:
			break;
	case 7:
			destruct(list);
			// Pour repartir d'une liste vide une fois la liste détruite
			list= (List*)malloc (sizeof( List));
			initialize(list);
			break;
	case 9:
			somme(list);
			break;
	default:
			printf("Choix non valide");
			break;	
	}
		printf("\n La liste vaut : ");
		display(list);	
		printf("\n");	
	}	
	return 0;
}