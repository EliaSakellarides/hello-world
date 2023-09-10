#include "algoritmoOrdinamento.h"
#include "cliente.h"
#include "libro.h"
#include "ordine.h"
#include <string.h>

// Comparazione per gli Ordini basata sull'ID
int compareOrdini(const Ordine* a, const Ordine* b) {
    return strcmp(a->idOrdine, b->idOrdine);
}

// Comparazione per i Clienti basata sull'ID
int compareClienti(const Cliente* a, const Cliente* b) {
    return strcmp(a->idCliente, b->idCliente);
}

// Comparazione per i Libri basata sull'ISBN
int compareLibri(const Libro* a, const Libro* b) {
    return strcmp(a->titolo, b->titolo);
}

// Partition per Ordini
int partitionOrdini(Ordine arr[], int low, int high) {
    Ordine pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compareOrdini(&arr[j], &pivot) < 0) {
            i++;
            Ordine temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Ordine temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Partition per Clienti
int partitionClienti(Cliente arr[], int low, int high) {
    Cliente pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compareClienti(&arr[j], &pivot) < 0) {
            i++;
            Cliente temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Cliente temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// Partition per Libri
int partitionLibri(Libro arr[], int low, int high) {
    Libro pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compareLibri(&arr[j], &pivot) < 0) {
            i++;
            Libro temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Libro temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

// QuickSort per Ordini
void quickSortOrdini(Ordine ordini[], int primo, int ultimo) {
    if (primo < ultimo) {
        int pi = partitionOrdini(ordini, primo, ultimo);
        quickSortOrdini(ordini, primo, pi - 1);
        quickSortOrdini(ordini, pi + 1, ultimo);
    }
}

// QuickSort per Clienti
void quickSortClienti(Cliente clienti[], int primo, int ultimo) {
    if (primo < ultimo) {
        int pi = partitionClienti(clienti, primo, ultimo);
        quickSortClienti(clienti, primo, pi - 1);
        quickSortClienti(clienti, pi + 1, ultimo);
    }
}

// QuickSort per Libri
void quickSortLibri(Libro libri[], int primo, int ultimo) {
    if (primo < ultimo) {
        int pi = partitionLibri(libri, primo, ultimo);
        quickSortLibri(libri, primo, pi - 1);
        quickSortLibri(libri, pi + 1, ultimo);
    }
}

void ordinaEVisualizzaLibri(Libro libri[], int numeroLibri) {
    quickSortLibri(libri, 0, numeroLibri - 1);
    visualizzaLibri(libri, numeroLibri);
}
