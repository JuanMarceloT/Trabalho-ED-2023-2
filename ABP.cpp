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

int ABP::_GetCalories(pNodoA *a, char food[30]) {
  while (a != NULL) {
    ABPStats.comp++;
    if (strcmp(a->info.name, food) == 0)
      return a->info.caloriesPer100g; // achou retorna o ponteiro para o nodo
    else if (strcmp(a->info.name, food) > 0)
      a = a->esq;
    else
      a = a->dir;
  }
  return -1; // não achou, retorna null
}

int _Height(pNodoA *a){
    if (a == NULL) {
        return -1; // Árvore vazia tem altura -1
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
    const char* min = ""; // Valor mínimo possível para a string
    const char* max = "zzzzzzzzzzzzzzzzzzzzzzzzz"; // Valor máximo possível para a string

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
int ABP::GetCalories(char food[30]) { return _GetCalories(root, food); }
TREESTATS ABP::GetStats() {
      if(!isBST(root)){
        printf("Test FAILEDs\n");
      }
      ABPStats.height = _Height(root);
      return ABPStats;
}
