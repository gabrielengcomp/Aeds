#include <stdlib.h>
#include <stdio.h>
#include "sorts.h"    


// quick sort

void troca(int vet[], int a, int b){
    int temp = vet[a];
    vet[a] = vet[b];
    vet[b] = temp;
}

void troca_aluno(Aluno* vet[], int i, int j){
    Aluno* temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;
}

void troca_somatorio(Aluno* vetAlunos[], float vetSomatorio[], int i, int j){
    float tempSomatorio = vetSomatorio[i];
    Aluno* tempAluno = vetAlunos[i];
    
    vetSomatorio[i] = vetSomatorio[j];
    vetAlunos[i] = vetAlunos[j];
    
    vetSomatorio[j] = tempSomatorio;
    vetAlunos[j] = tempAluno;
}

int particiona(int vet[], int inicio, int fim){
	int pivo = vet[fim]; ;
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

int particiona_nome(Aluno* vet[], int inicio, int fim){
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

int particiona_somatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim){
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

void quickSortMatricula(int vet[], int inicio, int fim){
    if (inicio < fim) {

        int pivo = particiona(vet, inicio, fim);
        
        quickSortMatricula(vet, inicio, pivo - 1);
        quickSortMatricula(vet, pivo + 1, fim);
    }
}

void quickSortNome(Aluno* vet[], int inicio, int fim){
    if (inicio < fim) {

        int pivo = particiona_nome(vet, inicio, fim);
        
        quickSortNome(vet, inicio, pivo - 1);
        quickSortNome(vet, pivo + 1, fim);
    }
}

void quickSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim){
    if (inicio < fim) {
        int pivo = particiona_somatorio(vetSomatorio, vetAlunos, inicio, fim);
        quickSortSomatorio(vetSomatorio, vetAlunos, inicio, pivo - 1);
        quickSortSomatorio(vetSomatorio, vetAlunos, pivo + 1, fim);
    }
}

float somatorionotas(Avaliacoes *avaliacao){
    float soma = 0;
    Avaliacoes *atual = avaliacao;
    while (atual != NULL) {
        soma += atual->notas;
        atual = atual->prox;
    }
    return soma;
}
void insertionSortMatricula(int vet[], int n){
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

void insertionSortNome(Aluno* vet[], int n){
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

void insertionSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int n){
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
