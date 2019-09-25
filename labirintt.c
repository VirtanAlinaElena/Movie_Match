#include "tema3.h"

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
	g->visited = (int*)calloc(V, sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost, char *name1, char *name2) 
{
	Pair p;

	p.name = strdup(name2);
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);
	
	p.name = strdup(name1);
	p.v = u;
	p.cost = cost;
	g->adjLists[v] = addLast(g->adjLists[v], p);
	return g;
}

int isEdge(Graph g, int u, int v)
{
	List tmp;
	tmp = g->adjLists[u];
	while (tmp != NULL)
	{	
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int main()
{
	int i, j, u, v, cost, rooms, portals, start, weight, late, ok;
	int *p, nrTimes, time, escapeChance = 0;
	int *escTime, escapeTime;
	char exit, *exitOptions;
	int index;
	List *timeList, drum, tmp, temp;
	Pair element;
	FILE* f;
	Graph g;
	Heap h = initHeap();

	f = fopen("labirint.in", "r");
	fscanf(f, "%d", &rooms);
	fscanf(f, "%d", &portals);
	fscanf(f, "%d", &start);
	start--;
	fgetc(f);
	timeList = (List*) malloc((rooms + 1) * sizeof(List));
	g = initGraph(rooms);
	for (i = 0; i < portals; i++)
	{
		fscanf(f, "%d", &u);
		fscanf(f, "%d", &v);
		fscanf(f, "%d", &cost);
		if (isEdge(g, u - 1, v - 1) == 1)
		{
			tmp = g->adjLists[u-1];
			while(tmp->data.v != v-1)
				tmp = tmp->next;
			if (tmp->data.cost > cost)
				tmp->data.cost = cost;

			tmp = g->adjLists[v - 1];
			while (tmp->data.v != u - 1)
				tmp = tmp->next;
			if (tmp->data.cost > cost)
				tmp->data.cost = cost;
		}
		else
			g = insertEdge(g, u - 1, v - 1, cost, " ", " ");
		fgetc(f);
	}
	//timeMatrix = (int**) malloc((rooms + 1) * sizeof(int*));

	// exista sau nu o iesire in camera respectiva 
	exitOptions = (char*) malloc((rooms + 1) * sizeof(char));
	for (i = 0; i < rooms; i++)
	{
		fscanf(f, "%c", &exit);
		fgetc(f);
		exitOptions[i] = exit;
		if (exit == 'Y')
			escapeChance = 1;
		fscanf(f, "%d", &nrTimes);
	
		for (j = 1; j <= nrTimes; j++)
		{
			fscanf(f, "%d", &time);
			element.cost = time;
			timeList[i] = addLast(timeList[i], element);
		}
		
		fgetc(f);
	}

	// dijkstra
	escTime = (int*) calloc(g->V + 1, sizeof(int));
	p = (int*) calloc(g->V + 1, sizeof(int));

	late = 0;

	// calculez intarzierea cauzata de prezenta unui paznic in camera
	tmp = timeList[start];
	ok = 0;
	while (tmp != NULL && !late)
	{
		if (tmp->data.cost == escTime[start])
		{
			late++;
			ok = 1;
		}

		if (ok == 1)
		{	
			temp = tmp;
			while (temp != NULL && temp->next != NULL)		
			{
				if (temp->next->data.cost - temp->data.cost == 1)
					late++;
				else 
					break;
				temp = temp->next;
			}
		}

		tmp = tmp->next;
	}

	for (u = 0; u < g->V; u++)
	{
		escTime[u] = INF;
		p[u] = -1;
	}
	escTime[start] = 0;
	g->visited[start] = 1;
	element.cost = escTime[start];
	element.v = start;
	h = insertHeap(h, element);
	// temp = g->adjLists[start];
	// while (temp != NULL)
	// {
	// 	u = temp->data.v;
	// 	escTime[u] = temp->data.cost + late;
	// 	element.v = u;
	// 	element.cost = escTime[u];
	// 	h = insertHeap(h, element);
	// 	p[u] = start;
	// 	temp = temp->next;
	// }
	
	while (!isEmptyHeap(h))
	{
		element = extractMin(h);
		u = element.v;
		g->visited[u] = 1;
		late = 0;
	
		tmp = timeList[u];
		ok = 0;
		while (tmp != NULL && !late)
		{
			if (tmp->data.cost == escTime[u])
			{
				late++;
				ok = 1;
			}

			if (ok == 1)
			{	
				temp = tmp;
				while (temp != NULL && temp->next != NULL)		
				{		
					if (temp->next->data.cost - temp->data.cost == 1)
						late++;
					else 
						break;
					temp = temp->next;
				}
			}

			tmp = tmp->next;
		}


		tmp = g->adjLists[u];
		while (tmp != NULL)
		{
			v = tmp->data.v;
			weight = tmp->data.cost;
			if (!g->visited[v] && escTime[v] > escTime[u] + weight + late)
			{
				escTime[v] = escTime[u] + weight + late;
				p[v] = u;
				element.v = v;
				element.cost = escTime[v];
				h = insertHeap(h, element);
			}
			tmp = tmp->next;
		}
	}

	fclose(f);
	if (escapeChance == 0) 
		printf("-1");
	else
	{
		escapeTime = INF;
		for (i = 0; i < g->V; i++)
			if (exitOptions[i] == 'Y')
				if (escTime[i] <= escapeTime)
				{
					escapeTime = escTime[i];
					index = i;
				}
		element.v = index;
		drum = initList(element);
		while (p[index] != -1)
		{
			index = p[index];
			element.v = index;
			drum = addFirst(drum, element);
		}
		// element.v = start;
		// drum = addFirst(drum, element);
		f = fopen("labirint.out", "w");
		fprintf(f, "%d\n", escapeTime);
		tmp = drum;
		while (drum != NULL)
		{
			if (drum->next == NULL)
				fprintf(f, "%d", drum->data.v + 1);
			else
				fprintf(f, "%d ", drum->data.v + 1);
			drum = drum->next;
		}
		// f = fopen(argv[2], "w");
		// fprintf(f, "%d\n", escapeTime);
		// while (p[index] != -1)
		// {
		// 	fprintf(f, "%d ", index + 1);
		// 	index = p[index];
		// }
		// fprintf(f, "%d\n", start + 1);

	}
	fclose(f);

	free(exitOptions);
	free(escTime);
	free(p);
	freeList(tmp);
	freeHeap(h);
	for (i = 0; i < g->V; i++)
		freeList(g->adjLists[i]);
	for (i = 0; i < g->V; i++)
		free(g->name[i]);
	free(g->name);
	free(g->visited);
	free(g);
	return 0;
}
