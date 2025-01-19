#include "trie.h"
/*
'NO' virou 'NODE' para evitar confusões com as funções da AVL que usam uma struct NO.
*/

Node *criar_Node()
{
  Node *novo_Node = (Node *)malloc(sizeof(Node));

  if (novo_Node)
  {
    novo_Node->fim_da_palavra = false;
    for (int i = 0; i < ALFABETO; i++)
    {
      novo_Node->filhos[i] = NULL;
    }
  }

  return novo_Node;
}

void inserir(Node *raiz, const char *palavra)
{
  Node *atual = raiz;

  for (int i = 0; palavra[i] != '\0'; i++)
  {
    int indice = palavra[i] - 'a';

    if (atual->filhos[indice] == NULL)
      atual->filhos[indice] = criar_Node();

    atual = atual->filhos[indice];
  }

  atual->fim_da_palavra = true;
}

bool buscar(Node *raiz, const char *palavra)
{
  Node *atual = raiz;

  for (int i = 0; palavra[i] != '\0'; i++)
  {
    int indice = palavra[i] - 'a';

    if (atual->filhos[indice] == NULL)
      return false;

    atual = atual->filhos[indice];
  }

  return atual->fim_da_palavra;
}

void liberar_trie(Node *raiz)
{
  if (raiz == NULL)
    return;

  for (int i = 0; i < ALFABETO; i++)
    liberar_trie(raiz->filhos[i]);

  free(raiz);
}
