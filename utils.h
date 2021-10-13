/* utils.h
 *
 * Protótipo das funções utilitárias
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

#ifndef _UTILS_H
#define _UTILS_H
#define MAX_LENGTH 120
#define ERR_OPEN_ARC "\n\n\tERRO: NÃO foi possível criar/encontrar o arquivo %s no diretorio atual!\nPor favor crie-o ou mova o projeto para um diretorio que possua permissão de leitura e escrita.\n"
#define WORD_NOT_REGISTERED_TEXT "Palavra não cadastrada.\nConsidere inseri-la.\n\n"
#define OPERATION_SUCCESS_TEXT "Operação realizada com sucesso!\n"
#define FILENAME "dicionario.txt"

#include "avl.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Função que aguarda o usuário pressionar ENTER para continuar a 
execução do programa. */
void congelar_tela();

/* Função recebe um vetor de caractere e seu inteiro de tamanho e lê as 
informações digitadas na linha. */
void read_line (char line[], int max_length);

/* Função recebe um inteiro para ser lido como entrada do teclado. */
bool read_int (int * var);

/* Função para buscar certa palavra numa AVL apontada por t
 * e mostra em tela caso encontrado, caso contrário pede para
 * cadastrar na AVL.
 */
void search_data(avl_tree * t);

/* Função cria informações de uma palavra
 * dentro duma AVL apontada por t. */
void add_data(avl_tree * t);

/* Função atualiza sinônimo de uma palavra
 * dentro duma AVL apontada por t, caso não ache
 * a palavra pede para cadastra-la.
 */
void update_data(avl_tree * t);

/* Função deleta certa palavra duma AVL apontada por t
 * caso exista. */
void delete_data(avl_tree * t);

void load_data(avl_tree * t);

void save_data(avl_tree t);

#endif
