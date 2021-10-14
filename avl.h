/* avl.h
 * Definição do TAD para representar uma árvore AVL e protótipo
 * de suas operações.
 *
 * Ciro C. Trindade
 * 06/out/2021
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

#ifndef _AVL_H
#define _AVL_H
#define INFO_MAX_LENGTH 31

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de dados
typedef struct {
    char palavra[INFO_MAX_LENGTH];
    char sinonimo[INFO_MAX_LENGTH];
} avl_info;

typedef struct avl_no * avl_tree;

struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do nó
};

/*
 * Escreve informações da AVL t num arquivo passado por parâmetro.
 */
void save_tree(avl_tree t, FILE * arquivo);


/*
 * Verifica se a palavra já ocorreu na árvore AVL t; 
 * caso afirmativo, seu sinônimo é atualizado; caso contrário,
 * a palavra é inserida em t e h sinaliza que houve um aumento da
 * altura de t.
 */
void avl_search(avl_tree * t, char * palavra, char * sinonimo, bool * h);


/* 
 * Faz uma rotação para a direita na árvore AVL t. 
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotação para a esquerda na árvore AVL t.
 */
void rotacao_esq(avl_tree *);

/*
 * Se a palavra x está contida na árvore AVL t, x é
 * removida de t, h sinaliza uma diminuição da altura
 * de t e a função devolve verdadeiro; caso contrário,
 * nada é feito e a função devolve falso.
 */
bool delete(avl_tree * t, char * x, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore esquerda e sinaliza se houve uma 
 * diminuição da altura dessa subárvore através de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da árvore AVL t após uma remoção 
 * em sua subárvore direita e sinaliza se houve uma 
 * diminuição da altura dessa subárvore através de h.
 */
void balance_dir(avl_tree *, bool *);

/*
 * Devolve um ponteiro para o nó que contém o menor
 * valor na árvore AVL t e sinaliza através de h se 
 * houve uma diminuição da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);

/* Devolve a profundidade da árvore AVL apontada por t. */
int avl_profundidade(avl_tree t);

/* Busca pela palavra na AVL apontada por t e
 * retorna verdadeiro caso esta seja encontrada ou falso caso contrário.
 */
bool avl_find_word(avl_tree * t, char * palavra, avl_tree * data);

#endif
