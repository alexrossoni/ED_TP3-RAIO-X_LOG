// Paciente.c
#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação das funções do TAD do paciente
Paciente criarPaciente(char nome[], char cpf[], int idade, int id) {
    Paciente paciente;

    // Copia as informações para a estrutura do paciente
    strcpy(paciente.nome, nome);
    strcpy(paciente.cpf, cpf);
    paciente.idade = idade;
    paciente.id = id;

    return paciente;
}

void exibirPaciente(Paciente paciente) {
    printf("ID: %d\n", paciente.id);
    printf("Nome: %s\n", paciente.nome);
    printf("CPF: %s\n", paciente.cpf);
    printf("Idade: %d\n", paciente.idade);
}

Paciente gerarPacienteAleatorio(int id) {
    Paciente paciente;

    // Nomes fictícios para simplificar
    char nomes[][20] = {"Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Henry", "Ivy", "Jack"};
    
    // Gera um nome aleatório
    strcpy(paciente.nome, nomes[rand() % (sizeof(nomes) / sizeof(nomes[0]))]);

    // Gera um CPF fictício (apenas para exemplo)
    sprintf(paciente.cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);

    // Gera uma idade aleatória entre 1 e 100
    paciente.idade = rand() % 100 + 1;

    // Atribui o ID fornecido
    paciente.id = id;

    return paciente;
}
