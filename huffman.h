#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_TREE_HEIGHT 256

typedef struct node{
    unsigned char character;        // Il carattere di cui contiamo a frequenza
    int frequency;                  // La frequenza con cui compare nel file
    struct node* left;              // Figlio sinistro
    struct node* right;             // Figlio destro
}node;

int countChar(const char* fileName, int frequencies[MAX_TREE_HEIGHT]);
node* createNode(const unsigned char ch, const int frequency);
node* buildHuffmanTree(int frequencies[MAX_TREE_HEIGHT]);
void generateCodes(node* root, char* const tmpCode, int top, char codes[256][MAX_TREE_HEIGHT]);
void writeHeader(int frequencies[MAX_TREE_HEIGHT], FILE* output);

#endif