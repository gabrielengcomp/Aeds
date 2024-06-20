#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 211

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

void cadastrar_aluno(){

    char str[30];

    Aluno *no;
    no = malloc(sizeof(Aluno));

    if(no == NULL)
    {
        printf("ERRO AO ALOCAR MEMORIA");
        return;
    }

    printf("\n___________________________\n");
    printf("\nCADASTRO DE ALUNO (PARA VOLTAR DIGITE 0)\n");
    printf("\nMATRICULA: ");
    scanf(" %i", &no->matricula);

    if(no->matricula == 0)
        return;
    
    fflush(stdin);
    printf("NOME: ");
    fgets(no->nome, sizeof(no->nome), stdin);
    /*printf("\nCURSO: ");
    fgets(str, sizeof(str), stdin);
    strcpy(no->curso, str);*/

    Lista_notas *notas;
    notas = malloc(sizeof(Lista_notas));
    notas->cabeca = NULL;
    no->avaliacoes = notas;

    printf("a");
    printf("%i", no->matricula);
    printf("b");
    printf("%s\n", no->nome);
    printf("c");

    return;
    //adicionar chamada para inserir()


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
    //t[id] = valor;
}

void menu()
{

    printf("\n___________________________\n");

    printf("[1] Cadastrar Aluno\n");

    printf("[2] Cadastrar Avaliação\n");

    printf("[3] Chamada\n");

    printf("[4] Relatorios\n");

    printf("[0] Sair");

    printf("\n___________________________\n");
}

int main(){
       

    Lista_alunos L;

    L.cabeca = NULL;

    

    int tabela[TAM];

    int opc = 0;



    inicializar(tabela);

	printf("\nTRABALHO DE ALGORITIMOS E ESTRUTURAS DE DADOS\n");
    printf("\nALUNOS: AUGUSTO FREITAS, GABRIEL HENRIQUE PIRES, VICENTE ZANATTA\n");
    printf("SEMESTRE: 24.1\n");

    while(1)

    {   

        menu();

        printf("Selecione: ");

        scanf("%i", &opc);



        switch(opc)

        {

            case 1:
                cadastrar_aluno();
            break;

            

            case 2:

            

            break;



            case 3:

            

            break;



            case 4:

            

            break;



            case 0:

                return 0;

            

            default:

                printf("Opcao Invalida\n");

            break;
            
        }

    }

    return 0;
}
