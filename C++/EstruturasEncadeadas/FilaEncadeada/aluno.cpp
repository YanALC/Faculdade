#include "aluno.h"

void Aluno::setNome(string aux)
{
    nome=aux;
}

void Aluno::setMatricula(string aux)
{
    matricula=aux;
}

void Aluno::setProximo(Aluno *aux)
{
    proximo=aux;
}

string Aluno::getNome()
{
    return nome;
}

string Aluno::getMatricula()
{
    return matricula;
}

Aluno *Aluno::getProximo() const
{
    return proximo;
}
