#ifndef NOARB_H
#define NOARB_H
#define VERMELHO 'v'
#define PRETO 'p'
#include "item.h"

template <class item> class NoARB{
private:
    NoARB *pai,*esquerda,*direita;
    item *dados;
    char cor;
public:
    NoARB(){
        pai=esquerda=direita=NULL;
        dados=NULL;
        cor=PRETO;
    }
    NoARB(item *aux){
        this->setDados(aux);
        pai=esquerda=direita=NULL;
        cor=PRETO;
    }
    ~NoARB(){
        pai=esquerda=direita=NULL;
        dados=NULL;
        delete pai;
        delete esquerda;
        delete direita;
        delete dados;
    }
    void setPai(NoARB *aux) {pai=aux;}
    void setEsquerda(NoARB *aux) {esquerda=aux;}
    void setDireita(NoARB *aux) {direita=aux;}
    void setDados(item *aux){
        if(aux)
            dados=aux;
        else throw string("\nDados nulos.");
    }
    void setCor(char value) {
        if(value==PRETO || value==VERMELHO)
            cor=value;
        else throw string("\nCor invalida.");
    }
    char getCor() {return cor;}
    NoARB *getPai()const {return pai;}
    NoARB *getEsquerda()const {return esquerda;}
    NoARB *getDireita()const {return direita;}
    Item *getDados()const {return dados;}
    static item *desmontarNo(NoARB *aux){
        item *retorno = aux->getDados();
        aux=NULL;
        delete aux;
        return retorno;
    }
};

#endif // NOARB_H
