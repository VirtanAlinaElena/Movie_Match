#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "list.h"
#include "queue.h"
#include "stack.h"
#include "heap.h" // list.h e deja inclusa in heap.h 
// deci nu e nevoie sa o mai includ odata ce am inclus heap.h

#define SIZE 200
#define INF 999999
#define BUFMAX 100

typedef struct graph {
	int V;
	char **name;
	List *adjLists;
	int *visited;
	int *start, *end;
}*Graph;

Graph initGraph(int V);
Graph insertEdge(Graph g, int u, int v, int cost, char *name1, char *name2);
Graph bfs(Graph g, int start);
Graph dfs(Graph g, int start);
Graph dfs2(Graph g, int start);
int isEdge(Graph g, int u, int v);
int exista_nod_nevizitat(Graph g);
int componenteConexe(Graph g);
int gradInrudire(Graph g, int source, int dest);
int Minim(int a, int b);
void dfsCV(Graph g, int v, int timp, int *idx, int *low, int *parent, int *ap);
void puncteArticulatie(Graph g, char *fisier);

#endif
