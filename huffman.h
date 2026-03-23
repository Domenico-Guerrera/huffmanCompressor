#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_TREE_HEIGHT 256

typedef struct node{
    unsigned char character;        // Il carattere di cui contiamo a frequenza
    int frequency;                  // La frequenza con cui compare nel file
    struct node* left;              // Figlio sinistro
    struct node* right;             // Figlio destro
}node;

int countChar(const char* fileName, int frequencies[256]);
node* createNode(const unsigned char ch, const int frequency);
node* buildHuffmanTree(int frequencies[256]);
void generateCodes(node* root, char* const tmpCode, int top, char codes[256][MAX_TREE_HEIGHT]);


#endif