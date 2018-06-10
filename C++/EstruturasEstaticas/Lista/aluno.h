#ifndef ALUNO_H
#define ALUNO_H
#include<string>
#include<iostream>
using namespace std;
class Aluno{
    private:
        string nome,matricula,cpf,fone;
    public:
        //Aluno();
        //~Aluno();

        void setNome(string);
        void setMatricula(string);
        void setCpf(string);
        void setFone(string);
        string getNome()const;
        string getMatricula()const;
        string getCpf()const;
        string getFone()const;
};
#endif // ALUNO_H
