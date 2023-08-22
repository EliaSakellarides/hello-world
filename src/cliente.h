#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTI 20

typedef struct {
    char idCliente[50];
    char nome[50];
    char cognome[50];
    int numeroOrdini; //numero di ordini effettuati dal singolo cliente
} Cliente;

void inizializzaClienti(Cliente clienti[]);
int salvaClienti(Cliente clienti[], int numeroClienti);
int aggiungiCliente(Cliente clienti[], int *numeroClienti, Cliente nuovoCliente);
int modificaCliente(Cliente clienti[], int numeroClienti, char id[], Cliente nuovoCliente);
int cancellaCliente(Cliente clienti[], int *numeroClienti, char id[]);
void visualizzaClienti(Cliente clienti[], int numeroClienti);
void caricaClienti(Cliente clienti[], int* numeroClienti, int maxSize); 


#endif
