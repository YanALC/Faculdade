#ifndef PILHA_H
#define PILHA_H
#include"livro.h"
class Pilha{
    private:
        Livro **vet;
        short int topo,tam;
    public:
        Pilha();
        ~Pilha();
        bool setTam(short int); //define tamanho e aloca
        short int getTam()const;
        bool push(Livro*);
        Livro *pop();
        bool pilhaVazia()const;
        bool pilhaCheia()const;
};
#endif // PILHA_H
