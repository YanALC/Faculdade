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
    bool operator >(Contato aux){
        if((this->getNome())>(aux.getNome())) return true;
        return false;
    }
    bool operator <(Contato aux){
        if((this->getNome())<(aux.getNome())) return true;
        return false;
    }
    bool operator ==(Contato aux){
        if((this->getNome())==(aux.getNome())) return true;
        return false;
    }
    bool operator !=(Contato aux){
        if((this->getNome())!=(aux.getNome())) return true;
        return false;
    }
    string stringItem(){
        return(this->nome+"\t"+this->telefone+"\n");
    }
};

#endif // ITEM_H
