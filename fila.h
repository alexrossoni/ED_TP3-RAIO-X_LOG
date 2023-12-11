// Fila.h
#ifndef FILA_H
#define FILA_H

#include "exame.h"
#include "paciente.h"

// Estrutura da fila
typedef struct {
    int *elementos;
    int tamanho;
    int capacidade;
    int frente;
    int tras;
} Fila;

// Protótipos das funções relacionadas à fila
void inicializarFila(Fila *fila, int capacidade);
void enfileirar(Fila *fila, int elemento);
int desenfileirar(Fila *fila);
Exame desenfileirarExame(Fila *fila, Paciente listaPacientes[], ListaExames lista);
int tamanhoFila(Fila *fila);
int filaVazia(Fila *fila);
void destruirFila(Fila *fila);

#endif
