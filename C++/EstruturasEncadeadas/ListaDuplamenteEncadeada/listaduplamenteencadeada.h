#ifndef LISTADUPLAMENTEENCADEADA_H
#define LISTADUPLAMENTEENCADEADA_H
#include "no.h"
template <class item> class ListaDuplamenteEncadeada{
private:
    No<item>*inicio,*final,*pos;
    int tamanho;
public:
    ListaDuplamenteEncadeada(){
        inicio=final=pos=NULL;
        tamanho=0;
    }
    ~ListaDuplamenteEncadeada(){
        if(!listaVazia()){
            No<item> *atual=inicio;
            while(atual->getProximo()!=NULL){
                atual=atual->getProximo();
                delete (atual->getAnterior());
            }atual->~No();
            atual=NULL;
            delete atual;
        }
        inicio->~No();
        final->~No();
        inicio=final=NULL;
        delete inicio;
        delete final;
    }
    int getTamanho() const {return tamanho;}
    bool listaVazia() const
    {
        return (inicio==NULL);
    }
    void inserirOrdenado(const item *aux);
    void inserirInicio(const item *aux);
    void inserirFinal(const item *aux);
    item *remover(item *key);
    item *removerInicio();
    item *removerFinal();
    item *buscar(item *key);
    item *operator [] (const int posicao);
    string listar();
    item *primeiro()
    {
        pos=inicio;
        if(pos) return pos->getDados();
        else return NULL;
    }
    item *proximo()
    {
        pos=pos->getProximo();
        if(pos) return pos->getDados();
        else return NULL;
    }
};

template <class item>
void ListaDuplamenteEncadeada<item>::inserirOrdenado(const item *aux)
{
    try{
        if(!aux) throw string("\nElemento vazio!");
        No<item>*novo = new No<item>(aux);
        if(listaVazia()){
            final=inicio=novo;
        }else{
            No<item>*atual = inicio;
            while(atual && (*aux > *(atual->getDados()))){
                atual=atual->getProximo();
            }
            if(atual==inicio){
                novo->setProximo(inicio);
                inicio->setAnterior(novo);
                inicio=novo;
           }else{
                if(atual==NULL){
                    final->setProximo(novo);
                    novo->setAnterior(final);
                    final=novo;
                }else{
                    novo->setProximo(atual);
                    atual->getAnterior()->setProximo(novo);
                    novo->setAnterior(atual->getAnterior());
                    atual->setAnterior(novo);
                }
            }
            atual=NULL;
            delete atual;
        }
        novo=NULL;
        delete novo;
        tamanho++;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template<class item>
void ListaDuplamenteEncadeada<item>::inserirInicio(const item *aux)
{
    try{
        if(!aux) throw string("\nElemento vazio!");
        No<item>*novo = new No<item>(aux);
        if(listaVazia())
            inicio=final=novo;
        else{
            novo->setProximo(inicio);
            inicio->setAnterior(novo);
            inicio=novo;
        }
        novo=NULL;
        delete novo;
        tamanho++;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
void ListaDuplamenteEncadeada<item>::inserirFinal(const item *aux)
{
    try{
        if(buscar(aux)) throw string("\nAresta já existe!");
        if(!aux) throw string("\nElemento vazio!");
        No<item>*novo = new No<item>(aux);
        if(listaVazia())
            inicio=final=novo;
        else{
            final->setProximo(novo);
            novo->setAnterior(final);
            final=novo;
        }
        novo=NULL;
        delete novo;
        tamanho++;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item>
item *ListaDuplamenteEncadeada<item>::remover(item *key)
{
    try{
        if(!key) throw string("\nElemento vazio!");
        if(listaVazia()) throw string("\nLista Vazia!");
        No<item>*aux=inicio;
        while(aux && (*key != *(aux->getDados()))){
            aux=aux->getProximo();
        }
        if(aux==NULL) throw string("\nElemento nao encontrado!");
        if(aux==inicio){
            inicio=inicio->getProximo();
            if(inicio==NULL) final=NULL;
            else aux->getProximo()->setAnterior(NULL);
            aux->setProximo(NULL);
        }else{
            if(aux==final){
                final=final->getAnterior();
                if(final==NULL) inicio=NULL;
                else aux->getAnterior()->setProximo(NULL);
                aux->setAnterior(NULL);
            }else{
                aux->getAnterior()->setProximo(aux->getProximo());
                aux->getProximo()->setAnterior(aux->getAnterior());
            }
        }
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
item *ListaDuplamenteEncadeada<item>::removerInicio()
{
    try{
        if(listaVazia()) throw string("\nLista vazia!");
        No<item>*aux=inicio;
        inicio=inicio->getProximo();
        if(inicio==NULL) final=NULL;
        else aux->getProximo()->setAnterior(NULL);
        aux->setProximo(NULL);
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

template<class item>
item *ListaDuplamenteEncadeada<item>::removerFinal()
{
    try{
        if(listaVazia()) throw string("\nLista vazia!");
        No<item>*aux=final;
        final=final->getAnterior();
        if(final==NULL) inicio=NULL;
        else aux->getAnterior()->setProximo(NULL);
        aux->setAnterior(NULL);
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
item *ListaDuplamenteEncadeada<item>::buscar(item *key)
{
    try{
        if(!key) throw string("\nElemento vazio!");
        if(listaVazia()) throw string("\nLista vazia!");
        No<item>*aux=inicio;
        while(aux && *key!=*(aux->getDados())){
            aux=aux->getProximo();
        }
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
item *ListaDuplamenteEncadeada<item>::operator [](const int posicao){
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
                    for(int i=1; i!=posicao; i++){
                        aux=aux->getProximo();
                    }return No<item>::desmontarNo(aux);
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

template <class item>
string ListaDuplamenteEncadeada<item>::listar()
{
    try{
        if(listaVazia()) throw string("\nLista vazia!");
        string aux="\n";
        No<item>*aux2 = inicio;
        while(aux2!=NULL){
            aux+=aux2->getDados()->stringItem();
            aux2=aux2->getProximo();
        }aux2=NULL;
        delete aux2;
        return aux;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

#endif // LISTADUPLAMENTEENCADEADA_H
