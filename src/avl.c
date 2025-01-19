#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avl.h>

int obter_altura(No *no)
{
  if (no == NULL)
    return -1;
  else
    return no->altura;
}

int calcular_fator_de_balanceamento(No *no)
{
  if (no == NULL)
    return 0;
  else
    return obter_altura(no->esquerdo) - obter_altura(no->direito);
}

No *criar_no(Palavra *dado)
{
  No *no = (No *)malloc(sizeof(No));
  no->dado = (Palavra *)malloc(sizeof(Palavra));
  strcpy(no->dado->palavra, dado->palavra);
  no->dado->x_inicio = dado->x_inicio;
  no->dado->y_inicio = dado->y_inicio;
  no->dado->x_fim = dado->x_fim;
  no->dado->y_fim = dado->y_fim;

  no->esquerdo = NULL;
  no->direito = NULL;
  no->altura = 0;
  return no;
}

No *rotacao_direita(No *y)
{
  No *x = y->esquerdo;
  No *z = x->direito;

  x->direito = y;
  y->esquerdo = z;

  y->altura = 1 + (obter_altura(y->esquerdo) > obter_altura(y->direito) ? obter_altura(y->esquerdo) : obter_altura(y->direito));
  x->altura = 1 + (obter_altura(x->esquerdo) > obter_altura(x->direito) ? obter_altura(x->esquerdo) : obter_altura(x->direito));

  return x;
}

No *rotacao_esquerda(No *x)
{
  No *y = x->direito;
  No *z = y->esquerdo;

  y->esquerdo = x;
  x->direito = z;

  x->altura = 1 + (obter_altura(x->esquerdo) > obter_altura(x->direito) ? obter_altura(x->esquerdo) : obter_altura(x->direito));
  y->altura = 1 + (obter_altura(y->esquerdo) > obter_altura(y->direito) ? obter_altura(y->esquerdo) : obter_altura(y->direito));

  return y;
}

No *inserir_no(No *no, Palavra *dado)
{
  if (no == NULL)
    return criar_no(dado);

  // Comparação de strings usando o campo 'palavra' da estrutura 'Palavra'
  if (strcmp(dado->palavra, no->dado->palavra) < 0)
  {
    no->esquerdo = inserir_no(no->esquerdo, dado);
  }
  else if (strcmp(dado->palavra, no->dado->palavra) > 0)
  {

    no->direito = inserir_no(no->direito, dado);
  }
  else
  {
    return no; // Palavra já existe, não insere duplicados
  }

  // Atualiza a altura do nó
  no->altura = 1 + (obter_altura(no->esquerdo) > obter_altura(no->direito) ? obter_altura(no->esquerdo) : obter_altura(no->direito));

  int balanceamento = calcular_fator_de_balanceamento(no);

  // Balanceamento AVL
  if (balanceamento > 1 && strcmp(dado->palavra, no->esquerdo->dado->palavra) < 0)
    return rotacao_direita(no);

  if (balanceamento < -1 && strcmp(dado->palavra, no->direito->dado->palavra) > 0)
    return rotacao_esquerda(no);

  if (balanceamento > 1 && strcmp(dado->palavra, no->esquerdo->dado->palavra) > 0)
  {
    no->esquerdo = rotacao_esquerda(no->esquerdo);
    return rotacao_direita(no);
  }

  if (balanceamento < -1 && strcmp(dado->palavra, no->direito->dado->palavra) < 0)
  {
    no->direito = rotacao_direita(no->direito);
    return rotacao_esquerda(no);
  }

  return no;
}

No *menor_valorNo(No *no)
{
  No *atual = no;
  while (atual->esquerdo != NULL)
    atual = atual->esquerdo;
  return atual;
}

No *remover_no(No *raiz, const char *dado)
{
  if (raiz == NULL)
    return raiz;

  // Comparação de strings usando o campo 'palavra' da estrutura 'Palavra'
  if (strcmp(dado, raiz->dado->palavra) < 0)
    raiz->esquerdo = remover_no(raiz->esquerdo, dado);
  else if (strcmp(dado, raiz->dado->palavra) > 0)
    raiz->direito = remover_no(raiz->direito, dado);
  else
  {
    if ((raiz->esquerdo == NULL) || (raiz->direito == NULL))
    {
      No *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

      if (temp == NULL)
      {
        temp = raiz;
        raiz = NULL;
      }
      else
      {
        *raiz = *temp;
      }

      free(temp->dado); // Libera a string
      free(temp);
    }
    else
    {
      No *temp = menor_valorNo(raiz->direito);
      free(raiz->dado);                                 // Libera a string atual
      raiz->dado = (Palavra *)malloc(sizeof(Palavra));  // Aloca espaço para a nova palavra
      strcpy(raiz->dado->palavra, temp->dado->palavra); // Copia a palavra do sucessor
      raiz->direito = remover_no(raiz->direito, temp->dado->palavra);
    }
  }

  if (raiz == NULL)
    return raiz;

  // Atualizar altura e balancear
  raiz->altura = 1 + (obter_altura(raiz->esquerdo) > obter_altura(raiz->direito) ? obter_altura(raiz->esquerdo) : obter_altura(raiz->direito));

  int balanceamento = calcular_fator_de_balanceamento(raiz);

  if (balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) >= 0)
    return rotacao_direita(raiz);

  if (balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) < 0)
  {
    raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
    return rotacao_direita(raiz);
  }

  if (balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) <= 0)
    return rotacao_esquerda(raiz);

  if (balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) > 0)
  {
    raiz->direito = rotacao_direita(raiz->direito);
    return rotacao_esquerda(raiz);
  }

  return raiz;
}

void imprimir_em_ordem(No *raiz)
{
  if (raiz != NULL)
  {
    imprimir_em_ordem(raiz->esquerdo);
    printf("%s ", raiz->dado->palavra); // Acessando o campo 'palavra' de 'Palavra'
    imprimir_em_ordem(raiz->direito);
  }
}
