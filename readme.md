<h1 align="center"> Controle de Sala de Aula </h1>
Repositório projetado para simular um sistema de controle de sala de aula que recebe informações do aluno, como matrícula, nome, curso e ano de ingresso e gera relaórios completos sobre desempenho e frequências dos alunos.

## Requerimentos
Para que os relatórios sejam gerados, primeiro, o usuário deve cadastrar os alunos e suas repecrivas matrículas no sistema.

## Usabilidade
O programa, armazena os alunos cadastrados em uma tabela *hash*. Dentro de cada campo da tabela, há uma lista encadeada com as informações pessoais de cada aluno.

## *TADs* e *STRUCTS*
Somadas as structs, as TADs foram utilizadas para armazenar, dentro de um tipo de variável criada, informações que serão alocadas em lista encadeadas.
```
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
    Lista_notas *avaliacoes;
    struct aluno *prox;
} Aluno;

typedef struct lista {
    Aluno *cabeca;
} Lista_alunos;

```

## *HASH*
Sempre que um aluno é cadastrado, ao preencher o número da matrícula de tal, ele automaticamente é adicionada a um campo da tabela hash. A tabela Hash recebe uma lista encadeada contendo as informações dos alunos e armazena-as em cada setor de um vetor. Para armazenar os alunos, a função "inserir_hash" faze o papel de inserir os alunos em seu determinado campo da tabela e para evitar colisões, a função "espalhamento" ajuda a separar alunos com números de matrículas muito parecidos ou próximos uns dos outros.
 ```
int funcaoespalhamento(int chave) {

    int val = 0;
    long int a = ((3^10)*20);
    val = (a*(a + chave^3))%TAM;
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
```
## SORTs

:construction: Documentação em construção :construction:

### Principais Funções:

#### Cadastrar aluno:
Para realizar o cadastro dos alunos, a função "cadastrar_aluno" é chamada e requer, como argumento da função, a lista encadeada dos alunos, para que o aluno seja salvo dentro dela e a tabela hash, que usará a matrícula do aluno para gerar o índice na tabela hash e, por fim, para armazena-los. Nela, a primeira execução refere-se a criação de uma lista encadeada especifica para o aluno que está sendo cadastrado, ela irá armazenar os dados da matrícula, nome, curso e ano de ingresso.  
```
void cadastrar_aluno(Aluno *tabela[]) {
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
    printf("\nMATRICULA: %ld\n", no->matricula);
    printf("NOME: %s\n", no->nome);
    printf("CURSO: %s\n", no->curso);
    printf("INGRESSO: %i\n", no->ingresso);
    printf("\n___________________________\n");

}
```

