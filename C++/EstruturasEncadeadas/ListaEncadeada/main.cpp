#include "testalista.h"

int main()
{
    TestaLista obj;
    char op2;
    cout<<"\n\n1. Lista desordenada;\n2. Lista ordenada;\n0. Sair."<<endl;
    cin>>op2;
    while(op2!='0'){
        while(op2!='1' && op2!='2'){
            cout<<"\nOpção inválida!\n1. Lista desordenada;\n2. Lista ordenada."<<endl;
            cin>>op2;
        }
        if(op2=='1'){
            obj.menuDesordenado();
        }else if(op2=='2'){
            obj.menuOrdenado();
        }
        cout<<"\n\n1. Lista desordenada;\n2. Lista ordenada;\n0. Sair."<<endl;
        cin>>op2;
    }if(op2=='0') exit(1);
}
