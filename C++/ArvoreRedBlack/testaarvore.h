#ifndef TESTAARVORE_H
#define TESTAARVORE_H
#include "arb.h"

class TestaArvore
{
private:
    ARB<Item> *obj = new ARB<Item>;
public:
    Item *criarItem();
    void mostrarItem(Item *);
    void menu();
};

#endif // TESTAARVORE_H
