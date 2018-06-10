#include<string>
#include<iostream>
#include"pilha.h"
using namespace std;

Pilha::Pilha(){
    topo=0;
    tam=2;
    vet=0;
}
bool Pilha::setTam(short int aux){
    if(aux){
        tam=aux;
        vet=new Livro*[tam];
        for(int i=0;i<tam;i++){
            vet[i]=0;
        }
        return true;
    }
    return false;
}
short int Pilha::getTam()const{
    return tam;
}
bool Pilha::pilhaVazia()const{
    if(topo==0)return true;
    return false;
}
bool Pilha::pilhaCheia()const{
    if(topo==tam)return true;
    return false;
}
bool Pilha::push(Livro *aux){
    if(aux==0)return false;
    if(pilhaCheia())return false;
    vet[topo]=aux;
    topo++;
    return true;
}
Livro *Pilha::pop(){
    if(pilhaVazia())return 0;
    Livro *aux=vet[topo-1];
    vet[topo-1]=0;
    topo--;
    return aux;
}
Pilha::~Pilha(){
    delete[]vet;
    vet=0;
}
