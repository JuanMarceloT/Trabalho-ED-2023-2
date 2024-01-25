#include "Structs.h"

#ifndef ABPTREE_H
#define ABPTREE_H

class ABP {
private:
    pNodoA* root;
    pNodoA *_find(pNodoA *a, char food[30]);
public:
    ABP();
    void insert(FOODINFO value);
    void print();
    pNodoA *find(char food[30]);
    TREESTATS GetStats();
};

#endif // ABPTREE_H
