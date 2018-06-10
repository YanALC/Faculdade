#include "contato.h"

Contato::Contato()
{}

void Contato::setNome(string aux)
{
    nome=aux;
}

void Contato::setTelefone(string aux)
{
    telefone=aux;
}

string Contato::getNome()
{
    return nome;
}

string Contato::getTelefone()
{
    return telefone;
}

void Contato::setProximo(Contato * aux)
{
    proximo=aux;
}

Contato *Contato::getProximo() const
{
    return proximo;
}
