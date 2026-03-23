#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char* argv[]){
    // Controllo di sicurezza: l'utente ha passato il nome del file?
    if (argc < 2) {
        printf("Errore: devi fornire un file in input.\n");
        return -1;
    }

    int success = 0;

    while(success == 0){
        FILE* input = fopen(argv[1], "rb");
        if(input == NULL){
            printf("Problema con l'apertura del file, chiusura in corso...");
            return -1;
        }
        FILE* output = fopen("Compression.txt", "w");
        if(output == NULL){
            printf("Problema con la compressione del file, chiusura in corso...");
            fclose(input);
            return -1;
        }

        //CODICE COMPRESSIONE HUFFMAN

        // Salvo l'esito di entrambe le chiusure
        int esito_in = fclose(input);
        int esito_out = fclose(output);

        // Controllo: hanno avuto successo entrambe?
        if(esito_in == 0 && esito_out == 0){
            success = 1; // Tutto perfetto, impostiamo la flag per uscire dal while
            printf("Compressione completata con successo!\n");
        } else {
            // Almeno una delle due chiusure ha fallito
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
    return 0;   
}