#include "tema3.h"
// #include "binarytree.c"
Graph initGraph(int V) {
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	
	// numarul de noduri din graf
	g->V = V;
	
	// numele fiecarui actor din graf
	g->name = (char**) malloc(V * sizeof(char*));
	for (i = 0; i < V; i++)
		g->name[i] = NULL;
	
	// lista vecinilor
	g->adjLists = (List*) malloc(V * sizeof(List));
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	
	// setez fiecare vecin ca fiind nevizitat
	g->visited = calloc(V, sizeof(int));
	
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost, char *name1, char *name2) 
{
	Pair p;

	p.name = strdup(name2);
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);
	
	free(p.name);
	p.name = strdup(name1);
	p.v = u;
	p.cost = cost;
	g->adjLists[v] = addLast(g->adjLists[v], p);
	free(p.name);
	return g;
}

Graph bfs(Graph g, int start) {
	int i, j;
	Queue q = NULL;
	List tmp;

	g->visited[start] = 1;
	q = enqueue(q, start);
	while(!isEmptyQueue(q)) 
	{
		i = first(q);
		printf("%d\n", i);
		q = dequeue(q);
		tmp = g->adjLists[i];
		while (tmp != NULL) 
		{
			j = tmp->data.v;
			if (g->visited[j] == 0) 
			{
				q = enqueue(q, j);
				g->visited[j] = 1;
			}
			tmp = tmp->next;
		}
	}
	freeQueue(q);
	return g;
}

Graph dfs(Graph g, int start) {
	int i;
	List tmp = NULL;
	g->visited[start] = 1;
	printf("%d\n", start);
	tmp = g->adjLists[start];
	while (tmp != NULL) 
	{
		i = tmp->data.v;
		if (g->visited[i] == 0)
			g = dfs(g, i);
		tmp = tmp->next;
	}
	return g;
}

