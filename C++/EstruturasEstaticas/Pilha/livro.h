#ifndef LIVRO_H
#define LIVRO_H
#include<string>
#include<iostream>
using namespace std;
class Livro{
    private:
        string titulo,autor,editora,local;
        short int ano,paginas,vol;
    public:
        //Livro();
        //~Livro();

        void setTitulo(string);
        void setAutor(string);
        void setEditora(string);
        void setLocal(string);
        bool setAno(short int);
        bool setPaginas(short int);
        bool setVol(short int);
        string getTitulo()const;
        string getAutor()const;
        string getEditora()const;
        string getLocal()const;
        short int getAno()const;
        short int getPaginas()const;
        short int getVol()const;
};
#endif // LIVRO_H
