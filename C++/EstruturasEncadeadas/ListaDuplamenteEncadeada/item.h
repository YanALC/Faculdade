#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;
class Contato{
private:
    string nome,telefone;
public:
    void setNome(string aux){nome=aux;}
    void setTelefone(string aux){telefone=aux;}
    string getNome()const{return nome;}
    string getTelefone()const{return telefone;}
    bool operator> (Contato aux){
        return ((this->getNome())>(aux.getNome())? true: false);
    }
    bool operator< (Contato aux){
        return ((this->getNome())<(aux.getNome())? true: false);
    }
    bool operator== (Contato aux){
        return ((this->getNome())==(aux.getNome())? true: false);
    }
    bool operator!= (Contato aux){
        return ((this->getNome())!=(aux.getNome())? true: false);
    }
    string stringItem(){
        return ("\n"+this->getNome()+"\t"+this->getTelefone());
    }
    friend ostream & operator <<(ostream &saida, const Contato *obj){
        if(obj){
            saida<<"\nNome: "<<obj->getNome()<<"\tTelefone: "<<obj->getTelefone()<<endl;
            return saida;
        }else throw string("\nContato nao existe!\n");
    }
    friend istream & operator >>(istream &entrada, Contato *obj){
        cout<<"\nVertice: ";
        cin>>obj->nome;
        cout<<"\nPeso: ";
        cin>>obj->telefone;
        return entrada;
    }
};

#endif // ITEM_H
