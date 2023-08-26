
#include "cliente.h"
#include <stdio.h>
#include <string.h>
#include "ordine.h"
#include "libro.h"

#define FILE_CLIENTI "clienti.bin"

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

    for (int i = 0; i < 20; i++) {
        snprintf(clienti[i].idCliente, sizeof(clienti[i].idCliente), "C%02d", i+1);

        // Nome
        strlcpy(clienti[i].nome, (i < sizeof(nomi) / sizeof(nomi[0]) ? nomi[i] : ""), sizeof(clienti[i].nome) - 1);
        clienti[i].nome[sizeof(clienti[i].nome) - 1] = '\0';  // Termination for safety

        // Cognome
        strlcpy(clienti[i].cognome, (i < sizeof(cognomi) / sizeof(cognomi[0]) ? cognomi[i] : ""), sizeof(clienti[i].cognome) - 1);
        clienti[i].cognome[sizeof(clienti[i].cognome) - 1] = '\0';  // Termination for safety

        clienti[i].numeroOrdini = 0;

        // Debug for verification
        printf("Debug - Cliente #%d: ID: %s, Nome: %s, Cognome: %s\n",
        i+1, clienti[i].idCliente, clienti[i].nome, clienti[i].cognome);
    }

}

void visualizzaClienti(const Cliente clienti[], int numeroClienti) {
    if (numeroClienti == 0) {
        printf("Non ci sono clienti disponibili.\n");
        return;
    }
    for (int i = 0; i < numeroClienti; i++) {
        printf("Debug: Stampa cliente %d\n", i+1);
        printf("%-4s %-10s %-10s %-20i\n",
               clienti[i].idCliente, clienti[i].nome, clienti[i].cognome, clienti[i].numeroOrdini);
    }


    printf("Ecco la lista dei clienti:\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("%-4s %-10s %-10s %-20s\n", "ID", "Nome", "Cognome", "Numero Ordini");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < numeroClienti; i++) {
        printf("%-4s %-10s %-10s %-20d\n",
               clienti[i].idCliente, clienti[i].nome, clienti[i].cognome, clienti[i].numeroOrdini);
    }
    printf("-------------------------------------------------------------------------------\n");

}

int caricaClienti(Cliente clienti[], int* numeroClienti) {
    FILE *clientiBinFile = fopen(FILE_CLIENTI, "rb");
    if (!clientiBinFile) {
        perror("Errore nell'apertura del file clienti.bin");
        *numeroClienti = 0;
        memset(clienti, 0, sizeof(Cliente) * MAX_CLIENTI);
        return -1;
    }

    int fileVersion;
    fread(&fileVersion, sizeof(int), 1, clientiBinFile);

    if(fileVersion != CLIENTI_FILE_VERSION) {
        printf("Versione attesa: %d, Versione trovata nel file: %d\n", CLIENTI_FILE_VERSION, fileVersion);
        printf("Versione del file non supportata.\n");
        fclose(clientiBinFile);
        return -1;
    }

    // Leggiamo il numero effettivo di clienti dal file
    fread(numeroClienti, sizeof(int), 1, clientiBinFile);
    if (*numeroClienti > MAX_CLIENTI) {
        printf("Errore: numero di clienti nel file eccede il massimo supportato.\n");
        fclose(clientiBinFile);
        return -1;
    }

    int numClientiVerificato = 0;
    for (int i = 0; i < *numeroClienti; i++) {
        if (clienti[i].idCliente[0] != '\0') {  // Assumendo che un ID vuoto indichi un record non valido
            numClientiVerificato++;
        }
    }
    if (numClientiVerificato != *numeroClienti) {
        printf("Attenzione: discrepanza nei dati dei clienti. Corretto il numero di clienti da %d a %d.\n", *numeroClienti, numClientiVerificato);
        *numeroClienti = numClientiVerificato;
    }


    // Carichiamo i dati dei clienti dal file
    fread(clienti, sizeof(Cliente), *numeroClienti, clientiBinFile);

    // Chiusura del file
    fclose(clientiBinFile);

    return 0;  // Ritorna 0 in caso di successo
}



int salvaClienti(Cliente clienti[], int numeroClienti) {
    FILE *file = fopen(FILE_CLIENTI, "wb");
    if (!file) {
        perror("Errore nell'apertura del file clienti.bin");
        return -1;
    }

    // Scrivi la versione del file prima di tutto
    int tempVersion = CLIENTI_FILE_VERSION;
    fwrite(&tempVersion, sizeof(int), 1, file);
    fwrite(&numeroClienti, sizeof(int), 1, file);
    fwrite(clienti, sizeof(Cliente), numeroClienti, file);
    fclose(file);
    return 0;
}



int aggiungiCliente(Cliente clienti[], int *numeroClienti, const Cliente *nuovoCliente) {
    if (*numeroClienti >= MAX_CLIENTI) {
        return -1;
    }
    clienti[*numeroClienti] = *nuovoCliente;
    (*numeroClienti)++;
    return 0;
}

int modificaCliente(Cliente clienti[], int numeroClienti, const char id[], const char* newNome, const char* newCognome) {
    for (int i = 0; i < numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            if (newNome) {
                strlcpy(clienti[i].nome, newNome, sizeof(clienti[i].nome));
            }
            if (newCognome) {
                strlcpy(clienti[i].cognome, newCognome, sizeof(clienti[i].cognome));
            }
            return 0;
        }
    }
    return -1;
}

int cancellaCliente(Cliente clienti[], int *numeroClienti, const char id[]) {
    for (int i = 0; i < *numeroClienti; i++) {
        if (strcmp(clienti[i].idCliente, id) == 0) {
            for (int j = i; j < *numeroClienti - 1; j++) {
                clienti[j] = clienti[j + 1];
            }
            (*numeroClienti)--;
            return 0;
        }
    }
    return -1;
}
