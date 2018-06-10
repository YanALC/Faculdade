#include "testaarvore.h"
#include <cstdlib>

Item *TestaArvore::criarItem()
{
    try{
        Item *objeto = new Item;
        int key;
        string aux,aux2;
        cin.ignore();
        cout<<"\nChave de Registro: ";
        cin>>aux;
        key=atoi(aux.c_str());
        while((key==0&&aux!="0")||!(objeto->setKey(key))){
            cout<<"\nChave invalida! Digite novamente: ";
            cin>>aux;
            key=atoi(aux.c_str());
        }
        objeto->setKey(key);
        cin.ignore();
        cout<<"\nNome: ";
        getline(cin,aux2);
        while(aux==""){
            cout<<"\nNome Invalido! Digite novamente: ";
            getline(cin,aux2);
        }
        objeto->setNome(aux2);
        return objeto;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
}

void TestaArvore::mostrarItem(Item *objeto)
{
    cout<<"\nChave de Registro: "<<objeto->getKey();
    cout<<"\nNome: "<<objeto->getNome();
}

void TestaArvore::menu()
{
    Item *pItem;
    char op;
    cout<<"\tARVORE RED BLACK"
          "\n1. Inserir item na arvore;\n"
          "2. Remover item da arvore;\n"
          "3. Buscar item na arvore;\n"
          "4. Mostrar Arvore;\n"
          "5. Testar Integridade da Arvore;\n"
          "0. Encerrar programa."<<endl;
    cin>>op;
    while(op!='0'){
        switch (op){
        case ('1'):
        {
            try{
                pItem=criarItem();
                obj->inserir(pItem);
                cout<<"\nItem inserido na arvore com sucesso.";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('2'):
        {
            try{
                if(!obj->arvoreVazia()){
                    Item *itemAux = new Item;
                    int aux;
                    cout<<"Digite a chave do item que deseja remover: ";
                    cin>>aux;
                    while(!(itemAux->setKey(aux))){
                        cout<<"Chave vazia. Digite novamente: ";
                        cin>>aux;
                    }
                    itemAux->setKey(aux);
                    mostrarItem(obj->pesquisar(itemAux));
                    if(obj->remover(itemAux))
                        cout<<"\nItem removido da arvore com sucesso.";
                    else
                        cout<<"\nInsucesso!";
                    itemAux=NULL;
                    delete itemAux;
                }else cout<<"\nArvore vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('3'):
        {
            try{
                if(!obj->arvoreVazia()){
                    Item *itemAux = new Item;
                    int aux;
                    cout<<"\nDigite a chave do item para a busca: ";
                    cin>>aux;
                    while(!(itemAux->setKey(aux))){
                        cout<<"Chave vazia. Digite novamente: ";
                        cin>>aux;
                    }
                    itemAux->setKey(aux);
                    obj->pesquisar(itemAux);
                    mostrarItem(obj->pesquisar(itemAux));
                    delete itemAux;
                }else cout<<"\nArvore vazia!";
            }
            catch(string &erro){
                cout<<erro;
            }
            break;
        }
        case ('4'):
        {
            if(!obj->arvoreVazia()){
                char op2;
                cout<<"Digite o tipo de ordenacao que sera mostrada a arvore:\n"
                      "1. Pre-ordem;\n"
                      "2. Em ordem;\n"
                      "3. Pos-ordem;\n"
                      "0. Voltar.\n";
                cin>>op2;
                while(op2!='0'){
                    switch (op2) {
                    case ('1'):
                    {
                        string preOrdem="";
                        obj->imprimePreOrdem(preOrdem);
                        cout<<preOrdem;
                        break;
                    }
                    case ('2'):
                    {
                        string emOrdem="";
                        obj->imprimeEmOrdem(emOrdem);
                        cout<<emOrdem;
                        break;
                    }
                    case ('3'):
                    {
                        string posOrdem="";
                        obj->imprimePosOrdem(posOrdem);
                        cout<<posOrdem;
                        break;
                    }
                    default:
                        cout<<"\nOpcao Invalida!\n";
                        break;
                    }
                    cout<<"\nDigite o tipo de ordenacao que sera mostrada a arvore:\n"
                          "1. Pre-ordem;\n"
                          "2. Em ordem;\n"
                          "3. Pos-ordem;\n"
                          "0. Voltar.\n";
                    cin>>op2;
                }
            }else cout<<"\nArvore vazia!";
            break;
        }
        case ('5'):
        {
            if(!obj->arvoreVazia()){
                string integridade="";
                obj->testaIntegridadeARB(integridade);
                cout<<integridade;
            }else cout<<"\nArvore vazia!";
            break;
        }
        default:
            cout<<"Opcao Invalida!";
            break;
        }
        cout<<"\n\n\tARVORE RED BLACK"
              "\n1. Inserir item na arvore;\n"
              "2. Remover item da arvore;\n"
              "3. Buscar item na arvore;\n"
              "4. Mostrar Arvore;\n"
              "5. Testar Integridade da Arvore;\n"
              "0. Encerrar programa."<<endl;
        cin>>op;
    }
}
