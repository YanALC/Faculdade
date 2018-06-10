#ifndef TESTAFILA_H
#define TESTAFILA_H
#include"fila.h"
class TestaFila{
    private:
        Fila obj;
    public:
        void menu();
        Aluno *cadastraAluno();
        void mostrarAluno(Aluno*);
};

#endif // TESTAFILA_H
