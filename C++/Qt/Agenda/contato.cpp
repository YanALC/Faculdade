#include "contato.h"

Contato::Contato(): nome(""){
    emails = new Lista<Email>();
    enderecos = new Lista<Endereco>();
    telefones = new Lista<Telefone>();
}

void Contato::setEmails(Lista<Email> *value)
{
    emails = value;
}

void Contato::setEnderecos(Lista<Endereco> *value)
{
    enderecos = value;
}

void Contato::setTelefones(Lista<Telefone> *value)
{
    telefones = value;
}

QString Contato::empacotaItem(int op)
{
    if(op==1)
        return QString::fromStdString(this->getNome());
    else{
        QString aux;
        aux="Nome: "+QString::fromStdString(this->getNome())+
                "\nTelefones\n"+this->getTelefones()->listar()+
                "\nEmails\n"+this->getEmails()->listar()+
                "\nEndereços\n"+this->getEnderecos()->listar()+"\n";
        return aux;
    }
}

string Contato::getNome() const
{
    return nome;
}

void Contato::setNome(const string &value)
{
    nome = value;
}

Lista<Telefone> *Contato::getTelefones() const
{
    return telefones;
}

void Contato::setTelefone(Telefone *value)
{
    telefones->inserirFinal(value);
}

Lista<Endereco> *Contato::getEnderecos() const
{
    return enderecos;
}

void Contato::setEndereco(Endereco *value)
{
    enderecos->inserirFinal(value);
}

Lista<Email> *Contato::getEmails() const
{
    return emails;
}

void Contato::setEmail(Email *value)
{
    emails->inserirFinal(value);
}
