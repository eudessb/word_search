#ifndef AVL_H
#define AVL_H

#define MAX_TAMANHO_PALAVRA 99

/**
 * Estrutura criada ao perceber que teria que armazenar de alguma maneira as coordenadas das palavras encontradas.
 */
typedef struct PalavraEncontrada
{
  char palavra[MAX_TAMANHO_PALAVRA];
  int x_inicio, y_inicio; //coordenadas x e y da primeira letra
  int x_fim, y_fim; // coordenadas x e y da última letra
} Palavra;

typedef struct No
{
  Palavra *dado;
  struct No *esquerdo;
  struct No *direito;
  int altura;
} No;

int obter_altura(No *no);

int calcular_fator_de_balanceamento(No *no);

No *criar_no(Palavra *dado);

No *rotacao_direita(No *y);

No *rotacao_esquerda(No *x);

No *inserir_no(No *no, Palavra *dado);

No *menor_valorNo(No *no);

No *remover_no(No *raiz, const char *dado);

void imprimir_em_ordem(No *raiz);

#endif