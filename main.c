#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char* argv[]){
    // Controllo di sicurezza: l'utente ha passato il nome del file?
    if (argc < 3) {
        printf("Errore: devi fornire un file in input.\n");
        return -1;
    }

    if(strcmp(argv[1], "-c") == 0){
        int success = 0;

        while(success == 0){
            // Apertura del file da comprimere e del file compresso
            FILE* input = fopen(argv[2], "rb");
            if(input == NULL){
                printf("Problema con l'apertura del file, chiusura in corso...");
                return -1;
            }
            FILE* output = fopen("Compression.bin", "wb");
            if(output == NULL){
                printf("Problema con la compressione del file, chiusura in corso...");
                fclose(input);
                return -1;
            }

            // Inizializzo l'array per contare le frequenze di un carattere e lo faccio
            int freqs[MAX_TREE_HEIGHT] = {0};
            countChar(input, freqs);

            // Costruisco l'albero di Huffman sulle frequenze
            node* root = buildHuffmanTree(freqs);

            // Preparo le variabili per generare i codici di compressione, basandomi sull'albero di Huffman
            char codes[256][MAX_TREE_HEIGHT] = {0};
            char tmpCode[256] = {0};
            generateCodes(root, tmpCode, 0, codes);
            writeHeader(freqs, output);
            rewind(input);

            // Comprimo i dati
            compressData(input, output, codes);
            
            // Salvo l'esito di entrambe le chiusure
            int esito_in = fclose(input);
            int esito_out = fclose(output);

            // Controllo: hanno avuto successo entrambe?
            if(esito_in == 0 && esito_out == 0){
                success = 1; // Tutto perfetto, impostiamo la flag per uscire dal while
                printf("Compressione completata con successo!\n");
            } else {    // Almeno una delle due chiusure ha fallito 
                int ans = 0;
                do{
                    printf("C'è stato un problema durante il salvataggio o la chiusura dei file.\n"
                        "> Inserire 1 per riprovare con la compressione;\n"
                        "> Inserire 0 per uscire;\n"
                        "> ");
                    scanf("%d", &ans);
                }while(ans != 1 && ans != 0);
                
                if(ans == 0){
                    return -1; // Uscita per scelta dell'utente
                }
                // Se ans è 1, non facciamo nulla: success è ancora 0, 
                // quindi il ciclo while ricomincerà tutto da capo automaticamente.
            }
        }
    } else if(strcmp(argv[1], "-d") == 0){
        int success = 0;
        
        while(success == 0){
            FILE* input = fopen(argv[2], "rb");
            if(input == NULL){
                printf("Problema con l'apertura del file, chiusura in corso...");
                return -1;
            }
            FILE* output = fopen("Decompression.txt", "w");
            if(output == NULL){
                printf("Problema con la decompressione del file, chiusura in corso...");
                fclose(input);
                return -1;              
            }
            
            int freqs[MAX_TREE_HEIGHT] = {0};
            readHeader(freqs, input);
            
            node* root = buildHuffmanTree(freqs);

            decompressData(input, output, root, getTotalChars(freqs));

            // Salvo l'esito di entrambe le chiusure
            int esito_in = fclose(input);
            int esito_out = fclose(output);

            // Controllo: hanno avuto successo entrambe?
            if(esito_in == 0 && esito_out == 0){
                success = 1; // Tutto perfetto, impostiamo la flag per uscire dal while
                printf("Decompressione completata con successo!\n");
            } else {    // Almeno una delle due chiusure ha fallito 
                int ans = 0;
                do{
                    printf("C'è stato un problema durante il salvataggio o la chiusura dei file.\n"
                        "> Inserire 1 per riprovare con la decompressione;\n"
                        "> Inserire 0 per uscire;\n"
                        "> ");
                    scanf("%d", &ans);
                }while(ans != 1 && ans != 0);
                
                if(ans == 0){
                    return -1; // Uscita per scelta dell'utente
                }
                // Se ans è 1, non facciamo nulla: success è ancora 0, 
                // quindi il ciclo while ricomincerà tutto da capo automaticamente.
            }

        }
    }else{
        printf("Flag non valido. Usare -c o -d per decidere di comprimere o decomprimere il file.\nChiusura in corso...");
        return -1;
    }
    return 0;   
}