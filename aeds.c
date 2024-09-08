#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "sorts.h"

#define TAM 211

typedef struct avaliacoes {
    float notas;
    float nMax;
    struct avaliacoes *prox;
} Avaliacoes;

typedef struct aluno {
    int matricula;
    char nome[30];
    char curso[20];
    int ingresso;
    int frequencia[18];
    Avaliacoes *avaliacao; // lista de tamanho variável, aumenta com o cadastro de avaliações 
    struct aluno *prox;
} Aluno;

typedef struct lista {
    Aluno *cabeca;
    int aula;
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

int funcaoespalhamento(int chave) {

    int val = 0;
    long int a = ((3^10)*20);
    val = (a*(a + chave^3))%TAM;

    return val;
}

void inserir_hash(Aluno *tabela[], int matricula, Aluno *endereco) {
    
    int i = 0;
    int id = 0;

    id = funcaoespalhamento(matricula);

    while (tabela[id] != NULL) //percorre a tabela caso o ind gerado pela HASH ja estaja ocupado (endereçamento aberto)
        { 
        id++;
        id = (id++) % TAM;// div por 211 para evitar "sair" da tabela e preservar a propriedade de circularidade
        }
    tabela[id] = endereco;
}

Aluno* buscarHash (Aluno *tabela[], int matricula) //busca na tabela e retorna ponteiro para aluno 
{
    int ind;

    ind = funcaoespalhamento(matricula);

    while(tabela[ind]->matricula != matricula)//percorre a tabela caso não ache no valor retornado pela funcHash, por conta do endereçamento aberto para tratar colisão
        ind = (ind++) % TAM;// div por 211 para evitar "sair" da tabela e preservar a propriedade de circularidade 
    
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
    printf("CADASTRO DE ALUNO (PARA VOLTAR DIGITE 0)\n");

    printf("\nMATRICULA: ");
    scanf("%i", &no->matricula);

    if (no->matricula == 0) {
        free(no);
        return;
    }

    inserir_hash(tabela, no->matricula, no); //linha 

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
            printf("\na\n");
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



int verificar_frequencia (Aluno *aluno) //returna quantas faltas um aluno tem  
{

    int i = 0;
    int faltas = 0;

    for(;i <= 18; i++)
        faltas += aluno->frequencia[i]; //loop para percorrer vetor contendo frequencia e soma as faltas

    return faltas;
    

}

void realizar_chamada(Lista_alunos *lista) {
    
    Aluno *no = lista->cabeca;
    lista->aula++;

    printf("\nREALIZANDO CHAMADA\n0 para presente\n1 para ausente\n");

    while(no != NULL)
    {
        printf("%s | %i: ", no->nome, no->matricula);
        scanf("%i", &no->frequencia[lista->aula]);
        if (verificar_frequencia(no) >= 10)// verifica se aluno esta reprovado por falta
        {
            printf("\n!! ALUNO REPROVADO POR FREQUENCIA !!\n");
        }

        no = no->prox;

    }

}// contabiliza a frequência dos alunos em um determinado dia, perguntando quem está presente e ausente. Assim que um aluno atingir 10 faltas, deve imprimir um aviso dizendo que o mesmo foi reprovado por infrequência.

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

void troca_somatorio(Aluno* vetAlunos[], float vetSomatorio[], int i, int j) {
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

int particiona_somatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim) {
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

void quickSortMatricula(int vet[], int inicio, int fim) {
    if (inicio < fim) {

        int pivo = particiona(vet, inicio, fim);
        
        quickSortMatricula(vet, inicio, pivo - 1);
        quickSortMatricula(vet, pivo + 1, fim);
    }
}

void quickSortNome(Aluno* vet[], int inicio, int fim) {
    if (inicio < fim) {

        int pivo = particiona_nome(vet, inicio, fim);
        
        quickSortNome(vet, inicio, pivo - 1);
        quickSortNome(vet, pivo + 1, fim);
    }
}

void quickSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona_somatorio(vetSomatorio, vetAlunos, inicio, fim);
        quickSortSomatorio(vetSomatorio, vetAlunos, inicio, pivo - 1);
        quickSortSomatorio(vetSomatorio, vetAlunos, pivo + 1, fim);
    }
}

float somatorionotas(Avaliacoes *avaliacao) {
    float soma = 0;
    Avaliacoes *atual = avaliacao;
    while (atual != NULL) {
        soma += atual->notas;
        atual = atual->prox;
    }
    return soma;
}
void insertionSortMatricula(int vet[], int n) {
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

void insertionSortNome(Aluno* vet[], int n) {
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

void insertionSortSomatorio(float vetSomatorio[], Aluno* vetAlunos[], int n) {
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

void print_ordenado(Aluno *tabela[], int tipo, int algoritmo){
    Aluno* vetNomes[TAM];
    float vetSomatorio[TAM];
    int vet[TAM];
    int cont = 0;
    for (int i = 0; i < TAM; i++) {
        if (tabela[i] != NULL) {
            if (tipo == 1){
                vet[cont] = tabela[i]->matricula;
                cont++;
            }
            else if (tipo == 2){
                vetNomes[cont] = tabela[i];
                vetSomatorio[cont] = somatorionotas(tabela[i]->avaliacao);
                cont++;
            }
            else if (tipo == 3){
                vetNomes[cont] = tabela[i];
                cont++;
            }
        }
    }

    // Escolha de algoritmo de ordenação
    if (algoritmo == 1) {
        // Ordenação por quicksort
        if (tipo == 1) quickSortMatricula(vet, 0, cont - 1);
        else if (tipo == 2) quickSortSomatorio(vetSomatorio, vetNomes, 0, cont - 1);
        else if (tipo == 3) quickSortNome(vetNomes, 0, cont - 1);
    } else if (algoritmo == 2) {
        // Ordenação por insertion sort
        if (tipo == 1) insertionSortMatricula(vet, cont);
        else if (tipo == 2) insertionSortSomatorio(vetSomatorio, vetNomes, cont);
        else if (tipo == 3) insertionSortNome(vetNomes, cont);
    }

    // Exibir os alunos ordenados
    if (tipo == 1) {
        printf("Alunos em ordem crescente de matrícula:\n");
        for (int i = 0; i < cont; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tabela[j] != NULL && tabela[j]->matricula == vet[i]) {
                    printf("Matrícula: %d, Nome: %s, Curso: %s, Ingresso: %d\n", tabela[j]->matricula, tabela[j]->nome,tabela[j]->curso, tabela[j]->ingresso);
                }
            }
        }
    } else if (tipo == 2) {
        printf("Alunos em ordem decrescente de somatório das notas:\n");
        for (int i = cont - 1; i >= 0; i--) {
            printf("Somatório das Notas: %.2f, Matrícula: %d, Nome: %s,  Curso: %s, Ingresso: %d\n",vetSomatorio[i], vetNomes[i]->matricula, vetNomes[i]->nome,  tabela[i]->curso, tabela[i]->ingresso);
        }
    } else if (tipo == 3) {
        printf("Alunos em ordem alfabética:\n");
        for (int i = 0; i < cont; i++) {
            printf("Nome: %s, Matrícula: %d, Curso: %s, Ingresso: %d\n", vetNomes[i]->nome, vetNomes[i]->matricula, vetNomes[i]->curso, vetNomes[i]->ingresso);
        }
    }
}


void relatorio_notas(Lista_alunos *lista) {
    if (lista->cabeca == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Aluno *aluno = lista->cabeca;
    float maxNota = -1.0, minNota = 101.0, soma = 0.0;
    int totalNotas = 0;
    
    // Array para armazenar as notas para ordenação
    float notasOrdenadas[TAM];
    
    // Percorre a lista de alunos para obter as notas
    while (aluno != NULL) {
        Avaliacoes *avaliacao = aluno->avaliacao;
        while (avaliacao != NULL) {
            float nota = avaliacao->notas;
            if (nota > maxNota) {
                maxNota = nota;
            }
            if (nota < minNota) {
                minNota = nota;
            }
            soma += nota;
            notasOrdenadas[totalNotas] = nota;
            totalNotas++;
            avaliacao = avaliacao->prox;
        }
        aluno = aluno->prox;
    }
    
    if (totalNotas == 0) {
        printf("Nenhuma avaliação registrada.\n");
        return;
    }
    
    // Calcula a média
    float media = soma / totalNotas;

    // Exibe os resultados
    printf("\nRelatório de Notas:\n");
    printf("Nota máxima: %.2f\n", maxNota);
    printf("Nota mínima: %.2f\n", minNota);
    printf("Média das notas: %.2f\n", media);

    // Ordena as notas em ordem decrescente (utilizando bubble sort como exemplo)
    for (int i = 0; i < totalNotas - 1; i++) {
        for (int j = 0; j < totalNotas - i - 1; j++) {
            if (notasOrdenadas[j] < notasOrdenadas[j + 1]) {
                float temp = notasOrdenadas[j];
                notasOrdenadas[j] = notasOrdenadas[j + 1];
                notasOrdenadas[j + 1] = temp;
            }
        }
    }

    // Exibe as notas em ordem decrescente
    printf("\nNotas em ordem decrescente:\n");
    for (int i = 0; i < totalNotas; i++) {
        printf("%.2f\n", notasOrdenadas[i]);
    }
}

void relatorio_alunos(Aluno *tabela[]) {
    int op, algoritmo;
    printf("\n___________________________\n");
    printf("Como deseja realizar a ordenação?\n[1] Por matrícula\n[2] Por somatório das notas\n[3] Por ordem alfabética\n");
    printf("___________________________\n");
    printf("Selecione: ");
    scanf("%d", &op);
    printf("\n___________________________\n");
    printf("Escolha o algoritmo de ordenação:\n[1] Quicksort\n[2] Insertion sort\n");
    printf("___________________________\n");
    printf("Selecione: ");
    scanf("%d", &algoritmo);
    printf("\n___________________________\n");
    if (op >= 1 && op <= 3 && (algoritmo == 1 || algoritmo == 2)) {
        print_ordenado(tabela, op, algoritmo);
    } else {
        printf("Opção Inválida\n");
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
    printf("[0] Sair\n");
    printf("___________________________\n");
}

int main() {

    Lista_alunos Lista_de_alunos;
    Lista_de_alunos.cabeca = NULL;
    Lista_de_alunos.aula = 0;

    Aluno *tabela[TAM] = {NULL};
    int opc = 0;
    int opord = 0;

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
                cadastrar_avaliacao(&Lista_de_alunos);
                break;

            case 3:
                realizar_chamada(&Lista_de_alunos);
                break;

            case 4:
                relatorio_alunos(tabela);
                break;

            case 5:
                relatorio_notas(&Lista_de_alunos);
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
