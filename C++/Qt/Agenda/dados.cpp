#include "dados.h"

Email::Email():emailID(""),emailDominio(""){}

Endereco::Endereco():logradouro(""),numero(0),cep(0),tipo(0){}

Telefone::Telefone():DDD(0),telefone(0),tipo(1){}

///FUNÇÕES DA CLASS TELEFONE

int Telefone::getDDD() const
{
    return DDD;
}

void Telefone::setDDD(int value)
{
    DDD = value;
}

long Telefone::getTelefone() const
{
    return telefone;
}

void Telefone::setTelefone(long value)
{
    telefone = value;
}

int Telefone::getTipo() const
{
    return tipo;
}

void Telefone::setTipo(int value)
{
    tipo = value;
}

QString Telefone::empacotaItem(int)
{
    QString aux;
    aux="("+QString::number(this->getDDD())+")"+QString::number(this->getTelefone())+"\t\tTipo: ";
    if(this->getTipo()==1) aux+="Celular";
    else{
        if(this->getTipo()==2) aux+="Residencial";
        else if(this->getTipo()==3) aux+="Profissional";
    }
    return aux;
}

///FUNÇÕES DA CLASS EMAIL

string Email::getEmailDominio() const
{
    return emailDominio;
}

void Email::setEmailDominio(const string &value)
{
    emailDominio = value;
}

QString Email::empacotaItem(int)
{
    QString aux;
    aux=QString::fromStdString(this->getEmailID())+"@"+QString::fromStdString(this->getEmailDominio());
    return aux;
}

string Email::getEmailID() const
{
    return emailID;
}

void Email::setEmailID(const string &value)
{
    emailID = value;
}

///FUNÇÕES DA CLASS ENDERECO

string Endereco::getLogradouro() const
{
    return logradouro;
}

void Endereco::setLogradouro(const string &value)
{
    logradouro = value;
}

int Endereco::getNumero() const
{
    return numero;
}

void Endereco::setNumero(int value)
{
    numero = value;
}

long Endereco::getCep() const
{
    return cep;
}

void Endereco::setCep(long value)
{
    cep = value;
}

int Endereco::getTipo() const
{
    return tipo;
}

void Endereco::setTipo(int value)
{
    tipo = value;
}

QString Endereco::empacotaItem(int)
{
    QString aux;
    aux="Rua: "+QString::fromStdString(this->getLogradouro())+"\tN°: "+QString::number(this->getNumero())+"\tCEP: "+QString::number(this->getCep())+"\tTipo: ";
    if(this->getTipo()==1) aux+="Residencial";
    else{
        if(this->getTipo()==2) aux+="Profissional";
        else aux+="Outro";
    }
    return aux;
}
