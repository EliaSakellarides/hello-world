#include <stdio.h>
#include <string.h>
#include "ordine.h"
#include "cliente.h"
#include "libro.h"


const char* statoToString(StatoOrdine stato) {
        switch (stato) {
            case StatoInserito: return "Inserito";
            case StatoEvaso: return "Evaso";
            case StatoAnnullato: return "Annullato";
            default: return "Sconosciuto";
        }
    }

// Funzione per salvare gli ordini su file
int salvaOrdini(Ordine ordini[], int numeroOrdini) {
    FILE* file = fopen("ordini.bin", "wb");
    if (file == NULL) {
        return 0; // errore nell'apertura del file
    }
    if (numeroOrdini == 0) return 0;{// nessun ordine da salvare
    }

    for (int i = 0; i < numeroOrdini; i++) {
        fwrite(&ordini[i], sizeof(Ordine), 1, file);
    }

    fclose(file);
    return 1; // operazione riuscita
}

void caricaOrdini(Ordine ordini[], int* numeroOrdini, int maxSize) {
    FILE* file = fopen("ordini.bin", "rb");
    if (file == NULL) {
        // Gestione dell'errore, se necessario
        *numeroOrdini = 0;
        return;
    }

    int count = 0;
    while (fread(&ordini[count], sizeof(Ordine), 1, file) == 1 && count < maxSize) {
        count++;
    }

    fclose(file);
    *numeroOrdini = count; 
}

int aggiungiOrdine(Ordine ordini[], int *numeroOrdini, Ordine nuovoOrdine) {
    if (*numeroOrdini >= MAX_ORDINI) {
        return 0; // numero massimo di ordini raggiunto
    }

    ordini[*numeroOrdini] = nuovoOrdine;
    (*numeroOrdini)++;
    salvaOrdini(ordini, *numeroOrdini);
    return 1; 
}

int modificaOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[], Ordine nuovoOrdine) {
    for (int i = 0; i < numeroOrdini; i++) {
        if (strcmp(ordini[i].idOrdine, idOrdine) == 0) {
            ordini[i] = nuovoOrdine;
            salvaOrdini(ordini, numeroOrdini);
            return 1; 
            break;
        }
    }
    return 0;
}

int cancellaOrdine(Ordine ordini[], int *numeroOrdini, char idOrdine[]) {
    int indice = -1;
    for (int i = 0; i < *numeroOrdini; i++) {
        if (strcmp(ordini[i].idOrdine, idOrdine) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        return 0;
    }

    for (int i = indice; i < *numeroOrdini - 1; i++) {
        ordini[i] = ordini[i + 1];
    }
    (*numeroOrdini)--;
    return 1;
}

int evadiOrdine(Ordine ordini[], int numeroOrdini, char idOrdine[]) {
    for (int i = 0; i < numeroOrdini; i++) {
        if (strcmp(ordini[i].idOrdine, idOrdine) == 0) {
        	ordini[i].stato = StatoEvaso;
            salvaOrdini(ordini, numeroOrdini); // salva le modifiche su file
            return 1; // operazione riuscita
        }
    }
    return 0; // id ordine non trovato
}

void visualizzaOrdini(const Ordine ordini[], int numeroOrdini) {
    for (int i = 0; i < numeroOrdini; i++) {
        printf("ID Ordine: %s\n", ordini[i].idOrdine);
        printf("ID Cliente: %s\n", ordini[i].cliente[0]->idCliente);
        printf("Cliente: %s %s\n", ordini[i].cliente[0]->nome, ordini[i].cliente[0]->cognome);
        printf("ID Libro: %s\n", ordini[i].libro[0]->idLibro);
        printf("Libro: %s\n", ordini[i].libro[0]->titolo);
        printf("Quantita: %d\n", ordini[i].quantita);
        printf("Stato: %s\n", statoToString(ordini[i].stato));
        printf("\n");
    }


}



