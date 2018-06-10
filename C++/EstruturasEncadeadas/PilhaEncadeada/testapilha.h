#ifndef TESTAPILHA_H
#define TESTAPILHA_H
#include"pilha.h"
class TestaPilha{
    private:
        Pilha obj;
    public:
        void menu();
        Contato *criaContato();
        void mostrarContato(Contato*);
};
#endif // TESTAPILHA_H
