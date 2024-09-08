# Sistema de Gerenciamento de Alunos

Este projeto é um sistema de gerenciamento de alunos em C que permite cadastrar alunos, gerenciar suas avaliações, realizar chamadas, gerar relatórios e ordenar dados utilizando diferentes algoritmos de ordenação.

## Estruturas de Dados (TAD)

### 1. `struct Avaliacoes`

A estrutura `Avaliacoes` armazena as notas de cada aluno. Cada aluno pode ter uma lista encadeada de avaliações, sendo que cada avaliação armazena a nota recebida.

```c
typedef struct avaliacoes {
    float notas;               // Nota da avaliação
    float nMax;                // Nota máxima possível da avaliação
    struct avaliacoes *prox;   // Ponteiro para a próxima avaliação
} Avaliacoes;
```

### 2. `struct Aluno`

A estrutura `Aluno` armazena as informações sobre cada aluno, incluindo sua matrícula, nome, curso, ano de ingresso, frequência (presenças/ausências nas aulas) e uma lista de avaliações associadas ao aluno.

```c
typedef struct aluno {
    int matricula;                 // Matrícula do aluno
    char nome[30];                 // Nome do aluno
    char curso[20];                // Curso que o aluno está matriculado
    int ingresso;                  // Ano de ingresso
    int frequencia[18];            // Presenças e ausências nas aulas (0 para presente, 1 para ausente)
    Avaliacoes *avaliacao;         // Lista encadeada de avaliações do aluno
    struct aluno *prox;            // Ponteiro para o próximo aluno na lista
} Aluno;
```

### 3. `struct Lista_alunos`

A estrutura `Lista_alunos` contém a lista encadeada de alunos e o número de aulas já ministradas. Serve como ponto de entrada para gerenciar a frequência dos alunos e o controle geral do sistema.

```c
typedef struct lista {
    Aluno *cabeca;  // Ponteiro para o primeiro aluno da lista
    int aula;       // Número de aulas ministradas, utilizado para controlar a frequência
} Lista_alunos;
```

## Funcionalidades

### 1. `verificar_frequencia(Aluno *aluno)`

Função que calcula o número total de faltas de um aluno, somando as ausências em seu vetor de frequência.

```c
int verificar_frequencia(Aluno *aluno) {
    int faltas = 0;
    for (int i = 0; i < 18; i++) {
        faltas += aluno->frequencia[i];
    }
    return faltas;
}
```

### 2. `realizar_chamada(Lista_alunos *lista)`

Função para realizar a chamada dos alunos. O usuário insere 0 para presente e 1 para ausente. Se um aluno acumular 10 ou mais faltas, é exibido um aviso de reprovação por frequência.

```c
void realizar_chamada(Lista_alunos *lista) {
    Aluno *no = lista->cabeca;
    lista->aula++;

    printf("\nREALIZANDO CHAMADA\n0 para presente\n1 para ausente\n");

    while (no != NULL) {
        printf("%s | %i: ", no->nome, no->matricula);
        scanf("%i", &no->frequencia[lista->aula]);
        if (verificar_frequencia(no) >= 10) {
            printf("\n!! ALUNO REPROVADO POR FREQUENCIA !!\n");
        }
        no = no->prox;
    }
}
```

### 3. Funções de Troca

Estas funções auxiliam nos algoritmos de ordenação, trocando elementos nos vetores.

- **`troca(int vet[], int a, int b)`**: Troca dois elementos em um vetor de inteiros.

  ```c
  void troca(int vet[], int a, int b) {
      int temp = vet[a];
      vet[a] = vet[b];
      vet[b] = temp;
  }
  ```

- **`troca_aluno(Aluno* vet[], int i, int j)`**: Troca dois elementos em um vetor de alunos.

  ```c
  void troca_aluno(Aluno* vet[], int i, int j) {
      Aluno* temp = vet[i];
      vet[i] = vet[j];
      vet[j] = temp;
  }
  ```

- **`troca_somatorio(Aluno* vetAlunos[], float vetSomatorio[], int i, int j)`**: Troca os alunos e seus respectivos somatórios de notas entre duas posições.

  ```c
  void troca_somatorio(Aluno* vetAlunos[], float vetSomatorio[], int i, int j) {
      float tempSomatorio = vetSomatorio[i];
      Aluno* tempAluno = vetAlunos[i];
      
      vetSomatorio[i] = vetSomatorio[j];
      vetAlunos[i] = vetAlunos[j];
      
      vetSomatorio[j] = tempSomatorio;
      vetAlunos[j] = tempAluno;
  }
  ```

### 4. Algoritmos de Partição para QuickSort

Estas funções são utilizadas pelo QuickSort para dividir os vetores em sub-vetores menores.

