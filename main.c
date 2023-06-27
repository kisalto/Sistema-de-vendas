#include "header.h"

//########################################

//Funcoes de listagem:

//########################################

void criarLista(Lista * lista)
{
    lista->inicio = NULL;
}

void adicionarProduto(Lista * lista, item * produtos)
{
    if (lista->inicio == NULL)
    {
        No * novoNo = (No *) malloc(sizeof(No));
        novoNo->prox = lista->inicio;
        novoNo->ant = NULL;
        novoNo->produto = produtos;
        lista->inicio = novoNo;
    }
    else
    {
        No * ptr, *novoNo = (No *) malloc(sizeof(No));
        novoNo->produto = produtos;

        if (novoNo->produto->codigo < lista->inicio->produto->codigo) {
            novoNo->prox = lista->inicio;
            lista->inicio->ant = novoNo;
            lista->inicio = novoNo;

        } else {
            ptr = lista->inicio;
            while (ptr->produto->codigo > novoNo->produto->codigo)
                ptr = ptr->prox;
            novoNo->prox = ptr->prox;
            if (ptr->prox)
                ptr->prox->ant = novoNo;
            novoNo->ant = ptr;
            ptr->prox = novoNo;
        }
    }
}

void adicionarNota(Lista * lista, Nota * nota)
{

    if (lista->Cup == NULL)
    {
        No * novoNo = (No *) malloc(sizeof(No));
        novoNo->prox = lista->Cup;
        novoNo->cupom = nota;
        lista->Cup = novoNo;

    }
    else
    {
        No * ptr = lista->Cup;
        No * novoNo = (No *) malloc(sizeof(No));
        novoNo->cupom = nota;

        while (ptr->prox != NULL)
        {
            ptr = ptr-> prox;
        }

        novoNo->prox = NULL;
        ptr->prox = novoNo;
    }
}

void apaga(Lista * lista, uint64_t cod)
{
    No * deleta = NULL;
    No * atual = lista->inicio;

    if (atual->produto->codigo == cod)
    {
        lista->inicio = atual->prox;
        if (lista->inicio)
            lista->inicio->ant = NULL;
        free(atual);
    }
    else
    {
        while (atual->prox->produto->codigo != cod)
            atual = atual->prox;
        if (atual->prox)
        {
            deleta = atual->prox;
            atual->prox = deleta->prox;
            if (deleta->prox)
                deleta->prox->ant = atual;
            free(deleta);
        }
    }
}

//#########################
//       exibir
//#########################

void exibir (Lista * lista)
{
    No * atual = lista->inicio;
    if (atual == NULL)
        printf("Nao existem produtos\n");
    else
    {
        printf("[Codigo] {Estoque} | Nome - Preco(R$)\n");
        printf("--------------------------------------------------------------\n\n");
        while (atual != NULL)
        {
            printf("[%" PRIu64 "] {%d} | %s - R$ %.2f\n", atual->produto->codigo, atual->produto->estoque, atual->produto->nome, atual->produto->valor);
            atual = atual->prox;
        }
        printf("--------------------------------------------------------------\n\n");
    }
}

void exibirC (Lista * lista)
{
    No * atual = lista->Cup;
    if (atual == NULL)
        printf("Nao existem produtos\n");
    else
    {
        printf("[Codigo] {Estoque} | Nome - Preco(R$) - SubTotal\n");
        printf("--------------------------------------------------------------\n\n");
        while (atual != NULL)
        {
            printf("[%" PRIu64 "] {%d} | %s - R$ %.2f  - %.2f\n", atual->cupom->codigo, atual->cupom->quanti, atual->cupom->nome, atual->cupom->valor, atual->cupom->subtotal);
            atual = atual->prox;
        }
        printf("--------------------------------------------------------------\n\n");
    }
}

void exibirRel (Lista * lista)
{
    No * atual = lista->inicio;

    float total = 0;
    float subTotal = 0;

    if (atual == NULL)
    {
        printf("Nao existem produtos\n");
        system("pause");
        system("cls");

    }
    else
    {
        printf("[Codigo] {Estoque} | Nome - Preco(R$) - SubTotal\n");
        printf("--------------------------------------------------------------\n\n");
        while (atual != NULL)
        {
            subTotal = atual->produto->venda * atual->produto->valor;
            total += subTotal;
            printf("[%" PRIu64 "] {%d} | %s - R$ %.2f - %.2f\n", atual->produto->codigo, atual->produto->estoque, atual->produto->nome, atual->produto->valor, subTotal);
            atual = atual->prox;
        }

        printf("Total: %.2f", total);

        printf("\n--------------------------------------------------------------\n\n");
    }
}

