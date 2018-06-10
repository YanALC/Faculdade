#ifndef LIST_H
#define LIST_H
#include "item.h"

template <class item> class No{
private:
    No<item>*anterior,*proximo;
    item *dados;
public:
    No(){
        anterior=proximo=NULL;
        dados=NULL;
    }
    No(item *aux){
        this->setDados(aux);
        proximo=anterior=NULL;
    }
    ~No(){
        anterior=proximo=NULL;
        dados=NULL;
        delete anterior;
        delete proximo;
        delete dados;
    }
    No<item> *getAnterior() const{return anterior;}
    void setAnterior(No<item> *value){anterior=value;}
    No<item> *getProximo() const{return proximo;}
    void setProximo(No<item> *value){proximo=value;}
    item *getDados() const{return dados;}
    void setDados(item *value){
        if(value)
            dados=value;
        else throw string("\nDados nulos.");
    }
    static item *desmontarNo(No<item>*aux)
    {
        try{
            item *retorno = aux->getDados();
            aux=NULL;
            delete aux;
            return retorno;
        }
        catch(bad_alloc &){
            throw string("\nMemoria Insuficiente!");
        }
    }
};

template <class item> class Lista{
private:
    No<item>*inicio,*final,*pos;
    int tamanho;
public:
    Lista(){
        inicio=final=pos=NULL;
        tamanho=0;
    }
    ~Lista(){
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
    bool listaVazia() const {return (inicio==NULL);}
    void inserirCrescente(item *aux);
    void inserirInicio(item *aux);
    void inserirFinal(item *aux);
    item *remover(item *key);
    item *removerInicio();
    item *removerFinal();
    item *buscar(item *key);
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
void Lista<item>::inserirCrescente(item *aux)
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
void Lista<item>::inserirInicio(item *aux)
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
void Lista<item>::inserirFinal(item *aux)
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
item *Lista<item>::remover(item *key)
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
item *Lista<item>::removerInicio()
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
item *Lista<item>::removerFinal()
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
item *Lista<item>::buscar(item *key)
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

#endif // LIST_H
