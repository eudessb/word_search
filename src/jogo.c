#include <stdio.h>
#include <stdlib.h>
// • ler tabuleiro: Função para ler o tabuleiro do arquivo tabuleiro.txt.
/*
Ajustar!
*/
void ler_tabuleiro(const char *tabuleiro)
{
    int tab_tamanho = 10;
    char matriz[tab_tamanho][tab_tamanho];
    FILE *file = fopen(tabuleiro, "r");
    if (file == NULL)
    {
        perror("Não foi possível abrir o arquivo");
        return;
    }
    for (int i = 0; i < tab_tamanho; i++)
    {
        for (int z = 0; z < tab_tamanho; z++)
        {
            if (fscanf(file, "%c ", &matriz[i][z]) != 1)
            {
                perror("Não foi possível ler o arquivo de maneira correta.");
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    for (int i = 0; i<tab_tamanho;i++)
    {
        for (int k = 0;k <tab_tamanho;k++)
        {
            printf(" %c",matriz[i][k]);
        }
        printf("\n");
    }
    return;
};

/*ler palavras: Função para ler o arquivo palavras.txt contendo as possı́veis palavras e armazená-las na Trie.*/
void ler_palavras() {};

/*buscar palavras: Função que irá buscar automaticamente as palavras no tabuleiro, verificando em todas as direções e em ordem direta e
inversa. Caso validada, inseri-la na AVL.*/
void buscar_palavras() {};

/*imprimir resultados: Função para exibir as palavras encontradas, armazenadas na AVL.*/
void imprimir_resultados() {};