#ifndef NO_H
#define NO_H
#include "dados.h"
template <class item> class No{
private:
    No<item>*anterior,*proximo;
    item *dados;
public:
    No(){
        anterior=NULL;
        proximo=NULL;
        dados=NULL;
    }
    ~No(){}
    No<item>*getAnterior() const;
    No<item>*getProximo() const;
    void setAnterior(No<item>*);
    void setProximo(No<item>*);
    item *getDados() const;
    bool setDados(item *);
    static No<item>*montarNo(item *);
    static item *desmontarNo(No<item>*);
};

template <class item> bool No<item>::setDados(item *aux){
    if(aux){
        dados=aux;
        return true;
    }return false;
}

template <class item> item *No<item>::getDados()const{
    return dados;
}

template <class item> void No<item>::setAnterior(No<item>*aux){
    anterior=aux;
}

template <class item> void No<item>::setProximo(No<item>*aux){
    proximo=aux;
}

template <class item> No<item> *No<item>::getAnterior() const
{
    return anterior;
}

template <class item> No<item>*No<item>::getProximo()const{
    return proximo;
}

template <class item> No<item>*No<item>::montarNo(item *aux){
    try{
        No<item>*novo = new No<item>;
        novo->setDados(aux);
        novo->setProximo(NULL);
        novo->setAnterior(NULL);
        return novo;
    }
    catch(bad_alloc &){
        throw QString("\nMemória Insuficiente!");
    }
}

template <class item> item *No<item>::desmontarNo(No<item>*aux)
{
    try{
        item *retorno = aux->getDados();
        aux=NULL;
        delete aux;
        return retorno;
    }
    catch(bad_alloc &){
        throw QString("\nMemória Insuficiente!");
    }
}
#endif // NO_H
