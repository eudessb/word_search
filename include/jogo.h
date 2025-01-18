#ifndef JOGO_H
#define JOGO_H

char **ler_tabuleiro(const char *tabuleiro, int *linhas, int *colunas);

void ler_palavras(const char *palavras_txt, Node *raiz);

No *buscar_palavras(Node *trie, char **tabuleiro, int linhas, int colunas);

void imprimir_resultados(No *raiz);

// Função criada para auxiliar a busca de palavras, trabalha em conjunto com buscar_palavras.
void buscar_direcao(Node *trie, char **tabuleiro, int linhas, int colunas, int x, int y, int dx, int dy, No **AVL);

void exibir_tabuleiro(char **matriz, int linhas, int colunas);

void liberar_avl(No *raiz);

void liberar_matriz(char **matriz, int linhas);

void menu();
#endif