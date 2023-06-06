// Mariana Nunes Terol - UC22200554

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define TAM 2
#define MAX_FABRICANTES 2
#define MAX_PRODUTOS 2
#define MAX_UF 27
#define MAX_NOME 100

typedef struct Fabricante
{
    char fabricante[50];
    char nomeM[50];
    char telefone[50];
    char site[50];
    char uf[3];
} Fabricante;

typedef struct Produto
{
    char descricao[100];
    float peso;
    float valorc;
    float valorv;
    float perclc;
    float valorlc;
    float percentualLucro;
    struct Fabricante fabricante;
} Produto;

const char *unidadesFederacao[MAX_UF] = {
    "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS",
    "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC",
    "SP", "SE", "TO"};

//-----------------------------------------------------------------------------------------------

void listarProdutosPorValor(Produto produtos[], int numProdutos)
{
    int i, j;

    for (i = 0; i < numProdutos - 1; i++)
    {
        for (j = 0; j < numProdutos - i - 1; j++)
        {
            if (produtos[j].valorv > produtos[j + 1].valorv)
            {
                Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    printf("Produtos em ordem crescente de valor:\n");

    for (i = 0; i < numProdutos; i++)
    {
        printf("- %s (R$ %.2f)\n", produtos[i].descricao, produtos[i].valorv);
    }
}

//-----------------------------------------------------------------------------------------------

int main(void)
{

    char a = 'r', b = 'n', c = 'e';
    int op = 0, i = 0, j = 0;
    int numProdutos = 0;
    int menorvalor, maiorvalor;
    int estados[MAX_UF] = {0};
    float maiorValor = 0;
    float menorValor;

    void listarProdutosPorValor(Produto produtos[], int numProdutos);

    Fabricante fabricantes[MAX_FABRICANTES];
    Produto produtos[MAX_PRODUTOS];

    menorValor = produtos[MAX_PRODUTOS].valorv;

    do
    {
        printf("\tDigite o numero correspondente a opcao desejada:\n\n");

        printf("[0] cadastrar fabricante\n");
        printf("[1] Cadastrar produto\n");
        printf("[2] Listar todas as marcas\n");
        printf("[3] Listar todos os produtos\n");
        printf("[4] Listar os produtos de um determinado estado\n");
        printf("[5] Listar os produtos de uma determinada marca\n");
        printf("[6] Apresentar o(s) estado(s) onde estÃ¡ registrado o produto mais caro\n");
        printf("[7] Apresentar o(s) fabricante(s) onde estÃ¡ registrado o produto mais barato\n");
        printf("[8] Listar todos os produtos em ordem crescente de valor\n");
        printf("[9] Listar todos os produtos em ordem crescente de maior 'valor do lucro'\n");
        printf("[10] Listar todos os produtos em ordem crescente de maior 'percentual de lucro'\n");

        printf("[11] Sair do programa\n");

        printf("\nOpcao: ");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 0:
            do
            {
                for (i = 0; i < MAX_FABRICANTES; i++)
                {

                    printf("\tFabricante:\n");
                    fgets(fabricantes[i].fabricante, 100, stdin);

                    printf("\nInforme o nome da marca: ");
                    fgets(fabricantes[i].nomeM, 100, stdin);

                    printf("\nInforme o telefone: ");
                    fgets(fabricantes[i].telefone, 100, stdin);

                    printf("\nInforme o site: ");
                    fgets(fabricantes[i].site, 100, stdin);

                    printf("Unidades da Federacao cadastradas:\n");
                    for (j = 0; j < MAX_UF; j++)
                    {
                        printf("%d. %s\n", j + 1, unidadesFederacao[j]);
                    }
                    int uf = -1;
                    printf("Informe o numero correspondente a sua UF: ");
                    scanf("%d", &uf);
                    getchar();

                    if (uf >= 1 && uf <= MAX_UF)
                    {
                        const char *ufEscolhida = unidadesFederacao[uf - 1];
                        memcpy(fabricantes[i].uf, ufEscolhida, strlen(ufEscolhida));
                    }
                    else
                    {
                        printf("Opcao invalida.\n");
                    }

                    printf("\n");
                }

                printf("Deseja cadastrar mais um produto? (S/N): ");
                scanf(" %c", &b);
                getchar();

            } while (b != 'N' && b != 'n');
            break;

        case 1:
            do
            {
                for (i = 0; i < MAX_PRODUTOS; i++)
                {
                    printf("\tProduto:\n");

                    printf("Informe a descricao do produto: ");
                    scanf(" %[^\n]s", produtos[i].descricao);
                    while (getchar() != '\n')
                        ;

                    printf("Informe o peso do produto: ");
                    scanf("%f", &produtos[i].peso);
                    while (getchar() != '\n')
                        ;

                    printf("Informe o valor de compra: ");
                    scanf("%f", &produtos[i].valorc);
                    while (getchar() != '\n')
                        ;

                    printf("Informe o valor de venda: ");
                    scanf("%f", &produtos[i].valorv);
                    while (getchar() != '\n')
                        ;

                    printf("Fabricante: ");
                    int fabricanteIndice;
                    while (true)
                    {
                        
                        scanf("%d", &fabricanteIndice);
                        while (getchar() != '\n');

                        if (fabricanteIndice >= 0 && fabricanteIndice < MAX_FABRICANTES)
                        {
                            produtos[i].fabricante = fabricantes[fabricanteIndice];
                            break;
                        }
                        else
                        {
                            printf("Indice de fabricante invalido escreva o indice entre 0 e 1.\n");
                        }
                    }

                    if (produtos[i].valorc != 0)
                    {
                        produtos[i].percentualLucro = (produtos[i].valorlc / produtos[i].valorc) * 100;
                    }
                    else
                    {
                        produtos[i].percentualLucro = 0;
                    }

                    produtos[i].valorlc = produtos[i].valorv - produtos[i].valorc;

                    produtos[i].percentualLucro = (produtos[i].valorlc / produtos[i].valorc) * 100;

                    if (fabricanteIndice >= 0 && fabricanteIndice < MAX_FABRICANTES)
                    {
                        produtos[i].fabricante = fabricantes[fabricanteIndice];
                    }
                    printf("\n");
                    numProdutos +=1 ; // incrementar numero de produtos
                }

                printf("Deseja cadastrar mais um produto? (S/N): ");
                scanf(" %c", &b);
                while (getchar() != '\n')
                    ;

            } while (b != 'N' && b != 'n');
            break;

        case 2:
            do
            {
                printf("=============================================\n");
                printf("\tListar todas as marcas\n");
                printf("=============================================\n");
                printf("marca  |   site     |    telefone     |  uf\n");
                printf("---------------------------------------------\n");
                for (i = 0; i < MAX_FABRICANTES; i++)
                {
                    printf("\tMarca %d:\n", i + 1);
                    printf("Nome: %s\t", fabricantes[i].nomeM);
                    printf("Site: %s\t", fabricantes[i].site);
                    printf("Telefone: %s\t", fabricantes[i].telefone);
                    printf("UF: %s\n\t", fabricantes[i].uf);
                    printf("Fabricante: %s\t", fabricantes[i].fabricante);
                    printf("\n");
                }

                printf("Digite R para voltar para o menu principal:\n");
                scanf(" %c", &a);

            } while (a != 'R' && a != 'r');
            break;

        case 3:

            do
            {
                printf("====================================================================================================================\n");
                printf("\t\t\t\tListar todos os Produtos\n");
                printf("====================================================================================================================\n");
                printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
                printf("--------------------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < MAX_PRODUTOS; i++)
                {
                    printf("\t\t\t\tProduto %d:\n\n", i + 1);
                    printf("Descricao: %s\t\n", produtos[i].descricao);
                    printf("Peso: %.2f\t\n", produtos[i].peso);
                    printf("Valor de Compra: %.2f\t\n", produtos[i].valorc);
                    printf("Valor de Venda: %.2f\t\n", produtos[i].valorv);
                    printf("Valor do Lucro: %.2f\t\n", produtos[i].valorlc);
                    printf("Percentual de Lucro: %.2f%%\t\n", produtos[i].percentualLucro);
                    printf("Fabricante: %s\n", produtos[i].fabricante.nomeM);

                    printf("\n");
                }

                printf("Digite R para voltar para o menu principal:\n");
                scanf(" %c", &a);

            } while (a != 'R' && a != 'r');
            break;

        case 4:
            do
            {
                char estado[3];
                printf("Digite a sigla do estado para listar os produtos: ");
                scanf("%s", estado);
                getchar();

                printf("====================================================================================================================\n");
                printf("\t\t\t\tProdutos no estado %s\n", estado);
                printf("====================================================================================================================\n");
                printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
                printf("--------------------------------------------------------------------------------------------------------------------\n");

                int encontrado = 0;
                for (i = 0; i < numProdutos; i++)
                {
                    if (strcmp(produtos[i].fabricante.uf, estado) == 0)
                    {
                        encontrado = 1;
                        printf("\t\t\t\tProduto %d:\n\n", i + 1);
                        printf("Descricao: %s\t", produtos[i].descricao);
                        printf("Peso: %.2f\t", produtos[i].peso);
                        printf("Valor de Compra: %.2f\t", produtos[i].valorc);
                        printf("Valor de Venda: %.2f\t", produtos[i].valorv);
                        printf("Valor do Lucro: %.2f\t", produtos[i].valorlc);
                        printf("Percentual de Lucro: %.2f%%\t", produtos[i].percentualLucro);
                        printf("Fabricante: %s\n\t", produtos[i].fabricante.nomeM);

                        printf("\n");
                    }
                }

                if (!encontrado)
                {
                    printf("Nenhum produto encontrado no estado %s.\n", estado);
                }

                printf("Digite R para voltar para o menu principal:\n");
                scanf(" %c", &a);
                getchar();

            } while (a != 'R' && a != 'r');
            break;

        case 5:
            do
            {
                char marca[MAX_NOME];
                printf("Digite o nome da marca para listar os produtos: ");
                fgets(marca, MAX_NOME, stdin);
                *(char*)(strchr(marca,'\n')) = '\0';

                printf("====================================================================================================================\n");
                printf("\t\t\t\tProdutos da marca %s\n", marca);
                printf("====================================================================================================================\n");
                printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
                printf("--------------------------------------------------------------------------------------------------------------------\n");

                int encontrado = 0;
                for (i = 0; i < numProdutos; i++)
                {
                    if (strcmp(produtos[i].fabricante.nomeM, marca) == 0)
                    {
                        encontrado = 1;
                        printf("\t\t\t\tProduto %d:\n\n", i + 1);
                        printf("Descricao: %s\t", produtos[i].descricao);
                        printf("Peso: %.2f\t", produtos[i].peso);
                        printf("Valor de Compra: %.2f\t", produtos[i].valorc);
                        printf("Valor de Venda: %.2f\t", produtos[i].valorv);
                        printf("Valor do Lucro: %.2f\t", produtos[i].valorlc);
                        printf("Percentual de Lucro: %.2f%%\t", produtos[i].percentualLucro);
                        printf("Fabricante: %s\n\t", produtos[i].fabricante.nomeM);

                        printf("\n");
                    }
                }

                if (!encontrado)
                {
                    printf("Nenhum produto encontrado da marca %s.\n", marca);
                }

                printf("Digite R para voltar para o menu principal:\n");
                scanf(" %c", &a);
                getchar();

            } while (a != 'R' && a != 'r');
            break;

        case 6:

            for (i = 0; i < numProdutos; i++)
            {
                if (produtos[i].valorv > maiorValor)
                {
                    maiorValor = produtos[i].valorv;
                }
            }

            printf("Estado(s) onde estÃ¡ registrado o produto mais caro:\n");

            for (i = 0; i < numProdutos; i++)
            {
                if (produtos[i].valorv == maiorValor)
                {
                    int estadoEncontrado = 0;

                    for (j = 0; j < MAX_UF; j++)
                    {
                        if (strcmp(produtos[i].fabricante.uf, unidadesFederacao[j]) == 0)
                        {
                            estados[j] = 1;
                            estadoEncontrado = 1;
                            break;
                        }
                    }

                    if (estadoEncontrado)
                    {
                        printf("- %s\n", produtos[i].fabricante.uf);
                    }
                }
            }

            printf("Digite R para voltar para o menu principal:\n");
            scanf(" %c", &a);
            getchar();

            break;
        case 7:

            for (i = 1; i < numProdutos; i++)
            {
                if (produtos[i].valorv < menorValor)
                {
                    menorValor = produtos[i].valorv;
                }
            }

            printf("Fabricante(s) onde estÃ¡ registrado o produto mais barato:\n");

            for (i = 0; i < numProdutos; i++)
            {
                if (produtos[i].valorv == menorValor)
                {
                    printf("- %s\n", produtos[i].fabricante.nomeM);
                }
            }

            printf("Digite R para voltar para o menu principal:\n");
            scanf(" %c", &a);
            getchar();

            break;

        case 8: // nn ta funcionando (arrumar)
                //  Codigo para listar todos os produtos em ordem crescente de valor
            listarProdutosPorValor(produtos, numProdutos);
            do
            {
                printf("====================================================================================================================\n");
                printf("\t\t\t\tListar todos os Produtos\n");
                printf("====================================================================================================================\n");
                printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
                printf("--------------------------------------------------------------------------------------------------------------------\n");
                for (i = 0; i < numProdutos; i++)
                {
                    printf("- %s (R$ %.2f)\n", produtos[i].descricao, produtos[i].valorv);
                }

                printf("Digite R para voltar para o menu principal:\n");
                scanf(" %c", &a);

            } while (a != 'R' && a != 'r');
            break;

        case 9:
            printf("====================================================================================================================\n");
            printf("\t\t\t\tProdutos em ordem crescente de valor de lucro\n");
            printf("====================================================================================================================\n");
            printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
            printf("--------------------------------------------------------------------------------------------------------------------\n");

            // Ordenar os produtos por valor de lucro usando bubble sort
            for (i = 0; i < numProdutos - 1; i++)
            {
                for (j = 0; j < numProdutos - i - 1; j++)
                {
                    if (produtos[j].valorlc > produtos[j + 1].valorlc)
                    {
                        Produto temp = produtos[j];
                        produtos[j] = produtos[j + 1];
                        produtos[j + 1] = temp;
                    }
                }
            }

            // Imprimir os produtos em ordem crescente de valor de lucro
            for (i = 0; i < numProdutos; i++)
            {
                printf("\t\t\t\tProduto %d:\n\n", i + 1);
                printf("Descricao: %s\t", produtos[i].descricao);
                printf("Peso: %.2f\t", produtos[i].peso);
                printf("Valor de Compra: %.2f\t", produtos[i].valorc);
                printf("Valor de Venda: %.2f\t", produtos[i].valorv);
                printf("Valor do Lucro: %.2f\t", produtos[i].valorlc);
                printf("Percentual de Lucro: %.2f%%\t", produtos[i].percentualLucro);
                printf("Fabricante: %s\n\t", produtos[i].fabricante.nomeM);

                printf("\n");
            }

            printf("Digite R para voltar para o menu principal:\n");
            scanf(" %c", &a);
            getchar();
            break;

        case 10:
            printf("====================================================================================================================\n");
            printf("\t\t\t\tProdutos em ordem crescente de percentual de lucro\n");
            printf("====================================================================================================================\n");
            printf("Descricao | peso | valor de compra | valor de venda | valor de lucro | percentual de lucro |  Fabricante\n");
            printf("--------------------------------------------------------------------------------------------------------------------\n");

            // Ordenar os produtos por percentual de lucro usando bubble sort
            for (i = 0; i < numProdutos - 1; i++)
            {
                for (j = 0; j < numProdutos - i - 1; j++)
                {
                    if (produtos[j].percentualLucro > produtos[j + 1].percentualLucro)
                    {
                        Produto temp = produtos[j];
                        produtos[j] = produtos[j + 1];
                        produtos[j + 1] = temp;
                    }
                }
            }

            // Imprimir os produtos em ordem crescente de percentual de lucro
            for (i = 0; i < numProdutos; i++)
            {
                printf("\t\t\t\tProduto %d:\n\n", i + 1);
                printf("Descricao: %s\t", produtos[i].descricao);
                printf("Peso: %.2f\t", produtos[i].peso);
                printf("Valor de Compra: %.2f\t", produtos[i].valorc);
                printf("Valor de Venda: %.2f\t", produtos[i].valorv);
                printf("Valor do Lucro: %.2f\t", produtos[i].valorlc);
                printf("Percentual de Lucro: %.2f%%\t", produtos[i].percentualLucro);
                printf("Fabricante: %s\n\t", produtos[i].fabricante.nomeM);
                printf("--------------------------------------------------------------------------------------------------------------------\n");
                printf("\n");
            }

            printf("Digite R para voltar para o menu principal:\n");
            scanf(" %c", &a);
            getchar();

            break;
        case 11:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }

    } while (op != 11);

    return 0;
}
