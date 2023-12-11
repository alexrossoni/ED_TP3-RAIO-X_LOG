// Simulacao.h
#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "paciente.h"
#include "fila.h"
#include "exame.h"
#include "radiologista.h"
#include <time.h>

// Estrutura principal para a simulação
typedef struct {
    Fila filaExames;
    Fila filaLaudos;
    Radiologista radiologistas[3];
    Aparelho aparelhos[5];
    int tempoTotalExames;
    int tempoTotalLaudos;
} Simulacao;

// Estruturas relativas ao logging
typedef struct {
  char message[256];
  time_t timestamp;
} LogEvent;

typedef struct {
  LogEvent events[30000];
  int count;
} Log;

// Protótipos das funções relacionadas à simulação
Simulacao iniciarSimulacao();

// Protótipos das funções relacionadas ao logging
Log* create_log(); // Função que cria o Log
void log_event(Log *log, const char *message); // Função para registrar um novo evento
void save_log_to_file(const Log *log, const char *filename); // Função que salva o log em arquivo .txt

#endif
