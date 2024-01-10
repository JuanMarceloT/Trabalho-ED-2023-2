#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

struct FOODINF {
  char name[50];
  int caloriesPer100g;
};
typedef struct FOODINF FOODINFO;

struct TNodoA {
  FOODINFO info;
  int FB;
  struct TNodoA *esq;
  struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

// avl e e abp

// avl
// Utilizei codigos disponiveis no moodle
class AVL {
private:
  TNodoA *root;

  pNodoA *rotacao_direita(pNodoA *p) {
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
  }
  pNodoA *rotacao_esquerda(pNodoA *p) {
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
  }
  pNodoA *rotacao_dupla_direita(pNodoA *p) {
    pNodoA *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
      p->FB = -1;
    else
      p->FB = 0;
    if (v->FB == -1)
      u->FB = 1;
    else
      u->FB = 0;
    p = v;
    return p;
  }
  pNodoA *rotacao_dupla_esquerda(pNodoA *p) {
    pNodoA *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
      p->FB = 1;
    else
      p->FB = 0;
    if (y->FB == 1)
      z->FB = -1;
    else
      z->FB = 0;
    p = y;
    return p;
  }
  pNodoA *Caso1(pNodoA *a, int *ok) {
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
      a = rotacao_direita(a);
    else
      a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
  }
  pNodoA *Caso2(pNodoA *a, int *ok) {
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
      a = rotacao_esquerda(a);
    else
      a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
  }

public:
  AVL() { root = nullptr; }

  int Inserir(FOODINFO x) {
    int ok = 0;
    root = Inserir(root, x, &ok);
    return ok;
  }
  void imprimir() { _imprimir(root, 1); }

private:
  void _imprimir(pNodoA *nodo, int nivel) {
    if (nodo == NULL)
      return;

    for (int i = 0; i < nivel; i++) {
      printf("=");
    }
    printf("%s\nesq: %s\ndir: %s\n\n\n", nodo->info.name, nodo->esq->info.name,
           nodo->dir->info.name);
    printf("\n");
    _imprimir(nodo->esq, (nivel + 1));
    _imprimir(nodo->dir, (nivel + 1));
  }
  pNodoA *Inserir(pNodoA *a, FOODINFO x, int *ok) {
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL) {
      a = (pNodoA *)malloc(sizeof(pNodoA));
      a->info = x;
      a->esq = NULL;
      a->dir = NULL;
      a->FB = 0;
      *ok = 1;
    } else if (strcmp(x.name, a->info.name) < 0) {
      a->esq = Inserir(a->esq, x, ok);
      if (*ok) {
        switch (a->FB) {
        case -1:
          a->FB = 0;
          *ok = 0;
          break;
        case 0:
          a->FB = 1;
          break;
        case 1:
          a = Caso1(a, ok);
          break;
        }
      }
    } else {
      a->dir = Inserir(a->dir, x, ok);
      if (*ok) {
        switch (a->FB) {
        case 1:
          a->FB = 0;
          *ok = 0;
          break;
        case 0:
          a->FB = -1;
          break;
        case -1:
          a = Caso2(a, ok);
          break;
        }
      }
    }
    return a;
  }
};
int main() {
  AVL tree;
  tree.Inserir({"apple", 50});
  tree.Inserir({"banana", 89});
  tree.Inserir({"orange", 43});
  tree.Inserir({"grape", 67});
  tree.Inserir({"kiwi", 41});

  std::cout << "Imprimir: " << std::endl;
  tree.imprimir();
  std::cout << std::endl;

  return 0;
}