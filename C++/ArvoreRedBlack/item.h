#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;
class Item{
private:
    int key;
    string nome;
public:
    bool setKey(int aux){
        if(aux){
            key=aux;
            return true;
        }return false;
    }
    int getKey()const{return key;}
    void setNome(string aux){nome=aux;}
    string getNome()const{return nome;}
    inline bool operator> (Item *aux){return (this->getKey()>aux->getKey());}
    inline bool operator< (Item *aux){return (this->getKey()<aux->getKey());}
    void operator= (Item *aux){
        this->key=aux->key;
        this->nome=aux->nome;
    }
    string empacotaItem()const{
        string aux;
        aux="\n"+to_string(key)+"\t"+nome;
        return aux;
    }
};
#endif // ITEM_H
