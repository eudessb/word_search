
#include "trie.h"
#define ALFABETO 26


No *criar_no()
{
  No *novo_no = (No *)malloc(sizeof(No));
  
  if(novo_no)
  {
    novo_no->fim_da_palavra = false;
    for(int i = 0; i < ALFABETO; i++){
      novo_no->filhos[i] = NULL;
    }
  }
  
  return novo_no;
}

void inserir(No *raiz, const char *palavra)
{
  No *atual = raiz;
  
  for(int i = 0; palavra[i] != '\0'; i++){
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      atual->filhos[indice] = criar_no();

    atual = atual->filhos[indice];
  }
  
  atual->fim_da_palavra = true;
}

bool buscar(No *raiz, const char *palavra)
{
  No *atual = raiz;
  
  for(int i = 0; palavra[i] != '\0'; i++){
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      return false;

    atual = atual->filhos[indice];
  }
  
  return atual->fim_da_palavra;
}

void liberar_trie(No *raiz)
{
  if(raiz == NULL)
    return;

  for(int i = 0; i < ALFABETO; i++)
        liberar_trie(raiz->filhos[i]);

  free(raiz);
}

