#include <stdio.h>
#include <stdlib.h>
#include "TADs.h"

#define TAM 211

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
