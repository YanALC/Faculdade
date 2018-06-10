#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

class Item{
private:
    string chave,nome;
public:
    string getChave() const{
        return chave;
    }
    void setChave(string value){
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
    bool operator ==(Item *aux){
        if((this->getChave())==(aux->getChave())) return true;
        return false;
    }
    bool operator !=(Item *aux){
        if((this->getChave())!=(aux->getChave())) return true;
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
        saida<<"\n"<<obj->chave<<"\t"<<obj->nome<<endl;
        return saida;
    }
    friend istream & operator >>(istream &entrada, Item *obj){
        entrada.ignore();
        cout<<"\nChave: ";
        getline(entrada,obj->chave);
        cout<<"\nNome: ";
        getline(entrada,obj->nome);
        return entrada;
    }
    string empacotaItem(){
        return (getChave()+"\t"+getNome());
    }
};
#endif // ITEM_H
