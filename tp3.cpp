#include "tp3.h"

void initialize (List * list){
	
	// La liste étant vide, le head et le tail pointent vers NULL
	list ->head= NULL;
	list ->tail= NULL;
}


void insert_empty_list(List *list,char *str)
{	
	int i,j;
	Element *e;
	Element *tmp;    //mémoriser la position précédente d'un élément qui est en cours d'étre créé afin de parcourir la liste en utilisant tmp=tmp->next

	if(list->head==NULL)
	{
		// calculer le nb d'élément à créer d'une donnée(str)
		int NB=strlen(str)/N;
		if (strlen(str)%N !=0) NB++; // au cas ou il y a un reste

		//créer le 1er element 
		e=(Element*)malloc(sizeof(Element));
		for(i=0; i<N; i++)
				e->data[i]=str[i];
		list->head=e;          // head pointe sur ce 1er element
		tmp=e;

		//consituer les reste éléments
		for(i=1;i<NB;i++)
		{
			e=(Element*)malloc(sizeof(Element));
			for(j=i*N; j< (i*N+N) && j<strlen(str); j++)
			{
				e->data[j%N]=str[j];
			}
			tmp->next=e;
			tmp=tmp->next;
		}

		// On crée un élément vide pour marque la fin de l'élément
		e=(Element*)malloc(sizeof(Element));
		e->data[0]='\0';
		e->next=NULL;
		tmp->next=e; 
		// tail pointe sur le dernier élément vide
		list->tail=e;
	}
	else
		printf("liste n'est pas vide: insert-empty-list");
}

/* version -0      sans utiliser insert_empty_list
void insert_begining_list(List *list, char *str)
{
	int i,j;
	Element *e;
	// tmp nous permet de savoir à quelle position on va ajoter un élément devant
	Element *tmp=list->head;         


	// calculer le nb d'élément à créer d'une donnée(str)
	int NB=strlen(str)/N;
	if (strlen(str)%N !=0) NB++;

	//si la liste contient initialisement des éléments
	if(list->head!=NULL)
	{
		// créer un élément vide
		e=(Element*)malloc(sizeof(Element));
		*e->data='\0';
		e->next=tmp;;
		tmp=e;

		//créer les éléments d'une donnée(str)
		for(i=0;i<NB;i++)
		{
			e=(Element*)malloc(sizeof(Element));
			for(j=(NB-1-i)*N; j< (NB-i)*N && j<strlen(str); ++j)
			{
				e->data[j%N]=str[j];
			}
			e->next=tmp;;
			tmp=e;
		}
		list->head=e;
	}
	else printf("erreur: liste initialisement vide");
}

*/

// version 1 en utilisant insert_empty_list
void insert_begining_list(List *list, char *str)
{
	Element *e;      
	List *dataList;

	//si la liste contient initialisement des éléments
	if(list->head!=NULL)
	{
		dataList=(List*)malloc (sizeof( List));	
		initialize(dataList);
		insert_empty_list(dataList,str);
		dataList->tail->next=list->head;
		list->head=dataList->head;
		free(dataList);                        //libération de mémoire
	}
	else printf("Erreur: liste initialisement vide");
}

 /*  version 0--  sans utiliser insert_empty_list 
void insert_end_list(List *list, char *str)
{
	int i,j;
	Element *e;
	Element *tmp=list->tail;

	// calculer le nb d'élément à créer d'une donnée(str)
	int NB=strlen(str)/N;
	if (strlen(str)%N !=0) NB++;

	if(list->head!=NULL)
	{
		for(i=0;i<NB;i++)
		{
			e=(Element*)malloc(sizeof(Element));
			for(j=i*N; j< (i*N+N) && j<strlen(str); j++)
			{
				e->data[j%N]=str[j];
			}
			tmp->next=e;
			tmp=tmp->next;
		}
		
		// créer un élément vide
		e=(Element*)malloc(sizeof(Element));
		e->data[0]='\0';
		tmp->next=e;
		e->next=NULL;

		list->tail=e;
	}
	else printf("Erreur: liste initialisement vide");
}
*/

 //  version 1--  en utilisant insert_empty_list
void insert_end_list(List *list, char *str)
{
	Element *e;
	List *dataList;

	if(list->head!=NULL)
	{
		dataList=(List*)malloc(sizeof(List));
		initialize(dataList);
		insert_empty_list(dataList,str);
		list->tail->next=dataList->head;
		list->tail=dataList->tail;
		free(dataList);
	}
	else printf("Erreur: liste initialisement vide");
}


int insert_after_position(List *list, char *str, int p)
{
	int cpt=0;     //compter le nb d'entiers
	Element *pos= list->head;
	List *dataList;

	// la liste vide ou la position négative, retourner l'erreur
	if(list->head==NULL || p<0)
	{ printf("erreur\n");
		return -1;
	}

	// insérer au début de la liste 
	if(p==0) 
	{
		insert_begining_list(list,str);
		return 0;
	}

	while(pos!= NULL )
	{
		// on compte le nb éléments avant la position pos
		if(pos->data[0]=='\0')
			cpt++;
		// on est à la fin de pème nombre
		if(cpt==p)
		{
			// si on veut ajouter à la fin de la liste (après dernier élément)
			if(pos->next==NULL)
			{
				insert_end_list(list,str);
				return 0;
			}
			else
			{
				dataList=(List*)malloc (sizeof( List));     //faut malloc??????
				initialize(dataList);
				insert_empty_list(dataList, str);
				dataList->tail->next=pos->next;
				pos->next=dataList->head;
				free(dataList);
			
				return 0;
			}
		 }
		 pos=pos->next;		
	}
	if(cpt< p)
	{	printf("Erreur: la position insere incorrect\n");
		return -1;
	}
}

