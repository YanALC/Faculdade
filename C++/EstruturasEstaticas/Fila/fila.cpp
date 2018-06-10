#include"fila.h"
Fila::Fila(){
    tam=0;
    final=0;
    vet=NULL;
}
void Fila::free(){
    Aluno *aux2 = NULL;
    while(!filaVazia()){
        aux2=desenfileirar();
        delete aux2;
    }
    aux2=NULL;
    delete[]vet;
    vet=NULL;
}
Fila::~Fila(){
    free();
}

bool Fila::setTam(short int aux){
    if(aux>=2){
        tam=aux;
        if(vet){
            free();
        }
        vet=new Aluno*[tam];
        return true;
    }
    return false;
}

short int Fila::getTam()const{
    return tam;
}
bool Fila::enfileirar(Aluno*aux){
    if(filaCheia()) return false;
    vet[final]=aux;
    final++;
    return true;
}

Aluno *Fila::desenfileirar(){
    if(filaVazia()) return NULL;
    Aluno*aux=vet[0];
    for(int i=0;i<final;i++){
        vet[i]=vet[i+1];
    }
    vet[final-1]=NULL;
    final--;
    return aux;
}
bool Fila::filaVazia()const{
    return (final==0);
}
bool Fila::filaCheia()const{
    return (final==tam);
}
