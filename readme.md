<h1 align="center"> Controle de Sala de Aula </h1>
Repositório projetado para simular um sistema de controle de sala de aula que recebe informações do aluno, como matrícula, nome, curso e ano de ingresso e gera relaórios completos sobre desempenho e frequências dos alunos.

## Requerimentos
Para que os relatórios sejam gerados, primeiro, o usuário deve cadastrar os alunos e suas repecrivas matrículas no sistema.

## Usabilidade
O programa, armazena os alunos cadastrados em uma tabela *hash*. Dentro de cada campo da tabela, há uma lista encadeada com as informações pessoais de cada aluno.

## *HASH*
Sempre que um aluno é cadastrado, ao preencher o número da matrícula de tal, ele automaticamente é adicionada a um campo da tabela hash. A tabela Hash recebe uma lista encadeada contendo as informações dos alunos e armazena-as em cada setor de um vetor. Para armazenar os alunos, a função "inserir_hash" faze o papel de inserir os alunos em seu determinado campo da tabela e para evitar colisões, a função "espalhamento" ajuda a separar alunos com números de matrículas muito parecidos ou próximos uns dos outros.
 ```
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
```


:construction: Documentação em construção :construction:
