#ifndef MINHEAP_H
#define MINHEAP_H

#include "huffman.h"

typedef struct minHeap {
    int size;                   // Numero di elementi attualmente nella heap
    int capacity;               // Capacità massima (es. 256)
    node **array;               // Array di puntatori a node (nota il doppio asterisco **)
} minHeap;

minHeap* createMinHeap(int capacity);           // Crea ed inizializza la struttura MinHeap, un albero in cui la radice è sempre minore dei suoi figli
void swapNodes(node **a, node **b);             // Funzione di scambio dei nodi
void minHeapify(minHeap *minHeap, int idx);
node* extractMin(minHeap *minHeap);
void insertMinHeap(minHeap *minHeap, node *minHeapNode);        // Funzione che gestisce l'inserimento e il corretto bilanciamento dell'albero

#endif