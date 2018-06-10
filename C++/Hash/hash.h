#ifndef HASH_H
#define HASH_H
#include "lista.h"

template <class item> class Hash{
private:
    ListaEncadeada<Item> **vetor;
    int tam,cont;
public:
    Hash(){vetor=NULL;}
    ~Hash(){
        if(vetor){
            for(int i=0;i<this->getTam();i++){
                vetor[i]=NULL;
                delete vetor[i];
            }
            vetor=NULL;
            delete [] vetor;
        }else throw string("O vetor não existe!");
    }
    int getTam() const;
    bool setTam(int value);
    int hashFunction(item *aux);
    bool inserir(item *aux);
    item *buscar(item *aux);
    item *remover(item *aux);
    string listar();
};

template <class item>
int Hash<item>::getTam() const
{
    return tam;
}

template <class item>
bool Hash<item>::setTam(int value)
{
    try{
        if(value>2){
            tam = value;
            cont=0;
            vetor = new ListaEncadeada<item> *[tam];
            for(int i=0; i<tam; i++){
                vetor[i] = new ListaEncadeada<item>;
            }return true;
        }return false;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template<class item>
int Hash<item>::hashFunction(item *aux)
{
    return (std::stoi(aux->getChave()))%tam;
}

template <class item>
bool Hash<item>::inserir(item *aux)
{
    try{
        cont++;
        if(cont<getTam()){
            int pos = hashFunction(aux);
            if(vetor[pos]->buscar(aux)==NULL){
                vetor[pos]->inserirFinal(aux);
                return true;
            }return false;
        }return false;
    }
    catch(string &erro){
        throw erro;
    }
}

template<class item>
item *Hash<item>::buscar(item *aux)
{
    try{
        return vetor[hashFunction(aux)]->buscar(aux);
    }
    catch (string &erro){
        throw erro;
    }
}

template<class item>
item *Hash<item>::remover(item *aux)
{
    try {
        if(*buscar(aux)==aux){
            cont--;
            return vetor[hashFunction(aux)]->remover(aux);
        }
        else
            return NULL;
    }
    catch (string &erro) {
        throw erro;
    }
}

template<class item>
string Hash<item>::listar()
{
    try{
        string aux="\n";
        for(int i=0;i<getTam();i++){
            aux+="VETOR["+to_string(i)+"]\t"+vetor[i]->listar()+"\n";
        }
        return aux;
    }
    catch (string &erro) {
        throw erro;
    }
}

#endif // HASH_H