//################################
//Buscar
//################################

item * buscar(Lista * lista, uint64_t cod)
{
    No * atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->produto->codigo == cod)
        {
            return atual->produto;
        }
        atual = atual->prox;
    }
    return NULL;

}

//########################################

//cadastro

//########################################

void cadastrar(Lista * lista)
{
    item * produtos = NULL;

    uint64_t cod = 0;
    int total = 0;
    int cont = 0;
    int estoque = 0;
    float valor = 0;
    char nome[25];
    char confirm = '\0';

    printf("Quantos produtos deseja adicionar?: ");
    scanf("%d", &total);
    getchar();

    while (cont < total && confirm != 's' && confirm != 'S')
    {
        printf("Produto [%d]\n", cont+1);
        printf("[Codigo > 0]: ");
        scanf("%" PRIu64, &cod);
        getchar();

        if (cod > 0)   // valida codigo
        {
            printf("Nome(max 25): ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            if (validarNome(nome) == 0)   // valida nome
            {
                printf("Preco\t    : R$");
                scanf("%f", &valor);
                getchar();
                if (validarValor(valor) == 0)   // valida valor
                {

                    printf("{Estoque}   : ");
                    scanf("%d", &estoque);
                    getchar();

                    if (validarEstoque(estoque) == 0)   // valida estoque
                    {

                        produtos = (item *) malloc(sizeof(item));
                        if (produtos == NULL)
                        {
                            printf("Erro na alocacao de memoria\n");
                            exit(-1);
                        }

                        produtos->codigo = cod;
                        sprintf(produtos->nome, nome);
                        produtos->valor = valor;
                        produtos->estoque = estoque;
                        produtos->venda = 0;

                        //Utilizacao de lista
                        adicionarProduto(lista, produtos);
                        cont++;

                        printf("Deseja continuar?\n");
                        scanf("%c", &confirm);
                        getchar();

                        //erros
                    }
                    else
                    {
                        printf("Estoque invalido!\n");
                        system("pause");
                        system("cls");
                        estoque = -1;
                    }
                }
                else
                {
                    printf("Valor invalido!\n");
                    system("pause");
                    system("cls");
                    valor = 0;
                }
            }
            else
            {
                printf("Nome invalido!\n");
                system("pause");
                system("cls");
                nome[0] = '\0';
            }
        }
        else
        {
            printf("Codigo de produto invalido!\n");
            system("pause");
            system("cls");
            cod = 0;
        }
    }
}

//########################################

//atualizar

//########################################

void atualizar(Lista * lista)
{

    item * produtos = NULL;

    uint64_t cod = 0;
    int quant = 0, op = 0;
    float valor = 0;
    char confirm = '\0';

    if (lista->inicio == NULL)
    {
        printf("Nenhum item cadastrado!\n");
        system("pause");
        system("cls");
    }
    else
    {
        while (confirm != 's' && confirm != 'S')
        {
            system("cls");

            exibir(lista);

            printf("\nEntre com o codigo do produto que deseja atualizar (0 para voltar): ");
            scanf("%" PRIu64, &cod);
            getchar();

            if (cod == 0)
            {
                system("cls");
                printf("Bye!\n");
                system("pause");
                system("cls");
                break;
            }

            produtos = buscar(lista, cod);

            if (produtos != NULL)
            {
                printf("O que deseja atualizar?\n");
                printf("1. Quantidade\n");
                printf("2. Valor\n");
                scanf("%d", &op);
                getchar();

                switch (op)
                {
                case 1:
                    printf("Entre com a nova quantidade: ");
                    scanf("%d", &quant);
                    getchar();

                    if (validarEstoque(quant) == 0)
                    {
                        printf("-------------------------------\n");
                        printf("Produto a ser atualizado: %s\n", produtos->nome);
                        printf("Tem certeza que deseja alterar o valor de {%d} para {%d}? (s/n)\n", produtos->estoque, quant);
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 's' || confirm == 'S')
                        {
                            produtos->estoque = quant;
                            printf("Estoque alterado com sucesso!\n");
                            system("pause");
                            system("cls");
                        }

                    }
                    else
                    {
                        printf("Quantidade invalida!\n");
                        system("pause");
                        system("cls");
                        quant = 0;
                    }
                    break;
                case 2:
                    printf("Entre com o novo valor: ");
                    scanf("%f", &valor);
                    getchar();

                    if (validarValor(valor) == 0)
                    {
                        printf("-------------------------------\n");
                        printf("Produto a ser atualizado: %s\n", produtos->nome);
                        printf("Tem certeza que deseja alterar o valor de {%.2f} para {%.2f}? (s/n)\n", produtos->valor, valor);
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 's' || confirm == 'S')
                        {
                            produtos->valor = valor;
                            printf("Valor alterado com sucesso!\n");
                            system("pause");
                            system("cls");
                        }

                    }
                    else
                    {
                        printf("Quantidade invalida!\n");
                        system("pause");
                        system("cls");
                        quant = 0;
                    }
                    break;
                default:
                    printf("opcao invalida!\n");
                    system("pause");
                    system("cls");
                    break;

                }
            }
            else
            {
                printf("Codigo de produto invalido!\n");
                system("pause");
                system("cls");
                cod = 0;
            }
        }
    }
}

