#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include <bits/stdc++.h>
#include <QString>
using namespace std;
class Thread
{
public:
    int identificacao,tempoTotal,tempoAtual=0;
    set<int> paradas;
    Thread(){}
    bool inline operator == (const Thread &comparar) const{return this->identificacao==comparar.identificacao;}
    void inline operator =  (Thread atribuir)
    {
        this->identificacao = atribuir.identificacao;
        this->tempoTotal = atribuir.tempoTotal;
        this->tempoAtual = 0;
        this->paradas = atribuir.paradas;
    }
};
#endif // THREAD_H
