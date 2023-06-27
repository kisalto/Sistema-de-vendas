#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

//estrutura base
typedef struct item {
    uint64_t codigo;
    char nome[25];
    float valor;
    int estoque;
    int venda;
} item;

//estrutura de venda
typedef struct Nota{
    uint64_t codigo;
    char nome[25];
    float valor;
    int quanti;
    float subtotal;
}Nota;

//estrutura no
typedef struct No {
    item * produto;
    Nota * cupom;
    struct No* ant;
    struct No *prox;
} No;

//estrutura lista
typedef struct Lista {
    No *inicio;
    No * Cup;
} Lista;


//Funcoes de listagem
void criarLista(Lista *);

//funcoes principais
void menuVendas(Lista *);
void menuProd(Lista *);

void cadastrar (Lista *);
void exibir (Lista *);
void atualizar (Lista *);
void excluir (Lista *);
void salvar(Lista *);
void ler(Lista *);
void finalizar(Lista *, Nota*, float);



//validacoes
int validarCod(Lista*, uint64_t);
int acharCod(Lista*, uint64_t);
int acharRel(Lista *, uint64_t);
int validarNome(char nome[25]);
int validarValor(float);
int validarEstoque(int);


#endif // HEADER_H_INCLUDED
