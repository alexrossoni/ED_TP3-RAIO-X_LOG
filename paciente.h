// Paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

// Estrutura do paciente
typedef struct {
    char nome[50];
    char cpf[15];
    int idade;
    int id;
} Paciente;

// Protótipos das funções relacionadas ao paciente
Paciente criarPaciente(char nome[], char cpf[], int idade, int id);
void exibirPaciente(Paciente paciente);
Paciente gerarPacienteAleatorio(int id);

#endif
