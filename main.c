/* main.c
 *
 * Implementação de um programa para listar uma AVL
 * de palavras e seus sinônimos, assim como gravar
 * essas informações num arquivo.
 * 
 * Artur Freire dos Santos
 * Gabriel Gonçales
 * Lucas Silva dos Anjos
 * Vinicius Freire Pereira
 * 
 * Ciências da Computação
 * 
 * 10/OUT/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "utils.h"
#include "avl.h"

enum menu_opcoes {
  CAD_DADO = 1,
  SEARCH_SINONIMO = 2,
  UPDATE_SINONIMO = 3,
  DELETE_DADO = 4,
  SAIR = 0
};

// exibe o menu de opções do sistema e devolve a escolha do usuário
int menu(char * [], int);

int main() {
  // configurando localização para português
  setlocale(LC_ALL, "Portuguese");

  // opções do menu
  char * opcoes[] = {
    "Cadastrar dados",
    "Procurar sinônimo de uma palavra",
    "Atualizar sinônimo de uma palavra",
    "Deletar palavra (e sinônimo)",
    "Sair do programa"
  };

  // variável para AVL de dicionário de palavras e seus sinônimos
  avl_tree dicionario = NULL;

  load_data(&dicionario);

  int op;
  do {
    op = menu(opcoes, sizeof(opcoes) / sizeof(char *));

    switch (op) {
      case CAD_DADO:
        add_data(&dicionario);
      	break;
      case SEARCH_SINONIMO:
        search_data(&dicionario);
      	break;
      case UPDATE_SINONIMO:
        update_data(&dicionario);
      	break;
      case DELETE_DADO:
        delete_data(&dicionario);
      	break;
      case SAIR:
        save_data(dicionario);
		printf("\nAdeus!\n");
      	break;
      default:
        printf("\n\tOpção inválida!\n");
      	break;
    }
  } while (op != SAIR);

  return 0;
}

int menu(char * opcoes[], int num) {
  int i, op;

  printf("\n\n\tMENU DE OPÇÕES\n\n");
  for (i = 0; i < num-1; i++) {
    printf("%02d - %s\n", i+1, opcoes[i]);
  }

  printf("%02d - %s\n", SAIR, opcoes[i]);
  printf("Opção: ");
  read_int(&op);
  
  return op;
}
