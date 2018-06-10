#ifndef TESTAPILHA_H
#define TESTAPILHA_H
#include"pilha.h"
class TestaPilha{
    private:
        Pilha obj;
    public:
        void menu();
        Livro *criaLivro();
        void mostrarLivro(Livro*);
};

#endif // TESTAPILHA_H
