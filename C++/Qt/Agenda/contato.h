#ifndef CONTATO_H
#define CONTATO_H
#include "lista.h"
class Contato
{
private:
    string nome;
    Lista<Email> *emails;
    Lista<Endereco> *enderecos;
    Lista<Telefone> *telefones;
public:
    Contato();
    bool operator> (Contato *aux){
        if((this->getNome())>(aux->getNome())) return true;
        return false;
    }
    bool operator!= (Contato *aux){
        if((this->getNome())!=(aux->getNome())) return true;
        return false;
    }
    void operator= (Contato *aux){
        this->setNome(aux->getNome());
        this->setTelefones(aux->getTelefones());
        this->setEmails(aux->getEmails());
        this->setEnderecos(aux->getEnderecos());
    }
    QString empacotaItem(int op);
    string getNome() const;
    void setNome(const string &value);
    Lista<Email> *getEmails() const;
    void setEmail(Email *value);
    Lista<Telefone> *getTelefones() const;
    void setTelefone(Telefone *value);
    Lista<Endereco> *getEnderecos() const;
    void setEndereco(Endereco *value);
    void setEmails(Lista<Email> *value);
    void setEnderecos(Lista<Endereco> *value);
    void setTelefones(Lista<Telefone> *value);
};
#endif // CONTATO_H
