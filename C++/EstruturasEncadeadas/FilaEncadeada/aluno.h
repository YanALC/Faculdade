#ifndef ALUNO_H
#define ALUNO_H
#include <string>
#include <iostream>
using namespace std;
class Aluno{
private:
    string nome,matricula;
    Aluno * proximo;
public:
    void setNome(string);
    void setMatricula(string);
    void setProximo(Aluno*);
    string getNome();
    string getMatricula();
    Aluno *getProximo()const;
};
#endif // ALUNO_H