//########################################

//excluir

//########################################

void excluir (Lista * lista)
{
    item * produtos = NULL;

    uint64_t cod;
    char confirm = '\0';

    if (lista->inicio == NULL)
    {
        printf("nenhum item cadastrado!\n");
        system("pause");
        system("cls");
    }
    else
    {
        while (confirm != 's' && confirm != 'S')
        {
            system("cls");

            exibir(lista);

            printf("\nEntre com o codigo do produto que deseja excluir (0 para voltar): ");
            scanf("%" PRIu64, &cod);
            getchar();

            produtos = buscar(lista, cod);

            if (produtos != NULL)
            {
                printf("-------------------------------\n");
                printf("Produto a ser excluir: %s\n", produtos->nome);
                printf("Tem certeza que deseja excluir? (s/n)\n");
                scanf("%c", &confirm);
                getchar();
                if (confirm == 's' || confirm == 'S') {
                    apaga(lista, cod);
                    printf("Item excluido com sucesso!\n");
                    system("pause");
                    system("cls");
                }

            }
            else if (cod == 0)
            {
                system("cls");
                break;

            }
            else
            {
                printf("Produto nao encontrado!\n");
                system("pause");
                system("cls");
            }
        }
    }
}

//########################################

//salvar

//########################################

void salvar(Lista * lista)
{

    if (!lista->inicio) {
        printf("Nenhum produto cadastrado!\n");
        system("pause");
        system("cls");
    } else {
        FILE *arquivo = fopen("produtos.txt", "w");
        if (arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo.\n");
            system("pause");
            system("cls");
            exit(-1);
        }

        No * atual = lista->inicio;

        if (atual == NULL)
        {
            printf("nenhum item cadastrado!\n");
            system("pause");
            system("cls");
        }
        else
        {
            while (atual != NULL)
            {
                fprintf(arquivo, "%" PRIu64 "\n", atual->produto->codigo);
                fprintf(arquivo, "%s\n", atual->produto->nome);
                fprintf(arquivo, "%.2f\n", atual->produto->valor);
                fprintf(arquivo, "%d\n", atual->produto->estoque);
                fprintf(arquivo, "%d\n", atual->produto->venda);
                atual = atual->prox;
            }
            
        }

        printf("Item salvo com sucesso!\n");
        system("pause");
        system("cls");

        fclose(arquivo);
    }
}

//########################################

//ler

//########################################

void ler(Lista * lista)
{

    //Limpa tudo
    No * proximo = NULL;
    No * atual = lista->inicio;

    while (proximo != NULL)
    {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(atual);
    free(proximo);

    //Recriar a lista
    criarLista(lista);

    //Abre o arquivo
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo produtos.txt\n");
        exit(1);
    }

    //Iniciou variaveis
    item * produtos = NULL;
    int tam = 0;

    while (!feof(arquivo))
    {
        produtos = (item *) malloc(sizeof(item));

        //Retira os valores do arquivo e coloca dentro de uma variavel
        fscanf(arquivo, "%" PRIu64 "\n", &produtos->codigo);
        fgets(produtos->nome, 25, arquivo);
        fscanf(arquivo, "%f\n", &produtos->valor);
        fscanf(arquivo, "%d\n", &produtos->estoque);
        fscanf(arquivo, "%d\n", &produtos->venda);

        //retira o \n do fgets
        tam = strlen(produtos->nome);
        produtos->nome[tam-1] = '\0';

        if (produtos->estoque > 0)
            adicionarProduto(lista, produtos);
    }

    printf("Arquivo lido com sucesso!\n");
    system("pause");
    system("cls");

    fclose(arquivo);
}