- **`particiona(int vet[], int inicio, int fim)`**: Particiona um vetor de inteiros.

  ```c
  int particiona(int vet[], int inicio, int fim){
      int pivo = vet[fim];
      int indice = inicio;
      
      for(int i = inicio; i < fim; i++){
          if(vet[i] <= pivo){
              troca(vet, i, indice);
              indice++;
          }
      }
      
      troca(vet, indice, fim);
      
      return indice;
  }
  ```

- **`particiona_nome(Aluno* vet[], int inicio, int fim)`**: Particiona um vetor de alunos com base em seus nomes.

  ```c
  int particiona_nome(Aluno* vet[], int inicio, int fim) {
      Aluno* pivo = vet[fim];
      int indice = inicio;
      
      for (int i = inicio; i < fim; i++) {
          if (strcmp(vet[i]->nome, pivo->nome) < 0) {
              troca_aluno(vet, i, indice);
              indice++;
          }
      }

      troca_aluno(vet, indice, fim);
      
      return indice;
  }
  ```

- **`particiona_somatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim)`**: Particiona um vetor de somatórios de notas.

  ```c
  int particiona_somatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim) {
      float pivo = vetSomatorio[fim];
      int indice = inicio;

      for (int i = inicio; i < fim; i++) {
          if (vetSomatorio[i] <= pivo) {
              troca_somatorio(vetAlunos, vetSomatorio, i, indice);
              indice++;
          }
      }

      troca_somatorio(vetAlunos, vetSomatorio, indice, fim);
      return indice;
  }
  ```

### 5. Algoritmos de Ordenação

Implementações dos algoritmos QuickSort e Insertion Sort para diferentes tipos de dados.

- **QuickSort**:

  - **`quickSortMatricula(int vet[], int inicio, int fim)`**: Ordena um vetor de inteiros (matrículas).

    ```c
    void quickSortMatricula(int vet[], int inicio, int fim) {
        if (inicio < fim) {
            int pivo = particiona(vet, inicio, fim);
            quickSortMatricula(vet, inicio, pivo - 1);
            quickSortMatricula(vet, pivo + 1, fim);
        }
    }
    ```

  - **`quickSortNome(Aluno* vet[], int inicio, int fim)`**: Ordena um vetor de alunos pelo nome.

    ```c
    void quickSortNome(Aluno* vet[], int inicio, int fim) {
        if (inicio < fim) {
            int pivo = particiona_nome(vet, inicio, fim);
            quickSortNome(vet, inicio, pivo - 1);
            quickSortNome(vet, pivo + 1, fim);
        }
    }
    ```

  - **`quickSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim)`**: Ordena os somatórios das notas de alunos.

    ```c
    void quickSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim) {
        if (inicio < fim) {
            int pivo = particiona_somatorio(vetSomatorio, vetAlunos, inicio, fim);
            quickSortSomatorio(vetSomatorio, vetAlunos, inicio, pivo - 1);
            quickSortSomatorio(vetSomatorio, vetAlunos, pivo + 1, fim);
        }
    }
    ```

- **InsertionSort**:

  - **`insertionSortMatricula(int vet[], int n)`**: Ordena um vetor de matrículas.

    ```c
    void insertionSortMatricula(int vet[], int n) {
        for (int i = 1; i < n; i++) {
            int chave = vet[i];
            int j = i - 1;
            while (j >= 0 && vet[j] > chave) {
                vet[j + 1] = vet[j];
                j = j - 1;
            }
            vet[j + 1] = chave;
        }
    }
    ```

  - **`insertionSortNome(Aluno* vet[], int n)`**: Ordena um vetor de alunos por nome.

    ```c
    void insertionSortNome(Aluno* vet[], int n) {
        for (int i = 1; i < n; i++) {
            Aluno* chave = vet[i];
            int j = i - 1;
            while (j >= 0 && strcmp(vet[j]->nome, chave->nome) > 0) {
                vet[j + 1] = vet[j];
                j = j - 1;
            }
            vet[j + 1] = chave;
        }
    }
    ```

  - **`insertionSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int n)`**: Ordena os somatórios das notas de alunos.

    ```c
    void insertionSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int n) {
        for (int i = 1; i < n; i++) {
            float chaveSomatorio = vetSomatorio[i];
            Aluno* chaveAluno = vetAlunos[i];
            int j = i - 1;
            while (j >= 0 && vetSomatorio[j] > chaveSomatorio) {
                vetSomatorio[j + 1] = vetSomatorio[j];
                vetAlunos[j + 1] = vetAlunos[j];
                j = j - 1;
            }
            vetSomatorio[j + 1] = chaveSomatorio;
            vetAlunos[j + 1] = chaveAluno;
        }
    }
    ```

