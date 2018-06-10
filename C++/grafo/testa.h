#ifndef TESTA_H
#define TESTA_H
#include "grafo.h"

class Testa{
private:
    Grafo *obj = NULL;
public:
    void menu();
    void menuBuscas();
    void imprimelistaAdj(int v);
    Grafo::Aresta *preecheAresta();
};

#endif // TESTA_H
