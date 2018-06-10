#ifndef TESTALISTA_H
#define TESTALISTA_H
#include"lista.h"
class TestaLista{
    private:
        ListaEncadeada<Contato> obj;
    public:
        void menuOrdenado();
        void menuDesordenado();
        Contato *inserirContato();
        void imprimirContato(Contato*aux);
};
#endif // TESTALISTA_H
