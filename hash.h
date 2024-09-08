#ifdef __HASH__
#define __HASH

int funcaoespalhamento(int chave);
void inserir_hash(Aluno *tabela[], int matricula, Aluno *endereco);
Aluno* buscarHash (Aluno *tabela[], int matricula); //busca na tabela e retorna ponteiro para aluno 
void exibir_tabela_hash(Aluno *tabela[]);

#endif