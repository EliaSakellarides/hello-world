#include <stdio.h>
#include <string.h>
#include "cliente.h"

#define FILE_CLIENTI "clienti.bin"
// Aggiunta-Modifica-Cancellazione degli ordini e dei clienti


void inizializzaClienti(Cliente clienti[]) {
    char *nomi[] = {"Mario", "Luca", "Francesca", "Maria", "Giulia", "Marco", "Roberto", "Anna", "Elisa", "Federico", "Riccardo", "Luisa", "Paolo", "Elena", "Simone", "Alessandra", "Gabriele", "Laura", "Davide", "Sara"};
    char *cognomi[] = {"Rossi", "Bianchi", "Verdi", "Neri", "Gialli", "Bruni", "Romano", "Colombo", "Ricci", "Costa", "Barbieri", "Fontana", "Rizzo", "Moretti", "Marino", "Greco", "Conti", "De Luca", "Mancini", "Rinaldi"};
    printf("cazzo");
    for (int i = 0; i < 20; i++) {
        snprintf(clienti[i].idCliente, sizeof(clienti[i].idCliente), "ID%03d", i+1);
        strncpy(clienti[i].nome, nomi[i], sizeof(clienti[i].nome) - 1);
        strncpy(clienti[i].cognome, cognomi[i], sizeof(clienti[i].cognome) - 1);

        clienti[i].numeroOrdini = 0; // inizializzato a 0
    }
}


// Funzione per salvare i clienti su file
int salvaClienti(Cliente clienti[], int numeroClienti) {
    FILE *file = fopen(FILE_CLIENTI, "wb");
    if (!file) {
        perror("Errore nell'apertura del file clienti.bin");
        return -1;
    }
    fwrite(&numeroClienti, sizeof(int), 1, file);
    fwrite(clienti, sizeof(Cliente), numeroClienti, file);
    fclose(file);
    return 0; // Salvataggio completato con successo
}

//funzione per caricare clienti
void caricaClienti(Cliente clienti[], int* numeroClienti, int maxSize) {
    FILE *file = fopen(FILE_CLIENTI, "rb");
    if (!file) {
    	perror("Errore nell'apertura del file clienti.bin per la lettura");
        *numeroClienti = 0;
        return;
    }
    fread(numeroClienti, sizeof(int), 1, file);
    if (*numeroClienti > maxSize) {
        *numeroClienti = maxSize; // Evita di sovrascrivere la memoria
    }
    fread(clienti, sizeof(Cliente), *numeroClienti, file);
    fclose(file);
}

// Aggiunta di un Cliente

int aggiungiCliente(Cliente clienti[], int *numeroClienti, Cliente nuovoCliente) {
    if (*numeroClienti >= MAX_CLIENTI) {
        return -1; // Numero massimo di clienti raggiunto
    }
    clienti[*numeroClienti] = nuovoCliente;
    (*numeroClienti)++;
    return 0; // Cliente aggiunto con successo
}

// Modifica di un cliente

int modificaCliente(Cliente clienti[], int numeroClienti, char id[], Cliente nuovoCliente) {
    for (int i = 0; i < numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            clienti[i] = nuovoCliente;
            return 0; // Cliente modificato con successo
        }
    }
    return -1; // Cliente non trovato
}

// Cancellazione di un cliente

int cancellaCliente(Cliente clienti[], int *numeroClienti, char id[]) {
    for (int i = 0; i < *numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            for (int j = i; j < *numeroClienti - 1; j++) {
                clienti[j] = clienti[j + 1]; // Sposta tutti gli elementi successivi
            }
            (*numeroClienti)--;
            return 0; // Cliente cancellato con successo
        }
    }
    return -1; // Cliente non trovato
}

// Funzione per visualizzare tutti i clienti
void visualizzaClienti(Cliente clienti[], int numeroClienti) {
	printf("Ciao");
    for (int i = 0; i < numeroClienti; i++) {
    	printf("Ciao");
        printf("ID: %s, Nome: %s, Cognome: %s, Numero Ordini: %d\n", 
               clienti[i].idCliente, clienti[i].nome, clienti[i].cognome, clienti[i].numeroOrdini);
    }
}
