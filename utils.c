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

void congelar_tela(char message[]) {
    printf("%s", message);
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

bool read_int (int * var) {
    int result;

    char line[MAX_LENGTH + 1];
    read_line(line, MAX_LENGTH);
    result = sscanf(line, "%d", var);
    return (result == 1);
}

void search_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH];
  avl_tree data = NULL;

  printf("\n\nInforma a palavra que deseja procurar: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (avl_search_word(t, palavra, &data)) {
    printf("%s econtrada.\nSinônimo: %s.\n", palavra, (*data).dado.sinonimo);
    congelar_tela("");
  } else {
    printf("Palavra não está cadastrada.\nQue tal inserir-lá.\n\n");

    add_data(t);
  }
}

void add_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH], sinonimo[MAX_LENGTH];
  bool h;

  printf("\n\nInforma a palavra a ser cadastrada: ");
  read_line(palavra, INFO_MAX_LENGTH);

  printf("Informa seu sinônimo: ");
  read_line(sinonimo, INFO_MAX_LENGTH);

  avl_search(t, palavra, sinonimo, &h);
}

void update_data(avl_tree * t) {
  char palavra[INFO_MAX_LENGTH], sinonimo[MAX_LENGTH], msg1[MAX_LENGTH], msg2[MAX_LENGTH];
  avl_tree data = NULL;
  bool h;

  if (*t == NULL) {
    printf("\nNenhuma palavra cadastrada.\nQue tal inserir-lá.\n\n");

    add_data(t);
  }

  printf("\n\nInforma a palavra para atualizar o sinônimo: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (avl_search_word(t, palavra, &data)) {
    printf("Informa seu novo sinônimo: ");
    read_line(sinonimo, INFO_MAX_LENGTH);

    strcpy((*data).dado.sinonimo, sinonimo);
  } else {
    printf("Palavra não cadastrada.\nQue tal inserir-lá.\n\n");

    add_data(t);
  }
}

void delete_data(avl_tree * t) {
  if (*t == NULL) {
    printf("\n\nNenhuma palavra cadastrada.\n");
    return;
  }

  char palavra[INFO_MAX_LENGTH];
  bool h;

  printf("\n\nInforma a palavra a ser deletada: ");
  read_line(palavra, INFO_MAX_LENGTH);

  if (delete(t, palavra, &h)) {
      printf("Remoção realizada com sucesso!\n");
  } else {
    printf("%s não está na árvore.\n", palavra);
  }
  congelar_tela("");
}

void load_data(avl_tree * t) {
  FILE * arquivo;
  char line[MAX_LENGTH], * dado;
  bool h;

  if (((arquivo = fopen(FILENAME, "r")) == NULL)) {
    fprintf(stderr, "Erro ao abrir: %s\nArquivo pode não existir.\n", FILENAME);
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
    fprintf(stderr, "Erro ao abrir: %s\nArquivo pode não existir.\n", FILENAME);
    return;
  }

  save_tree(t, arquivo);

  fclose(arquivo);
}
