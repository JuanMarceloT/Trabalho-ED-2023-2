
#pragma once

struct FOODINFO {
  char name[50];
  int caloriesPer100g;
};
typedef struct FOODINFO FOODINFO;

struct TreeStats {
char tree[5];
  int nodes;
  int height;
  int rotations;
  int comp;
};
typedef struct TreeStats TREESTATS;

struct TNodoA {
  FOODINFO info;
  int FB;
  struct TNodoA *esq;
  struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;