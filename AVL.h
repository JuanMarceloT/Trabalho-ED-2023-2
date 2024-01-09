#include "Structs.h"

#ifndef AVLTREE_H
#define AVLTREE_H

class AVL {
private:
    pNodoA* root;
public:
    AVL();
    void insert(FOODINFO value);
    void print();
    int GetCalories(char food[30]);
    TREESTATS GetStats();
};

#endif // AVLTREE_H
