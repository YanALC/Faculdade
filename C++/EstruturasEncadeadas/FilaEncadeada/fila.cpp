#include "fila.h"

Fila::Fila()
{
    inicio=NULL;
    final=NULL;
}

bool Fila::enfileirar(Aluno *aux)
{
    if(aux==NULL) return false;
    aux->setProximo(NULL);
    if(filaVazia()){
        inicio=final=aux;
        return true;
    }
    final->setProximo(aux);
    final=aux;
    return true;
}

Aluno *Fila::desenfileirar()
{
    if(filaVazia()) return NULL;
    Aluno *aux = inicio;
    inicio=inicio->getProximo();
    aux->setProximo(NULL);
    if(inicio==NULL) final==NULL;
    return aux;
}

bool Fila::filaVazia() const
{
    return (inicio==NULL);
}

Fila::~Fila()
{
    Aluno *aux=NULL;
    while(!filaVazia()){
        aux=desenfileirar();
        delete aux;
    }
}
