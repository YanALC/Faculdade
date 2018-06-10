#include"testafila.h"

Aluno *TestaFila::cadastraAluno()
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
    return objeto;
}

void TestaFila::mostrarAluno(Aluno *objeto)
{
    cout<<"\nNome completo do aluno: "<<objeto->getNome();
    cout<<"\nCPF do aluno: "<<objeto->getCpf();
    cout<<"\nMatricula do aluno: "<<objeto->getMatricula();
}

void TestaFila::menu(){
    short int aux;
    Aluno *aluno;
    cout<<"\nQual o tamanho da fila: ";
    cin>>aux;
    obj.setTam(aux);
    while(!obj.setTam(aux)){
        cout<<"\nDigite um inteiro valido. Qual o tamanho da pilha: ";
        cin>>aux;
        obj.setTam(aux);
    }
    char op;
    cout<<"\n\n1. Enfileirar aluno;\n2. Desenfileirar e remover primeiro aluno da fila;\n3. Encerrar programa."<<endl;
    cin>>op;
    while(op!='3'){
        switch (op){
            case('1'):
                aluno=cadastraAluno();
                if(obj.enfileirar(aluno)){
                    cout<<"\nAluno enfileirado com sucesso.";
                }else{
                    cout<<"\nFila cheia!";
                }
                break;
            case('2'):
                if(!obj.filaVazia()){
                    mostrarAluno(obj.desenfileirar());
                    cout<<"\nAluno removido da fila com sucesso com sucesso.";
                }else{
                    cout<<"\nFila vazia!";
                }
                break;
             case('3'):
                system("pause");
             default:
                cout<<"Opção Inválida!";
                break;

        }
        cout<<"\n\n1. Enfileirar aluno;\n2. Desenfileirar e remover primeiro aluno da fila;\n3. Encerrar programa."<<endl;
        cin>>op;
    }
}
