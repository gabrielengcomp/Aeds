#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 211

typedef struct avaliacao {
    float notas;
    struct avaliacao *prox;
} Avaliacao;

typedef struct lista_de_avaliacoes {
    Avaliacao *cabeca;
} Lista_notas;

typedef struct aluno {
    long int matricula;
    char nome[30];
    char curso[20];
    int ingresso;
    int frequencia[18];
    Lista_notas *avaliacoes; // lista de tamanho variável, aumenta com o cadastro de avaliações 
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
    return chave % TAM;
}

void inserir_hash(Aluno *tabela[], int matricula, Aluno *endereco) {
    int id = funcaoespalhamento(matricula);
    while (tabela[id] != NULL) {
        id = (id + 1) % TAM;
    }
    tabela[id] = endereco;
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
    scanf("%ld", &no->matricula);

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

    Lista_notas *notas = malloc(sizeof(Lista_notas));
    if (notas == NULL) {
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

}// solicita os dados para o cadastro de um aluno e, se já existem avaliações no sistema, pede as notas contabilizadas. Se já existem chamadas realizadas no sistema, solicita também a presença do aluno em cada um dos dias

void cadastrar_avaliacao() {

}// recebe uma avaliação e o seu valor total. Em seguida, solicita a nota de cada aluno

void realizar_chamada() {

}// contabiliza a frequência dos alunos em um determinado dia, perguntando quem está presente e ausente. Assim que um aluno atingir 10 faltas, deve imprimir um aviso dizendo que o mesmo foi reprovado por infrequência.

void relatorio_alunos() {

}// Imprime a lista de alunos informando a matrícula, nome, soma de todas as notas já registradas e o número de faltas. Além disso, antes de imprimir o relatório dá a opção de ordenar a lista por um destes campos.

void relatorio_notas() {

}// Imprime o relatório de notas de uma determinada avaliação informando a nota máxima, mínima e média. Após isso, imprime todas as notas em ordem decrescente sem indicar o nome dos alunos

void exibir_lista(Lista_alunos *lista) {
    Aluno *no = lista->cabeca;

    while (no != NULL) {
        printf("\nMatrícula: %ld", no->matricula);
        printf("\nNome: %s", no->nome);
        printf("\nCurso: %s", no->curso);
        printf("\nIngresso: %d\n", no->ingresso);
        no = no->prox;
    }

    printf("___________________________");
}

void exibir_tabela_hash(Aluno *tabela[]) {
    printf("\nTabela Hash:\n");
    for (int i = 0; i < TAM; i++) {
        if (tabela[i] != NULL) {
            printf("Posição %d:\n", i);
            Aluno *aluno = tabela[i];
            printf("\tMatrícula: %ld\n", aluno->matricula);
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
    printf("[4] Relatórios\n");
    printf("[5] Exibir Lista de Alunos\n");
    printf("[6] Exibir Tabela Hash\n");
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
                // Implementar função cadastrar_avaliacao()
                break;

            case 3:
                // Implementar função realizar_chamada()
                break;

            case 4:
                // Implementar função relatorio_alunos()
                break;

            case 5:
                exibir_lista(&Lista_de_alunos);
                break;

            case 6:
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
