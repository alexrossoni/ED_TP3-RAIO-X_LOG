// Exame.h
#ifndef EXAME_H
#define EXAME_H

// Estrutura do exame
typedef struct {
    int id;
    int instante;
    int condicao;
    int concluido; // 1 - Sim / 0 - Não
} Exame;

// Nó da lista de exames
typedef struct Nodo {
    Exame exame;
    struct Nodo *prox;
} Nodo;

// Lista de exames
typedef struct {
    Nodo *cabeca;
} ListaExames;

// Estrutura do aparelho
typedef struct {
    int disponivel;  // Flag para indicar a disponibilidade do aparelho
} Aparelho;

// Protótipos das funções relacionadas ao exame
Exame criarExame(int id, int instante, int condicao, int concluido);
void exibirExame(Exame exame);

// Protótipos das funções relacionadas a lista de exames
void inserirExame(ListaExames *lista, Exame novoExame);
void removerExame(ListaExames *lista, int id);
void atualizarConcluido(ListaExames *lista, int id, int novoConcluido);
Exame buscarExamePorId(ListaExames lista, int id);

// Protótipos das funções relacionadas ao aparelho
Aparelho criarAparelho();
int aparelhoDisponivel(Aparelho *aparelho);
void ocuparAparelho(Aparelho *aparelho);
void liberarAparelho(Aparelho *aparelho);
int encontrarAparelhoDisponivel(Aparelho *arrayAparelhos, int tamanhoArray);


#endif
