#ifndef FILA_H
#define FILA_H
#include"aluno.h"
class Fila{
    private:
        Aluno **vet;
        short int tam,final;
    public:
        Fila();
        ~Fila();
        void free();
        bool setTam(short int); //define tamanho e aloca
        short int getTam()const;
        bool enfileirar(Aluno*);
        Aluno *desenfileirar();
        bool filaVazia()const;
        bool filaCheia()const;
};

#endif // FILA_H
