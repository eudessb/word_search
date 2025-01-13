#include "../include/trie.h"
#include <stdio.h>
#include <stdbool.h>
#include "jogo.c"
int main(void)
{
    while (true)
    {
        int options;
        scanf("%d", &options);
        switch (options)
        {
        case 0:
            exit(EXIT_SUCCESS);
            break;
        case 1:
            printf("Olá\n");
            break;

        case 2:
            ler_tabuleiro("/home/eudessb/Documentos/UFRN/projeto3unidade/data/tabuleiro.txt");
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        default:
            break;
        }
    }
    return 0;
}