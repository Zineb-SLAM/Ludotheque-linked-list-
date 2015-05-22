#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

typedef struct Element {
	char data[N];
	struct Element* next;

}Element;

typedef struct List {
	struct Element* head;
	struct Element* tail;

}List;

void initialize (List * list);

void insert_empty_list(List *list,char *str);

void insert_begining_list(List *list, char *str);

void insert_end_list(List *list, char *str);

int insert_after_position(List *list, char *str, int p);

int delete_data(List* list, int p);

int compare(char *str1,char *str2);

int sort(List *list);

void display(List *list);

void destruct(List *list);
void somme (List *list);