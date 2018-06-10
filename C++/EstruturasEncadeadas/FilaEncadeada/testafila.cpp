#include"testafila.h"

Aluno *TestaFila::cadastraAluno()
{
    Aluno *objeto = new Aluno;
    string aux;
    cin.ignore();
    cout<<"\nDigite o nome completo do aluno: ";
    getline(cin,aux);
    objeto->setNome(aux);
    cout<<"\nDigite a matricula do aluno: ";
    getline(cin,aux);
    objeto->setMatricula(aux);
    return objeto;
}

void TestaFila::mostrarAluno(Aluno *objeto)
{
    cout<<"\nNome completo do aluno: "<<objeto->getNome();
    cout<<"\nMatricula do aluno: "<<objeto->getMatricula();
}

void TestaFila::menu(){
    Aluno *aluno;
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
                    cout<<"\nObjeto nulo!";
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
