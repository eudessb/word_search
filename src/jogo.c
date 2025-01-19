#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/trie.h"
#include "../include/avl.h"
#include "../include/jogo.h"


#define MAX_PALAVRAS 99

//Lê o tabuleiro de tabuleiro.txt
char **ler_tabuleiro(const char *tabuleiro, int *linhas, int *colunas)
{
    int num_linhas;
    int num_colunas;
    FILE *file = fopen(tabuleiro, "r");
    if (file == NULL)
    {
        printf("Arquivo não encontrado ou erro de permissão.\n"); //Arquivo vazio
        return NULL;
    }
    fscanf(file, "%d %d", &num_linhas, &num_colunas); //Escaneia as dimensões da matriz
    char **matriz = (char **)malloc(num_linhas * sizeof(char *)); // Alocação da Matriz
    for (int i = 0; i < num_linhas; i++)
    {
        matriz[i] = (char *)malloc(num_colunas * sizeof(char));
    }
    for (int k = 0; k < num_linhas; k++)
    {
        for (int z = 0; z < num_colunas; z++)
        {
            if (fscanf(file, " %c", &matriz[k][z]) != 1)
            {
                perror("Não foi possível ler o arquivo de maneira correta.");
                for (int i = 0; i < num_linhas; i++)
                {
                    free(matriz[i]);//desaloca a memória em caso de erro.
                }
                free(matriz);
                fclose(file);
                return NULL;
            }
        }
    }
    // Armazena o número de linhas e colunas para uso posterior por outras funções
    *linhas = num_linhas;
    *colunas = num_colunas;

    return matriz;
}

/*ler palavras: Função para ler o arquivo palavras.txt contendo as possı́veis palavras e armazená-las na Trie.*/
void ler_palavras(const char *palavras_txt, Node *raiz)
{
    FILE *arquivo = fopen(palavras_txt, "r");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir o arquivo");
        return;
    }
    int count = 0;
    char palavra[99];

    while (count < MAX_PALAVRAS && fscanf(arquivo, "%99s", palavra) == 1)
    {
        inserir(raiz, palavra);
        count++;
    }
    printf("Palavras carregadas com sucesso.\n");
    fclose(arquivo);
}

/*
Função criada para verificar se a função 'buscar_direcao' está formando uma palavra que existe na trie.
Caso um prefixo existente na trie não esteja sendo formado a função retornará 'False'.
*/
bool verificar_prefixo(Node *raiz, const char *prefixo)
{
    Node *atual = raiz;
    for (int i = 0; prefixo[i] != '\0'; i++)
    {
        int indice = prefixo[i] - 'a';     // Converte o caractere em um índice
        if (atual->filhos[indice] == NULL) // Prefixo não encontrado
        {
            return false;
        }
        atual = atual->filhos[indice];
    }
    return true;
}
/*buscar palavras: Função que irá buscar automaticamente as palavras no tabuleiro, verificando em todas as direções e em ordem direta e
inversa. Caso validada, inseri-la na AVL.
Usa 'buscar_direcao' como função auxiliar. 
*/
No *buscar_palavras(Node *trie, char **matriz, int linhas, int colunas)
{
    No *AVL = NULL;
    for (int x = 0; x < linhas; x++)
    {
        for (int y = 0; y < colunas; y++)
        {
            buscar_direcao(trie, matriz, linhas, colunas, x, y, 0, 1, &AVL);   // Direita
            buscar_direcao(trie, matriz, linhas, colunas, x, y, 0, -1, &AVL);  // Esquerda
            buscar_direcao(trie, matriz, linhas, colunas, x, y, 1, 0, &AVL);   // Para baixo
            buscar_direcao(trie, matriz, linhas, colunas, x, y, -1, 0, &AVL);  // Para cima
            buscar_direcao(trie, matriz, linhas, colunas, x, y, 1, 1, &AVL);   // Baixo-direita
            buscar_direcao(trie, matriz, linhas, colunas, x, y, -1, -1, &AVL); // Cima-esquerda
            buscar_direcao(trie, matriz, linhas, colunas, x, y, -1, 1, &AVL);  // Baixo-esquerda
            buscar_direcao(trie, matriz, linhas, colunas, x, y, 1, -1, &AVL);  // Cima-direita
        }
    }
    return AVL;
}

// 'dx' e 'dy' definem se a busca vai ser diagonal, horizontal ou vertical. 
void buscar_direcao(Node *trie, char **tabuleiro, int linhas, int colunas, int x, int y, int dx, int dy, No **AVL)
{
    char palavra[MAX_TAMANHO_PALAVRA ]; 
    int indice = 0;
    int x_inicio = x, y_inicio = y; //Armazena o X e Y passados inicialmente.
    for (int passo = 0; passo < MAX_TAMANHO_PALAVRA; passo++)
    {
        int nx = x + passo * dx;
        int ny = y + passo * dy;
        // Verifica se saiu do limite do tabuleiro
        if (nx < 0 || nx >= linhas || ny < 0 || ny >= colunas)
        {
            break;
        }
        // Adiciona a letra à palavra
        palavra[indice] = tolower(tabuleiro[nx][ny]);
        indice++;
        palavra[indice] = '\0'; // Finaliza a string

        // Verifica se o prefixo é válido
        if (!verificar_prefixo(trie, palavra))
        {
            break; // Interrompe se não for prefixo válido
        }
        // Verifica se a palavra foi encontrada
        if (buscar(trie, palavra))
        {
            //Insere as coordenadas da palavra encontrada.
            Palavra p;
            strcpy(p.palavra, palavra);
            p.x_inicio = x_inicio;
            p.y_inicio = y_inicio;
            p.x_fim = nx;
            p.y_fim = ny;
            *AVL = inserir_no(*AVL, &p); // Insere a palavra na AVL
        }
    }
}

/*imprimir resultados: Função para exibir as palavras encontradas, armazenadas na AVL.*/
void imprimir_resultados(No *raiz)
{
    if (raiz != NULL)
    {
        imprimir_resultados(raiz->esquerdo);
        printf("%s, Início: (%d, %d), Fim: (%d, %d)\n",
               raiz->dado->palavra, raiz->dado->x_inicio, raiz->dado->y_inicio, raiz->dado->x_fim, raiz->dado->y_fim);
        imprimir_resultados(raiz->direito);
    }
}
//Exibe o tabuleiro lido do arquivo tabuleiro.txt
void exibir_tabuleiro(char **matriz, int linhas, int colunas)
{
    printf("\n===Tabuleiro===\n");
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

//Libera a memória alocada para a matriz
void liberar_matriz(char **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}
//Libera a memória alocada para a AVL.
void liberar_avl(No *raiz)
{
    if (raiz != NULL)
    {
        liberar_avl(raiz->esquerdo);
        liberar_avl(raiz->direito);
        free(raiz->dado); // Se armazenar strings
        free(raiz);
    }
}
//Menu com as opções de operações para o usuário.
void menu()
{
    printf("\n==== Caça-Palavras ====\n");
    printf("0. ENCERRAR PROGRAMA.\n");
    printf("1. EXIBIR O MENU.\n");
    printf("2. LER TABULEIRO.\n");
    printf("3. LER PALAVRAS (INSERIR NA TRIE)\n");
    printf("4. PROCURAR E EXIBIR PALAVRAS NA TRIE.\n");
    printf("5. REEXIBIR PALAVRAS.\n");
    printf("6. REMOVER PALAVRA.\n");
    printf("7. EXIBIR TABULEIRO.\n");
}
