#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 211

typedef struct avaliacoes {
    float notas;
    float nMax;
    struct avaliacoes *prox;
} Avaliacoes;

typedef struct aluno {
    int matricula;
    char nome[30];
    char curso[20];
    int ingresso;
    int frequencia[18];
    Avaliacoes *avaliacao; // lista de tamanho variável, aumenta com o cadastro de avaliações 
    struct aluno *prox;
} Aluno;

typedef struct lista {
    Aluno *cabeca;
    int aula;
} Lista_alunos;

//Quick sort

void troca(int vet[], int a, int b);

void troca_aluno(Aluno* vet[], int i, int j);

void troca_somatorio(Aluno* vetAlunos[], float vetSomatorio[], int i, int j);

int particiona(int vet[], int inicio, int fim);

int particiona_nome(Aluno* vet[], int inicio, int fim);

int particiona_somatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim);

void quickSortMatricula(int vet[], int inicio, int fim);

void quickSortNome(Aluno* vet[], int inicio, int fim);

void quickSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim);

float somatorionotas(Avaliacoes *avaliacao);

//Insertion

void insertionSortMatricula(int vet[], int n);

void insertionSortNome(Aluno* vet[], int n);

void insertionSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int n);
