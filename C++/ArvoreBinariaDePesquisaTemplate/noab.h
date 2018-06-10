#ifndef NOAB_H
#define NOAB_H
#include "item.h"
template <class item> class NoAB{
private:
    NoAB *pai,*esquerda,*direita;
    item *dados;
public:
    NoAB(){
        pai=esquerda=direita=NULL;
        dados=NULL;
    }
    NoAB(item *aux){
        this->setDados(aux);
        esquerda=direita=pai=NULL;
    }
    ~NoAB(){
        pai=esquerda=direita=NULL;
        dados=NULL;
        delete pai;
        delete esquerda;
        delete direita;
        delete dados;
    }
    void setPai(NoAB *aux) {pai=aux;}
    void setEsquerda(NoAB *aux) {esquerda=aux;}
    void setDireita(NoAB *aux) {direita=aux;}
    bool setDados(item *aux) {
        if(aux){
            dados=aux;
            return true;
        }return false;
    }
    NoAB *getPai()const {return pai;}
    NoAB *getEsquerda()const {return esquerda;}
    NoAB *getDireita()const {return direita;}
    item *getDados()const {return dados;}
    static item *desmontarNo(NoAB *aux){
        item *retorno = aux->getDados();
        aux=NULL;
        delete aux;
        return retorno;
    }
};

#endif // NOAB_H
