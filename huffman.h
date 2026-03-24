#ifndef HUFFMAN_H
#define HUFFMAN_H
#define MAX_TREE_HEIGHT 256

typedef struct node{
    unsigned char character;        // Il carattere di cui contiamo a frequenza
    int frequency;                  // La frequenza con cui compare nel file
    struct node* left;              // Figlio sinistro
    struct node* right;             // Figlio destro
}node;

void countChar(FILE* input, int frequencies[MAX_TREE_HEIGHT]);
node* createNode(const unsigned char ch, const int frequency);
node* buildHuffmanTree(int frequencies[MAX_TREE_HEIGHT]);
void generateCodes(node* root, char* const tmpCode, int top, char codes[256][MAX_TREE_HEIGHT]);
void writeHeader(int frequencies[MAX_TREE_HEIGHT], FILE* output);
void compressData(FILE* input, FILE* output, char codes[256][MAX_TREE_HEIGHT]);
void readHeader(int* const frequencies, FILE* input);
int getTotalChars(int* const frequencies);
void decompressData(FILE* input, FILE* output, node* root, int totalCh);

#endif