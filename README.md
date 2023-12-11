# Trabalho Prático 2 de Estrutura de Dados: Simulação de Realização de Exames de Raio-X

Este repositório contém um programa em C que implementa a simulação de um processo de realização de exames de raio-X em um hospital, com ênfase na organização da fila para laudo médico. O programa é destinado à disciplina de Estrutura de Dados e foi desenvolvido no ambiente Ubuntu 22.04 com GCC v11 (É **fortemente recomendável** a execução do programa em um ambiente de mesma configuração).

---

## ▶️ Executando o Programa

Para executar o programa, siga os passos abaixo:

### Pré-requisitos

1. Certifique-se de que você tenha o GCC v11+ instalado no seu sistema. Você pode verificar se o GCC está instalado executando o seguinte comando no terminal:

```bash
gcc --version
```

  - Se o GCC não estiver instalado, você pode instalá-lo com o seguinte comando:
  ```bash
  sudo apt install gcc
  ```

2. Certifique-se de que o utilitário Make esteja instalado:

```bash
make --version
```

  - Se o Make estiver instalado, você verá informações sobre a versão. Caso contrário, você pode instalá-lo usando o seguinte comando:
  ```bash
  sudo apt-get install make
  ```

### Compilando o Programa

1. Clone este repositório para o seu sistema:
```bash
git clone https://github.com/alexrossoni/ED_TP2-RAIO-X.git
```

2. Acesse o diretório do projeto:
```bash
cd ED_TP2-RAIO-X
```

3. Compile o programa usando o Makefile:
```bash
make
```

### Executar o Programa

Após a compilação, você pode executar o programa da seguinte maneira:
```bash
./simulacao_raio_x
```

---

## 💡 Principais Decisões de Implementação

#### Módulos e Arquivos Separados
A implementação foi estruturada usando múltiplos arquivos para promover a modularidade e facilitar a manutenção do código. Cada entidade essencial tem seu próprio conjunto de arquivos (.h e .c).

#### Estrutura de Dados
O projeto utiliza algumas estruturas de dados para a simulação, sendo elas: Simulação, Paciente, Exame, Aparelho, Radiologista e Fila.

  - Simulação: É a estrutura principal para a simulação, foi criada para facilitar a organização do código;
  - Paciente: Estrutura que representa um paciente do hospital, contém Nome, CPF, Idade e ID;
  - Exame: Estrutura que representao um exame realizado em um paciente, contém ID do paciente, o instante de tempo em que o registro foi gerado e a condição (normal ou patológica) sugerida pela simulação;
  - Aparelho: Estrutura que representa um aparelho de raio-x, contém apenas seu status que pode estar disponível ou não;
  - Radiologista: Estrutura que representa um Radiologista, contém apenas seu status que pode estar disponível ou não;
  - Fila: Estrutura padrão de fila para controle de espera dos pacientes;

#### Alocação de Memória
Para a alocação de memória, o projeto utiliza funções malloc para alocar memória na funções necessárias. É importante notar que o código trata possíveis erros de alocação de memória, exibindo mensagens de erro e encerrando o programa em caso de falha na alocação.

#### Gerenciamento de Memória
O projeto inclui uma função destruirFila para liberar a memória alocada para as filas. Essa função é chamada para evitar vazamento de memória quando as imagens não são mais necessárias.

#### Fila de Exames e Laudos
Utiliza-se uma fila simples para armazenar os exames a serem realizados e outra fila para os laudos a serem emitidos. Isso reflete o fluxo de pacientes em um hospital e garante que os exames sejam atendidos na ordem de chegada.

#### Simulação de Eventos Temporizados
O simulador opera em unidades de tempo. A cada iteração do loop principal (cada "tempo"), verifica-se a chegada de pacientes, a realização de exames e a emissão de laudos. Isso simula o fluxo de eventos em um hospital ao longo do tempo. Também foi utilizada a função de espera sleep() para controlar a velocidade de execução e exibição das informações.

#### Métricas de Desempenho
Foram implementadas métricas para avaliar o desempenho do sistema, incluindo o tempo médio de laudo, o tempo médio de laudo por patologia e a quantidade de exames realizados após o limite de tempo estabelecido. Essas métricas fornecem dados sobre a eficiência e a capacidade do sistema.

#### Saída Formatada
A saída foi formatada de maneira clara para facilitar a interpretação. Mensagens informativas, como tempo médio de laudo por patologia, são exibidas com precisão para tornar os resultados compreensíveis.

---

## 👨🏽‍💻 Autor

Alex Rossoni Junior
