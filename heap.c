#include "heap.h"


Heap initHeap() {
	Heap h;
	h = malloc(sizeof(struct heap)); 
	h->size = 0;
	h->capacity = MAX;
	return h;
}

void swap(Pair v[], int i, int j)
{
	Pair aux;
	aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

Heap siftDown(Heap h, int index) {
	int minIndex = index;
	int left = index * 2 + 1;
	int right = index * 2 + 2;

	if (left < h->size)
		if(h->vector[left].cost <= h->vector[minIndex].cost)
			minIndex = left;

	if (right < h->size)
		if (h->vector[right].cost <= h->vector[minIndex].cost)
			minIndex = right;

	if (index != minIndex)
	{
		swap(h->vector, index, minIndex);
		h = siftDown(h, minIndex);
	}
	return h;
}

Heap siftUp(Heap h, int index) {
	int parent;
	parent = (index - 1)/2;
	while (h->vector[index].cost <= h->vector[parent].cost)
	{
		swap(h->vector, index, parent);
		index = parent;
		if (index == 0)
			break;
		parent = (index - 1) / 2;
	}
	return h;
}

Heap insertHeap(Heap h, Pair element) {
	int index;

	if (h->size == 0)
	{
		h->vector[h->size] = element;
		h->size++;
		return h;
	}
	else
	{
		h->vector[h->size] = element;
		h->size++;
		index = h->size - 1;
		siftUp(h, index);

	}
	return h;
}

Pair extractMin(Heap h) {
	int index;
	Pair Min;
	Min = h->vector[0];
	h->vector[0] = h->vector[h->size - 1];
	h->size = h->size - 1;

	index = 0;
	h = siftDown(h, index);
	return Min;
}

int isEmptyHeap(Heap h) {
 	if (h == NULL || h->size == 0)
 		return 1;
 	return 0;
}

Heap freeHeap(Heap h) {
	free(h);
	return h;
}
