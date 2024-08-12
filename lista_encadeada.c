#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}

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
