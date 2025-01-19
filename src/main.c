#include <stdio.h>
#include <stdbool.h>
#include "../include/trie.h"
#include "../include/avl.h"
#include "../include/jogo.h"

int main(void)
{
    Node *trie = criar_Node();
    char **matriz;
    int linhas, colunas;
    No *raiz = NULL;
    bool rodando = true;
    menu();
    while (rodando)
    {
        int operations;
        if (scanf("%d", &operations) != 1) // Tratar entradas não numéricas
        {
            printf("Opção inválida!\n");
            while (getchar() != '\n')
                continue;
        }
        switch (operations)
        {
        case 0:
            rodando = false;
            break;
        case 1:
            menu();
            break;
        case 2:
            matriz = ler_tabuleiro("data/tabuleiro.txt", &linhas, &colunas);
            if (matriz == NULL)
            {
                printf("Erro ao carregar o tabuleiro.\n");
                return 1;
            }
            else
                printf("\nTabuleiro carregado com sucesso.\n");
            break;
        case 3:
            ler_palavras("data/palavras.txt", trie);
            break;
        case 4:
            raiz = buscar_palavras(trie, matriz, linhas, colunas);
            imprimir_resultados(raiz);
            break;
        case 5:
            if (raiz == NULL)
            {
                printf("Árvore vazia. Leia o tabuleiro (2), as palavras (3) e use a opção (4) para buscar as palavras .\n");
                break;
            }
            imprimir_resultados(raiz);
            break;
        case 6:
        {
            char palavra_removida[99];
            while (getchar() != '\n')
                ;
            printf("Digite a palavra que deseja remover: ");
            fgets(palavra_removida, 99, stdin);
            palavra_removida[strcspn(palavra_removida, "\n")] = '\0';
            raiz = remover_no(raiz, palavra_removida);
            printf("Palavra '%s' removida, se encontrada.Use a opção (5) para ver se a palavra foi removida.\n", palavra_removida);
        }
        break;
        case 7:
            exibir_tabuleiro(matriz, linhas, colunas);
        default:
            break;
        }
    }
    // Libera a memória
    liberar_matriz(matriz, linhas);
    liberar_avl(raiz);

    return 0;
}
