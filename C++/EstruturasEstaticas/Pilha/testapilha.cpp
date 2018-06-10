#include<iostream>
#include<cstdlib>
#include"testapilha.h"
using namespace std;

Livro *TestaPilha::criaLivro(){
    Livro *objeto = new Livro;
    string aux;
    short int valor;
    cin.ignore();
    cout<<"\nDigite o titulo do livro: ";
    getline(cin, aux);
    objeto->setTitulo(aux);
    cout<<"Digite o autor do livro: ";
    getline(cin, aux);
    objeto->setAutor(aux);
    cout<<"Digite a editora do livro: ";
    getline(cin, aux);
    objeto->setEditora(aux);
    cout<<"Digite o local de criacao do livro: ";
    getline(cin, aux);
    objeto->setLocal(aux);
    cout<<"Digite o ano de lancamento do livro: ";
    cin>>valor;
    objeto->setAno(valor);
    while(!objeto->setAno(valor)){
        cout<<"Ano invalido, digite um ano entre 1500 e 2018: ";
        cin>>valor;
        objeto->setAno(valor);
    }
    cout<<"Digite o numero de paginas do livro: ";
    cin>>valor;
    objeto->setPaginas(valor);
    cout<<"Digite o volume do livro: ";
    cin>>valor;
    objeto->setVol(valor);
    return objeto;
}

void TestaPilha::mostrarLivro(Livro*objeto){
    cout<<"\nTitulo do livro: "<<objeto->getTitulo();
    cout<<"\nAutor do livro: "<<objeto->getAutor();
    cout<<"\nEditora do livro: "<<objeto->getEditora();
    cout<<"\nLocal da criacao do livro: "<<objeto->getLocal();
    cout<<"\nAno de lancamento do livro: "<<objeto->getAno();
    cout<<"\nNumero de paginas do livro: "<<objeto->getPaginas();
    cout<<"\nVolume do livro: "<<objeto->getVol();
}

void TestaPilha::menu(){
    short int aux2;
    Livro *liv;
    cout<<"\nQual o tamanho da pilha: ";
    cin>>aux2;
    obj.setTam(aux2);
    while(!obj.setTam(aux2)){
        cout<<"\nDigite um inteiro valido. Qual o tamanho da pilha: ";
        cin>>aux2;
        obj.setTam(aux2);
    }
    char op;
    cout<<"\n\n1. Inserir livro na pilha;\n2. Desempilhar e remover último livro adicionado na pilha;\n3. Encerrar programa."<<endl;
    cin>>op;
    while(op!='3'){
        switch (op){
            case('1'):
                liv=criaLivro();
                if(obj.push(liv)){
                    cout<<"\nElemento inserido na pilha com sucesso.";
                }else{
                    cout<<"\nPilha cheia!";
                }
                break;
            case('2'):
                if(!obj.pilhaVazia()){
                    mostrarLivro(obj.pop());
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
        cout<<"\n\n1. Inserir livro na pilha;\n2. Desempilhar e remover último livro adicionado na pilha;\n3. Encerrar programa."<<endl;
        cin>>op;
    }
}
