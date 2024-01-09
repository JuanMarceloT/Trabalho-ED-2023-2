#include "Structs.h"

#ifndef ABPTREE_H
#define ABPTREE_H

class ABP {
private:
    pNodoA* root;
    TREESTATS AVLStats;
public:
    ABP();
    void insert(FOODINFO value);
    void print();
    int GetCalories(char food[30]);
    TREESTATS GetStats();
};

#endif // ABPTREE_H
