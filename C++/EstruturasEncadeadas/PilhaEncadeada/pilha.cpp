#include "pilha.h"
Pilha::Pilha(){
    topo=NULL;
}
bool Pilha::pilhaVazia()const{
    return (topo==NULL);
}
Contato * Pilha::pop(){
    if(pilhaVazia()) return NULL;
    Contato * aux = topo;
    topo=aux->getProximo();
    aux->setProximo(NULL);
    return aux;
}
bool Pilha::push(Contato * novo){
    if(novo){
        novo->setProximo(topo);
        topo=novo;
        return true;
    }return false;
}
Pilha::~Pilha(){
    Contato * aux = NULL;
    while(!pilhaVazia()){
        aux=pop();
        delete aux;
    }
}
