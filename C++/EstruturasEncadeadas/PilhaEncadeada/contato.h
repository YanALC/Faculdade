#ifndef CONTATO_H
#define CONTATO_H
#include <string>
#include <iostream>
using namespace std;
class Contato{
private:
    string nome, telefone;
    Contato * proximo;
public:
    void setNome(string);
    void setTelefone(string);
    string getNome();
    string getTelefone();
    void setProximo(Contato*);
    Contato * getProximo()const;
    Contato();
};

#endif // CONTATO_H
