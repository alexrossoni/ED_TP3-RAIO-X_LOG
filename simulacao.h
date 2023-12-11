// Simulacao.h
#ifndef SIMULACAO_H
#define SIMULACAO_H

#include "paciente.h"
#include "fila.h"
#include "exame.h"
#include "radiologista.h"

// Estrutura principal para a simulação
typedef struct {
    Fila filaExames;
    Fila filaLaudos;
    Radiologista radiologistas[3];
    Aparelho aparelhos[5];
    int tempoTotalExames;
    int tempoTotalLaudos;
} Simulacao;

// Protótipos das funções relacionadas à simulação
Simulacao iniciarSimulacao();

#endif
