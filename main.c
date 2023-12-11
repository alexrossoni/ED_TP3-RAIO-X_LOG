#include "simulacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    // Inicializa a simulação
    Simulacao simulacao = iniciarSimulacao();
    Log *log = create_log();
    char msg_log[255];

    // Lista de pacientes
    Paciente listaPacientes[100];
    int numeroPacientes = sizeof(listaPacientes) / sizeof(listaPacientes[0]);

    // Preenche a lista de possíveis pacientes com dados aleatórios
    for (int i = 0; i < numeroPacientes; i++) {
        listaPacientes[i] = gerarPacienteAleatorio(i);
    }

    srand((unsigned int)time(NULL));  // Inicializa a semente para geração de números aleatórios

    int tempoTotalSimulacao = 43200; // Número total de unidades de tempo para a simulação

    ListaExames listaExames;
    listaExames.cabeca = NULL;
    
    // Tempo de laudos de cada patologia
    int tempoTotalLaudosNormal = 0;
    int tempoTotalLaudosBronquite = 0;
    int tempoTotalLaudosPneumonia = 0;
    int tempoTotalLaudosFraturaFemur = 0;
    int tempoTotalLaudosApendicite = 0;

    // Quantidade total de laudos de cada patologia
    int totalLaudosNormal = 0;
    int totalLaudosBronquite = 0;
    int totalLaudosPneumonia = 0;
    int totalLaudosFraturaFemur = 0;
    int totalLaudosApendicite = 0;

    // QUantidade total de laudos
    int totalLaudos = 0;

    // Total de laudos feitos após o limite de tempo
    int totalLaudosAtrasados = 0;

    // Controle da simulação para cada unidade de tempo
    int tempo = 0;
    int tempoMetricas = 0;

    while (tempo < tempoTotalSimulacao) {
        // 1. Chegada de pacientes com probabilidade de 20%
        if (rand() % 100 < 20) {
            int idPaciente = listaPacientes[rand() % 100].id;
            sprintf(msg_log, "Instante: %d | O paciente com ID %d foi chegou ao hospital.", tempo, idPaciente);
            log_event(log, msg_log);
            msg_log[0] = '\0';

            enfileirar(&simulacao.filaExames, idPaciente);
            sprintf(msg_log, "Instante: %d | O paciente com ID %d foi foi para fila de exames.", tempo, idPaciente);
            log_event(log, msg_log);
            msg_log[0] = '\0';
        }
        
        int aparelhoIndex;
        int radiologistaIndex;

        // 2. Realização de exames
        aparelhoIndex = encontrarAparelhoDisponivel(simulacao.aparelhos, 5);
        if (!filaVazia(&simulacao.filaExames)) {
            ocuparAparelho(&simulacao.aparelhos[aparelhoIndex]);
            int idPaciente = desenfileirar(&simulacao.filaExames); // Retira o paciente da fila de exames e retorna seu ID
            sprintf(msg_log, "Instante: %d | O paciente com ID %d foi realizar o exame.", tempo, idPaciente);
            log_event(log, msg_log);
            msg_log[0] = '\0';

            int tempoExame = rand() % 6 + 5; // Tempo do exame entre 5 e 10 unidades
            simulacao.tempoTotalExames += tempoExame;

            // Soma o tempo de exame ao tempo de simulação
            tempo += tempoExame;

            // Cada patologia/condição foi separada por índices para facilitar a codificação
            int condicao = rand() % 100 < 30 ? 1 : // 1 - Saúde Normal
                            rand() % 100 < 20 ? 2 : // 2 - Bronquite
                            rand() % 100 < 20 ? 3 : // 3 - Pneumonia
                            rand() % 100 < 15 ? 4 : // 4 - Fratura de Fêmur
                            5;                      // 5 - Apendicite

            Exame exame = criarExame(idPaciente, tempoExame, condicao, 0); // 0 - Não concluído, exame iniciado com status não concluído
            inserirExame(&listaExames, exame); // Insere o exame na lista de exames realizados
            sprintf(msg_log, "Instante: %d | Exame do paciente com ID %d foi realizado com sucesso!", tempo, idPaciente);
            log_event(log, msg_log);
            msg_log[0] = '\0';

            enfileirar(&simulacao.filaLaudos, exame.id); // Põe o exame na fila para laudo

            liberarAparelho(&simulacao.aparelhos[aparelhoIndex]);
        }

        // 3. Realização de laudos
        radiologistaIndex = encontrarRadiologistaDisponivel(simulacao.radiologistas, 3);
        if (!filaVazia(&simulacao.filaLaudos)) {
            ocuparRadiologista(&simulacao.radiologistas[radiologistaIndex]);

            Exame exame = desenfileirarExame(&simulacao.filaLaudos, listaPacientes, listaExames);
            sprintf(msg_log, "Instante: %d | O paciente com ID %d foi realizar o laudo.", tempo, exame.id);
            log_event(log, msg_log);
            msg_log[0] = '\0';

            atualizarConcluido(&listaExames, exame.id, 1); // 1 - Concluído, atualiza o status do exame para concluído

            int tempoLaudo = rand() % 21 + 10; // Tempo do laudo entre 10 e 30 unidades
            simulacao.tempoTotalLaudos += tempoLaudo;

            int tempoEntregaLaudo = rand() % 10000 + 1; // Gerando um tempo de entrega do laudo (menor que 7200 Un. de tempo está dentro do prazo, maior que 7200 Un. de tempo esta atrasado)
            if (tempoEntregaLaudo > 7200) {
                totalLaudosAtrasados += 1;
            }

            // Soma o tempo de preparo do laudo e o tempo de entrega ao tempo de simulação
            tempo += tempoLaudo + tempoEntregaLaudo;

            // Aqui adicionamos o tempo de cada exame de acordo com a patologia e suas quantidades para usar no calculo de métricas, lembrando que separei cada patologia por um índice:
            // 1 - Saúde Normal;
            // 2 - Bronquite;
            // 3 - Pneumonia;
            // 4 - Fratura de Fêmur;
            // 5 - Apendicite
            if (exame.condicao == 1) {
                tempoTotalLaudosNormal += tempoLaudo;
                totalLaudosNormal++;
            } else if (exame.condicao == 2) {
                tempoTotalLaudosBronquite += tempoLaudo;
                totalLaudosBronquite++;
            } else if (exame.condicao == 3) {
                tempoTotalLaudosPneumonia += tempoLaudo;
                totalLaudosPneumonia++;
            } else if (exame.condicao == 4) {
                tempoTotalLaudosFraturaFemur += tempoLaudo;
                totalLaudosFraturaFemur++;
            } else if (exame.condicao == 5) {
                tempoTotalLaudosApendicite += tempoLaudo;
                totalLaudosApendicite++;
            }

            sprintf(msg_log, "Instante: %d | Laudo do paciente com ID %d foi realizado com sucesso!", tempo, exame.id);
            log_event(log, msg_log);
            msg_log[0] = '\0';

            liberarRadiologista(&simulacao.radiologistas[radiologistaIndex]);
        }

        // 4. Atualização do relatório de métricas a cada 10 unidades de tempo
        if (tempoMetricas % 10 == 0) {
            // Métricas de desempenho aqui
            totalLaudos = totalLaudosNormal + totalLaudosBronquite + totalLaudosPneumonia + totalLaudosFraturaFemur + totalLaudosApendicite;
            printf("\n------Atualização do relatório de métricas:\n\n");

            // Tempo médio de laudo, tempo médio de laudo por patologia, quantidade de exames após o limite de tempo
            if (totalLaudos > 0) {
                printf("---Tempo médio de laudos: %d unid. tempo\n", simulacao.tempoTotalLaudos / totalLaudos);
                printf("---Laudos entregues em atraso: %d\n\n", totalLaudosAtrasados);
                printf("--Tempo médio de laudos por patologia:\n");
                if (totalLaudosNormal > 0) {
                    printf("-Tempo médio de laudo (Normal): %d unid. tempo | Qtd. de laudos: %d\n", tempoTotalLaudosNormal / totalLaudosNormal, totalLaudosNormal);
                } else {
                    printf("-Tempo médio de laudo (Normal): Não há dados\n");
                };
                if (totalLaudosBronquite > 0) {
                    printf("-Tempo médio de laudo (Bronquite): %d unid. tempo | Qtd. de laudos: %d\n", tempoTotalLaudosBronquite / totalLaudosBronquite, totalLaudosBronquite);
                } else {
                    printf("-Tempo médio de laudo (Bronquite): Não há dados\n");
                };
                if (totalLaudosPneumonia > 0) {
                    printf("-Tempo médio de laudo (Pneumonia): %d unid. tempo | Qtd. de laudos: %d\n", tempoTotalLaudosPneumonia / totalLaudosPneumonia, totalLaudosPneumonia);
                } else {
                    printf("-Tempo médio de laudo (Pneumonia): Não há dados\n");
                };
                if (totalLaudosFraturaFemur > 0) {
                    printf("-Tempo médio de laudo (Fratura de Femur): %d unid. tempo | Qtd. de laudos: %d\n", tempoTotalLaudosFraturaFemur / totalLaudosFraturaFemur, totalLaudosFraturaFemur);
                } else {
                    printf("-Tempo médio de laudo (Fratura de Femur): Não há dados\n");
                };
                if (totalLaudosApendicite > 0) {
                    printf("-Tempo médio de laudo (Apendicite): %d unid. tempo | Qtd. de laudos: %d\n", tempoTotalLaudosApendicite / totalLaudosApendicite, totalLaudosApendicite);
                } else {
                    printf("-Tempo médio de laudo (Apendicite): Não há dados\n");
                };
            } else {
                printf("--Ainda não há métricas computadas.\n");
            }
        }

        tempoMetricas++;
        tempo++;

        sleep(1);
    }

    // Libera a memória utilizada pelas filas
    destruirFila(&simulacao.filaLaudos);
    destruirFila(&simulacao.filaExames);

    save_log_to_file(log, "log.txt");

    printf("\n---Fim de expediente no hospital.\n");

    return 0;
}
