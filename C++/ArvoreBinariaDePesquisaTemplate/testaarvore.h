#ifndef TESTAARVORE_H
#define TESTAARVORE_H
#include "abp.h"

class TestaArvore
{
private:
    ABP<Item> *obj = new ABP<Item>;
public:
    Item *criarItem();
    void mostrarItem(Item *);
    void menu();
};

#endif // TESTAARVORE_H
