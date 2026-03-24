#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "minheap.h"

void countChar(FILE* input, int frequencies[MAX_TREE_HEIGHT]){
    int ch;
    while((ch = fgetc(input)) != EOF)
        frequencies[ch]++;

}    

node* createNode(const unsigned char ch, const int frequency){
    node* newNode = malloc(sizeof(node));
    if (newNode != NULL){
        newNode->character = ch;
        newNode->frequency = frequency;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    return NULL;
}

node* buildHuffmanTree(int frequencies[MAX_TREE_HEIGHT]){
    minHeap* minHeap = createMinHeap(MAX_TREE_HEIGHT);
    for(int i = 0; i<MAX_TREE_HEIGHT; i++){
        if(frequencies[i] > 0){
            node* newNode = createNode(i, frequencies[i]);
            insertMinHeap(minHeap, newNode);
        }
    }
    while(minHeap->size > 1){
        node* minL = extractMin(minHeap);
        node* minR = extractMin(minHeap);
        node* newFather = createNode('$', minL->frequency + minR->frequency);
        newFather->left = minL;
        newFather->right= minR;
        insertMinHeap(minHeap, newFather);
    }

    node* root = extractMin(minHeap);
    free(minHeap->array);
    free(minHeap);
    return root;
}

void generateCodes(node* root, char* const tmpCode, int top, char codes[256][MAX_TREE_HEIGHT]){
    if (root == NULL) 
        return;
    if(root->left == NULL && root->right == NULL){
        tmpCode[top] = '\0';
        strcpy(codes[root->character], tmpCode);
    }
    if(root->left != NULL){
        tmpCode[top] = '0';
        generateCodes(root->left, tmpCode, top+1, codes);
    }
    if(root->right != NULL){
        tmpCode[top] = '1';
        generateCodes(root->right, tmpCode, top+1, codes);
    }
}

void writeHeader(int frequencies[MAX_TREE_HEIGHT], FILE* output){
    fwrite(frequencies, sizeof(int), MAX_TREE_HEIGHT, output);
}

void compressData(FILE* input, FILE* output, char codes[256][MAX_TREE_HEIGHT]){
    unsigned char buffer = 0;       // Il nostro secchio da 8 bit (tutto a zero)
    int bitCount = 0;               // Quanti bit abbiamo infilato nel secchio
    int ch;                         // Variabile per leggere i caratteri dal file originale

    while((ch = fgetc(input)) != EOF){
        char* strCode = codes[ch];
        for(int i = 0; strCode[i] != '\0'; i++){
            buffer <<= 1;
            if(strCode[i] == '1'){
                buffer |= 1;
            }
            ++bitCount;
            if(bitCount == 8){
                fputc(buffer, output);
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    if(bitCount > 0){
        buffer <<= 8-bitCount;
        fputc(buffer, output);
    }
}