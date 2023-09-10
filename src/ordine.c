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




void inizializzaOrdini(Cliente *clienti, Libro *libri, Ordine *ordini, int numeroClienti, int numeroLibri) {

    int count = 0;
    for (int i = 0; i < numeroClienti; i++) {
        for (int j = 0; j < numeroLibri; j++) {
            if (count >= MAX_ORDINI) {
                printf("Raggiunto il massimo numero di ordini possibili.\n");
                return;
            }
            // Inizializzazione dell'ordine
            snprintf(ordini[count].idOrdine, sizeof(ordini[count].idOrdine), "%s_%s", clienti[i].idCliente, libri[j].idLibro);
            ordini[count].cliente = &clienti[i];
            ordini[count].libro = &libri[j];
            // Puoi inizializzare altri campi qui
            count++;
        }
    }
}






int salvaOrdini(Ordine ordini[], int numeroOrdini) {
    FILE* file = fopen("ordini.bin", "wb");
    if (!file) {
        perror("Errore nell'apertura del file ordini.bin");
        return -1;
    }

    if (numeroOrdini == 0) {
        fclose(file);
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

void visualizzaClienteConPiuOrdini(Cliente clienti[], int numeroClienti, Ordine ordini[], int numeroOrdini) {
    int maxOrdini = 0;
    Cliente* clienteTop = NULL;

    for (int i = 0; i < numeroClienti; i++) {  // Cambia numeroOrdini con numeroClienti
        if (clienti[i].numeroOrdini > maxOrdini) {
            maxOrdini = clienti[i].numeroOrdini;
            clienteTop = &clienti[i];
        }
    }

    if (clienteTop) {
        printf("Il cliente con il numero maggiore di ordini è: %s %s con %d ordini.\n",
               clienteTop->nome, clienteTop->cognome, clienteTop->numeroOrdini);
    } else {
        printf("Nessun cliente trovato.\n");
    }
}








