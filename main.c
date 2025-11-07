#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definindo as estruturas de dados

typedef struct{
    char nome[100];
    char cpf[12]; // Precisa ser string por poder começar com 0
}Pessoa;

typedef struct{
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    char id[20]; // Precisa ser string por poder começar com 0
    int quantidadeDisponivel;
    Pessoa* pessoasEmprestimos[11];
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
        // Verifica duplicidade comparando o id informado com os já cadastrados
        for (int j = 0; j < b->qLivros; j++){
            if(strcmp(idCadastro, b->livros[j].id) == 0){
                printf("Ja existe um livro com esse codigo, retornando...\n");
                break; // não cadastra este livro, mas continua para a próxima iteração
            }
        }

        strcpy(b->livros[i].id,idCadastro);
        printf("Digite o titulo do Livro: ");
        scanf(" %99[^\n]", b->livros[i].titulo);
        printf("Digite o nome do autor do Livro: ");
        scanf(" %99[^\n]", b->livros[i].autor);
        printf("Digite o ano de publicacao do Livro: ");
        scanf(" %d", &b->livros[i].anoPublicacao);
        printf("Digite a quantidade disponivel do Livro (max 10): ");
        scanf(" %d", &b->livros[i].quantidadeDisponivel);
        // inicializa campo de empréstimos
        b->livros[i].contadorEmprestimos = 0;
        for (int k = 0; k < 11; k++) b->livros[i].pessoasEmprestimos[k] = NULL;
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
    // Usa espaço antes do % para descartar newline pendente
    scanf(" %99[^\n]", novaPessoa.nome);
    printf("Digite o cpf da pessoa: ");
    scanf(" %11s", novaPessoa.cpf);
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
    // Verifica se já existe empréstimo para esse CPF
    for (int i = 0; i < 11; i++){
        if (livroEmprestimo->pessoasEmprestimos[i] != NULL){
            if (strcmp(pessoaEmprestimo.cpf, livroEmprestimo->pessoasEmprestimos[i]->cpf) == 0){
                printf("Essa pessoa já pegou esse livro emprestado\n");
                return;
            }
        }
    }
    // inserir na primeira posição livre
    for (int i = 0; i < 11; i++){
        if (livroEmprestimo->pessoasEmprestimos[i] == NULL){
            Pessoa* p = malloc(sizeof(Pessoa));
            *p = pessoaEmprestimo;
            livroEmprestimo->pessoasEmprestimos[i] = p;
            livroEmprestimo->contadorEmprestimos++;
            livroEmprestimo->quantidadeDisponivel--;
            printf("LIVRO: %s - %s, Foi emprestado para: %s - %s\n",livroEmprestimo->id,livroEmprestimo->titulo,pessoaEmprestimo.nome,pessoaEmprestimo.cpf);
            printf("Agora a quantidade disponível deste livro para empréstimos é: %d\n",livroEmprestimo->quantidadeDisponivel);
            return;
        }
    }
    printf("Não há espaço para registrar mais empréstimos para este livro.\n");
}

// Devolução de livros
void devolverLivro(Biblioteca* b)
{
    Livro* livroDevolucao = consultarLivrosSearchId(b);
    if (livroDevolucao == NULL) return;
    if (livroDevolucao->pessoasEmprestimos[0] == NULL)
    {
        printf("O livro: %s não está emprestado para ninguém",livroDevolucao->titulo);
        return;
    }else
    {
        char pesquisaCliente[100];
        bool encontrouCliente = false;
        int idCliente = 0;
        printf("Que cliente está devolvendo o livro?");
        scanf("%s", pesquisaCliente);
        for (idCliente = 0; idCliente < 11; idCliente++)
        {
            if (livroDevolucao->pessoasEmprestimos[idCliente] == NULL) continue;
            if (strcmp(pesquisaCliente,livroDevolucao->pessoasEmprestimos[idCliente]->nome) == 0)
            {
                encontrouCliente = true;
                break;
            }
        }
        if (encontrouCliente)
        {
            // libera a memória do registro que está sendo devolvido
            free(livroDevolucao->pessoasEmprestimos[idCliente]);
            // desloca os demais registros para preencher o buraco
            for (int k = idCliente; k < 10; k++){
                livroDevolucao->pessoasEmprestimos[k] = livroDevolucao->pessoasEmprestimos[k+1];
            }
            livroDevolucao->pessoasEmprestimos[10] = NULL;
            if (livroDevolucao->contadorEmprestimos > 0) livroDevolucao->contadorEmprestimos--;
            livroDevolucao->quantidadeDisponivel++;
            printf("Devolução registrada com sucesso. Agora disponível: %d\n", livroDevolucao->quantidadeDisponivel);
        }
    }
}
//Remoção de livros
void removerLivro(Biblioteca* b){
    
}


// Menu


int main(){
    Biblioteca novaBiblioteca = {0};
    cadastroLivros(&novaBiblioteca);
    consultarLivros(&novaBiblioteca);
    emprestarLivro(&novaBiblioteca);
 return 0;   
}