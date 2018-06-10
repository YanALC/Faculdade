#ifndef PILHA_H
#define PILHA_H
#include "contato.h"
class Pilha{
private:
    Contato* topo;
public:
    Pilha();
    ~Pilha();
    bool push(Contato*);
    Contato* pop();
    bool pilhaVazia()const;
};
#endif // PILHA_H
