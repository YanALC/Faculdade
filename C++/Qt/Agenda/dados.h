#ifndef DADOS_H
#define DADOS_H
#include <iostream>
#include <QString>
using namespace std;

class Telefone{
private:
    int DDD;
    long telefone;
    int tipo; //1=Celular ; 2=Residencial ; 3=Profissional
public:
    Telefone();
    int getDDD() const;
    void setDDD(int value);
    long getTelefone() const;
    void setTelefone(long value);
    int getTipo() const;
    void setTipo(int value);
    QString empacotaItem(int);
    bool operator> (Telefone *aux){
        if((this->getTipo())>(aux->getTipo())) return true;
        return false;
    }
    bool operator!= (Telefone *aux){
        if((this->getDDD()+this->getTelefone())!=(aux->getDDD()+aux->getTelefone())) return true;
        return false;
    }
};

class Email{
private:
    string emailID;
    string emailDominio;
public:
    Email();
    string getEmailID() const;
    void setEmailID(const string &value);
    string getEmailDominio() const;
    void setEmailDominio(const string &value);
    QString empacotaItem(int);
    bool operator> (Email *aux){
        if((this->getEmailID()+this->getEmailDominio())>(aux->getEmailID()+aux->getEmailDominio())) return true;
        return false;
    }
    bool operator!= (Email *aux){
        if((this->getEmailID()+this->getEmailDominio())!=(aux->getEmailID()+aux->getEmailDominio())) return true;
        return false;
    }
};

class Endereco{
private:
    string logradouro;
    int numero;
    long cep;
    int tipo; //1=Residencial ; 2=Profissional ; 0=Outros
public:
    Endereco();
    string getLogradouro() const;
    void setLogradouro(const string &value);
    int getNumero() const;
    void setNumero(int value);
    long getCep() const;
    void setCep(long value);
    int getTipo() const;
    void setTipo(int value);
    QString empacotaItem(int);
    bool operator> (Endereco *aux){
        if((this->getTipo())>(aux->getTipo())) return true;
        return false;
    }
    bool operator!= (Endereco *aux){
        if((this->getLogradouro()+std::to_string(this->getNumero())+std::to_string(this->getCep()))!=(aux->getLogradouro()+to_string(aux->getNumero())+to_string(aux->getCep()))) return true;
        return false;
    }
};

#endif // DADOS_H
