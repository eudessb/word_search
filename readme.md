# Caça-Palavras

Projeto de um caça-palavras usando árvores digitais (tries) e árvores AVL,escrito na linguagem **C** como parte da disciplina de Estruturas de Dados Básicas II.

## Estrutura de diretórios

Este projeto contém a seguinte estrutura de diretórios:

**src** :Contém os arquivos de código-fonte em C. Nele estão as principais funções desenvolvidas para o projeto:

- `main.c`:Arquivo principal do programa, interaje com o usuário.
- `jogo.c`:Arquivo com a lógica do jogo.
- `avl.c`:Arquivo com a implementação da árvore AVL.
- `trie.c`:Arquivo com a implementação da trie.

**include**: Contém os cabeçalhos (.h) dos códigos-fonte utilizados no projeto.

**data**: Contém os arquivos de texto lidos pelo programa, como as letras que formam o tabuleiro do caça-palavras

## Fluxo do programa

O fluxo do programa ocorre de maneira relativamente simples. Primeiro as letras serão inseridas numa matriz para que possa ser formado um tabuleiro. Após o tabuleiro ter sido criado o programa utilizará `buscar_palavras`  para percorrer a matriz em todas as direções, validar sequências de letras na trie e inserir palavras válidas na AVL.

## Dependências

- **Compilador:** GCC
- **Make**: Para facilitar a compilação e execução do projeto.

## Arquivo Makefile

O projeto usa um **Makefile** para facilitar a compilação e execução. Aqui estão os comandos principais disponíveis, utilize-os no diretório
**../Gerenciador_De_Biblioteca**.

- **Compilar o programa**:
  `make`
- **Compilar e executar o programa**:
  `make run`
- **Limpar o diretório**:
  `make clean`

