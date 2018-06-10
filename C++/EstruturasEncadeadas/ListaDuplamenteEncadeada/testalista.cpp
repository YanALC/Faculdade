#include "testalista.h"

Contato *TestaLista::criarItem()
{
    try{
        Contato *objeto = new Contato;
        string aux;
        do{
            cin.ignore();
            cout<<"\nNome do contato: ";
            getline(cin,aux);
        }while(aux=="");
        objeto->setNome(aux);
        do{
            cout<<"\nTelefone do contato: ";
            getline(cin,aux);
        }while(aux=="");
        objeto->setTelefone(aux);
        return objeto;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
}

void TestaLista::mostrarItem(Contato *objeto)
{
    if(objeto)
        cout<<"\nNome do contato: "<<objeto->getNome()+"\nTelefone do contato: "<<objeto->getTelefone() << endl;
    else cout<<"\nObjeto nulo!";
}

void TestaLista::menuDesordenado()
{
    char op;
    cout<<"\n\n1. Inserir contato no final da lista;\n"
          "2. Remover contato da lista;\n"
          "3. Buscar contato (pelo nome);\n"
          "4. Acessar por posicao;\n"
          "5. Imprimir toda a lista;\n"
          "6. Voltar."<<endl;
    cin>>op;
    while(op!='6'){
        switch (op){
        case ('1'):
        {
            try{
                obj->inserirFinal(criarItem());
                cout<<"\nItem inserido na lista com sucesso.";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('2'):
        {
            try{
                if(!obj->listaVazia()){
                    Contato *contatoAux = new Contato;
                    string aux;
                    cin.ignore();
                    cout<<"Digite o nome do contato que deseja remover: ";
                    getline(cin,aux);
                    contatoAux->setNome(aux);
                    mostrarItem(obj->remover(contatoAux));
                    cout<<"\nItem removido da lista com sucesso.";
                    contatoAux=NULL;
                    delete contatoAux;
                }else cout<<"\nLista vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('3'):
        {
            try{
                if(!obj->listaVazia()){
                    Contato *contatoAux = new Contato;
                    string aux;
                    cin.ignore();
                    cout<<"\nDigite o nome completo do contato para a busca: ";
                    getline(cin,aux);
                    contatoAux->setNome(aux);
                    mostrarItem(obj->buscar(contatoAux));
                    contatoAux=NULL;
                    delete contatoAux;
                }else cout<<"\nLista vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('4'):
        {
            try {
                int pos;
                cout<<"\nPosicao a ser acessada: ";
                cin>>pos;
                mostrarItem((*obj)[pos]);
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('5'):
        {
            try{
                cout<<obj->listar();
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        default:
            cout<<"Opcao Invalida!";
            break;
        }
        cout<<"\n\n1. Inserir contato no final da lista;\n"
              "2. Remover contato da lista;\n"
              "3. Buscar contato (pelo nome);\n"
              "4. Acessar por posicao;\n"
              "5. Imprimir toda a lista;\n"
              "6. Voltar."<<endl;
        cin>>op;
        if(op=='6') obj->~ListaDuplamenteEncadeada();
    }
}

void TestaLista::menuOrdenado(){
    char op;
    cout<<"\n\n1. Inserir contato na lista;\n"
          "2. Remover contato especifico da lista;\n"
          "3. Buscar contato (pelo nome);\n"
          "4. Acessar por posicao;\n"
          "5. Imprimir toda a lista;\n"
          "6. Voltar."<<endl;
    cin>>op;
    while(op!='6'){
        switch (op){
        case ('1'):
        {
            try{
                obj->inserirOrdenado(criarItem());
                cout<<"\nItem inserido na lista com sucesso.";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('2'):
        {
            try{
                if(!obj->listaVazia()){
                    Contato *contatoAux = new Contato;
                    string aux;
                    cin.ignore();
                    cout<<"Digite o nome do contato que deseja remover: ";
                    getline(cin,aux);
                    contatoAux->setNome(aux);
                    mostrarItem(obj->remover(contatoAux));
                    cout<<"\nItem removido da lista com sucesso.";
                    contatoAux=NULL;
                    delete contatoAux;
                }else cout<<"\nLista vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('3'):
        {
            try{
                if(!obj->listaVazia()){
                    Contato *contatoAux = new Contato;
                    string aux;
                    cin.ignore();
                    cout<<"\nDigite o nome completo do contato para a busca: ";
                    getline(cin,aux);
                    contatoAux->setNome(aux);
                    mostrarItem(obj->buscar(contatoAux));
                    contatoAux=NULL;
                    delete contatoAux;
                }else cout<<"\nLista vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('4'):
        {
            try {
                int pos;
                cout<<"\nPosicao a ser acessada: ";
                cin>>pos;
                mostrarItem((*obj)[pos]);
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('5'):
        {
            try{
                cout<<obj->listar();
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        default:
            cout<<"Opcao Invalida!";
            break;
        }
        cout<<"\n\n1. Inserir contato na lista;\n"
              "2. Remover contato especifico da lista;\n"
              "3. Buscar contato (pelo nome);\n"
              "4. Acessar por posicao;\n"
              "5. Imprimir toda a lista;\n"
              "6. Voltar."<<endl;
        cin>>op;
        if(op=='6') obj->~ListaDuplamenteEncadeada();
    }
}
