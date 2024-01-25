
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "AVL.h"
#include "Structs.h"
// avl
// Utilizei codigos disponiveis no moodle

TNodoA *root;
TREESTATS AVLStats;

pNodoA *rotacao_direita(pNodoA *p)
{
  AVLStats.rotations++;
  pNodoA *u;
  u = p->esq;
  p->esq = u->dir;
  u->dir = p;
  p->FB = 0;
  p = u;
  return p;
}
pNodoA *rotacao_esquerda(pNodoA *p)
{
  AVLStats.rotations++;
  pNodoA *z;
  z = p->dir;
  p->dir = z->esq;
  z->esq = p;
  p->FB = 0;
  p = z;
  return p;
}
pNodoA *rotacao_dupla_direita(pNodoA *p)
{
  AVLStats.rotations++;
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
pNodoA *rotacao_dupla_esquerda(pNodoA *p)
{
  AVLStats.rotations++;
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
pNodoA *Caso1(pNodoA *a, int *ok)
{
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
pNodoA *Caso2(pNodoA *a, int *ok)
{
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

void _imprimir(pNodoA *nodo, int nivel)
{
  if (nodo == NULL)
    return;

  for (int i = 0; i < nivel; i++)
  {
    printf("=");
  }
  printf("%s\nesq: %s\ndir: %s\n\n\n", nodo->info.name, nodo->esq->info.name,
         nodo->dir->info.name);
  printf("\n");
  _imprimir(nodo->esq, (nivel + 1));
  _imprimir(nodo->dir, (nivel + 1));
}

pNodoA *Inserir(pNodoA *a, FOODINFO x, int *ok)
{
  /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
  x, a chave a ser inserida e h a altura da árvore */

  if (a == NULL)
  {
    a = (pNodoA *)malloc(sizeof(pNodoA));
    a->info = x;
    a->esq = NULL;
    a->dir = NULL;
    a->FB = 0;
    *ok = 1;
  }
  else if (strcmp(x.name, a->info.name) < 0)
  {
    a->esq = Inserir(a->esq, x, ok);
    if (*ok)
    {
      switch (a->FB)
      {
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
  }
  else
  {
    a->dir = Inserir(a->dir, x, ok);
    if (*ok)
    {
      switch (a->FB)
      {
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


pNodoA *AVL::_find(pNodoA *a, char *chave)
{
  while (a != NULL)
  {
    AVLStats.comp++;
    if (!strcmp(a->info.name, chave))
    {
      return a;
    }
    else
    {
      if (strcmp(a->info.name, chave) > 0)
        a = a->esq;
      else
        a = a->dir;
    }
  }
  return NULL;
}


int _Altura(pNodoA *a)
{
  int Alt_Esq, Alt_Dir;
  if (a == NULL)
    return 0;
  else
  {
    Alt_Esq = _Altura(a->esq);
    Alt_Dir = _Altura(a->dir);
    if (Alt_Esq > Alt_Dir)
      return (1 + Alt_Esq);
    else
      return (1 + Alt_Dir);
  }
}

bool isAVL(pNodoA *root)
{
  if (root == NULL)
  {
    return true;
  }

  int heightDiff = abs(_Altura(root->esq) - _Altura(root->dir));
  if (heightDiff > 1)
  {
    return false;
  }

  return isAVL(root->esq) && isAVL(root->dir);
}

AVL::AVL()
{
  root = nullptr;
  AVLStats.rotations = 0;
  AVLStats.nodes = 0;
  strcpy(AVLStats.tree, "AVL");
}

pNodoA *AVL::find(char food[30])
{
  return AVL::_find(root, food);
}

void AVL::insert(FOODINFO x)
{
  int ok = 0;
  root = Inserir(root, x, &ok);
  AVLStats.nodes++;
}
void AVL::print()
{
  _imprimir(root, 1);
}

TREESTATS AVL::GetStats()
{
  AVLStats.height = _Altura(root);
  if (!isAVL(root))
  {
    printf("Test FAILED\n");
  }
  return AVLStats;
}
