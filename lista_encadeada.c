#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs.h"

#define TAM 211

Aluno *acessa(Lista_alunos *L, int i) {
    Aluno *aluno = L->cabeca;
    int j = 0;
    while (aluno != NULL && j != i) {
        aluno = aluno->prox;
        j++;
    }
    return aluno;
}// acessa a matrícula do aluno referente a matrícula armazenada na lista encadeada

void excluir_aluno(Lista_alunos *L, int matricula) //desconsiderar 
{
    Aluno *atual = L->cabeca;
    Aluno *anterior = NULL;

    if (atual == NULL) {
        printf("Lista de alunos vazia. Nada a excluir.\n");
        return;
    }

    while (atual != NULL && atual->matricula != matricula) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        return;
    }

    if (anterior == NULL) {
        L->cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Aluno com matrícula %d excluído com sucesso.\n", matricula);
}

Aluno *busca(Lista_alunos *L, int x) //busca aluno na lista encadeada
{
    Aluno *aluno = L->cabeca;
    while (aluno != NULL && aluno->matricula != x) {
        aluno = aluno->prox;
    }
    return aluno;
}

void inserir_aluno(Aluno *novo_aluno, Lista_alunos *lista) {
    if (lista->cabeca == NULL)//caso lista vazia
    {
        lista->cabeca = novo_aluno;
        novo_aluno->prox = NULL;
    } else
    {
        Aluno *aux = lista->cabeca;
        while (aux->prox != NULL)//percorre a lista, ate o ultimo nó
            aux = aux->prox;

        aux->prox = novo_aluno;
        novo_aluno->prox = NULL;
    }
}// insere um nó Aluno na lista de alunos

void cadastrar_aluno(Lista_alunos *lista, Aluno *tabela[]) {
    char str[30];
    Aluno *no = malloc(sizeof(Aluno));

    if (no == NULL) {
        printf("ERRO AO ALOCAR MEMORIA");
        return;
    }

    printf("\n___________________________\n");
    printf("CADASTRO DE ALUNO (PARA VOLTAR DIGITE 0)\n");

    printf("\nMATRICULA: ");
    scanf("%i", &no->matricula);

    if (no->matricula == 0) {
        free(no);
        return;
    }

    //inserir_hash(tabela, no->matricula, no); //linha 

    getchar();

    printf("NOME: ");
    fgets(no->nome, sizeof(no->nome), stdin);
    no->nome[strcspn(no->nome, "\n")] = '\0';

    printf("CURSO: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    strcpy(no->curso, str);

    printf("ANO DE INGRESSO: ");
    scanf("%i", &no->ingresso);

    Avaliacoes *notas = malloc(sizeof(Avaliacoes)); //aloca espaço para a cabeça da lista de avaliações
    if (notas == NULL) {
        free(no);
        printf("ERRO AO ALOCAR MEMORIA PARA AS AVALIACOES! 0_0");
        return;
    }

    
    for(int i = 0; i <= lista->aula; i++) //adiciona falta ao vetor de frequencia do aluno, até o numero de chamadas realizadas
        no->frequencia[i] = 1;

    notas = NULL;

    inserir_aluno(no, lista); //linha 

    printf("\nCADASTRO REALIZADO COM SUCESSO!\n");
}// solicita os dados para o cadastro de um aluno e, se já existem avaliações no sistema, pede as notas contabilizadas. Se já existem chamadas realizadas no sistema, solicita também a presença do aluno em cada um dos dias

void inserir_avl (Aluno *no, float notaMax) //recebe o nó do aluno, a nota maxima, cria a avaliação e add na lista de avaliações do aluno
{
    float nota = 0;
    Avaliacoes *avl;
    Avaliacoes *aux;
    
    printf("\n %s| %i | NOTA: ", no->nome, no->matricula);
    scanf("%2f", &nota);

    if(nota >= 0)
    {
        avl = malloc(sizeof(Avaliacoes));
        if(avl == NULL)
        {
            printf("\n!!!ERRO AO ALOCAR MEMORIA!!!");
            return;
        }
         
        avl->nMax = notaMax;
        avl->notas = nota;
        avl->prox = NULL;
        if(no->avaliacao == NULL) //caso lista vazia
            no->avaliacao = avl;  
        else
        {
            aux = no->avaliacao;
            while(aux->prox != NULL) //percorre a lista até achar o ultimo nó
            { 
                aux = aux->prox;
            }
             aux->prox = avl;
        }
    }
}


void cadastrar_avaliacao(Lista_alunos *Lista) 
{
    float notaMax = 0;

    printf("___________________________");
    printf("\nCADASTRO DE AVALIACOES (PARA VOLTAR DIGITE 0): ");

    Aluno *no = Lista->cabeca;

    printf("\nNota Maxima: ");
    scanf("%f", &notaMax);

    if (notaMax <= 0) //saida opcional da função
        return;
    while (no != NULL) //loop para percorrer a lista de alunos 
    {
        inserir_avl(no, notaMax); // linha 187
        no = no->prox;
    }
}


void exibir_lista(Lista_alunos *lista) 
{
    Aluno *no = lista->cabeca;

    if(lista->cabeca == NULL)
    {
        printf("\nNAO HA ALUNOS CADASTRADOS\n");
    }
    else
    { 
        while (no != NULL) 
        {
            printf("\nMatrícula: %d", no->matricula);
            printf("\nNome: %s", no->nome);
            printf("\nCurso: %s", no->curso);
            printf("\nIngresso: %d\n", no->ingresso);
            no = no->prox;
        }
    }

    printf("___________________________");
}