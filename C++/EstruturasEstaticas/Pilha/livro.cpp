#include"livro.h"
#include<iostream>
using namespace std;
void Livro::setTitulo(string aux){
    titulo=aux;
}
void Livro::setAutor(string aux){
    autor=aux;
}
void Livro::setEditora(string aux){
    editora=aux;
}
void Livro::setLocal(string aux){
    local=aux;
}
bool Livro::setAno(short int aux){
    if(aux>1500 && aux<2018){
        ano=aux;
        return true;
    }return false;
}
bool Livro::setPaginas(short int aux){
    if(aux>0){
        paginas=aux;
        return true;
    }return false;
}
bool Livro::setVol(short int aux){
    if(aux>0){
        vol=aux;
        return true;
    }return false;
}
string Livro::getTitulo()const{
    return titulo;
}
string Livro::getAutor()const{
   return autor;
}
string Livro::getEditora()const{
   return editora;
}
string Livro::getLocal()const{
   return local;
}
short int Livro::getAno()const{
    return ano;
}
short int Livro::getPaginas()const{
    return paginas;
}
short int Livro::getVol()const{
    return vol;
}
