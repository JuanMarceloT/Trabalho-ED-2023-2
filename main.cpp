#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

struct TNodoA {
  FOODINFO info;
  int FB;
  struct TNodoA *esq;
  struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

struct FOODINFO {
  char name[50];
  int caloriesPer100g;
};
// avl e e abp

// avl

class avl {
private:

    TNodoA *raiz;

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

    AVLTree() : raiz(nullptr) {}


    int Inserir(FOODINFO x) {
    int ok = 0;
    root = Inserir(root, x, &ok);
    return ok;
  }
private:
  pNodoA *Inserir(pNodoA *a, TipoInfo x, int *ok) {
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL) {
      a = (pNodoA *)malloc(sizeof(pNodoA));
      a->info = x;
      a->esq = NULL;
      a->dir = NULL;
      a->FB = 0;
      *ok = 1;
    } else if (strcmp(x, a->info) < 0) {
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

}



int main(int argc, char* argv[]){

  if (argc != 4) {
    printf("Argumentos insuficientes");
    return 1;
  }

  FILE *SourceFIle;
  char line[100];
  SourceFIle = fopen(argv[1], "r");

  if (SourceFIle == NULL) {
    printf("File opening failed.\n");
    return 1;
  }

  while (fgets(line, sizeof(line), SourceFIle) != NULL) {
    struct FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL) {
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL) {
        food.caloriesPer100g = std::stoi(token);
      }
      // printf("Food: %s and calories: %d per 100 grams\n",
      // food.name,food.caloriesPer100g);
    }
  }
  fclose(SourceFIle);

  FILE *OutputFile;
  OutputFile = fopen(argv[2], "w");

  if (OutputFile == NULL) {
    printf("Failed to create file.\n");
    return 1;
  }
  fprintf(OutputFile, "%s", "test");

  fclose(OutputFile);

  // organizando palavras pelo ordem alfabetica

  char word1[] = "bazane";
  char word2[] = "bazana";

  int result = strcmp(word1, word2);
  printf("%d\n", result);


  return 0;
}