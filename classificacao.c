#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* copyArray(int* arr, int n) {
    int* copy = malloc(sizeof(int) * n);
    memcpy(copy, arr, sizeof(int) * n);
    return copy;
}

void swap(int* v, int i, int n, int *count) {
    int aux = v[i];
    v[i] = v[n];
    v[n] = aux;
    (*count)++;
}

void bubblesort(int v[], int n, int *count) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            (*count)++;
            if (v[i] > v[j]) {
                swap(v,i,j,count);
            }
        }
    }
}

int testBubbleSort(int v[], int n) {
    int count = 0;
    int* copy = copyArray(v, n);
    bubblesort(copy, n, &count);
    free(copy);
    return count;
}

void heapify(int v[], int n, int i, int *count) {
    int raiz = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && v[esquerda] > v[raiz]) raiz = esquerda; (*count)++; // Troca esquerda com raiz
    if (direita < n && v[direita] > v[raiz]) raiz = direita; (*count)++;// Troca direita com raiz

    if (raiz != i) { // Verifica se a raiz precisa ser alterada
        swap(v, i, raiz, count); // Realiza a troca
        heapify(v, n, raiz, count); // Garante recursivamente o heap máximo
    }
}

void heapsort(int v[], int n, int* count) {
    // Cria o heap máximo a partir dos nós não folha (n / 2 - 1)
    // Valores maiores que n / 2 - 1 são nós folha
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, count);
    }

    // Recria o heap máximo reduzindo o tamanho da heap a cada iteração (heap parcial)
    for (int i = n - 1; i > 0; i--) {
        swap(v, 0, i, count); // Troca o primeiro valor (maior) pelo último da heap parcial

        heapify(v, i, 0, count); // Atualiza o heap máximo parcial
    }
}

int testHeapSort(int v[], int n){
    int count = 0;
    int* copy = copyArray(v, n);
    heapsort(copy, n, &count);
    free(copy);
    return count;
}

void insertionsort(int v[], int n, int* count) {
    int pivo, j;
    for (int i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;

        while (j >= 0 && pivo < v[j]) {
            v[j + 1] = v[j]; // desloca para a direita
            j--;
            (*count)++;
        }
        v[j + 1] = pivo;
    }
}

int testInsertionsort(int v[], int n){
    int count = 0;
    int* copy = copyArray(v, n);
    insertionsort(copy, n, &count);
    free(copy);
    return count;
}

void merge(int v[], int inicio, int meio, int fim, int* count) {
    int aux[fim - inicio + 1];
    int i = inicio, j = meio + 1, k = 0;
    
    while (i <= meio && j <= fim) { // Intercala
        aux[k++] = v[i] <= v[j] ? v[i++] : v[j++];
        (*count)++;
    }
    while (i <= meio) aux[k++] = v[i++]; (*count)++; // Copia o resto do subvetor que não terminou
    while (j <= fim) aux[k++] = v[j++]; (*count)++; // Copia o resto do subvetor que não terminou

    for (i = inicio, k = 0; i <= fim; i++, k++) { // Copia de volta para o vetor original
        v[i] = aux[k];
        (*count)++;
    }
}

void _mergesort(int v[], int inicio, int fim, int* count) {
    int meio = (inicio + fim) / 2;

    if (inicio < fim) {
        _mergesort(v, inicio, meio, count); // Dividir
        _mergesort(v, meio + 1, fim, count);

        merge(v, inicio, meio, fim, count); // Conquistar
    }
}

void mergesort(int v[], int n, int* count) {
    _mergesort(v, 0, n - 1, count);
}

int testMegeSort(int v[], int n){
    int count = 0;
    int* copy = copyArray(v, n);
    mergesort(copy, n, &count);
    free(copy);
    return count;
}

