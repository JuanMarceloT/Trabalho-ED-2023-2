#include "Structs.h"

#ifndef AVLTREE_H
#define AVLTREE_H

class AVL {
private:
    pNodoA* root;
    pNodoA *_find(pNodoA *a, char food[30]);
public:
    AVL();
    void insert(FOODINFO value);
    void print();
    pNodoA *find(char food[30]);
    TREESTATS GetStats();
};

#endif // AVLTREE_H
