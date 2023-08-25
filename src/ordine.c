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




void inizializzaOrdini(Ordine ordini[]) {
	for (int i = 0; i < MAX_ORDINI; i++) {
	    strcpy(ordini[i].idOrdine, "");

	        ordini[i].cliente = NULL;
	        ordini[i].libro = NULL;
	        ordini[i].quantita = 0;
	        ordini[i].stato = StatoInserito;
	}
}

int salvaOrdini(Ordine ordini[], int numeroOrdini) {
    FILE* file = fopen("ordini.bin", "wb");
    if (file == NULL || numeroOrdini == 0) {
        return 0;
    }

    for (int i = 0; i < numeroOrdini; i++) {
        fwrite(&ordini[i], sizeof(Ordine), 1, file);
    }

    fclose(file);
    return 1;
}

void caricaOrdini(Ordine ordini[], int* numeroOrdini, int maxSize) {
    FILE* file = fopen("ordini.bin", "rb");
    if (file == NULL) {
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
        return 0;
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
            salvaOrdini(ordini, numeroOrdini);
            return 1;
        }
    }
    return 0;
}

void visualizzaOrdini(const Ordine ordini[], int numeroOrdini) {
    for (int i = 0; i < numeroOrdini; i++) {
        printf("ID Ordine: %s\n", ordini[i].idOrdine);
        printf("ID Cliente: %s\n", ordini[i].cliente->idCliente);  // Accesso corretto ai campi con puntatori
        printf("Cliente: %s %s\n", ordini[i].cliente->nome, ordini[i].cliente->cognome);
        printf("ID Libro: %s\n", ordini[i].libro->idLibro);
        printf("Libro: %s\n", ordini[i].libro->titolo);
        printf("Quantita: %d\n", ordini[i].quantita);
        printf("Stato: %s\n", statoToString(ordini[i].stato));
        printf("\n");
    }
}
