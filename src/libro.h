
#ifndef LIBRO_H
#define LIBRO_H
#define MAX_LIBRI 100

typedef struct{
	char titolo [100];
	char autore [50];
	int annoPubblicazione;
	char isbn [20];
	char idLibro[20];
	char *scuola[20]; //es. Scuola primaria o secondaria
	

} Libro;

void visualizzaLibri(Libro libri[], int numeroLibri);

void inizializzaLibri(Libro libri[]);

//carica i libri dal file binario in un array 

void caricaLibri(Libro libri[], int *numeroLibri);

//salva l'array dei libri in un file binario 

void salvaLibri(const Libro libri[], int numeroLibri);

//aggiungi un nuovo libro all'array e salva sul file

void aggiungiLibro(Libro libri[], int *numeroLibri, const Libro *nuovoLibro);

//ricerca libro per codice ISBN

const Libro *ricercaLibroPerISBN(const Libro libri[], int numeroLibri, const char *isbn);

#endif // LIBRO_H
