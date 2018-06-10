#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

class Item{
private:
    long int chave=0;
    string nome;
public:
    long int getChave() const{
        return chave;
    }
    void setChave(long int value){
        chave = value;
    }
    string getNome() const{
        return nome;
    }
    void setNome(const string &value){
        nome = value;
    }
    bool operator >(Item *aux){
        if((this->getChave())>(aux->getChave())) return true;
        return false;
    }
    bool operator <(Item *aux){
        if((this->getChave())<(aux->getChave())) return true;
        return false;
    }
    bool operator =(Item *aux){
        if((this->getChave())==(aux->getChave())) return true;
        return false;
    }
    bool operator <=(Item *aux){
        if((this->getChave())<=(aux->getChave())) return true;
        return false;
    }
    bool operator >=(Item *aux){
        if((this->getChave())>=(aux->getChave())) return true;
        return false;
    }
    friend ostream & operator <<(ostream &saida, const Item *obj){
        saida<<"\t\n"<<obj->chave<<"\t"<<endl;
        return saida;
    }
    friend istream & operator >>(istream &entrada, Item *obj){
        cout<<"\nChave: ";
        entrada>>obj->chave;
        while(obj->chave<=0){
            cout<<"\nChave somente positiva! Chave: ";
            entrada>>obj->chave;
        }entrada.ignore();
        cout<<"\nNome: ";
        getline(entrada,obj->nome);
        return entrada;
    }
};

#endif // ITEM_H
