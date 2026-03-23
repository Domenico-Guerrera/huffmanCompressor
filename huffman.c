#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "minheap.h"

int countChar(FILE* input, int frequencies[MAX_TREE_HEIGHT]){
    if(input != NULL){
        int ch;
        while((ch = fgetc(input)) != EOF)
            frequencies[ch]++;
    }else{
        return -1;
    }

    fclose(input);
    return 1;
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
    return extractMin(minHeap);
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

}
