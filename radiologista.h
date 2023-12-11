// Radiologista.h
#ifndef RADIOLOGISTA_H
#define RADIOLOGISTA_H

// Estrutura do radiologista
typedef struct {
    int disponivel;  // Flag para indicar a disponibilidade do radiologista
} Radiologista;

// Protótipos das funções relacionadas ao radiologista
Radiologista criarRadiologista();
int radiologistaDisponivel(Radiologista *radiologista);
void ocuparRadiologista(Radiologista *radiologista);
void liberarRadiologista(Radiologista *radiologista);
int encontrarRadiologistaDisponivel(Radiologista *arrayRadiologistas, int tamanhoArray);

#endif
