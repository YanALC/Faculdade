#include "testalista.h"

Contato *TestaLista::inserirContato()
{
    Contato *objeto = new Contato;
    string aux;
    cin.ignore();
    cout<<"\nNome do contato: ";
    getline(cin,aux);
    objeto->setNome(aux);
    cout<<"\nTelefone do contato: ";
    getline(cin,aux);
    objeto->setTelefone(aux);
    return objeto;
}

void TestaLista::imprimirContato(Contato *aux)
{
    cout<<"\nNome do contato: "<<aux->getNome();
    cout<<"\nTelefone do contato: "<<aux->getTelefone();
}

void TestaLista::menuDesordenado()
{
    Contato *contato = new Contato;
    char op;
    cout<<"\n\n1. Inserir contato no inicio da lista;\n"
          "2. Inserir contato no final da lista;\n"
          "3. Remover contato da lista;\n"
          "4. Buscar Contato (pelo nome);\n"
          "5. Imprimir toda a lista;\n"
          "6. Voltar."<<endl;
    cin>>op;
    while(op!='6'){
        switch (op){
        case ('1'):
            contato=inserirContato();
            if(obj.inserirInicio(contato))
                cout<<"\nContato inserido na lista com sucesso.";
            else
                cout<<"\nObjeto Vazio!";
            break;
        case ('2'):
            contato=inserirContato();
            if(obj.inserirFinal(contato))
                cout<<"\nContato inserido na lista com sucesso.";
            else
                cout<<"\nObjeto Vazio!";
            break;
        case ('3'):
            if(!obj.listaVazia()){
                Contato *contatoAux = new Contato;
                string aux;
                cin.ignore();
                cout<<"Digite o nome do contato que deseja remover: ";
                getline(cin,aux);
                contatoAux->setNome(aux);
                if(obj.buscar(contatoAux)){
                    imprimirContato(obj.remover(contatoAux));
                    cout<<"\nContato removido da lista com sucesso.";
                }else
                    cout<<"\nNão foi encontrado nenhum contato com este nome.";
                contatoAux = NULL;
                delete contatoAux;
            }else cout<<"\nLista vazia!";
            break;
        case ('4'):
            if(!obj.listaVazia()){
                Contato *contatoAux = new Contato;
                string aux;
                cin.ignore();
                cout<<"\nDigite o nome completo do contato para a busca: ";
                getline(cin,aux);
                contatoAux->setNome(aux);
                if(obj.buscar(contatoAux))
                    imprimirContato(obj.buscar(contatoAux));
                else
                    cout<<"\nNão foi encontrado nenhum contato com este nome.";
                contatoAux = NULL;
                delete contatoAux;
            }else cout<<"\nLista vazia!";
            break;
        case ('5'):
            cout<<obj.listar();
            break;
        default:
            cout<<"Opção Inválida!";
            break;
        }
        cout<<"\n\n1. Inserir contato no inicio da lista;\n"
              "2. Inserir contato no final da lista;\n"
              "3. Remover contato da lista;\n"
              "4. Buscar contato (pelo nome);\n"
              "5. Imprimir toda a lista;\n"
              "6. Voltar."<<endl;
        cin>>op;
        if(op=='6') obj.~ListaEncadeada();
    }
}

void TestaLista::menuOrdenado(){
    Contato *contato = new Contato;
    char op;
    cout<<"\n\n1. Inserir contato na lista;\n"
          "2. Remover contato especifico da lista;\n"
          "3. Buscar Contato (pelo nome);\n"
          "4. Imprimir toda a lista;\n"
          "5. Voltar."<<endl;
    cin>>op;
    while(op!='5'){
        switch (op){
        case ('1'):
            contato=inserirContato();
            if(obj.inserirCrescente(contato))
                cout<<"\nContato inserido na lista com sucesso.";
            else
                cout<<"\nObjeto Vazio!";
            break;
        case ('2'):
            if(!obj.listaVazia()){
                Contato *contatoAux = new Contato;
                string aux;
                cin.ignore();
                cout<<"Digite o nome do contato que deseja remover: ";
                getline(cin,aux);
                contatoAux->setNome(aux);
                if(obj.buscar(contatoAux)){
                    imprimirContato(obj.remover(contatoAux));
                    cout<<"\nContato removido da lista com sucesso.";
                }else
                    cout<<"\nNão foi encontrado nenhum contato com este nome.";
                contatoAux = NULL;
                delete contatoAux;
            }else cout<<"\nLista vazia!";
            break;
        case ('3'):
            if(!obj.listaVazia()){
                Contato *contatoAux = new Contato;
                string aux;
                cin.ignore();
                cout<<"\nDigite o nome completo do contato para a busca: ";
                getline(cin,aux);
                contatoAux->setNome(aux);
                if(obj.buscar(contatoAux))
                    imprimirContato(obj.buscar(contatoAux));
                else
                    cout<<"\nNão foi encontrado nenhum contato com este nome.";
                contatoAux = NULL;
                delete contatoAux;
            }else cout<<"\nLista vazia!";
            break;
        case ('4'):
            cout<<obj.listar();
            break;
        default:
            cout<<"Opção Inválida!";
            break;
        }
        cout<<"\n\n1. Inserir contato na lista;\n"
              "2. Remover contato especifico da lista;\n"
              "3. Buscar Contato (pelo nome);\n"
              "4. Imprimir toda a lista;\n"
              "5. Voltar."<<endl;
        cin>>op;
        if(op=='5') obj.~ListaEncadeada();
    }
}
