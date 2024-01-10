#include "Structs.h"

#ifndef ABPTREE_H
#define ABPTREE_H

class ABP {
private:
    pNodoA* root;
    int _GetCalories(pNodoA *a, char food[30]);
public:
    ABP();
    void insert(FOODINFO value);
    void print();
    int GetCalories(char food[30]);
    TREESTATS GetStats();
};

#endif // ABPTREE_H
