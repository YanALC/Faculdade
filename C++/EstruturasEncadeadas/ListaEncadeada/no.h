#ifndef NO_H
#define NO_H
#include "item.h"
template <class item> class No{
private:
    item *dados;
    No<item> *proximo;
public:
    No(){
        dados=NULL;
        proximo=NULL;
    }
    No(item *aux){
        this->setDados(aux);
        proximo=NULL;
    }
    ~No(){
        dados=NULL;
        proximo=NULL;
        delete dados;
        delete proximo;
    }
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













#endif // NO_H
