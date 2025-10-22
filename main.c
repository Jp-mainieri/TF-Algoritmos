#include <stdio.h>

typedef struct{
    char nome[100];
    long cpf;
}Pessoa;

typedef struct{
    int id;
    char titulo[100];
    char autor[100];
    int anoPublicacao;
    int quantidadeDisponivel;
    Pessoa pessoasEmprestimos[50];
    int contadorEmprestimos;
}Livro;

typedef struct{
    Livro livros[99];
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
            printf("Quantidade de livros a cadastrar ultrapassa o limite da Biblioteca");
        }
    }while(b->qLivros + qCadastro > 100);
    
    for (int i = b->qLivros; i < b->qLivros + qCadastro ; i++){
        int idCadastro;
        printf("Digite o ID do livro: ");
        scanf("%d",&b->livros[i].id);
        for (int j = 0; j < b->qLivros; j++){
            if(b->livros[i].id == b->livros[j].id){
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
        b->qlivros++;
    }
}

void ConsultarLivros(Biblioteca *b) {

}

int main(){
    Biblioteca bibi = {0};
    CadastroLivros(&bibi);
 return 0;   
}