#ifndef LISTA_H
#define LISTA_H
#include"aluno.h"
class Lista{
    private:
        Aluno **vet;
        short int tam,final;
    public:
        Lista();
        ~Lista();
        void free();
        bool setTam(short int); //define tamanho e aloca
        short int getTam()const;
        bool inserirFinal(Aluno*);
        bool inserirOrdenado(Aluno*);
        Aluno *remover(Aluno*);
        bool listaVazia()const;
        bool listaCheia()const;
        Aluno *buscar(string);
        void imprimirAluno(Aluno*);
        string imprimirTudo();
};

#endif // LISTA_H
