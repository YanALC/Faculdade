#ifndef LISTA_H
#define LISTA_H
#include "no.h"
template <class item> class ListaEncadeada{
private:
    No<item> *inicio, *final;
    int tamanho;
public:
    ListaEncadeada()
    {
        inicio=final=NULL;
        tamanho=0;
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
            }
            atual->~No();
            anterior->~No();
            atual=anterior=NULL;
            delete anterior;
            delete atual;
        }
    }
    bool listaVazia()const {return (inicio==NULL);}
    int getTamanho()const {return tamanho;}
    void inserirFinal(const item *aux);
    void inserirInicio(const item *aux);
    void inserirCrescente(const item *aux);
    item *removerInicio();
    item *removerFinal();
    item *remover(item *key);
    item *buscar(item *key);
    item *operator [] (const int posicao);
    string listar();
};

template <class item> 
void ListaEncadeada<item>::inserirFinal(const item *aux)
{
    try{
        if(aux==NULL) throw string("\nElemento vazio!");
        No<item> *novo = new No<item>(aux);
        if(listaVazia()){
            inicio=final=novo;
        }else{
            final->setProximo(novo);
            final=novo;
        }tamanho++;
        novo=NULL;
        delete novo;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> 
void ListaEncadeada<item>::inserirInicio(const item *aux)
{
    try{
        if(aux==NULL) throw string("\nElemento vazio!");
        No<item> *novo = new No<item>(aux);
        if(listaVazia())
            inicio=final=novo;
        else{
            novo->setProximo(inicio);
            inicio=novo;
        }
        novo=NULL;
        delete novo;
        tamanho++;
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> 
void ListaEncadeada<item>::inserirCrescente(const item *aux)
{
    try{
        if(aux==NULL) throw string("\nElemento vazio!");
        No<item> *novo = new No<item>(aux);
        if(listaVazia())
            final=inicio=novo;
        else{
            No<item> *anterior,*atual;
            for(anterior=NULL, atual=inicio; atual!=NULL && *(novo->getDados())>*(atual->getDados()); anterior=atual, atual=atual->getProximo());
            if(atual==inicio){
                novo->setProximo(inicio);
                inicio=novo;
            }else{
                anterior->setProximo(novo);
                novo->setProximo(atual);
                if(atual==NULL) final=novo;
            }atual=anterior=novo=NULL;
            delete atual;
            delete anterior;
            delete novo;
            tamanho++;
        }
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
item *ListaEncadeada<item>::removerInicio()
{
    try{
        if(listaVazia()) throw string("\nLista Vazia!");
        No<item> *aux=inicio;
        inicio=inicio->getProximo();
        aux->setProximo(NULL);
        if(inicio==NULL) final=NULL;
        tamanho--;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw string("\nMemória Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
item *ListaEncadeada<item>::removerFinal()
{
    try{
        if(listaVazia()) throw string("\nLista Vazia!");
        No<item> *aux,*anterior;
        for(aux=inicio, anterior=NULL; aux!=final; anterior=aux, aux=aux->getProximo());
        anterior->setProximo(NULL);
        final=anterior;
        anterior=NULL;
        delete anterior;
        tamanho--;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
item *ListaEncadeada<item>::remover(item *key)
{
    try{
        if(listaVazia()) throw string("\nLista Vazia!");
        if(!key) throw string("\nElemento vazio!");
        No<item> *anterior,*aux;
        for(anterior=NULL, aux=inicio; aux && *key!=*(aux->getDados()); anterior=aux, aux=aux->getProximo());
        if(!aux) throw string("\nElemento nao encontrado!");
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
        tamanho--;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
item *ListaEncadeada<item>::buscar(item *key)
{
    try{
        if(!key) throw string("\nElemento vazio!");
        No<item> *aux;
        for(aux=inicio; aux && *key!=*(aux->getDados()); aux=aux->getProximo());
        if(!aux) throw string("\nElemento nao encontrado!");
        if(!aux->getDados()) return NULL;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template<class item>
item *ListaEncadeada<item>::operator [](const int posicao){
    try{
        if(!listaVazia()){
            if (posicao<1 || posicao>tamanho) {
                throw string("Posicao nao existe na lista!");
            }
            if(posicao==tamanho){
                return (final->getDados());
            }else{
                if(tamanho>1){
                    No<item> *aux=inicio;
                    for(int i=1; i!=posicao; i++, aux=aux->getProximo());
                    return No<item>::desmontarNo(aux);
                }else return (inicio->getDados());
            }
        }else return NULL;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> string ListaEncadeada<item>::listar()
{
    try{
        if(listaVazia()) throw string("\nLista vazia!");
        string aux="\n";
        No<item> *aux2;
        for(aux2=inicio; aux2!=NULL; aux+=aux2->getDados()->stringItem(), aux2=aux2->getProximo());
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

#endif // LISTA_H
