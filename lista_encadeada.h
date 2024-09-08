#ifdef __LISTA_ENCADEADA__
#define __LISTA_ENCADEADA__

Aluno *acessa(Lista_alunos *L, int i); // acessa a matrícula do aluno referente a matrícula armazenada na lista encadeada
void excluir_aluno(Lista_alunos *L, int matricula); //desconsiderar 
Aluno *busca(Lista_alunos *L, int x); //busca aluno na lista encadeada
void inserir_aluno(Aluno *novo_aluno, Lista_alunos *lista);// insere um nó Aluno na lista de alunos
void cadastrar_aluno(Lista_alunos *lista, Aluno *tabela[]);// solicita os dados para o cadastro de um aluno e, se já existem avaliações no sistema, pede as notas contabilizadas. Se já existem chamadas realizadas no sistema, solicita também a presença do aluno em cada um dos dias
void inserir_avl (Aluno *no, float notaMax); //recebe o nó do aluno, a nota maxima, cria a avaliação e add na lista de avaliações do aluno
void cadastrar_avaliacao(Lista_alunos *Lista); 
void exibir_lista(Lista_alunos *lista) 






#endif