#include <stdio.h>
#include <string.h>
#include "ordine.h"
#include "cliente.h"
#include "libro.h"
#include <stdlib.h>


const char* statoToString(StatoOrdine stato) {
    switch (stato) {
        case StatoInserito: return "Inserito";
        case StatoEvaso: return "Evaso";
        case StatoAnnullato: return "Annullato";
        default: return "Sconosciuto";
    }
}




void inizializzaOrdini(const Cliente clienti[], const Libro libri[], Ordine ordini[], int numeroClienti, int numeroLibri) {

    // Supponiamo che tu voglia creare un ordine per ogni cliente e libro
    int count = 0; // Questo terrà traccia di quanti ordini sono stati effettivamente creati

    for (int i = 0; i < numeroClienti; i++) {
        for (int j = 0; j < numeroLibri; j++) {
            if (count >= MAX_ORDINI) {
                printf("Raggiunto il massimo numero di ordini possibili.\n");
                return;
            }

            // Inizializzazione dell'ordine
            strncpy(ordini[count].idOrdine, clienti[i].idCliente, MAX_ID + 1);
            strncat(ordini[count].idOrdine, "_", 1);
            strncat(ordini[count].idOrdine, libri[j].idLibro, 20);

            ordini[count].cliente = &clienti[i];  // Impostazione del puntatore al cliente
            ordini[count].libro = &libri[j];      // Impostazione del puntatore al libro

            // Potresti voler inizializzare altri campi dell'ordine qui, come la quantità, lo stato, ecc.

            count++;
        }
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
        return;   // This is okay since the function's return type is void
    }

    int count = 0;
    while (fread(&ordini[count], sizeof(Ordine), 1, file) == 1 && count < maxSize) {
        count++;
    }

    if (fclose(file) != 0) {
        perror("Failed to close the file");
        return;   // You might want to handle this error more gracefully in a real application
    }
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

void visualizzaOrdini(const Cliente clienti[], int numeroClienti, const Ordine ordini[], int numeroOrdini, const Libro libri[], int numeroLibri) {
    if (ordini == NULL || numeroOrdini <= 0) {
        printf("Nessun ordine da visualizzare.\n");
        return;
    }


    // Header della tabella
    printf("%-10s %-10s %-15s %-15s %-30s %-10s %-10s\n",
           "ID Ordine", "ID Cliente", "Nome", "Cognome", "Titolo Libro", "Quantita", "Stato");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numeroOrdini; i++) {
        if (ordini[i].cliente == NULL || ordini[i].libro == NULL) {
        	printf("Ordine con ID %s non valido.\n", ordini[i].idOrdine);
            continue;
        }

        printf("%-10s %-10s %-15s %-15s %-30s %-10d %-10s\n",
               ordini[i].idOrdine,
               ordini[i].cliente->idCliente,
               ordini[i].cliente->nome,
               ordini[i].cliente->cognome,
               ordini[i].libro->titolo,
               ordini[i].quantita,
               statoToString(ordini[i].stato));
    }
}






