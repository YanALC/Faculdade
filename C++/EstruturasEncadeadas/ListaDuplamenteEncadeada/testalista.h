#ifndef TESTALISTADUPLAMENTEENCADEADA_H
#define TESTALISTADUPLAMENTEENCADEADA_H
#include "listaduplamenteencadeada.h"
class TestaLista{
private:
    ListaDuplamenteEncadeada<Contato> *obj = new ListaDuplamenteEncadeada<Contato>;
public:
    void menuOrdenado();
    void menuDesordenado();
    Contato *criarItem();
    void mostrarItem(Contato *);
    string listar();
};

#endif // TESTALISTADUPLAMENTEENCADEADA_H
