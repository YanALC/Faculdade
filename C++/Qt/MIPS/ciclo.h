#ifndef CICLO_H
#define CICLO_H
#include<instrucao.h>
#include<QString>
class ciclo // classse que armazenara a quantidade de ciclo
{
public:
    vector<int> IF,ID,EX,WB;
    ciclo(uint ifn, uint id, uint ex, uint wb);
};

#endif // CICLO_H
