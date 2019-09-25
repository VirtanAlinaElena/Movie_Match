#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define MAX 	10000
#define SIZE 	200

//typedef int Type;
//typedef Pair Type;

typedef struct heap {
	Pair vector[MAX];
	int size;
	int capacity;
	//int (*compare_func)(const void*, const void*);
} *Heap;

// functie de interschimbare a doua elemente
void swap(Pair v[], int i, int j);

// Inițializează cu 0 dimensiunea heap-ului și atribuie valoarea pentru
// funcția generică de comparare.
// De asemenea, alocă și memorie pentru structura heap.
Heap initHeap();

//Funcții auxiliare care realizează "cernerea" pentru a menține proprie-
//tățile structurii de date.
Heap siftDown(Heap h, int index);
Heap siftUp(Heap h, int index);

//Introduce un element în heap și realizează "cernerea" pentru asigura-
//rea respectării proprietăților de maxHeap.
Heap insertHeap(Heap h, Pair element);

//	Extrage elementul maxim din heap (rădăcina heap-ului).
Pair extractMin(Heap h);

// verifica daca heap-ul mai are sau nu elemente 
int isEmptyHeap(Heap h);

//	Funcție care dezaloca memoria alocată pentru structura de date.
Heap freeHeap(Heap h);