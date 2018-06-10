#include<cstdlib>
#include"testapilha.h"

Contato *TestaPilha::criaContato(){
    Contato *objeto = new Contato;
    string aux;
    cin.ignore();
    cout<<"\nDigite o nome do contato: ";
    getline(cin, aux);
    objeto->setNome(aux);
    cout<<"Digite o telefone do contato: ";
    getline(cin, aux);
    objeto->setTelefone(aux);
    return objeto;
}

void TestaPilha::mostrarContato(Contato*objeto){
    cout<<"\nNome: "<<objeto->getNome();
    cout<<"\nTelefone: "<<objeto->getTelefone();
}

void TestaPilha::menu(){
    Contato *contato;
    char op;
    cout<<"\n\n1. Inserir contato na pilha;\n2. Desempilhar e remover último contato adicionado na pilha;\n3. Encerrar programa."<<endl;
    cin>>op;
    while(op!='3'){
        switch (op){
            case('1'):
                contato=criaContato();
                if(obj.push(contato)){
                    cout<<"\nElemento inserido na pilha com sucesso.";
                }else{
                    cout<<"\nElemento vazio!";
                }
                break;
            case('2'):
                if(!obj.pilhaVazia()){
                    mostrarContato(obj.pop());
                    cout<<"\nElemento removido da pilha com sucesso.";
                }else{
                    cout<<"\nPilha vazia!";
                }
                break;
             case('3'):
                system("pause");
             default:
                break;
        }
        cout<<"\n\n1. Inserir contato na pilha;\n2. Desempilhar e remover último contato adicionado na pilha;\n3. Encerrar programa."<<endl;
        cin>>op;
    }
}