int partition(int v[], int inicio, int fim, int* count) {
    int pivo = v[fim]; // Pivô será o último elemento da partição
    int i = (inicio - 1); // Indica a posição correta do pivô até então

    for (int j = inicio; j <= fim - 1; j++) {
        (*count)++;
        if (v[j] < pivo) { // Verifica se o elemento atual é menor que o pivô
            i++; // Incrementa o índice da posição correta do pivô

            swap(v, i, j, count); // Realiza a troca (swap) do elemento atual
        }
    }
    swap(v, i + 1, fim, count); // Posiciona o pivô na posição correta

    return i + 1; // Informa o índice a ser utilizado para o próximo particionamento
}

void _quicksort(int v[], int inicio, int fim, int* count) {
    if (inicio < fim) {
        int meio = partition(v, inicio, fim, count);
        _quicksort(v, inicio, meio - 1, count); // Antes do pivô
        _quicksort(v, meio + 1, fim, count); // Após pivô
    }
}

void quicksort(int v[], int n, int* count) {
    _quicksort(v, 0, n - 1, count);
}

int testQuickSort(int v[], int n){
    int count = 0;
    int* copy = copyArray(v, n);
    quicksort(copy, n, &count);
    free(copy);
    return count;
}

void countingsort(int v[], int n, int exp, int* count) {
    int saida[n], frequencia[10] = {0}; // Dígitos de 0 a 9, inicializa a frequência com zeros
    // Armazena a frequência de cada valor pelo índice
    for (int i = 0; i < n; i++) { 
        (*count)++;
        frequencia[(v[i] / exp) % 10]++;
    } 
    // Armazena a soma do elemento atual com o elemento anterior
    for (int i = 1; i < 10; i++) { 
        (*count)++;
        frequencia[i] += frequencia[i - 1];
    }
    // Cria a saída a partir do vetor de entrada e da frequência
    for (int i = n - 1; i >= 0; i--) { 
        (*count)++;
        saida[frequencia[(v[i] / exp) % 10] - 1] = v[i];
        frequencia[(v[i] / exp) % 10]--;  // Decrementa corretamente a posição no vetor de frequência
    }
    // Copia o vetor de saída para o vetor de entrada
    for (int i = 0; i < n; i++) { 
        (*count)++;
        v[i] = saida[i];
    } 
}

int max(int v[], int n, int* count) {
    int max = v[0];
    for (int i = 1; i < n; i++) {
        (*count)++;
        if (v[i] > max)
            (*count)++;
            max = v[i];
    }
    return max;
}

void radixsort(int v[], int n, int* count) {
    int m = max(v, n, count); // Obtém o maior número para conhecer a quantidade de dígitos
    for (int exp = 1; m / exp > 0; exp *= 10) //Realiza o counting sort para cada dígito
        countingsort(v, n, exp, count); // exp é atualizada com 10^i, onde i é o dígito atual 10, 100, 1000, ...
}

int testRadixSort(int v[], int n){
    int count = 0;
    int* copy = copyArray(v, n);
    radixsort(copy, n, &count);
    free(copy);
    return count;
}

int main() {
    srand(time(NULL));

    const char *filename = "dados.csv";
    FILE *file = fopen(filename, "w");
    fprintf(file, "QTD,Bubblesort,Heapsort,Insertionsort,MegeSort,QuickSort,RadixSort\n");

    for (int x = 1; x <= 1000; x++) {

        int n = x;
        int* vetor = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++){
            vetor[i] = rand() / 100;
        }
        printf("\nVetor com %d elementos: \n", x);
        int bubble = testBubbleSort(vetor, n);
        int heap = testHeapSort(vetor, n);
        int insertion = testInsertionsort(vetor, n);
        int merge = testMegeSort(vetor, n);
        int quick = testQuickSort(vetor, n);
        int radix = testRadixSort(vetor, n);

        printf("Bubblesort: %d\n", bubble);
        printf("Heapsort: %d\n", heap);
        printf("Insertionsort: %d\n", insertion);
        printf("MegeSort: %d\n", merge);
        printf("QuickSort: %d\n", quick);
        printf("RadixSort: %d\n", radix);

        fprintf(file, "%d,%d,%d,%d,%d,%d,%d\n",x,bubble,heap,insertion,merge,quick,radix);
    }
    fclose(file);
}
