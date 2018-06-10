#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

class Celula{
private:
    int vertice;
    float peso;
public:
    Celula(){}
    Celula(int v,float p){
        vertice=v;
        peso=p;
    }
    bool operator== (Celula aux){
        return (this->vertice == aux.vertice);
    }
    bool operator!= (Celula aux){
        return (this->vertice != aux.vertice);
    }
    bool operator> (Celula aux){
        return ((this->vertice)>(aux.vertice));
    }
    bool operator< (Celula aux){
        return ((this->vertice)<(aux.vertice));
    }
    friend ostream & operator <<(ostream &saida, const Celula *obj){
        if(obj){
            saida<<"\nVertice: "<<obj->getVertice()<<"\tPeso: "<<obj->getPeso()<<endl;
            return saida;
        }else throw string("\nCelula nao existe!\n");
    }
    friend istream & operator >>(istream &entrada, Celula *obj){
        cout<<"\nVertice: ";
        cin>>obj->vertice;
        cout<<"\nPeso: ";
        cin>>obj->peso;
        return entrada;
    }
    string empacotaItem(){
        return string("Vertice: "+to_string(vertice)+"\tPeso: "+to_string(peso));
    }
    int getVertice() const {return vertice;}
    void setVertice(int value) {vertice = value;}
    float getPeso() const {return peso;}
    void setPeso(int value) {peso = value;}
};

template <class item1,class item2> class Pair{
private:
    item1 i1;
    item2 i2;
public:
    Pair(){}
    Pair(item1 primeiro,item2 segundo){
        this->i1=primeiro;
        this->i2=segundo;
    }
    item1 getI1() {return i1;}
    void setI1(item1 value) {i1 = value;}
    item2 getI2() {return i2;}
    void setI2(item2 value) {i2 = value;}
    bool operator> (Pair<item1,item2> aux){
        return ((this->getI2())>(aux.getI2()));
    }
    bool operator!= (Pair<item1,item2> aux){
        return ((this->getI2())!=(aux.getI2()));
    }
    friend ostream & operator <<(ostream &saida, Pair *obj){
        if(obj){
        saida<<"\nVertice origem: "<<obj->getI1()<<"\tPeso acumulado: "<<obj->getI2()<<endl;
        return saida;
        }else throw string("\nObjeto nulo!\n");
    }
};

//class Item{
//private:
//    string chave,nome;
//public:
//    string getChave() const{
//        return chave;
//    }
//    void setChave(string value){
//        chave = value;
//    }
//    string getNome() const{
//        return nome;
//    }
//    void setNome(const string &value){
//        nome = value;
//    }
//    bool operator >(Item *aux){
//        if((this->getChave())>(aux->getChave())) return true;
//        return false;
//    }
//    bool operator <(Item *aux){
//        if((this->getChave())<(aux->getChave())) return true;
//        return false;
//    }
//    bool operator ==(Item *aux){
//        if((this->getChave())==(aux->getChave())) return true;
//        return false;
//    }
//    bool operator !=(Item *aux){
//        if((this->getChave())!=(aux->getChave())) return true;
//        return false;
//    }
//    bool operator <=(Item *aux){
//        if((this->getChave())<=(aux->getChave())) return true;
//        return false;
//    }
//    bool operator >=(Item *aux){
//        if((this->getChave())>=(aux->getChave())) return true;
//        return false;
//    }
//    friend ostream & operator <<(ostream &saida, const Item *obj){
//        saida<<"\n"<<obj->chave<<"\t"<<obj->nome<<endl;
//        return saida;
//    }
//    friend istream & operator >>(istream &entrada, Item *obj){
//        entrada.ignore();
//        cout<<"\nChave: ";
//        getline(entrada,obj->chave);
//        cout<<"\nNome: ";
//        getline(entrada,obj->nome);
//        return entrada;
//    }
//    string empacotaItem(){
//        return (getChave()+"\t"+getNome());
//    }
//};
#endif // ITEM_H
