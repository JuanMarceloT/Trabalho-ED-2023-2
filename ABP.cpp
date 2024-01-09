#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Structs.h"
// ABP
// Utilizei codigos disponiveis no moodle
class ABP {
private:
  pNodoA *root;
  pNodoA *InsereArvore(pNodoA *a, FOODINFO ch) {
    if (a == NULL) {
      a = (pNodoA *)malloc(sizeof(pNodoA));
      a->info = ch;
      a->esq = NULL;
      a->dir = NULL;
    } else if (strcmp(ch.name, a->info.name) < 0)
      a->esq = InsereArvore(a->esq, ch);
    else
      a->dir = InsereArvore(a->dir, ch);
    return a;
  }
  void ImprimeArvore(pNodoA *a) {
    if (a != NULL) {
      ImprimeArvore(a->esq);
      printf("%s\n", a->info.name);
      ImprimeArvore(a->dir);
    }
  }

public:
  ABP() { root = nullptr; }

  void Inserir(FOODINFO x) { root = InsereArvore(root, x); }
  void imprimir() { ImprimeArvore(root); }
};
