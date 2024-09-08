
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
    int aula; //armazena quantidade de aulas já ministradas, a partir das chamdas realizadas
} Lista_alunos;
