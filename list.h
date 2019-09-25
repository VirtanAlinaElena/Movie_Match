#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>	

typedef struct pair {
	// costul nodului respectiv
	int cost;

	// id-ul nodului respectiv
	int v;

	// numele actorului pe care il retine nodul respectiv
	char* name;
} Pair;

typedef struct list {
	Pair data;
	struct list *prev, *next;
}*List;

List initList(Pair data);
List addFirst(List list, Pair data);
List addLast(List list, Pair data);
List deleteItem(List list, Pair data);
List freeList(List list);

#endif