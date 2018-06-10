#include"testalista.h"
#include<cstdlib>

Aluno *TestaLista::inserirAluno()
{
    Aluno *objeto = new Aluno;
    string aux;
    cin.ignore();
    cout<<"\nDigite o nome completo do aluno: ";
    getline(cin,aux);
    objeto->setNome(aux);
    cout<<"\nDigite o CPF do aluno: ";
    getline(cin,aux);
    objeto->setCpf(aux);
    cout<<"\nDigite a matricula do aluno: ";
    getline(cin,aux);
    objeto->setMatricula(aux);
    cout<<"\nDigite o telefone do aluno: ";
    getline(cin,aux);
    objeto->setFone(aux);
    return objeto;
}

void TestaLista::menu(){
    short int aux;
    Aluno *aluno;
    cout<<"\nQual o tamanho da lista: ";
    cin>>aux;
    obj.setTam(aux);
    while(!obj.setTam(aux)){
        cout<<"\nDigite um inteiro valido. Qual o tamanho da lista: ";
        cin>>aux;
        obj.setTam(aux);
    }
    char op2;
    cout<<"\n\n1. Lista desordenada;\n2. Lista ordenada."<<endl;
    cin>>op2;
    while(op2!='1' && op2!='2'){
        cout<<"\nOpção inválida!\n1. Lista desordenada;\n2. Lista ordenada."<<endl;
        cin>>op2;
    }
    char op;
    cout<<"\n\n1. Inserir aluno na lista;\n2. Remover aluno da lista;\n3. Buscar Aluno (pelo nome);\n4. Imprimir toda a lista;\n5. Encerrar programa."<<endl;
    cin>>op;
    while(op!=5){
        switch (op){
            case ('1'):
                if(!obj.listaCheia()){
                    aluno=inserirAluno();
                    if(op2=='1'){
                        if(obj.inserirFinal(aluno)){
                            cout<<"\nAluno inserido na lista com sucesso.";
                        }else{
                            cout<<"\nInsucesso!";
                        }
                    }else{
                        if(obj.inserirOrdenado(aluno)){
                            cout<<"\nAluno inserido na lista com sucesso.";
                        }else{
                            cout<<"\nInsucesso!";
                        }
                    }
                }else{
                    cout<<"\nLista cheia!";
                }
                break;
            case ('2'):
                if(!obj.listaVazia()){
                    string aux;
                    cin.ignore();
                    cout<<"Digite o nome do aluno que deseja remover: ";
                    getline(cin,aux);
                    if(obj.buscar(aux)){
                        obj.imprimirAluno(obj.buscar(aux));
                        if(obj.remover(obj.buscar(aux))){
                            cout<<"\nAluno removido da lista com sucesso.";
                        }else{
                            cout<<"\nInsucesso!";
                        }
                    }else{
                        cout<<"\nNão foi encontrado nenhum aluno com este nome.";
                    }
                }else{
                    cout<<"\nLista vazia!";
                }
                break;
            case ('3'):
                if(!obj.listaVazia()){
                    string aux;
                    cin.ignore();
                    cout<<"\nDigite o nome completo do aluno para a busca: ";
                    getline(cin,aux);
                    if(obj.buscar(aux)){
                        obj.imprimirAluno(obj.buscar(aux));
                    }else{
                        cout<<"\nNão foi encontrado nenhum aluno com este nome.";
                    }
                }else{
                    cout<<"\nLista vazia!";
                }
                break;
            case ('4'):
                cout<<obj.imprimirTudo();
                break;
            case ('5'):
                system("pause");
            default:
                cout<<"Opção Inválida!";
                break;
        }
        cout<<"\n\n1. Inserir aluno na lista;\n2. Remover aluno da lista;\n3. Buscar Aluno (pelo nome);\n4. Imprimir toda a lista;\n5. Encerrar programa."<<endl;
        cin>>op;
    }
}
