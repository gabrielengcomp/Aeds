#include <stdio.h>
#include <stdlib.h>

#define TAM 211

typedef struct avaliacao{
    float notas;
    struct avaliacao *prox;
}Avaliacao;

typedef struct aluno{
    long int matricula;    
    struct aluno *prox;
    char nome[30]; 
    char curso[20];
    int  ingresso;
    int frequencia[18];
    Avaliacao nota; //lista de tamanho variavel, aumenta com o cadastro de avaliações
}Aluno;

typedef struct lista{
    Aluno *cabeca;
}Lista;

Aluno *acessa(Lista *L, int i){
    Aluno *
}//acessa a matricula do aluno referente a matricula armazenada na lista encadeada

void cadastrar_aluno(){

}//solicita os dados para o cadastro de um aluno e, se ja existem avaliacoes no sistema, pedeas notas contabilizadas.  Se ja existem chamadas realizadas no sistema, solicita tambem a presenca do aluno em cada um dos dias

void cadastrar_avaliacao(){

}//recebe uma avaliacao e o seu valor total. Em seguida, solicita a nota de cada aluno

void realizar_chamada(){

}//contabiliza a frequencia dos alunos em um determinado dia, perguntando quem esta presentee ausente.  Assim que um aluno atingir 10 faltas, deve imprimir um aviso dizendo que o mesmo foi reprovadopor infrequencia.

void relatorio_alunos(){

}// Imprime a lista de alunos informando a matrıcula, nome, soma de todas as notas ja registradas e o numero de faltas.  Alem disso, antes de imprimir o relatorio da a opcao de ordenar a lista porum destes campos.

void relatorio_notas(){

}//  Imprime o relatorio de notas de uma determinada avaliacao informando a nota maxima,mınima e media.  Apos isso, imprime todas as notas em ordem decrescente sem indicar o nome dos alunos

void inicializar(int t[]){
    for(int i = 0; i<TAM; i++)
        t[i]=-1;
}
int funcaoespalhamento(int chave){
    return chave%TAM;
}
void inserir(int t[], int matricula){
    int id = funcaoespalhamento(matricula);
    while(t[id] != -1){

    }
    t[id] = valor;
}

int main(){
    int tabela[TAM];
    inicializar(tabela);
}
