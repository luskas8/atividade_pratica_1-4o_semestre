/* utils.c
 *
 * Implementação de funções utilitárias
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

#include "utils.h"

void congelar_tela() {
    printf("Pressione ENTER para voltar ao menu...\n");
    char ch;
    read_line(&ch, 1);
}

void read_line(char line[], int max_length) {
    int i = 0;
    char ch;

    while ((ch = getchar()) != '\n') {
        if (i < max_length)
            line[i++] = ch;
    }
    line[i] = '\0';
}

bool read_int(int * var) {
    int result;
    char line[MAX_LENGTH + 1];
    read_line(line, MAX_LENGTH);
    result = sscanf(line, "%d", var);
    return (result == 1);
}

void search_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH];
  avl_tree data = NULL;

  printf("\n\nInforme a palavra que deseja procurar: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (avl_search_word(t, palavra, &data)) {
    printf("A palavra \"%s\" foi encontrada.\nSeu sinônimo é: %s\n", palavra, (*data).dado.sinonimo);
    congelar_tela();
  } else {
    printf(WORD_NOT_REGISTERED_TEXT);
  }
}

void add_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH], sinonimo[MAX_LENGTH];
  bool h;

  printf("\n\nInforme a palavra a ser cadastrada: ");
  read_line(palavra, INFO_MAX_LENGTH);

  printf("Informe seu sinônimo: ");
  read_line(sinonimo, INFO_MAX_LENGTH);

  avl_search(t, palavra, sinonimo, &h);
  printf(OPERATION_SUCCESS_TEXT);
}

void update_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH], sinonimo[MAX_LENGTH], msg1[MAX_LENGTH], msg2[MAX_LENGTH];
  avl_tree data = NULL;
  bool h;

  if (*t == NULL) {
    printf("\nNenhuma palavra cadastrada.\nA edição é impossível.\n\n");
  }

  printf("\n\nInforme a palavra para atualizar o sinônimo: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (avl_search_word(t, palavra, &data)) {
    printf("Informe seu novo sinônimo: ");
    read_line(sinonimo, INFO_MAX_LENGTH);

    strcpy((*data).dado.sinonimo, sinonimo);
	printf(OPERATION_SUCCESS_TEXT);
  } else {
    printf(WORD_NOT_REGISTERED_TEXT);
  }
}

void delete_data(avl_tree * t) {
  if (*t == NULL) {
    printf("\n\nNenhuma palavra cadastrada. A remoção é impossível.\n");
    return;
  }

  char palavra[INFO_MAX_LENGTH];
  bool h;

  printf("\n\nInforme a palavra a ser excluída: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (delete(t, palavra, &h)) {
    printf(OPERATION_SUCCESS_TEXT);
  } else {
    printf(WORD_NOT_REGISTERED_TEXT);
  }
  congelar_tela();
}

void load_data(avl_tree * t) {
  FILE * arquivo;
  char line[MAX_LENGTH], * dado;
  bool h;

  if (((arquivo = fopen(FILENAME, "r")) == NULL)) {
    fprintf(stderr, ERR_OPEN_ARC, FILENAME);
    return;
  }

  while (fgets(line, MAX_LENGTH, arquivo) != NULL) {
    char palavra[INFO_MAX_LENGTH], sinonimo[INFO_MAX_LENGTH];
    int ctl = 0;

    dado = strtok(line, " ");
    while (dado != NULL) {
      if (strlen(dado) > 1) {
        if (ctl == 0) {
          strcpy(palavra, dado);
          ctl++;
        } else {
          strcpy(sinonimo, dado);
        }
      }
      dado = strtok(NULL, " ");
    }

    avl_search(t, palavra, sinonimo, &h);
  }

  fclose(arquivo);
}

void save_data(avl_tree t) {
  FILE * arquivo;

  if (((arquivo = fopen(FILENAME, "w")) == NULL)) {
    fprintf(stderr, ERR_OPEN_ARC, FILENAME);
    return;
  }

  save_tree(t, arquivo);

  fclose(arquivo);
}
