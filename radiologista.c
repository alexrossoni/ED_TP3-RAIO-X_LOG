// Radiologista.c
#include "radiologista.h"
#include <stdlib.h>
#include <stdio.h>

// Implementação das funções do TAD do radiologista
Radiologista criarRadiologista() {
    Radiologista radiologista;
    radiologista.disponivel = 1;  // Inicialmente, o radiologista está disponível
    return radiologista;
}

int radiologistaDisponivel(Radiologista *radiologista) {
    return radiologista->disponivel;
}

void ocuparRadiologista(Radiologista *radiologista) {
    radiologista->disponivel = 0;  // Ocupa o radiologista
}

void liberarRadiologista(Radiologista *radiologista) {
    radiologista->disponivel = 1;  // Libera o radiologista
}

int encontrarRadiologistaDisponivel(Radiologista *arrayRadiologistas, int tamanhoArray) {
    for (int i = 0; i < tamanhoArray; i++) {
        if (radiologistaDisponivel(&arrayRadiologistas[i])) {
            return i;
        }
    }

    // Se nenhum radiologista estiver disponível, retornar um radiologista com disponibilidade igual a 0
    Radiologista radiologistaNaoDisponivel = {0};
    return radiologistaNaoDisponivel.disponivel;
}
