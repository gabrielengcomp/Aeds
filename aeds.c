#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include "sorts.h"
#include "lista_encadeada.h"

int verificar_frequencia (Aluno *aluno) //returna quantas faltas um aluno tem  
{

    int i = 0;
    int faltas = 0;

    for(;i < 18; i++)
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
