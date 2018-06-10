#ifndef ALUNO_H
#define ALUNO_H
#include<string>
#include<iostream>
using namespace std;
class Aluno{
    private:
        string nome,matricula,cpf;
    public:
        //Aluno();
        //~Aluno();

        void setNome(string);
        void setMatricula(string);
        void setCpf(string);
        string getNome()const;
        string getMatricula()const;
        string getCpf()const;
};

#endif // ALUNO_H
