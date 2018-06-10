#ifndef FILA_H
#define FILA_H
#include "aluno.h"
class Fila{
private:
    Aluno *inicio,*final;
public:
    bool enfileirar(Aluno*);
    Aluno *desenfileirar();
    bool filaVazia()const;
    Fila();
    ~Fila();
};
#endif // FILA_H
