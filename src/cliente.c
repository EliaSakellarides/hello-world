#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "ordine.h"
#include "libro.h"

#define FILE_CLIENTI "clienti.bin"
// Aggiunta-Modifica-Cancellazione dei clienti


void inizializzaClienti(Cliente clienti[]) {
    memset(clienti, 0, sizeof(Cliente) * MAX_CLIENTI);

    const char *nomi[] = {
        "Mario", "Luca", "Francesca", "Maria", "Giulia", "Marco",
        "Roberto", "Anna", "Elisa", "Federico", "Riccardo", "Luisa",
        "Paolo", "Elena", "Simone", "Alessandra", "Gabriele", "Laura",
        "Davide", "Sara"
    };

    const char *cognomi[] = {
        "Rossi", "Bianchi", "Verdi", "Neri", "Gialli", "Bruni", "Romano",
        "Colombo", "Ricci", "Costa", "Barbieri", "Fontana", "Rizzo",
        "Moretti", "Marino", "Greco", "Conti", "De Luca", "Mancini", "Rinaldi"
    };



    for (size_t i = 0; i < MAX_CLIENTI; i++) {
           snprintf(clienti[i].idCliente, sizeof(clienti[i].idCliente), "C%03zu", i+1);

           if (i < sizeof(nomi) / sizeof(nomi[0])) {
               snprintf(clienti[i].nome, sizeof(clienti[i].nome), "%s", nomi[i]);
           } else {
               clienti[i].nome[0] = '\0';
           }

           if (i < sizeof(cognomi) / sizeof(cognomi[0])) {
               snprintf(clienti[i].cognome, sizeof(clienti[i].cognome), "%s", cognomi[i]);
           } else {
               clienti[i].cognome[0] = '\0';
           }

           clienti[i].numeroOrdini = 0; // inizializzato a 0

           // Debug per verificare l'inizializzazione
           printf("Debug - Cliente #%zu: ID: %s, Nome: %s, Cognome: %s\n",
           i+1, clienti[i].idCliente, clienti[i].nome, clienti[i].cognome);
       }
   }


// Funzione per visualizzare tutti i clienti
void visualizzaClienti(Cliente clienti[], int numeroClienti) {
    if (numeroClienti == 0) {
        printf("Non ci sono clienti disponibili.\n");
        return;
    }

    printf("Ecco la lista dei clienti:\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("%-10s %-30s %-30s %-20s\n",
           "ID", "Nome", "Cognome", "Numero Ordini");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < numeroClienti; i++) {
    	printf("%-10s %-30s %-30s %-20d\n",
    	    clienti[i].idCliente, clienti[i].nome, clienti[i].cognome, clienti[i].numeroOrdini);    }
    printf("-------------------------------------------------------------------------------\n");
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
int caricaClienti(Cliente clienti[], int* numeroClienti, int maxSize) {
    memset(clienti, 0, sizeof(Cliente) * MAX_CLIENTI);

    FILE *clientiBinFile = fopen(FILE_CLIENTI, "rb");
    if (clientiBinFile == NULL) {
        perror("Errore nell'apertura del file clienti.bin");
        return -1;
    }

    fread(numeroClienti, sizeof(int), 1, clientiBinFile);
    if (*numeroClienti > maxSize) {
        *numeroClienti = maxSize; // Evita di sovrascrivere la memoria
    }
    fread(clienti, sizeof(Cliente), *numeroClienti, clientiBinFile);
    fclose(clientiBinFile);
    return 0;
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

int modificaCliente(Cliente clienti[], int numeroClienti, char id[], char* newNome, char* newCognome){
    for (int i = 0; i < numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            if (newNome) {
                strlcpy(clienti[i].nome, newNome, sizeof(clienti[i].nome));
            }
            if (newCognome) {
                strlcpy(clienti[i].cognome, newCognome, sizeof(clienti[i].cognome));
            }
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

