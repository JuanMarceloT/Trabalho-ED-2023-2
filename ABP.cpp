#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Structs.h"
#include "ABP.h"
// ABP
// Utilizei codigos disponiveis no moodle
    TREESTATS ABPStats;


int comp(const char *a,const char *b){
  ABPStats.comp++;
  return(strcmp(a,b));
}

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

int _Height(pNodoA *a){
    if (a == NULL) {
        return 0; // Árvore vazia tem altura -1
    } else {
        int leftHeight = _Height(a->esq);
        int rightHeight = _Height(a->dir);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}

pNodoA *ABP::_find(pNodoA *a, char *chave)
{
  while (a != NULL)
  {
    ABPStats.comp++;
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


bool isBSTUtil(pNodoA* node, const char* minValue, const char* maxValue) {
    if (node == NULL) {
        return true;
    }

    if (strcmp(node->info.name, minValue) < 0 || strcmp(node->info.name, maxValue) > 0) {
        return false;
    }

    return (isBSTUtil(node->esq, minValue, node->info.name) &&
            isBSTUtil(node->dir, node->info.name, maxValue));
}

bool isBST(pNodoA* root) {
    const char* min = ""; // Valor min para a string
    const char* max = "zzzzzzzzzzzzzzzzzzzzzzzzz"; // Valor max para a string

    return isBSTUtil(root, min, max);
}


ABP::ABP() { 
  root = nullptr; 
  ABPStats.rotations = 0;
    ABPStats.nodes = 0; 
    strcpy(ABPStats.tree, "ABP");}

void ABP::insert(FOODINFO x) {
    root = InsereArvore(root, x);
    ABPStats.nodes++;
}
void ABP::print() { ImprimeArvore(root); }
pNodoA *ABP::find(char food[30]) { return ABP::_find(root, food); }
TREESTATS ABP::GetStats() {
      if(!isBST(root)){
        printf("Test FAILEDs\n");
      }
      ABPStats.height = _Height(root);
      return ABPStats;
}
