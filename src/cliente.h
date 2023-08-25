#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTI 20
#define MAX_NOME 50
#define MAX_COGNOME 50
#define MAX_ID 5

typedef struct {
    char idCliente[MAX_ID];
    char nome[MAX_NOME];
    char cognome[MAX_COGNOME];
    int numeroOrdini; //numero di ordini effettuati dal singolo cliente
} Cliente;

void inizializzaClienti(Cliente clienti[]);
int salvaClienti(Cliente clienti[], int numeroClienti);
int aggiungiCliente(Cliente clienti[], int *numeroClienti, Cliente nuovoCliente);
int modificaCliente(Cliente clienti[], int numeroClienti, char id[], char* newNome, char* newCognome);
int cancellaCliente(Cliente clienti[], int *numeroClienti, char id[]);
void visualizzaClienti(Cliente clienti[], int numeroClienti);
int caricaClienti(Cliente clienti[], int* numeroClienti, int maxSize);


#endif
