/* avl.c
 * Implementação das operações realizadas sobre o TAD que  
 * representa uma árvore AVL.
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
 
#include "avl.h"

void save_tree(avl_tree t, FILE * arquivo) {
    if (t != NULL) {
        save_tree(t->esq, arquivo);
        fprintf(arquivo, "%s %s\n", t->dado.palavra, t->dado.sinonimo);
        save_tree(t->dir, arquivo);
    }
}

void avl_search(avl_tree * t, char * palavra, char * sinonimo, bool * h) {
    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocação de memória!\n");
            exit(1);
        }
        *h = true;
        strcpy((*t)->dado.palavra, palavra);
        strcpy((*t)->dado.sinonimo, sinonimo);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcasecmp(palavra, (*t)->dado.palavra) < 0) {
        avl_search(&(*t)->esq, palavra, sinonimo, h);
        if (*h) {
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        *h = false;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    if ((*t)->esq->bal == -1) {
                        rotacao_dir(t);
                        (*t)->dir->bal = 0;
                    }
                    else {
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);

                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            }
        }
    }
    else if (strcasecmp(palavra, (*t)->dado.palavra) > 0) {
        avl_search(&(*t)->dir, palavra, sinonimo, h);
        if (*h) {
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                         *h = false;
                         break;
                case 0 : (*t)->bal = 1;
                         break;
                case 1:
                    if ((*t)->dir->bal == 1) {
                        rotacao_esq(t);
                        (*t)->esq->bal = 0;
                    }
                    else {
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);

                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
					}
                    *h = false;
                    (*t)->bal = 0;
                    break;
            }
        }
    }
    else {
        strcpy((*t)->dado.sinonimo, sinonimo);
        *h = false;
    }
}

bool avl_find_word(avl_tree * t, char * palavra, avl_tree * data) {
    if (*t == NULL) {
        return false;
    }

    if (strcasecmp(palavra, (*t)->dado.palavra) == 0) {
        (*data) = (*t);
        return true;
    } else if (strcasecmp(palavra, (*t)->dado.palavra) < 0) {
        return avl_search_word(&(*t)->esq, palavra, data);
    } else if (strcasecmp(palavra, (*t)->dado.palavra) > 0) {
        return avl_search_word(&(*t)->dir, palavra, data);
    }
}

// Rotação para a esquerda
void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}

// Rotação para a direita
void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


bool delete(avl_tree * t, char * x, bool * h) {
    avl_tree p;
    bool result;
    if (*t == NULL) {
        return false;
	}
    else if (strcasecmp(x,(*t)->dado.palavra) == 0) {
        p = *t;
        if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) {
            *t = p->esq;
            *h = true;
        }
        else {
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.palavra) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
}

void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1:
			(*t)->bal = 0;
			break;
        case 0:
			(*t)->bal = -1;
			*h = false;
			break;
        case -1:
			p1 = (*t)->esq;
			b1 = p1->bal;
			if (b1 <= 0) {
				(*t)->esq = p1->dir;
				p1->dir = *t;
				if (b1 == 0) {
					(*t)->bal = -1;
					p1->bal = 1;
					*h = false;
				}
				else {
					(*t)->bal = 0;
					p1->bal = 0;
				}
				*t = p1;
			}
			else {
				p2 = p1->dir;
				b2 = p2->bal;
				p1->dir = p2->esq;
				p2->esq = p1;
				p1->esq = p2->dir;
				p2->dir = *t;
				if(b2 == -1) (*t)->bal = 1;
				else (*t)->bal = 0;
				if(b2 == 1) p1->bal = -1;
				else p1->bal = 0;
				*t = p2;
				p2->bal = 0;
			}
    }
}

void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1:
			(*t)->bal = 0;
            break;
        case 0:
			(*t)->bal = 1;
			*h = false;
			break;
        case 1:
			p1 = (*t)->dir;
			b1 = p1->bal;
			if (b1 >= 0) {
				(*t)->dir = p1->esq;
				p1->esq = *t;
				if (b1 == 0) {
					(*t)->bal = 1;
					p1->bal = -1;
					*h = false;
				}
				else {
					(*t)->bal = 0;
					p1->bal = 0;
				}
				*t = p1;
			}
			else {
				p2 = p1->esq;
				b2 = p2->bal;
				p1->esq = p2->dir;
				p2->dir = p1;
				p1->dir = p2->esq;
				p2->esq = *t;
				if (b2 == 1) (*t)->bal = -1;
				else (*t)->bal = 0;
				if (b2 == -1) p1->bal = 1;
				else p1->bal = 0;
				*t = p2;
				p2->bal = 0;
			}
    }
}

avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}

int avl_profundidade(avl_tree t) {
    if (t == NULL) {
        return 0;
    }
    int e = avl_profundidade(t->esq);
    int d = avl_profundidade(t->dir);
    return 1 + (e > d ? e : d);
}
