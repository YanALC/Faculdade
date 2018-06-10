#include "testa.h"

void Testa::menu()
{
    try{
        int tam;
        cout<<"\nQuantidade de vertices: ";
        cin>>tam;
        while(tam<3){
            cout<<"\nNao pode ser menor do que 3! Digite novamente: ";
            cin>>tam;
        }if(tam>2) obj = new Grafo(tam);
        char op;
        do{
            cout<<"\n\tGRAFO"
                  "\n1. inserir aresta;"
                  "\n2. verificar existencia ou editar aresta;"
                  "\n3. obter lista adjacente a um vertice;"
                  "\n4. retirar uma aresta;"
                  "\n5. imprimir grafo;"
                  "\n6. obter grafo transposto;"
                  "\n7. obter aresta de menor peso;"
                  "\n8. visitas e buscas"
                  "\n0. sair."<<endl;
            cin>>op;
            switch(op){
            case ('1'):{
                try{
                    obj->inserirAresta(this->preecheAresta())? cout<<"\nAresta inserida com sucesso!": cout<<"\nAresta nao inserida!";
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('2'):{
                try{
                    Grafo::Aresta *aresta = new Grafo::Aresta;
                    int v1,v2;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v1;
                    }while(v1<0||v1>obj->getTamanho()-1);
                    do{
                        cout<<"\nVertice Destino: ";
                        cin>>v2;
                    }while(v2<0||v2>obj->getTamanho()-1);
                    if(obj->existeAresta(v1,v2)){
                        cout<<"\nA Aresta existe!";
                        aresta = obj->existeAresta(v1,v2);
                        cout<<aresta;
                        char op2;
                        do{
                            cout<<"\nDeseja editar a aresta?(s/n)";
                            cin>>op2;
                        }while(op2!='s'&&op2!='n');
                        if(op2=='s'){
                            obj->retirarAresta(v1,v2);
                            aresta = preecheAresta();
                            obj->inserirAresta(aresta);
                        }
                    }
                    else
                        cout<<"\nA Aresta nao existe!";
                    aresta=NULL;
                    delete aresta;
                }
                catch(bad_alloc &){
                    cout<<"\nMemoria Insuficiente!";
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('3'):{
                try{
                    int v;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v;
                    }while(v<0||v>obj->getTamanho()-1);
                    this->imprimelistaAdj(v);
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('4'):{
                try{
                    int v1,v2;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v1;
                    }while(v1<0||v1>obj->getTamanho()-1);
                    do{
                        cout<<"\nVertice Destino: ";
                        cin>>v2;
                    }while(v2<0||v2>obj->getTamanho()-1);
                    cout<<obj->retirarAresta(v1,v2);
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('5'):{
                try{
                    obj->imprime();
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('6'):{
                try{
                    obj->grafoTransposto()->imprime();
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('7'):{
                try{
                    int v;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v;
                    }while(v<0||v>obj->getTamanho()-1);
                    obj->arestaMenorPeso(v)!=NULL? cout<<obj->arestaMenorPeso(v): cout<<"\nVertice nao tem arestas de destino!";
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('8'):{
                try{
                    menuBuscas();
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            default:
                if(op!='0') cout<<"\nOpcao Invalida!";
                break;
            }
        }while(op!='0');
    }
    catch(string &erro){
        cout<<erro;
    }
    catch(bad_alloc &){
        cout<<"\nMemoria Insuficiente!";
    }
}

void Testa::menuBuscas()
{
    try{
        char op2;
        do{
            cout<<"\n\n\t1. visita em Profundidade;"
                  "\n\t2. visita em Largura;"
                  "\n\t3. Dijkstra;"
                  "\n\t4. Programacao Dinamica;"
                  "\n\t0. voltar"<<endl;
            cin>>op2;
            switch(op2){
            case('1'):{
                try{
                    obj->profundidade();
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('2'):{
                try{
                    int* largura = obj->largura();
                    char op2;
                    do{
                        cout<<"\n\nImprimir menor caminho?(s/n)";
                        cin>>op2;
                    }while(op2!='s'&&op2!='n');
                    if(op2=='s'){
                        int v1,v2;
                        do{
                            cout<<"\nVertice Origem: ";
                            cin>>v1;
                        }while(v1<0||v1>obj->getTamanho()-1);
                        do{
                            cout<<"\nVertice Destino: ";
                            cin>>v2;
                        }while(v2<0||v2>obj->getTamanho()-1);
                        obj->imprimeMenorCaminho(v1,v2,largura);
                    }largura=NULL;
                    delete[] largura;
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('3'):{
                try{
                    int v1,v2;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v1;
                    }while(v1<0||v1>obj->getTamanho()-1);
                    do{
                        cout<<"\nVertice Destino: ";
                        cin>>v2;
                    }while(v2<0||v2>obj->getTamanho()-1);
                    obj->imprimeCaminhoMinimo(v1,v2, obj->dijkstra(v1));
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            case('4'):{
                try{
                    int v1,v2;
                    do{
                        cout<<"\nVertice Origem: ";
                        cin>>v1;
                    }while(v1<0||v1>obj->getTamanho()-1);
                    do{
                        cout<<"\nVertice Destino: ";
                        cin>>v2;
                    }while(v2<0||v2>obj->getTamanho()-1);
                    obj->imprimeCaminhoMinimo(v1,v2, obj->pDinamica());
                }
                catch(string &erro){
                    cout<<erro;
                }
                break;
            }
            default:
                if(op2!='0') cout<<"\nOpcao Invalida!";
                break;
            }
        }while (op2!='0');
    }
    catch(string &erro){
        cout<<erro;
    }
    catch(bad_alloc &){
        cout<<"\nMemoria Insuficiente!";
    }
}

void Testa::imprimelistaAdj(int v)
{
    try{
        if(!obj->listaAdjVazia(v)){
            Grafo::Aresta *aux = obj->primeiraAresta(v);
            Celula *aux2 = NULL;
            while(aux!=NULL){
                aux2 = new Celula(aux->getV2(),aux->getPeso());
                cout<<aux2;
                aux = obj->proximaAresta(v);
            }
            aux=NULL;
            aux2=NULL;
            delete aux;
            delete aux2;
        }else cout<<"\nLista de vertices adjacentes a "<<v<<" eh vazia!";
    }
    catch(string &erro){
        throw erro;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
}

Grafo::Aresta *Testa::preecheAresta()
{
    try{
        Grafo::Aresta *aux = new Grafo::Aresta;
        cin>>aux;
        while((aux->getV1()<0||aux->getV1()>obj->getTamanho()-1)||(aux->getV2()<0||aux->getV2()>obj->getTamanho()-1)){
            cout<<"\nVertices fora do intervalo do tamanho do grafo!";
            cin>>aux;
        }
        return aux;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}
