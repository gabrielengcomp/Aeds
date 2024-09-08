#ifndef __SORTS_H__
#define __SORTS_H__

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

#endif