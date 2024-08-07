#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 211

typedef struct avaliacoes {
    float notas;
    struct avaliacoes *prox;
} Avaliacoes;

/*typedef struct lista_de_avaliacoes {
    Avaliacao *cabeca;
} Lista_notas;*/

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

int funcaoespalhamento(int chave) {//ocorre overflow em numeros grandes

    int val = 0;

    val = ((chave % TAM) + (long int)(10^24*(chave)))%TAM;
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

void realizar_chamada(Lista_alunos *lista) {
    
    Aluno *no = lista->cabeca;

    printf("\nREALIZANDO CHAMDA\n");

    while(no != NULL)
    {
        printf("%s | %i: ", no->nome, no->matricula);
        scanf("%i", &no->frequencia[no->aula]);
        no->aula++;
        no = no->prox;

    }

   /* int i = 0;

    for(;i <= 18; i++)
    {
        printf("%i ", no->frequencia[i]);
    }
    printf("\n");*/

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

int main() {

    Lista_alunos Lista_de_alunos;
    Lista_de_alunos.cabeca = NULL;

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
            
            case 0:
                return 0;

            default:
                printf("Opção Inválida\n");
                break;
        }
    }
    return 0;
}
