#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

struct FOODINFO {
  char name[50];
  int caloriesPer100g;
};
typedef struct FOODINFO FOODINFO;

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
  int rotações;

  pNodoA *rotacao_direita(pNodoA *p) {
    rotações++;
    pNodoA *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
  }
  pNodoA *rotacao_esquerda(pNodoA *p) {
    rotações++;
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
  }
  pNodoA *rotacao_dupla_direita(pNodoA *p) {
    rotações++;
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
    rotações++;
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
  int _GetCalories(pNodoA *a, char food[30]){
    printf("tigas %s\n", a->info.name);
    if(strcmp(a->info.name, food) == 0)
      return a->info.caloriesPer100g;
    else if(strcmp(a->info.name, food) < 0)
      return _GetCalories(a->dir, food);
    else
      return _GetCalories(a->esq, food);
  }
public:
  AVL() { 
    root = nullptr;
    rotações = 0; }

  int GetCalories(char food[30]){
    return _GetCalories(root, food);
  }

  int Inserir(FOODINFO x) {
    int ok = 0;
    root = Inserir(root, x, &ok);
    return ok;
  }
  void imprimir() {
     _imprimir(root, 1);
     printf("\n\nRotações %d", rotações); }

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

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Argumentos insuficientes");
    return 1;
  }

  FILE *SourceFIle;
  char line[50];
  SourceFIle = fopen(argv[1], "r");

  if (SourceFIle == NULL) {
    printf("File opening failed.\n");
    return 1;
  }

  AVL avl;


  while (fgets(line, sizeof(line), SourceFIle) != NULL) {
    struct FOODINFO food;

    char *token = strtok(line, ";");
    if (token != NULL) {
      strcpy(food.name, token);
      token = strtok(NULL, ";");
      if (token != NULL) {
        food.caloriesPer100g = std::stoi(token);
      }
      avl.Inserir(food);
      //printf("Food: %s and calories: %d per 100 grams\n",food.name,food.caloriesPer100g);
    }
  }
  fclose(SourceFIle);
  //avl.imprimir();
  char foodtest[30];
  strcpy(foodtest, "Spice Cake");
  printf("calories from %s is %d", foodtest, avl.GetCalories(foodtest));
  FILE *OutputFile;
  OutputFile = fopen(argv[2], "w");

  if (OutputFile == NULL) {
    printf("Failed to create file.\n");
    return 1;
  }
  fprintf(OutputFile, "%s", "test");

  fclose(OutputFile);

  

  return 0;
}