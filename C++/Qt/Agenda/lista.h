#ifndef LISTA_H
#define LISTA_H
#include <QListWidget>
#include "no.h"
template <class item> class Lista{
private:
    No<item>*inicio,*final;
    int i;
public:
    Lista(){
        inicio=NULL;
        final=NULL;
        i=0;
    }
    ~Lista(){
        if(!listaVazia()){
            No<item> *atual=inicio;
            while(atual->getProximo()!=NULL){
                atual=atual->getProximo();
                delete (atual->getAnterior());
            }atual=NULL;
            delete atual;
        }final=inicio=NULL;
        i=0;
    }
    int getI() const
    {
        return i;
    }
    bool listaVazia() const
    {
        return (inicio==NULL);
    }
    void inserirOrdenado(item *);
    void inserirFinal(item *);
    item *remover(item *);
    item *removerInicio();
    item *buscar(item *);
    QString listar();
    item *operator [] (int posicao);
    void listarUI(QListWidget *aux);
};

template <class item> void Lista<item>::inserirOrdenado(item *aux)
{
    try{
        if(aux==NULL) throw QString("\nElemento vazio!");
        No<item>*novo = No<item>::montarNo(aux);
        if(listaVazia()){
            final=inicio=novo;
        }else{
            No<item>*atual = inicio;
            while(atual!=NULL && novo->getDados()->operator >(atual->getDados())){
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
        i++;
        novo=NULL;
        delete novo;
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class item> void Lista<item>::inserirFinal(item *aux)
{
    try{
        if(aux==NULL) throw QString("\nElemento vazio!");
        No<item>*novo = No<item>::montarNo(aux);
        if(listaVazia()){
            inicio=final=novo;
        }else{
            final->setProximo(novo);
            novo->setAnterior(final);
            final=novo;
        }
        i++;
        novo=NULL;
        delete novo;
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class item> item *Lista<item>::remover(item *key)
{
    try{
        if(listaVazia()) throw QString("\nLista vazia!");
        No<item>*aux=inicio;
        while(aux!=NULL && key->operator!=(aux->getDados())){
            aux=aux->getProximo();
        }
        if(aux==NULL) throw QString("\nElemento não encontrado!");
        if(aux==inicio){
            inicio=aux->getProximo();
            if(inicio==NULL) final=NULL;
            else aux->getProximo()->setAnterior(NULL);
            aux->setProximo(NULL);
        }else{
            if(aux==final) {
                aux->getAnterior()->setProximo(NULL);
                final=aux->getAnterior();
                aux->setAnterior(NULL);
            }else{
                aux->getAnterior()->setProximo(aux->getProximo());
                aux->getProximo()->setAnterior(aux->getAnterior());
            }
        }
        i--;
        return aux->getDados();
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class item> item *Lista<item>::removerInicio()
{
    try{
        if(listaVazia()) throw QString("\nLista vazia!");
        No<item>*aux=inicio;
        inicio=aux->getProximo();
        if(inicio==NULL) final=NULL;
        else aux->getProximo()->setAnterior(NULL);
        aux->setProximo(NULL);
        i--;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class item> item *Lista<item>::buscar(item *key)
{
    try{
        if(listaVazia()) throw QString("\nLista vazia!");
        No<item>*aux=inicio;
        while(aux!=NULL && key->operator!=(aux->getDados())){
            aux=aux->getProximo();
        }
        if(!aux) throw string("\nElemento não encontrado!");
        if(!aux->getDados()) return NULL;
        return No<item>::desmontarNo(aux);
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class item> QString Lista<item>::listar()
{
    try{
//        if(listaVazia()) throw QString("\nLista vazia!");
        QString aux="";
        No<item>*aux2 = inicio;
        while(aux2!=NULL){
            aux+=aux2->getDados()->empacotaItem(2)+"\n";
            aux2=aux2->getProximo();
        }
        delete aux2;
        return aux;
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template<class item>
item *Lista<item>::operator [](int posicao){
    try{
        if (!listaVazia()){
            No<item> *aux = inicio;
            if (posicao>i || posicao<0) {
                throw QString("Selecione um item!");
            }
            if(posicao == i){
                return (final->getDados());
            }else{
                if(i>1){
                    for(int i2=0; i2!=posicao; i2++){
                        aux = aux->getProximo();
                    }return (aux->getDados());
                }else{
                    return (inicio->getDados());
                }
            }
        }else return NULL;
    }
    catch(bad_alloc&){
        throw QString("\nMemória Insuficiente!");
    }
    catch(QString &erro){
        throw erro;
    }
}

template<class item> void Lista<item>::listarUI(QListWidget *aux){
    try{
        if(listaVazia()) return;
        No<item> *aux2 = inicio;
        while(aux2!=NULL){
            aux->addItem(aux2->getDados()->empacotaItem(1));
            aux2=aux2->getProximo();
        }
        delete aux2;
    }
    catch(bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}
#endif // LISTA_H
