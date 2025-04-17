#include <stdio.h>

#define TAMCli 3
#define TAMProd 3
#define TAMVendas 100


typedef struct {
    int id;
    char nome[20];
    int quantidade;
    float valor;
} Produto;

typedef struct {
    int id;
    char nome[20];
} Cliente;

typedef struct {
    int idCliente;
    int idProduto;
    int quantProduto;
    float valorTotal;
} Venda;

void cadastrarCliente(Cliente c[], int *totalClientes) {
    for (int i = 0; i < TAMCli; i++) {
        printf("Cliente %d, Primeiro Nome: ", i + 1);
        scanf("%s", c[i].nome);
        c[i].id = i + 1;
    }
    *totalClientes = TAMCli;
}

void cadastrarProduto(Produto p[], int *totalProdutos) {
    for (int i = 0; i < TAMProd; i++) {
        printf("\nProduto %d - Nome: ", i + 1);
        scanf("%s", p[i].nome);

        // Validacao para aceitar apenas valores positivos
        do {
            printf("Quantidade: ");
            scanf("%d", &p[i].quantidade);

            if (p[i].quantidade < 1) {
                printf("valor invalido!\n");
            }
        } while (p[i].quantidade < 1);


        // Validacao para aceitar apenas valores positivos
        do {
            printf("Valor: ");
            scanf("%f", &p[i].valor);

            if (p[i].valor <= 0) {
                printf("Valor nao permitido. Digite novamente.\n");
            }
        } while (p[i].valor <= 0);

        p[i].id = i + 1;
    }

    *totalProdutos = TAMProd;
}

void consultarCliente(Cliente c[], int totalClientes) {
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Clientes ---");
    for (int i = 0; i < totalClientes; i++) {
        printf("\nId: %d", c[i].id);
        printf("\nNome: %s\n", c[i].nome);
    }
}

void consultarProduto(Produto p[], int totalProdutos) {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Produtos ---");
    for (int i = 0; i < totalProdutos; i++) {
        printf("\nId: %d", p[i].id);
        printf("\nNome: %s", p[i].nome);
        printf("\nQuantidade: %d", p[i].quantidade);
        printf("\nValor: R$ %.2f", p[i].valor);
        printf("\n--------------------------");
    }
}

//Realizar venda
void realizarVenda(Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos, Venda vendas[], int *totalVendas) {
    if (totalClientes == 0 || totalProdutos == 0) {
        printf("\nNao ha clientes ou produtos cadastrados.\n");
        return;
    }

    int idCli, idProd, quantidade;
    printf("\nID do cliente: ");
    scanf("%d", &idCli);
    printf("ID do produto: ");
    scanf("%d", &idProd);
    printf("Quantidade desejada: ");
    scanf("%d", &quantidade);

    //Verifica cliente
    int clienteEncontrado = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idCli) {
            clienteEncontrado = 1;
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    //Verifica produto
    int produtoEncontrado = 0;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].id == idProd) {
            produtoEncontrado = 1;

            if (quantidade > produtos[i].quantidade) {
                printf("Estoque insuficiente. Estoque atual: %d\n", produtos[i].quantidade);
                return;
            }

            // Realiza venda
            vendas[*totalVendas].idCliente = idCli;
            vendas[*totalVendas].idProduto = idProd;
            vendas[*totalVendas].quantProduto = quantidade;
            vendas[*totalVendas].valorTotal = quantidade * produtos[i].valor;
            produtos[i].quantidade -= quantidade;

            printf("Venda realizada com sucesso! Valor total: R$ %.2f\n", vendas[*totalVendas].valorTotal);
            (*totalVendas)++;
            return;
        }
    }

    if (!produtoEncontrado) {
        printf("Produto nao encontrado.\n");
    }
}

//Consultar vendas
void consultarVendas(Venda vendas[], int totalVendas) {
    if (totalVendas == 0) {
        printf("\nNenhuma venda realizada ainda.\n");
        return;
    }

    printf("\n--- Lista de Vendas ---");
    for (int i = 0; i < totalVendas; i++) {
        printf("\nCliente ID: %d", vendas[i].idCliente);
        printf("\nProduto ID: %d", vendas[i].idProduto);
        printf("\nQuantidade: %d", vendas[i].quantProduto);
        printf("\nValor total: R$ %.2f", vendas[i].valorTotal);
        printf("\n--------------------------");
    }
}

int main() {
    int opcao, sair = 0;
    int totalClientes = 0, totalProdutos = 0, totalVendas = 0;

    Cliente clientes[TAMCli];
    Produto produtos[TAMProd];
    Venda vendas[TAMVendas];

    do {
        printf("\n\n>>>> Sistema de Vendas <<<<");
        printf("\n1 - Cadastrar Clientes");
        printf("\n2 - Cadastrar Produtos");
        printf("\n3 - Consultar Clientes");
        printf("\n4 - Consultar Produtos");
        printf("\n5 - Realizar Venda");
        printf("\n6 - Consultar Vendas");
        printf("\n7 - Sair");
        printf("\n>>>> Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, &totalClientes);
                break;
            case 2:
                cadastrarProduto(produtos, &totalProdutos);
                break;
            case 3:
                consultarCliente(clientes, totalClientes);
                break;
            case 4:
                consultarProduto(produtos, totalProdutos);
                break;
            case 5:
                realizarVenda(clientes, totalClientes, produtos, totalProdutos, vendas, &totalVendas);
                break;
            case 6:
                consultarVendas(vendas, totalVendas);
                break;
            case 7:
                sair = 1;
                break;
            default:
                printf("\nOpcao invalida!");
        }

    } while (!sair);

    return 0;
}
