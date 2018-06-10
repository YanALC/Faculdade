#include"aluno.h"
void Aluno::setNome(string aux){
    nome=aux;
}
void Aluno::setMatricula(string aux){
    matricula=aux;
}
void Aluno::setCpf(string aux){
    cpf=aux;
}
string Aluno::getNome()const{
    return nome;
}
string Aluno::getMatricula()const{
    return matricula;
}
string Aluno::getCpf()const{
    return cpf;
}
