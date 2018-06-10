#include "testa.h"

void Testa::menu()
{
    try{
        int tam;
        cout<<"\nTamanho do vetor: ";
        cin>>tam;
        while(!obj->setTam(tam)){
            cout<<"Tamanho do vetor não pode ser menor do que 3! Digite novamente: ";
            cin>>tam;
            obj->setTam(tam);
        }
        char op2;
        do{
            cout<<"\n\tTABELA HASH"
                  "\n1. inserir;"
                  "\n2. buscar;"
                  "\n3. remover;"
                  "\n4. mostrar vetor;"
                  "\n0. sair"<<endl;
            cin>>op2;
            switch(op2){
            case ('1'):
            {
                try{
                    Item *item = new Item;
                    cin>>item;
                    if(obj->inserir(item))
                        cout<<"\nItem inserido com sucesso na tabela!";
                    else
                        cout<<"\nItem não foi inserido.";
                    item=NULL;
                    delete item;
                }
                catch(string &erro){
                    cout<<erro;
                }
                catch(bad_alloc &){
                    throw string("\nMemória Insuficiente!");
                }

            }break;
            case ('2'):{
                try{
                    Item *itemAux = new Item;
                    string aux;
                    cin.ignore();
                    cout<<"\nChave para a busca: ";
                    getline(cin,aux);
                    itemAux->setChave(aux);
                    if(obj->buscar(itemAux)){
                        cout<<obj->buscar(itemAux);
                        char op;
                        do{
                            cout<<"\nDeseja modificar este item? (1=sim ; 0=não)";
                            cin>>op;
                        }while(op!='1' && op!='0');
                        if(op=='1'){
                            if(obj->remover(itemAux)){
                                cin>>itemAux;
                                if(obj->inserir(itemAux))
                                    cout<<"\nItem modificado com sucesso!";
                                else cout<<"\nInsucesso!";
                            }else cout<<"\nInsucesso!";
                        }
                    }
                    else{
                        cout<<"\nNão foi encontrado nenhum item com esta chave.";
                    }
                    itemAux=NULL;
                    delete itemAux;
                }
                catch(string &erro){
                    cout<<erro;
                }
                catch(bad_alloc &){
                    throw string("\nMemória Insuficiente!");
                }
                break;
            }
            case ('3'):{
                try{
                    Item *itemAux = new Item;
                    string aux;
                    cin.ignore();
                    cout<<"\nChave para a remoção: ";
                    getline(cin,aux);
                    itemAux->setChave(aux);
                    if(obj->buscar(itemAux)){
                        cout<<obj->remover(itemAux);
                        cout<<"\nItem removido da tabela Hash!";
                    }else cout<<"\nNão foi encontrado nenhum item com esta chave.";
                }
                catch(string &erro){
                    cout<<erro;
                }
                catch(bad_alloc &){
                    throw string("\nMemória Insuficiente!");
                }
                break;
            }
            case ('4'):{
                try{
                    cout<<obj->listar();
                }
                catch(string &erro){
                    cout<<erro;
                }
                catch(bad_alloc &){
                    throw string("\nMemória Insuficiente!");
                }
                break;
            }
            }
        }while(op2!='0');
    }
    catch(string &erro){
        cout<<erro;
    }
}