//########################################

//Menu de Produtos

//########################################

void menuProd (Lista * lista)
{
    int op = 0;

    while (op != 7)
    {
        printf("1. Exibir.\n");
        printf("2. Cadastrar.\n");
        printf("3. Atualizar.\n");
        printf("4. Excluir.\n");
        printf("5. Salvar.\n");
        printf("6. Ler.\n");
        printf("7. Voltar.\n");
        scanf("%d", &op);
        getchar();

        system("cls");

        switch (op)
        {
        case 1:
            exibir(lista);
            system("pause");
            system("cls");
            break;
        case 2:
            cadastrar(lista);
            system("cls");
            break;
        case 3:
            atualizar(lista);
            break;
        case 4:
            excluir(lista);
            break;
        case 5:
            salvar(lista);
            break;
        case 6:
            ler(lista);
            break;
        case 7:
            system("cls");
            printf("Tenha uma boa venda bebel!\n");
            system("pause");
            system("cls");
            break;
        default:
            printf("Opcao Invalida!\n");
            system("pause");
            system("cls");
            break;
        }
    }
}

//########################################

//Menu de Venda

//########################################

void menuVendas(Lista *lista)
{
    item * produtos = NULL;
    Nota * nota = NULL;

    int quantidade = 0;
    float total = 0;
    char confirmar = '\0';
    short int op = 0;
    uint64_t cod = 0;
    do
    {
        printf("O que deseja?\n");
        printf("1 - Realizar venda\n"
               "2 - Relatorio de vendas\n"
               "3 - Voltar\n");
        scanf("%hd", &op);
        getchar();

        switch(op)
        {
        case 1:
            lista->Cup = NULL;
            confirmar = '\0';
            
            while(confirmar != 's' && confirmar != 'S')
            {
                nota = (Nota *) malloc(sizeof(Nota));
                if (nota == NULL)
                {
                    printf("Erro na alocacao!\n");
                    exit(-1);
                }
                if(lista->inicio == NULL)
                {
                    printf("Nenhum produto cadastrado\n");
                    system("pause");
                    system("cls");
                    break;

                }
                else
                {
                    exibir(lista);

                    printf("Digite o codigo do item\n");
                    scanf("%" PRIu64, &cod);
                    getchar();
                    produtos = buscar(lista, cod);
                    if(produtos == NULL)
                    {
                        puts("Produto nao encontrado!");
                        system("pause");
                        system("cls");
                        break;
                    }
                    else
                    {
                        printf("Quantidade desejada Bebel? \n");
                        scanf("%i", &quantidade); //Leitura da Quantidade deseja pelo cliente
                        getchar();

                        if (quantidade > produtos->estoque || quantidade <= 0)
                        {
                            printf("Quantidade invalida!\n");
                            system("pause");
                            system("cls");
                        }
                        else
                        {
                            produtos->estoque -= quantidade;
                            produtos->venda += quantidade;

                            nota->codigo = produtos->codigo;
                            sprintf(nota->nome, produtos->nome);
                            nota->quanti = quantidade;
                            nota->valor = produtos->valor;
                            nota->subtotal = produtos->valor * quantidade;
                            total += nota->subtotal;

                            adicionarNota(lista, nota);
                        }

                        printf("Deseja continuar para o pagamento?(s/n)\n");
                        scanf("%c", &confirmar);
                        getchar();

                        system("cls");

                        if (confirmar == 's' || confirmar == 'S')
                        {
                            //salva e avan�a para o pagamento
                            finalizar(lista, nota, total);
                            salvar(lista);

                            //exibe cupom
                            exibirC(lista);

                            //Limpa o cupom
                            No * proximo = NULL;
                            No * atual = lista->Cup;

                            while (proximo != NULL)
                            {
                                proximo = atual->prox;
                                free(atual);
                                atual = proximo;
                            }
                            free(atual);
                            free(proximo);

                            system("pause");
                            system("cls");
                        }
                    }
                }
            }

            break;

        case 2:
            exibirRel(lista);
            system("pause");
            system("cls");
            break;
        case 3:
            puts("Voltando..");
            system("pause");
            system("cls");
            break;

        default:
            printf("Selecione uma opcao valida!\n");
            system("pause");
            system("cls");
            break;

        }
    }

    while (op != 3);
}

