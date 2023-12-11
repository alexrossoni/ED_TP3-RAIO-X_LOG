// Fila.c
#include "fila.h"
#include "paciente.h"
#include <stdlib.h>

// Implementação das funções do TAD da fila
void inicializarFila(Fila *fila, int capacidade) {
    fila->elementos = (int *)malloc(sizeof(int) * capacidade);
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    fila->frente = 0;
    fila->tras = -1;
}

void enfileirar(Fila *fila, int elemento) {
    if (fila->tamanho < fila->capacidade) {
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->elementos[fila->tras] = elemento;
        fila->tamanho++;
    }
}

int desenfileirar(Fila *fila) {
    int elemento = -1;
    if (fila->tamanho > 0) {
        elemento = fila->elementos[fila->frente];
        fila->frente = (fila->frente + 1) % fila->capacidade;
        fila->tamanho--;
    }
    return elemento;
}

int tamanhoFila(Fila *fila) {
    return fila->tamanho;
}

int filaVazia(Fila *fila) {
    return (fila->tamanho == 0);
}

void destruirFila(Fila *fila) {
    free(fila->elementos);
}

Exame desenfileirarExame(Fila *fila, Paciente listaPacientes[], ListaExames lista) {
    Exame exameVazio = { -1, -1, -1, -1 };  // Exame "vazio" para indicar que a fila está vazia
    if (filaVazia(fila)) {
        return exameVazio;
    }

    int idPaciente = fila->elementos[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;

    // Pegando informações do paciente com o ID
    Paciente paciente = listaPacientes[idPaciente];

    Exame exame = buscarExamePorId(lista, paciente.id);

    return exame;
}
