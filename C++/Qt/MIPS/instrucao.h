#ifndef INSTRUCAO_H
#define INSTRUCAO_H
#include<bits/stdc++.h>
using namespace std;

class instrucao
{
public:
    int id,numeroClock;
    set<int> dependencias;
    instrucao(){}
    instrucao(int id)
    {
        this->id=id;
    }
    instrucao(int id,int numeroClock, set<int> dependencias)
    {
        this->id = id;
        this->numeroClock = numeroClock;
        this->dependencias = dependencias;
    }
    bool inline operator >  (const instrucao  &comparar) const {return this->id>comparar.id;}
    bool inline operator <  (const instrucao  &comparar) const {return this->id<comparar.id;}
    bool inline operator >= (const instrucao &comparar) const {return this->id>=comparar.id;}
    bool inline operator <= (instrucao &comparar) {return this->id<=comparar.id;}
    bool inline operator == (const instrucao &comparar) const{return this->id==comparar.id;}
    void inline operator =  (instrucao atribuir)  {
        this->id = atribuir.id;
        this->numeroClock = atribuir.numeroClock;
        this->dependencias = atribuir.dependencias;
    }
};

#endif // INSTRUCAO_H
