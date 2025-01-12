#include <stdio.h>
#include <stdlib.h>
#include <avl.h>

int obter_altura(No* no)
{
  if(no == NULL)
    return -1;
  else
    return no->altura;
}

int calcular_fator_de_balanceamento(No* no)
{
  if(no == NULL)
    return 0;
  else
    return obter_altura(no->esquerdo) - obter_altura(no->direito);
}

No* criar_no(int dado)
{
  No* no = (No*)malloc(sizeof(No));
  no->dado = dado;
  no->esquerdo = NULL;
  no->direito = NULL;
  no->altura = 0;
  
  return no;
}

No* rotacao_direita(No* y)
{
  No* x = y->esquerdo;
  No* z = x->direito;

  x->direito = y;
  y->esquerdo = z;

  if(obter_altura(y->esquerdo) > obter_altura(y->direito))
    y->altura = 1 + obter_altura(y->esquerdo);
  else
    y->altura = 1 + obter_altura(y->direito);

  if(obter_altura(x->esquerdo) > obter_altura(x->direito))
    x->altura = 1 + obter_altura(x->esquerdo);
  else
    x->altura = 1 + obter_altura(x->direito);

  return x;
}

No* rotacao_esquerda(No* x)
{
  No* y = x->direito;
  No* z = y->esquerdo;

  y->esquerdo = x;
  x->direito = z;

  if(obter_altura(x->esquerdo) > obter_altura(x->direito))
    x->altura = 1 + obter_altura(x->esquerdo);
  else
    x->altura = 1 + obter_altura(x->direito);

  if (obter_altura(y->esquerdo) > obter_altura(y->direito))
    y->altura = 1 + obter_altura(y->esquerdo);
  else
    y->altura = 1 + obter_altura(y->direito);

  return y;
}

No* inserir_no(No* no, int dado)
{
  if(no == NULL)
    return criar_no(dado);

  if(dado < no->dado)
    no->esquerdo = inserir_no(no->esquerdo, dado);
  else if(dado > no->dado)
    no->direito = inserir_no(no->direito, dado);
  else
    return no;

  if(obter_altura(no->esquerdo) > obter_altura(no->direito))
    no->altura = 1 + obter_altura(no->esquerdo);
  else
    no->altura = 1 + obter_altura(no->direito);

  int balanceamento = calcular_fator_de_balanceamento(no);

  /* Caso 1: Desbalanceamento à esquerda (Rotação à direita). */
  if(balanceamento > 1 && dado < no->esquerdo->dado)
    return rotacao_direita(no);

  /* Caso 2: Desbalanceamento à direita (Rotação à esquerda). */
  if(balanceamento < -1 && dado > no->direito->dado)
    return rotacao_esquerda(no);

  /* Caso 3: Desbalanceamento esquerda-direita (Rotação dupla esquerda-direita). */
  if(balanceamento > 1 && dado > no->esquerdo->dado){
    no->esquerdo = rotacao_esquerda(no->esquerdo);
    return rotacao_direita(no);
  }

  /* Caso 4: Desbalanceamento direita-esquerda (Rotação dupla direita-esquerda). */
  if(balanceamento < -1 && dado < no->direito->dado){
    no->direito = rotacao_direita(no->direito);
    return rotacao_esquerda(no);
  }

  return no;
}

No* menor_valorNo(No* no)
{
  No* atual = no;
  
  while(atual->esquerdo != NULL)
    atual = atual->esquerdo;

  return atual;
}

No* remover_no(No* raiz, int dado)
{
  if(raiz == NULL)
    return raiz;

  if(dado < raiz->dado){
    raiz->esquerdo = remover_no(raiz->esquerdo, dado);
  }else if(dado > raiz->dado){
    raiz->direito = remover_no(raiz->direito, dado);
  }else{
    /* Nó com apenas um filho ou nenhum. */
    if((raiz->esquerdo == NULL) || (raiz->direito == NULL)){
      No* temp;
          
      if(raiz->esquerdo != NULL)
        temp = raiz->esquerdo;
      else
        temp = raiz->direito;
    
      /* Caso de nenhum filho. */
      if(temp == NULL){
        temp = raiz;
        raiz = NULL;
      }else{
        *raiz = *temp;
      }

      free(temp);
    }else{
      /* Caso de dois filhos: obtém o sucessor. */
      No* temp = menor_valorNo(raiz->direito);

      raiz->dado = temp->dado;

      raiz->direito = remover_no(raiz->direito, temp->dado);
    }
  }

  /* Se a árvore tinha apenas um nó. */
  if(raiz == NULL)
    return raiz;

  if(obter_altura(raiz->esquerdo) > obter_altura(raiz->direito))
    raiz->altura = 1 + obter_altura(raiz->esquerdo);
  else
    raiz->altura = 1 + obter_altura(raiz->direito);

  int balanceamento = calcular_fator_de_balanceamento(raiz);

  /* Caso 1: Desbalanceamento à esquerda. */
  if(balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) >= 0)
    return rotacao_direita(raiz);

  /* Caso 2: Desbalanceamento esquerda-direita. */
  if(balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) < 0){
    raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
    return rotacao_direita(raiz);
  }

  /* Caso 3: Desbalanceamento à direita. */
  if(balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) <= 0)
    return rotacao_esquerda(raiz);

  /* Caso 4: Desbalanceamento direita-esquerda. */
  if(balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) > 0){
    raiz->direito = rotacao_direita(raiz->direito);
    return rotacao_esquerda(raiz);
  }

  return raiz;
}

void imprimir_em_ordem(No* raiz)
{
  if(raiz != NULL){
    imprimir_em_ordem(raiz->esquerdo);
    printf("%d ", raiz->dado);
    imprimir_em_ordem(raiz->direito);
  }
}



