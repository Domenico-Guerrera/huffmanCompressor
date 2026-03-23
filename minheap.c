#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "minheap.h"

minHeap* createMinHeap(int capacity){
    minHeap *map = malloc(sizeof(minHeap));
    if (map != NULL){
        map->size = 0;
        map->capacity = capacity;
        map->array = malloc(capacity * sizeof(node *));
        if (map->array != NULL)
            return map;
        else
            return NULL;
    }
    else
        return NULL;
}

void swapNodes(node **a, node **b){
    node *tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertMinHeap(minHeap *minHeap, node *minHeapNode){
    if (minHeap->size < minHeap->capacity){
        minHeap->array[minHeap->size++] = minHeapNode;
        int i = minHeap->size - 1;
        while (i > 0 && minHeap->array[i]->frequency < minHeap->array[(i - 1) / 2]->frequency){
            swapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

node *extractMin(minHeap *minHeap){
    node *tmp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[(minHeap->size) - 1];
    minHeap->size = minHeap->size - 1;
    minHeapify(minHeap, 0);
    return tmp;
}

void minHeapify(minHeap *minHeap, int idx){
    int minIdx = idx;
    if(2*idx + 1 < minHeap->size && minHeap->array[2*idx + 1]->frequency < minHeap->array[minIdx]->frequency){
        minIdx = 2*idx + 1;
    }
    if(2*idx + 2 < minHeap->size && minHeap->array[2*idx + 2]->frequency < minHeap->array[minIdx]->frequency){
        minIdx = 2*idx + 2;
    }
    if(minIdx != idx){
        swapNodes(&minHeap->array[minIdx], &minHeap->array[idx]);
        minHeapify(minHeap, minIdx);
    }
}