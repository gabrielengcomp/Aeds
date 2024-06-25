
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avaliacao{
    float notas;
    struct avaliacao *prox;
}Avaliacao;

typedef struct lista_de_avaliacoes{
    Avaliacao *cabeca;
}Lista_notas;

typedef struct aluno{
    long int matricula;    
    char nome[30]; 
    char curso[20];
    int  ingresso;
    int frequencia[18];
    Lista_notas *avaliacoes; //lista de tamanho variavel, aumenta com o cadastro de avaliações 
    struct aluno *prox;
}Aluno;

typedef struct lista{
    Aluno *cabeca;
    Aluno *prox;
}Lista_alunos;

Aluno *acessa(Lista_alunos *L, int i){
    Aluno *aluno = L->cabeca;
    int j = 0;
    while(aluno != NULL && j != i){
        aluno = aluno -> prox;
        j++;
    }
    return aluno;
}//acessa a matricula do aluno referente a matricula armazenada na lista encadeada

Aluno *busca(Lista_alunos *L, int x){
    Aluno *aluno = L -> cabeca;
    int j = 0;
    while(aluno != NULL && aluno -> matricula != x){
        aluno = aluno -> prox;
    }
    return aluno;
}

void inserir_aluno(Aluno *novo_aluno, Lista_alunos *lista)
{
    Aluno *aux = lista->cabeca;
    
    if(aux == NULL)
    {
        lista->prox = novo_aluno;
        novo_aluno->prox = NULL;
    }
    else
    { 
        while(aux->prox != NULL)
            aux = aux->prox;
    
        aux->prox = novo_aluno;
        novo_aluno->prox = NULL;
    }
}//insere um no Aluno na lista de alunos

void cadastrar_aluno(Lista_alunos *lista) 
{
    char str[30];
    Aluno *no = malloc(sizeof(Aluno));

    if (no == NULL) 
    {
        printf("ERRO AO ALOCAR MEMORIA");
        return;
    }

    printf("\n___________________________\n");
    printf("\nCADASTRO DE ALUNO (PARA VOLTAR DIGITE 0)\n");
    
    printf("\nMATRICULA: ");
    scanf("%ld", &no->matricula);

    if (no->matricula == 0)
    {
        free(no);
        return;
    }

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

    Lista_notas *notas = malloc(sizeof(Lista_notas));
    if (notas == NULL) 
    {
        free(no);
        printf("ERRO AO ALOCAR MEMORIA PARA AS AVALIACOES");
        return;
    }

    notas->cabeca = NULL;
    no->avaliacoes = notas;
    
    inserir_aluno(no, lista);

    printf("\nCADASTRO REALIZADO COM SUCESSO\n");
    printf("\nMATRICULA: %ld\n", no->matricula);
    printf("NOME: %s\n", no->nome);
    printf("CURSO: %s\n", no->curso);
    printf("INGRESSO: %i\n", no->ingresso); 
    printf("\n___________________________\n");

}//solicita os dados para o cadastro de um aluno e, se ja existem avaliacoes no sistema, pedeas notas contabilizadas.  Se ja existem chamadas realizadas no sistema, solicita tambem a presenca do aluno em cada um dos dias

void exibir_lista(Lista_alunos *lista)
{
    Aluno* no = lista->cabeca;

    while(no != NULL)
    {
        printf("\n%ld", no->matricula);
        printf("\n%s", no->nome);
        printf("\n%s", no->curso);
        printf("\n%d\n",no->ingresso);
        no = no->prox;
    }

    printf("*******************");
}