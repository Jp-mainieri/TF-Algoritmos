#include <stdio.h>
#include <string.h>

// Definindo as estruturas de dados

typedef struct{
    char nome[100];
    char cpf[11]; // Precisa ser string por poder começar com 0
}Pessoa;

typedef struct{
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    char id[20]; // Precisa ser string por poder começar com 0
    int quantidadeDisponivel;
    Pessoa pessoasEmprestimos[11];
    int contadorEmprestimos;
}Livro;

typedef struct{
    Livro livros[100];
    int qLivros;
}Biblioteca;

// Cadastrar Livros

void cadastroLivros(Biblioteca* b) {
    printf("%d",b->qLivros);
    if (b->qLivros == 100) {
        printf("Nao tem como cadastrar mais livros nesta Biblioteca\n");
        return;
    }
    int qCadastro;
    
    do{
        printf("Digite quantos livros voce deseja cadastrar: ");
        scanf("%d",&qCadastro);
        if (b->qLivros + qCadastro > 100){
            printf("Quantidade de livros para cadastrar ultrapassa o limite da Biblioteca\n");
        }
    }while(b->qLivros + qCadastro > 100);

    const int inicioCadastro = b->qLivros;
    const int finalCadastro = b->qLivros + qCadastro;

    for (int i = inicioCadastro; i < finalCadastro; i++){
        char idCadastro[20];
        printf("Digite o ID do livro: ");
        scanf("%19s",idCadastro);
        for (int j = 0; j < b->qLivros; j++){
            if(strcmp(b->livros[i].id,b->livros[j].id) == 0){
                strcpy(b->livros[i].id,idCadastro);
                printf("Ja existe um livro com esse codigo, retornando...\n");
                return;
            }
        }
        printf("Digite o titulo do Livro: ");
        scanf(" %[^\n]", b->livros[i].titulo);
        printf("Digite o nome do autor do Livro: ");
        scanf(" %[^\n]", b->livros[i].autor);
        printf("Digite o ano de publicacao do Livro: ");
        scanf(" %d", &b->livros[i].anoPublicacao);
        printf("Digite a quantidade disponivel do Livro (max 10): ");
        scanf(" %d", &b->livros[i].quantidadeDisponivel);
        printf("==============================\n");
        b->qLivros++;
    }
}

// Sistema de consulta de livros

void consultarLivrosListAll(Biblioteca* b)
{
    for (int i = 0; i < b->qLivros; i++ )
    {
        printf("%s - %s \n",b->livros[i].id,  b->livros[i].titulo); // Printa todos os livros da biblioteca
    }
}

Livro* consultarLivrosSearchId(Biblioteca* b)
{
    Livro* pesquisaLivro = NULL;
    char search[20];
    printf("Digite o código do livro para pesquisar: ");
    scanf("%19s",search);
    for (int i = 0; i < b->qLivros; i++)
    {
        if (strcmp(search,b->livros[i].id) == 0)
        {
            printf("%s - %s\n",b->livros[i].id,b->livros[i].titulo); //Printa o livro com o id pesquisado
            pesquisaLivro = &b->livros[i];
            return pesquisaLivro;
        }
    }
    printf("Nenhum livro foi encontrado com o codigo inserido.");
    return pesquisaLivro;
}

void consultarLivros(Biblioteca* b) {
    int escolhaConsulta;
    printf("CONSULTAR LIVROS=========\n");
    printf("1 - Listar todos os livros cadastrados\n");
    printf("2 - Pesquisar livro a partir do código (ID)\n");
    printf(">");
    scanf("%d",&escolhaConsulta);

    switch (escolhaConsulta)
    {
        case 1:
            consultarLivrosListAll(b);
        break;
        case 2:
            consultarLivrosSearchId(b);
        break;
        default:
            printf("Opção Inválida");
    }
}

// Cadastro de pessoas

Pessoa cadastrarPessoa()
{
    Pessoa novaPessoa;
    printf("Digite o nome da pessoa: ");
    scanf("%[^\n]", novaPessoa.nome);
    printf("Digite o cpf da pessoa: ");
    scanf("%s", novaPessoa.cpf);
    return novaPessoa;
}


// Sistema de empréstimos de livros

void emprestarLivro(Biblioteca* b)
{
    Livro* livroEmprestimo = consultarLivrosSearchId(b);
    if (livroEmprestimo == NULL) return;
    if (livroEmprestimo->quantidadeDisponivel == 0)
    {
        printf("Não há exemplares disponíveis para empréstimos neste momento.\n");
        return;
    }
    Pessoa pessoaEmprestimo = cadastrarPessoa();
    // Coloca a pessoa que está pegando o livro emprestado no vetor pessoasEmprestimos na primeira posição livre do vetor.
    for (int i = 0; i < 10; i++) if (livroEmprestimo->pessoasEmprestimos[i].cpf[10] != '\0')
    {
        if (strcmp(pessoaEmprestimo.cpf,livroEmprestimo->pessoasEmprestimos[i].cpf) == 0)
        {
            printf("Essa pessoa já pegou esse livro emprestado\n");
            return;
        }
    }else
        {
            livroEmprestimo->pessoasEmprestimos[i] = pessoaEmprestimo;
            livroEmprestimo->quantidadeDisponivel--;
            printf("LIVRO: %s - %s, Foi emprestado para: %s - %s\n",livroEmprestimo->id,livroEmprestimo->titulo,pessoaEmprestimo.nome,pessoaEmprestimo.cpf);
            printf("Agora a quantidade disponível deste livro para empréstimos é: %d",livroEmprestimo->quantidadeDisponivel);
            return;
        }
}

// Devolução de livros

// Menu


int main(){
    Biblioteca novaBiblioteca = {0};
    cadastroLivros(&novaBiblioteca);
    consultarLivros(&novaBiblioteca);
    emprestarLivro(&novaBiblioteca);
 return 0;   
}