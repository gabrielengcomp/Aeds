#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "sorts.h"

#define TAM 211

typedef struct avaliacoes {
    float notas;
    struct avaliacoes *prox;
} Avaliacoes;

/*typedef struct lista_de_avaliacoes {
    Avaliacao *cabeca;
} Lista_notas;
*/
typedef struct aluno {
    int matricula;
    char nome[30];
    char curso[20];
    int ingresso;
    int frequencia[18];
    int aula;
    Avaliacoes *avaliacao; // lista de tamanho variável, aumenta com o cadastro de avaliações 
    struct aluno *prox;
} Aluno;

typedef struct lista {
    Aluno *cabeca;
} Lista_alunos;

Aluno *acessa(Lista_alunos *L, int i) {
    Aluno *aluno = L->cabeca;
    int j = 0;
    while (aluno != NULL && j != i) {
        aluno = aluno->prox;
        j++;
    }
    return aluno;
}// acessa a matrícula do aluno referente a matrícula armazenada na lista encadeada

void excluir_aluno(Lista_alunos *L, int matricula) {
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

Aluno *busca(Lista_alunos *L, int x) {
    Aluno *aluno = L->cabeca;
    while (aluno != NULL && aluno->matricula != x) {
        aluno = aluno->prox;
    }
    return aluno;
}

void inserir_aluno(Aluno *novo_aluno, Lista_alunos *lista) {
    if (lista->cabeca == NULL) {
        lista->cabeca = novo_aluno;
        novo_aluno->prox = NULL;
    } else {
        Aluno *aux = lista->cabeca;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo_aluno;
        novo_aluno->prox = NULL;
    }
}// insere um no Aluno na lista de alunos

int funcaoespalhamento(int chave) {

    int val = 0;
    long int a = ((3^10)*20);
    val = (a*(a + chave^3))%TAM;
    printf("%i\n", val);

    return val;
}

void inserir_hash(Aluno *tabela[], int matricula, Aluno *endereco) {
    
    int i = 0;
    int id = 0;

    id = funcaoespalhamento(matricula);

    while (tabela[id] != NULL) {
        
        id = (id + i) % TAM;
        printf("\nid) %i\n", id);
        i++;
    }
    tabela[id] = endereco;
}

Aluno* buscarHash (Aluno *tabela[], int matricula)
{
    int ind;

    ind = funcaoespalhamento(matricula);

    while(tabela[ind]->matricula != matricula)
        ind = (ind++) % TAM;
    
    return tabela[ind];
}

void cadastrar_aluno(Lista_alunos *lista, Aluno *tabela[]) {
    char str[30];
    Aluno *no = malloc(sizeof(Aluno));

    if (no == NULL) {
        printf("ERRO AO ALOCAR MEMORIA");
        return;
    }

    printf("\n___________________________\n");
    printf("\nCADASTRO DE ALUNO (PARA VOLTAR DIGITE 0)\n");

    printf("\nMATRICULA: ");
    scanf("%i", &no->matricula);

    if (no->matricula == 0) {
        free(no);
        return;
    }

    inserir_hash(tabela, no->matricula, no);

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

    Avaliacoes *notas = malloc(sizeof(Avaliacoes));
    if (notas == NULL) {
        free(no);
        printf("ERRO AO ALOCAR MEMORIA PARA AS AVALIACOES");
        return;
    }

    notas = NULL;
    no->aula = 0;

    inserir_aluno(no, lista);

    printf("\nCADASTRO REALIZADO COM SUCESSO\n");
    printf("\nMATRICULA: %d\n", no->matricula);
    printf("NOME: %s\n", no->nome);
    printf("CURSO: %s\n", no->curso);
    printf("INGRESSO: %i\n", no->ingresso);
    printf("\n___________________________\n");

}// solicita os dados para o cadastro de um aluno e, se já existem avaliações no sistema, pede as notas contabilizadas. Se já existem chamadas realizadas no sistema, solicita também a presença do aluno em cada um dos dias

void cadastrar_avaliacao(Aluno **tabela) {

    float nota = 0;
    int matricula = 0;
    int id = 0;
    int cond = 1;
    Aluno *no;
    Avaliacoes *avl;
    Avaliacoes *aux;

    printf("___________________________");
    printf("\nCADASTRO DE AVALIACOES (PARA VOLTAR DIGITE 0): ");

    while(1)
    {
        cond = 1;
        printf("\nMatricula: ");
        scanf("%i", &matricula);

        if(matricula == 0)
            break;
        else
        {
            id = funcaoespalhamento(matricula);

            if(tabela[id] == NULL)
            {
                printf("\nMATRICULA NAO ENCONTRADA\n");
                cond = 0;
            }
            else
            {
                no = tabela[id];
            }

            while(cond)
            {
                printf("\nNOTA: ");
                scanf("%2f", &nota);
                cond = (nota == -1) ? 0 : 1;

                printf("\na\n");
                if(nota >= 0)
                {
                    avl = malloc(sizeof(Avaliacoes));
                    
                    avl->notas = nota;
                    avl->prox = NULL;
                    printf("\nb\n");
                    if(no->avaliacao == NULL)
                    {
                      no->avaliacao = avl;  
                    }
                    else
                    {
                        aux = no->avaliacao;
                        printf("\nd");
                        while(aux->prox != NULL)
                            printf("\nc\n");
                            aux = aux->prox;
                        
                        aux = avl;
                        printf("\ne");
                    }
                    printf("\nf");
                }
                printf("\ng");

            }
            printf("\nh");
        }
        printf("\ni");

    }




}// recebe uma avaliação e o seu valor total. Em seguida, solicita a nota de cada aluno

int verificar_frequencia (Aluno *aluno) //returna quantas faltas um aluno tem  
{

    int i = 0;
    int faltas = 0;

    for(;i <= 18; i++)
        faltas += aluno->frequencia[i];

    return faltas;
    

}

void realizar_chamada(Lista_alunos *lista) {
    
    Aluno *no = lista->cabeca;

    printf("\nREALIZANDO CHAMDA\n");

    while(no != NULL)
    {
        printf("%s | %i: ", no->nome, no->matricula);
        scanf("%i", &no->frequencia[no->aula]);
        no->aula++;
        if (verificar_frequencia(no) > 18)
        {
            printf("\n!! ALUNO REPROVADO POR FREQUENCIA !!\n");
        }

        no = no->prox;

    }

}// contabiliza a frequência dos alunos em um determinado dia, perguntando quem está presente e ausente. Assim que um aluno atingir 10 faltas, deve imprimir um aviso dizendo que o mesmo foi reprovado por infrequência.


void relatorio_alunos() {

}// Imprime a lista de alunos informando a matrícula, nome, soma de todas as notas já registradas e o número de faltas. Além disso, antes de imprimir o relatório dá a opção de ordenar a lista por um destes campos.

void relatorio_notas() {

}// Imprime o relatório de notas de uma determinada avaliação informando a nota máxima, mínima e média. Após isso, imprime todas as notas em ordem decrescente sem indicar o nome dos alunos

void exibir_lista(Lista_alunos *lista) {
    Aluno *no = lista->cabeca;

    if(lista->cabeca == NULL)
    {
        printf("\nNAO HA ALUNOS CADASTRADOS\n");
    }
    else
    { 
        while (no != NULL) {
            printf("\nMatrícula: %d", no->matricula);
            printf("\nNome: %s", no->nome);
            printf("\nCurso: %s", no->curso);
            printf("\nIngresso: %d\n", no->ingresso);
            no = no->prox;
        }
    }

    printf("___________________________");
}

void exibir_tabela_hash(Aluno *tabela[]) {
    printf("\nTabela Hash:\n");
    for (int i = 0; i < TAM; i++) {
        if (tabela[i] != NULL) {
            printf("Posição %d:\n", i);
            Aluno *aluno = tabela[i];
            printf("\tMatrícula: %d\n", aluno->matricula);
            printf("\tNome: %s\n", aluno->nome);
            printf("\tCurso: %s\n", aluno->curso);
            printf("\tIngresso: %d\n", aluno->ingresso);
        }
    }
    printf("___________________________\n");
}


/*SORTS
Quick sort
*/
void troca(int vet[], int a, int b) {
    int temp = vet[a];
    vet[a] = vet[b];
    vet[b] = temp;
}

void troca_aluno(Aluno* vet[], int i, int j) {
    Aluno* temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;
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

void quickSort(int vet[], int inicio, int fim) {
    if (inicio < fim) {

        int pivo = particiona(vet, inicio, fim);
        
        quickSort(vet, inicio, pivo - 1);
        quickSort(vet, pivo + 1, fim);
    }
}

void quickSortNome(Aluno* vet[], int inicio, int fim) {
    if (inicio < fim) {

        int pivo = particiona_nome(vet, inicio, fim);
        
        quickSortNome(vet, inicio, pivo - 1);
        quickSortNome(vet, pivo + 1, fim);
    }
}

void print_ordenado(Aluno *tabela[], int tipo){
    
    Aluno* vetNomes[TAM];
    int vet[TAM];
    int cont = 0;

    for (int i = 0; i < TAM; i++) {
        if (tabela[i] != NULL) {
            if (tipo == 1){
            vet[cont] = tabela[i]->matricula;
            cont++;
            }

            else if (tipo == 2){
            //somatorio das notas
            }
            else if (tipo == 3){
            vetNomes[cont] = tabela[i];
            cont++;
            }
        }
    }

    // Ordenação por matrícula
    if (tipo == 1) {
        quickSort(vet, 0, cont - 1);
        printf("Alunos em ordem crescente de matrícula:\n");
        for (int i = 0; i < cont; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tabela[j] != NULL && tabela[j]->matricula == vet[i]) {
                    printf("Matrícula: %d, Nome: %s, Curso: %s, Ingresso: %d\n", 
                            tabela[j]->matricula, tabela[j]->nome, 
                            tabela[j]->curso, tabela[j]->ingresso);
                    break;
                }
            }
        }
    }

    // Ordenação por nome
    else if (tipo == 3) {
        quickSortNome(vetNomes, 0, cont - 1);
        printf("Alunos em ordem alfabética:\n");
        for (int i = 0; i < cont; i++) {
            printf("Matrícula: %d, Nome: %s, Curso: %s, Ingresso: %d\n", 
                    vetNomes[i]->matricula, vetNomes[i]->nome, 
                    vetNomes[i]->curso, vetNomes[i]->ingresso);
        }
    }
}

