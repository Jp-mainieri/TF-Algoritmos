#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[100];
    long cpf;
}Pessoa;

typedef struct{
    char id[20];
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    int quantidadeDisponivel;
    Pessoa pessoasEmprestimos[50];
    int contadorEmprestimos;
}Livro;

typedef struct{
    Livro livros[100];
    int qLivros;
}Biblioteca;

void CadastroLivros(Biblioteca *b) {
    printf("%d",b->qLivros);
    if (b->qLivros == 100) {
        printf("Nao tem como cadastrar mais livros nesta Biblioteca");
        return;
    }
    int qCadastro;
    
    do{
        printf("Digite quantos livros voce deseja cadastrar: ");
        scanf("%d",&qCadastro);
        if (b->qLivros + qCadastro > 100){
            printf("Quantidade de livros para cadastrar ultrapassa o limite da Biblioteca");
        }
    }while(b->qLivros + qCadastro > 100);

    const int inicioCadastro = b->qLivros;
    const int finalCadastro = b->qLivros + qCadastro;

    for (int i = inicioCadastro; i < finalCadastro; i++){
        int idCadastro;
        printf("Digite o ID do livro: ");
        scanf("%d",&b->livros[i].id);
        for (int j = 0; j < b->qLivros; j++){
            if(strcmp(b->livros[i].id,b->livros[j].id) == 0){
                printf("Ja existe um livro com esse codigo, retornando...");
                return;
            }
        }
        printf("Digite o titulo do Livro: ");
        scanf(" %[^\n]", b->livros[i].titulo);
        printf("Digite o nome do autor do Livro: ");
        scanf(" %[^\n]", b->livros[i].autor);
        printf("Digite o ano de publicacao do Livro: ");
        scanf(" %d", &b->livros[i].anoPublicacao);
        printf("Digite a quantidade disponivel do Livro: ");
        scanf(" %d", &b->livros[i].quantidadeDisponivel);
        printf("==============================");
        b->qLivros++;
    }
}

void ConsultarLivros(Biblioteca *b) {

}

int main(){
    Biblioteca novaBiblioteca = {0};
    CadastroLivros(&novaBiblioteca);
 return 0;   
}