#ifndef NO_H
#define NO_H
#include "item.h"
template <class item> class No{
private:
    item *dados;
    No<item> *proximo;
public:
    bool setDados(item*);
    void setProximo(No<item>*);
    item *getDados()const;
    No<item> *getProximo()const;
    static No<item> *montarNo(item*);
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

template <class item> void No<item>::setProximo(No<item> *aux){
    proximo=aux;
}

template <class item> No<item> *No<item>::getProximo()const{
    return proximo;
}

template <class item> No<item> *No<item>::montarNo(item *aux){
    try{
        No<item> *novo = new No;
        novo->setDados(aux);
        novo->setProximo(NULL);
        return novo;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template <class item> item *No<item>::desmontarNo(No<item> *aux)
{
    try{
        item *retorno = aux->getDados();
        delete aux;
        aux=NULL;
        return retorno;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}
#endif // NO_H
