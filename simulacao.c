// Simulacao.c
#include "Simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h>

// Implementação das funções relacionadas à simulação
Simulacao iniciarSimulacao() {
    Simulacao simulacao;

    // Inicializa as filas
    inicializarFila(&simulacao.filaExames, 100); // Tamanho da fila de exames
    inicializarFila(&simulacao.filaLaudos, 100); // Tamanho da fila de laudos

    // Inicializa os radiologistas
    for (int i = 0; i < 3; i++) {
        simulacao.radiologistas[i] = criarRadiologista();
    }

    // Inicializa os aparelhos
    for (int i = 0; i < 5; i++) {
        simulacao.aparelhos[i] = criarAparelho();
    }

    simulacao.tempoTotalExames = 0;
    simulacao.tempoTotalLaudos = 0;

    return simulacao;
}
