// Exame.c
#include "exame.h"
#include <stdio.h>
#include <stdlib.h>

// Implementação das funções do TAD do exame
Exame criarExame(int id, int instante, int condicao, int concluido) {
    Exame exame;
    exame.id = id;
    exame.instante = instante;
    exame.condicao = condicao;
    exame.concluido = concluido;
    return exame;
}

void exibirExame(Exame exame) {
    printf("ID do Exame: %d\n", exame.id);
    printf("Instante de Tempo: %d\n", exame.instante);
    printf("Condição Sugerida: %d\n", exame.condicao);
    printf("Concluido: %d\n", exame.concluido);
    printf("\n");
}

// Implementação das funções da lista de exames
void inserirExame(ListaExames *lista, Exame novoExame) {
    Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    novoNodo->exame = novoExame;
    novoNodo->prox = lista->cabeca;
    lista->cabeca = novoNodo;
}

void removerExame(ListaExames *lista, int id) {
    Nodo *atual = lista->cabeca;
    Nodo *anterior = NULL;

    while (atual != NULL && atual->exame.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Exame com id %d não encontrado\n", id);
        return;
    }

    if (anterior == NULL) {
        // O exame a ser removido é o primeiro da lista
        lista->cabeca = atual->prox;
    } else {
        // O exame a ser removido não é o primeiro da lista
        anterior->prox = atual->prox;
    }

    free(atual);
}

void atualizarConcluido(ListaExames *lista, int id, int novoConcluido) {
    Nodo *atual = lista->cabeca;

    while (atual != NULL && atual->exame.id != id) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Exame com id %d não encontrado\n", id);
        return;
    }

    atual->exame.concluido = novoConcluido;
}

Exame buscarExamePorId(ListaExames lista, int id) {
    Nodo *atual = lista.cabeca;

    while (atual != NULL && atual->exame.id != id) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        // Retornar um exame com id -1 para indicar que não foi encontrado
        Exame exameNaoEncontrado = {-1, 0, 0, 0};
        return exameNaoEncontrado;
    }

    return atual->exame;
}

// Implementação das funções do TAD do aparelho
Aparelho criarAparelho() {
    Aparelho aparelho;
    aparelho.disponivel = 1;  // Inicialmente, o aparelho está disponível
    return aparelho;
}

int aparelhoDisponivel(Aparelho *aparelho) {
    return aparelho->disponivel;
}

void ocuparAparelho(Aparelho *aparelho) {
    aparelho->disponivel = 0;  // Ocupa o aparelho
}

void liberarAparelho(Aparelho *aparelho) {
    aparelho->disponivel = 1;  // Libera o aparelho
}

int encontrarAparelhoDisponivel(Aparelho *arrayAparelhos, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        if (aparelhoDisponivel(&arrayAparelhos[i])) {
            return i;
        }
    }

    // Se nenhum aparelho estiver disponível, retornar um radiologista com disponibilidade igual a -1
    Aparelho aparelhoNaoDisponivel = {-1};
    return aparelhoNaoDisponivel.disponivel;
}