//########################################

//Pagamento

//########################################

void finalizar(Lista *lista, Nota *nota, float total)
{
    short int formapgt, parcela;
    float pagamento = 0, troco = 0;
    do
    {
        printf("Selecione a forma de pagamento\n"
               "-------------------------------\n"
               "1 - Pagamento a vista\n"
               "2 - Pagamento a prazo\n"
               "-------------------------------\n");
        scanf("%hd", &formapgt);
        getchar();
        switch (formapgt)
        {

        case 1:
            if (total < 50)
            {
                printf("Devido ao valor de sua compra\nVoce recebeu 5%% de desconto!\n");
                total = (total - (total * 0.05));
            }

            else if (total >= 50 && total < 100)
            {
                printf("Devido ao valor de sua compra\nVoce recebeu 10%% de desconto!\n");
                total = (total - (total * 0.1));
            }
            else
            {
                printf("Devido ao valor de sua compra\nVoce recebeu 18%% de desconto!\n");
                total = (total - (total * 0.18));
            }
            while (pagamento < total)
            {
                printf("O Total a se pagar eh: R$ %.2f", total);
                printf("\n---------------------------------------\n");
                printf("Insira o valor do pagamento: \n");
                scanf("%f", &pagamento);
                getchar();
                if (pagamento >= total)
                {
                    troco = pagamento - total;
                    total -= pagamento;
                    printf("O troco eh R$ %.2f\n", troco);
                    system("pause");
                }
                if (pagamento < 0)
                {
                    printf("Utilize um valor valido\n");
                }
                else
                {
                    total -= pagamento;
                    pagamento = 0;
                }
                system("cls");
            }
            break;
        case 2:
            while (parcela < 2 || parcela > 5)
            {
                system("cls");
                printf("----------------------\n"
                       "|  Qnt | %% De Juros  |\n"
                       "|  2x  |    5%%       |\n"
                       "|  3x  |    5%%       |\n"
                       "|  4x  |    8%%       |\n"
                       "|  5x  |    8%%       |\n"
                       "----------------------\n"
                       "Quantas parcelas?: ");
                scanf("%hd", &parcela);
                getchar();
                if (parcela < 2 || parcela > 5)
                    printf("Digite uma opcao valida!\n");
                else
                {
                    switch (parcela)
                    {
                    case 2:
                        total = (total + (total * 0.05));
                        nota->quanti = total / 2;
                        break;
                    case 3:
                        total = (total + (total * 0.05));
                        nota->quanti = total / 3;
                        break;
                    case 4:
                        total = (total + (total * 0.08));
                        nota->quanti = total / 4;
                        break;
                    case 5:
                        total = (total + (total * 0.08));
                        nota->quanti = total / 5;
                        break;
                    }
                    //  printf("Ficaram %i Parcelas De R$ %.2f \n", parcela, nota->quanti);
                    printf("Em um total de : R$ %.2f\n", total);
                    system("pause");
                    system("cls");
                }
            }
        }

    }
    while (formapgt < 1 || formapgt > 2);
}

//########################################

//Main Menu

//########################################
int main()
{
    Lista * lista = (Lista *) malloc(sizeof(Lista));
    if (lista == NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(-1);
    }

    criarLista(lista);

    int op = 0;

    while (op != 3)
    {
        printf("1. Produtos.\n");
        printf("2. Vendas.\n");
        printf("3. Sair.\n");
        scanf("%d", &op);
        getchar();

        system("cls");

        switch (op)
        {
        case 1:
            menuProd(lista);
            break;
        case 2:
            menuVendas(lista);
            break;
        case 3:
            printf("Obrigado por usar nosso sistema bebel!\n");
            break;
        default:
            printf("Opcao Invalida!\n");
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}

//########################################

//Confirmacoes

//########################################

int validarNome(char nome[25])
{
    int cont = 0;
    for (int i = 0; i < strlen(nome); i++)
    {
        if (nome[i] == ' ')
            cont++;
    }
    if (nome == NULL || nome[0] == '\0' || nome[0] == '\n')
        return 1;
    else if (cont == strlen(nome)-1)
        return 1;
    else if (strlen(nome) > 25)
        return 1;
    else
        return 0;
}

int validarValor(float valor)
{
    if (valor < 0)
        return 1;
    else
        return 0;
}

int validarEstoque(int estoque)
{
    if (estoque < 0)
        return 1;
    else
        return 0;
}
