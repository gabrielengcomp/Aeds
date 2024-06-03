#include <stdio.h>
#include <stdlib.h>

#define TAM 211

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