### 6. `print_ordenado(Aluno *tabela[], int tipo, int algoritmo)`

Função que imprime os dados dos alunos ordenados de acordo com o tipo de ordenação escolhido:

- **Tipo**:
  - `1`: Matrícula
  - `2`: Somatório das notas
  - `3`: Ordem alfabética (nome)
- **Algoritmo**:
  - `1`: QuickSort
  - `2`: InsertionSort

```c
void print_ordenado(Aluno *tabela[], int tipo, int algoritmo) {
    // Implementação que prepara os vetores e chama as funções de ordenação
    // Em seguida, imprime os dados ordenados
}
```

### 7. `somatorionotas(Avaliacoes *avaliacao)`

Calcula o somatório das notas de um aluno percorrendo sua lista de avaliações.

```c
float somatorionotas(Avaliacoes *avaliacao) {
    float soma = 0;
    Avaliacoes *atual = avaliacao;
    while (atual != NULL) {
        soma += atual->notas;
        atual = atual->prox;
    }
    return soma;
}
```

### 8. `relatorio_notas(Lista_alunos *lista)`

Gera um relatório com a nota máxima, mínima, e média das notas dos alunos, além de exibir as notas em ordem decrescente.

```c
void relatorio_notas(Lista_alunos *lista) {
    // Implementação que percorre os alunos e avaliações para calcular os dados estatísticos
    // Utiliza Bubble Sort para ordenar as notas em ordem decrescente
}
```

### 9. `relatorio_alunos(Aluno *tabela[])`

Gera um relatório de alunos permitindo ao usuário escolher o tipo de ordenação (matrícula, somatório de notas ou ordem alfabética) e o algoritmo (QuickSort ou InsertionSort).

```c
void relatorio_alunos(Aluno *tabela[]) {
    int op, algoritmo;
    printf("\n___________________________\n");
    printf("Como deseja realizar a ordenação?\n[1] Por matrícula\n[2] Por somatório das notas\n[3] Por ordem alfabética\n");
    printf("___________________________\n");
    printf("Selecione: ");
    scanf("%d", &op);
    printf("\n___________________________\n");
    printf("Escolha o algoritmo de ordenação:\n[1] Quicksort\n[2] Insertion sort\n");
    printf("___________________________\n");
    printf("Selecione: ");
    scanf("%d", &algoritmo);
    printf("\n___________________________\n");
    if (op >= 1 && op <= 3 && (algoritmo == 1 || algoritmo == 2)) {
        print_ordenado(tabela, op, algoritmo);
    } else {
        printf("Opção Inválida\n");
    }
}
```

### 10. `menu()`

Exibe o menu principal do sistema, com opções para cadastrar alunos, registrar avaliações, realizar chamada, gerar relatórios e sair do programa.

```c
void menu() {
    printf("\n___________________________\n");
    printf("[1] Cadastrar Aluno\n");
    printf("[2] Cadastrar Avaliação\n");
    printf("[3] Chamada\n");
    printf("[4] Relatório de alunos\n");
    printf("[5] Relatório de notas\n");
    printf("[6] Exibir Lista de Alunos\n");
    printf("[7] Exibir Tabela Hash\n");
    printf("[0] Sair\n");
    printf("___________________________\n");
}
```

### 11. `main()`

Função principal que inicializa a lista de alunos e a tabela hash e chama o menu para o controle do sistema.

```c
int main() {
    Lista_alunos Lista_de_alunos;
    Lista_de_alunos.cabeca = NULL;
    Lista_de_alunos.aula = 0;

    Aluno *tabela[TAM] = {NULL};
    int opc = 0;

    printf("\nTRABALHO DE ALGORITMOS E ESTRUTURAS DE DADOS\n");
    printf("\nALUNOS: AUGUSTO FREITAS, GABRIEL HENRIQUE PIRES, VICENTE ZANATTA\n");
    printf("SEMESTRE: 24.1\n");

    while (1) {
        menu();
        printf("Selecione: ");
        scanf("%i", &opc);

        switch (opc) {
            case 1:
                cadastrar_aluno(&Lista_de_alunos, tabela);
                break;
            // Demais casos...
            case 0:
                return 0;
            default:
                printf("Opção Inválida\n");
                break;
        }
    }
    return 0;
}
```

## Como Executar

1. **Clone o repositório**:

   ```bash
   git clone https://github.com/seu_usuario/seu_repositorio.git
   ```

2. **Compile o código** usando `gcc` ou outro compilador de C:

   ```bash
   gcc main.c -o sistema
   ```

3. **Execute o programa**:

   ```bash
   ./sistema
   ```

## Autores

- **Augusto Freitas**
- **Gabriel Henrique Pires**
- **Vicente Zanatta**

### Semestre

- **24.1**

---
