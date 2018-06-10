#ifndef LIST_H
#define LIST_H
#include "no.h"

template <class item> class ListaEncadeada{
private:
    No<item> *inicio, *final;
    bool listaVazia()const;
public:
    ListaEncadeada()
    {
        inicio=final=NULL;
    }
    ~ListaEncadeada()
    {
        if(!listaVazia()){
            No<item> *atual=inicio,
                    *anterior=NULL;
            while(atual->getProximo()!=NULL){
                anterior=atual;
                atual=atual->getProximo();
                delete anterior;
            }delete atual;
        }
    }
    bool inserirFinal(item*);
    item *remover(item*);
    item *buscar(item*);
    string listar();
};

template <class item> bool ListaEncadeada<item>::inserirFinal(item *aux)
{
    try{
        if(aux==NULL) throw string("\nElemento vazio!");
        No<item> *novo = No<item>::montarNo(aux);
        if(listaVazia()){
            inicio=final=novo;
        }else{
            final->setProximo(novo);
            final=novo;
        }
        novo=NULL;
        delete novo;
        return true;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> item *ListaEncadeada<item>::remover(item *key)
{
    try{
        if(listaVazia()) throw string("\nLista Vazia!");
        No<item> *anterior=NULL;
        No<item> *aux=inicio;
        while(aux!=NULL && *key!=aux->getDados()){
            anterior=aux;
            aux=aux->getProximo();
        }
        if(aux==NULL) return NULL;
        if(aux==inicio){
            inicio=inicio->getProximo();
            aux->setProximo(NULL);
            if(inicio==NULL) final=NULL;
        }else{
            anterior->setProximo(aux->getProximo());
            aux->setProximo(NULL);
            if(aux==final) final=anterior;
        }
        anterior=NULL;
        delete anterior;
        item *retorno = No<item>::desmontarNo(aux);
        return retorno;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> bool ListaEncadeada<item>::listaVazia()const
{
    return (inicio==NULL);
}

template <class item> item *ListaEncadeada<item>::buscar(item *key)
{
    try{
        No<item> *aux=inicio;
        while(aux!=NULL && *key!=aux->getDados()){
            aux=aux->getProximo();
        }
        if(aux==NULL) return NULL;
        item *retorno = new item;
        *retorno=*(aux->getDados());
        aux=NULL;
        delete aux;
        return retorno;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> string ListaEncadeada<item>::listar()
{
    try{
//        if(listaVazia()) throw string("\nLista vazia!");
        string aux="\n";
        No<item> *aux2 = inicio;
        while(aux2){
            aux+=aux2->getDados()->empacotaItem()+"\n";
            aux2=aux2->getProximo();
        }
        aux2=NULL;
        delete aux2;
        return aux;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

#endif // LIST_H
