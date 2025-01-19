#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define ALFABETO 26

/*
'NO' virou 'NODE' para evitar confusões com as funções da AVL que usam uma struct NO.
*/
typedef struct Node
{
    struct Node *filhos[ALFABETO];
    bool fim_da_palavra;
} Node;

bool buscar(Node *raiz, const char *palavra);

Node *criar_Node();

void inserir(Node *raiz, const char *palavra);

void liberar_trie(Node *raiz);

#endif