int isEdge(Graph g, int u, int v)
{
	List tmp = NULL;
	tmp = g->adjLists[u];
	while (tmp != NULL)
	{	
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

Graph dfs2(Graph g, int start) {
	int i;
	List tmp = NULL;
	g->visited[start] = 1;
	tmp = g->adjLists[start];
	while (tmp != NULL) 
	{
		i = tmp->data.v;
		if (g->visited[i] == 0)
			g = dfs2(g, i);
		tmp = tmp->next;
	}
	return g;
}

int exista_nod_nevizitat(Graph g)
{
	int i;
	for (i = 0; i < g->V; i++)
		if (g->visited[i] == 0)
			// nodul nevizitat
			return i;
	// daca toate nodurile au fost vizitate
	return -1;
}

int componenteConexe(Graph g)
{
	int comp = 0;
	int i;

	for (i = 0; i < g->V; i++)
		g->visited[i] = 0;
	for (i = 0; i < g->V; i++)
	{
		if (!g->visited[i])
		{
			dfs2(g, i);
			comp++;
		}
	}
	return comp;

}

int gradDeInrudire(Graph g, int start, int end)
{
	int v, i, j;
	Queue q = NULL;
	List tmp;
	int *dist = (int*) calloc(g->V, sizeof(int));
	int *p = (int*) calloc(g->V, sizeof(int));

	// tratez cazul cand nu e latura intre start si end
 	for (i = 0; i < g->V; i++)
		g->visited[i] = 0;
	dfs2(g, start);
	if (!g->visited[end])
		return 0;

 	for (v = 0; v < g->V; v++)
		g->visited[v] = 0;
	q = enqueue(q, start);
	g->visited[start] = 1;
	for (v = 0; v < g->V; v++)
	{
		dist[v] = -1;
		p[v] = -1;
	}
	dist[start] = 0;

	while(!isEmptyQueue(q)) 
	{
		i = first(q);
		q = dequeue(q);
		tmp = g->adjLists[i];
		while (tmp != NULL) 
		{
			j = tmp->data.v;
			if (g->visited[j] == 0) 
			{
				g->visited[j] = 1;
				dist[j] = dist[i] + 1;
				p[j] = i;
				q = enqueue(q, j);
			}
			tmp = tmp->next;
		}
	}
	int u = end;
	int grad = 1;
	while (p[u] != start)
	{	grad++;
		u = p[u];
	}
	free(dist);
	free(p);
	freeQueue(q);
	return grad;
}

int Minim(int a, int b)
{
	if (a < b)
		return a;
	else return b;
}

void dfsCV(Graph g, int v, int timp, int *idx, int *low, int *parent, int *ap)
{
	int children, u;
	List tmp = NULL;

	children = 0;
	g->visited[v] = 1;
	idx[v] = low[v] = ++timp;
	tmp = g->adjLists[v];
	while (tmp != NULL)
	{
		u = tmp->data.v;
		if (!g->visited[u])
		{
			children++;
			parent[u] = v;
			dfsCV(g, u, timp, idx, low, parent, ap);
			
			low[v] = Minim(low[v], low[u]);

			if (parent[v] == -1 && children > 1)
				ap[v] = 1;
			if (parent[v] != -1 && low[u] >= idx[v])
				ap[v] = 1;

		}
		else
			if (u != parent[v])
				low[v] = Minim(low[v], idx[u]);
		tmp = tmp->next;
	}
}

void puncteArticulatie(Graph g, char *fisier)
{
	int v, u;
	int timp = 0;
	// retine timpii de descoperire pentru fiecare nod din graf
	int *idx = (int*) malloc(g->V * sizeof(int));
	int *low = (int*) malloc(g->V * sizeof(int)); 
	int *parent = (int*) malloc(g->V * sizeof(int));
	int *ap = (int*) malloc(g->V * sizeof(int));
	for (v = 0; v < g->V; v++)
	{
		parent[v] = -1;
		g->visited[v] = 0;
		ap[v] = 0;
		idx[v] = -1;
		low[v] = INF;
	}

	for (v = 0; v < g->V; v++)
		if (!g->visited[v])
			dfsCV(g, v, timp, idx, low, parent, ap);
	int nrPuncteArt = 0, vert = 0;
	char **cuteVertex;
	FILE *fis;
	for (v = 0; v < g->V; v++)
		if(ap[v] == 1)
			nrPuncteArt++;
	cuteVertex = (char**) malloc(nrPuncteArt * sizeof(char*));
	fis = fopen(fisier, "w");
	fprintf(fis, "%d\n", nrPuncteArt);
	for (v = 0; v < g->V; v++)
		if (ap[v] == 1)
		{
			cuteVertex[vert] = strdup(g->name[v]);
			vert++;
		}
	for (u = 0; u < nrPuncteArt - 1; u++)
		for (v = u + 1; v < nrPuncteArt; v++)
			if (strcmp(cuteVertex[u], cuteVertex[v]) > 0)
			{
				char *aux;
				aux = strdup(cuteVertex[u]);
				free(cuteVertex[u]);
				cuteVertex[u] = strdup(cuteVertex[v]);
				free(cuteVertex[v]);
				cuteVertex[v] = strdup(aux);
				free(aux);
			}
	for (u = 0; u < nrPuncteArt; u++)
		if (u != nrPuncteArt)
			fprintf(fis, "%s\n", cuteVertex[u]);
		else
			fprintf(fis, "%s", cuteVertex[u]);

	free(idx);
	free(low);
	free(ap);
	free(parent);
	for (u = 0; u < nrPuncteArt; u++)
		free(cuteVertex[u]);
	free(cuteVertex);

	fclose(fis); 
}

// void GenerareClici(Graph g, int i, Tree CS, Tree NOT, Tree CA)
// {
// 	int c, x;
// 	if (CA != NULL)
// 	{
// 		c = CA->value;
// 		CA = delete(CA, c);
// 		CS = insert(CS, c);

// 		CA = delete(CA, x);
// 		NOT = delete(NOT, x);
// 		GenerareClici(g, i + 1, CS, NOT, CA);
// 		CS = delete(CS, c);
// 		NOT = insert(NOT, c);
// 	}

// 	if (CA == NULL && NOT == NULL)
// 	{

// 	}
// }

int main(int argc, char *argv[])
{
	int i, j, k, l, nr_actors;
	FILE *f;
	int films, filmActors, ok, actors;
	int source = -1, dest = -1;
	char name[BUFMAX], filmName[BUFMAX]; 
	//Tree CS, NOT, AC;
	Graph g;
	g = initGraph(6000);

	f = fopen(argv[2], "r");
	fscanf(f, "%d", &films);
	fgetc(f);
	nr_actors = 0;
	for (i = 0; i < films; i++)
	{
		fgets(filmName, BUFMAX, f);
		fscanf(f, "%d", &filmActors);
		fgetc(f);

		int *key;
	 	key = (int*) calloc((filmActors + 1), sizeof(int));
	 	actors = 0;
		for (j = 0; j < filmActors; j++)
		{
			fgets(name, BUFMAX, f);
			name[strlen(name) - 1] = '\0';

			ok = 0; // pp ca actorul cu numele name nu a jucat in niciun film pana acum
			for (k = 0; k < nr_actors; k++)
				if (strcmp(g->name[k], name) == 0)
				{
					ok = 1; // actorul name a jucat deja intr-un film
					break;
				}
			if (ok == 0)
			{
				key[actors] = nr_actors;
				g->name[nr_actors] = strdup(name);
				nr_actors++;
				actors++;

			}
			else
			{
				key[actors] = k;
				actors++;
			}

			for (l = 0; l < actors - 1; l++)
					if (!isEdge(g, key[actors - 1], key[l]))
						g = insertEdge(g, key[actors - 1], key[l], 1, g->name[key[actors - 1]], g->name[key[l]]);
		}
		free(key);
	}
	g->V = nr_actors;
	while (fgets(name, BUFMAX, f) != NULL)
	{
		name[strlen(name) - 1] = '\0';
		for (k = 0; k < g->V; k++)
			if (strcmp(g->name[k], name) == 0)
		 	{
		 		if (source == -1)
		 			source = k;
		 		else
		 			dest = k;
		 	}
	}
	fclose(f);
	// g->adjLists = realloc(g->adjLists, (g->V + 1) * sizeof(List));
	// g->name = realloc(g->name, (g->V + 1) * sizeof(char*));
	// g->visited = realloc(g->visited, (g->V + 1) * sizeof(int));
	for (i = 0; i < g->V; i++)
		g->visited[i] = 0;

	f = fopen(argv[3], "w");
	
	// task1
	if (strcmp(argv[1], "-c1") == 0)
		fprintf(f, "%d\n", componenteConexe(g));
	
	// task2
	if (strcmp(argv[1], "-c2") == 0)
		fprintf(f, "%d\n", gradDeInrudire(g, source, dest));
	
	fclose(f);

	//task3
	if (strcmp(argv[1], "-c3") == 0)
		puncteArticulatie(g, argv[3]);

	//bonus
	// if (strcmp(argv[1], "-b") == 0)
	// 	GenerareClici(g, 0, CS, NOT, AC);


	for (i = 0; i < g->V; i++)
		freeList(g->adjLists[i]);
	free(g->adjLists);
	for (i = 0; i < g->V; i++)
		free(g->name[i]);
	free(g->name);
	free(g->visited);
	free(g);
	return 0;
}