void menu() {
    printf("\n___________________________\n");
    printf("[1] Cadastrar Aluno\n");
    printf("[2] Cadastrar Avaliação\n");
    printf("[3] Chamada\n");
    printf("[4] Relatório de alunos\n");
    printf("[5] Relatório de notas\n");
    printf("[6] Exibir Lista de Alunos\n");
    printf("[7] Exibir Tabela Hash\n");
    printf("[8] Exibir alunos ordenados pela matricula\n");
    printf("[0] Sair\n");
    printf("___________________________\n");
}

int main() {

    Lista_alunos Lista_de_alunos;
    Lista_de_alunos.cabeca = NULL;

    Aluno *tabela[TAM] = {NULL};
    int opc = 0;
    int opord = 0;

    printf("\nTRABALHO DE ALGORITMOS E ESTRUTURAS DE DADOS\n");
    printf("\nALUNOS: AUGUSTO FREITAS, GABRIEL HENRIQUE pivoRES, VICENTE ZANATTA\n");
    printf("SEMESTRE: 24.1\n");

    while (1) {
        menu();
        printf("Selecione: ");
        scanf("%i", &opc);

        switch (opc) {
            case 1:
                cadastrar_aluno(&Lista_de_alunos, tabela);
                break;

            case 2:
                cadastrar_avaliacao(tabela);
                break;

            case 3:
                realizar_chamada(&Lista_de_alunos);
                break;

            case 4:
                relatorio_alunos();
                break;

            case 5:
                relatorio_notas();
                break;
            
            case 6:
                exibir_lista(&Lista_de_alunos);
                break;

            case 7:
                exibir_tabela_hash(tabela);
                break;
            
            case 8:

                printf("como deseja realizar a ordenação?\n"
                "[1] Por matricula\n"
                "[2] Por somatorio das notas\n"
                "[3] Por ordem alfabética\n");
                scanf("%d",&opord);
               
                switch (opord){
                    case 1:
                        print_ordenado(tabela, opord);
                        break;
                    case 2:
                        print_ordenado(tabela, opord);
                        break;
                    case 3:
                        print_ordenado(tabela, opord);
                        break;
                    
                    default:
                        printf("Opção Inválida\n");
                        break;
                }
                
                break;
            
            case 0:
                return 0;

            default:
                printf("Opção Inválida\n");
                break;
        }
    }
    return 0;
}