int delete_data(List* list, int p)
{
	int cpt=0;     //compter le nb de nombre passé
	Element *pos= list->head;
	Element *posPrec;
	Element *tmp, *dataBegin;


	// la liste vide ou la position négative, retourner l'erreur
	if(list->head==NULL || p<0)
		return -1;
	 //condition de saut: soit on arrive à la fin de list, soit on trouve la bonne position
	while(pos->next!= NULL && cpt!=p)
	{
		pos=pos->next;	
		// on compte le nb éléments avant la position pos
		if(pos->data[0]=='\0')
		{	cpt++;
			// on est à la fin de (p-1)ème nombre
			if(cpt==p-1)
			{	posPrec=pos;
				dataBegin=pos->next;
			}		
		}
	}
	if(cpt==p)
	{	
		if(p==1)              // dans le cas ou l'on souhaite supprimer la première donnée
		{
			dataBegin=list->head;
			list->head=pos->next;
		}
		else
		{
			if(pos->next==NULL)   // dans le cas ou l'on souhaite supprimer la dernière donnée, il faut bien positionner tail
				list->tail=posPrec;		
			posPrec->next=pos->next;		
		}
		//supprimer pème data
		while(dataBegin->data[0]!='\0')
		{
				tmp=dataBegin;
			    dataBegin=dataBegin->next;
				free(tmp);								
		}
		free(dataBegin);   //supprimer le dernier élément vide
	}
	if(cpt<p)
	{	printf("Erreur: La posision n'existe pas dans la liste!\n");
		return -1;
	}
}


int compare(char *str1,char *str2)
{
	if(atoi(str1)>atoi(str2))
		return 1;
	else
		return 2;
}

int sort(List *list)
{
	if(list->head==NULL)
		return -1;
	else{		
		List * list2= (List*)malloc (sizeof( List));	
		initialize(list2);
		char mbp [100] ="" ;	
		Element *e=list->head;	
		char * tmp=(char *) malloc (20 * sizeof(char)); 
		// Tant qu'il reste des éléments dans la liste
		while (list->head != NULL){
			int pos=0;
			int minPos=0;
			char * tmp=(char *) malloc (20 * sizeof(char)); 
			char mbp [100] ="" ;
			Element *e=list->head;	
			// on crée le premier élément
			while (e->data[0]!='\0'){
				int i=atoi(e->data);				
				sprintf(tmp,"%d",i);		
				strcat(mbp, tmp);			
				e=e->next;
			}	
			e=e->next;
			char  minStr [100] ;	
			pos=pos+1;
			// on consdière le premier élément comme le min
			minPos=pos;
			strcpy(minStr,mbp);	
				// on parcourt la liste
				while (e !=NULL){
					char mbp [100] ="" ;	
						// crée chaque élément
					while (e->data[0]!='\0'){
						int i=atoi(e->data);						
						sprintf(tmp,"%d",i);		
						strcat(mbp, tmp);						
						e=e->next;
					}
					pos=pos+1;
						// si la valeur de l'élément est plus petite que le min actuel, alors il devient min
					if ( compare(mbp,minStr)==2){
							strcpy(minStr,mbp);
							minPos=pos;
					}				
					e=e->next;				
				}	
					// on ajoute dans la seconde liste, l'élément à la suite, on est donc sur que les éléments précédents sont plus petits
				if (list2->head != NULL)
					insert_end_list(list2,minStr);				
				else
					insert_empty_list(list2,minStr);
					// on supprime l'élément de la première liste
				delete_data(list,minPos);			
		}		
			// A la fin, la liste1 est vide alors que la liste2 est pleine et triée
			//, on fait donc pointer le head de liste1 sur le head de liste2 et le tail de liste1 sur le tail de liste2
		list->head=list2->head;
		list->tail=list2->tail;
		free (tmp);
		free(list2);
		}
}
void display(List *list)
{
	Element *pos=list->head;   //pour parcourir la liste

	if(pos==NULL)
		printf("EMPTY LIST\n");
	else
		while(pos!=list->tail)        // si on n'est pas sur la fin de liste
		{	
			// séparer les entiers en regardant si l'élément est vide
			if(pos->data[0]=='\0') 
				printf(" ");
			else 
				printf("%d",atoi(pos->data));
			pos=pos->next;
		}
}
void somme (List *list){
	int somme =0;	
	char som [100];
	Element *e=list->head;	
	// on parcourt la liste
	while (e!=NULL){
		char mbp [100] ="" ;	
		char * tmp=(char *) malloc (20 * sizeof(char)); 
		// on parcourt l'élément
		while (e->data[0]!='\0'){
			int i=atoi(e->data);				
			sprintf(tmp,"%d",i);		
			strcat(mbp, tmp);			
			e=e->next;
		}		
			// on ajoute la valeur de  l'élément actuel
		somme=somme + atoi(mbp);		
		e=e->next;		
	}
	sprintf(som,"%d",somme);
	insert_end_list(list,som);
}

void destruct(List *list)
{
	Element *tmp;
	while(list->head!=NULL)
	{
		tmp=list->head;
		list->head=list->head->next;
		free(tmp);
	}
	free(list);
}