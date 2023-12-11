// Simulacao.c
#include "simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Implementação das funções relacionadas ao logging
Log* create_log() {
    Log *l = (Log *)malloc(sizeof(Log));
    l->count = 0;
    return l;
}

// Função para registrar eventos no log
void log_event(Log *log, const char *message) {
    if (log->count < 1000) {
        strncpy(log->events[log->count].message, message, sizeof(log->events[log->count].message));
        log->events[log->count].timestamp = time(NULL);
        log->count++;
    } else {
        printf("Arquivo de logging cheio. Nao e possivel adicionar registros.\n");
    }
}

// Função para salvar o log em um arquivo .txt
void save_log_to_file(const Log *log, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < log->count; i++) 
        {
            fprintf(file, "--- LOG TIMESTAMP %ld\n", log->events[i].timestamp);
            fprintf(file, "- %s\n", log->events[i].message);
        }
        fclose(file);

    } else {
        printf("Nao foi possivel abrir o arquivo %s de logging para registros.\n", filename);
    }
}
