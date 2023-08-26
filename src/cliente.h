#ifndef CLIENTE_H
#define CLIENTE_H
#define MAX_CLIENTI 100
#define CLIENTI_FILE_VERSION 1
#define CHECKSUM_INIT 0


#define MAX_NOME 20
#define MAX_COGNOME 20
#define MAX_ID 4

typedef struct {
	char idCliente[MAX_ID + 1];
    char cognome[20];
    char nome[20];
    int numeroOrdini; //numero di ordini effettuati dal singolo cliente
} Cliente;

void inizializzaClienti(Cliente clienti[]);
int salvaClienti(Cliente clienti[], int numeroClienti);
int aggiungiCliente(Cliente clienti[], int *numeroClienti, const Cliente *nuovoCliente);
int modificaCliente(Cliente clienti[], int numeroClienti,const char id[], const char* newNome, const char* newCognome);
int cancellaCliente(Cliente clienti[], int *numeroClienti,const char id[]);
void visualizzaClienti(const Cliente clienti[], int numeroClienti);
int caricaClienti(Cliente clienti[], int *numeroClienti);


#endif
