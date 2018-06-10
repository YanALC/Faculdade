#include "grafo.h"

bool Grafo::inserirAresta(Grafo::Aresta *aux)
{
    try{
        vetor[aux->getV1()]->inserirFinal(new Celula(aux->getV2(),aux->getPeso()));
        return true;
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo::Aresta *Grafo::existeAresta(int v1, int v2)
{
    try{
        Celula *item = new Celula(v2,0);
        return (vetor[v1]->buscar(item)? new Aresta(v1,v2,vetor[v1]->buscar(item)->getPeso()): NULL);
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo::Aresta *Grafo::primeiraAresta(int v)
{
    try{
        Celula *item = vetor[v]->primeiro();
        return (item? new Aresta(v,item->getVertice(),item->getPeso()): NULL);
    }
    catch(bad_alloc&){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo::Aresta *Grafo::proximaAresta(int v)
{
    try{
        Celula *item = vetor[v]->proximo();
        return (item != NULL? new Aresta(v,item->getVertice(),item->getPeso()): NULL);
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo::Aresta *Grafo::retirarAresta(int v1, int v2)
{
    try{
        Celula *item = vetor[v1]->remover(new Celula(v2,0));
        return (item != NULL? new Aresta(v1,v2,item->getPeso()): NULL);
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo *Grafo::grafoTransposto()
{
    try{
        Grafo *grafoTransposto = new Grafo(this->tamanho);
        Grafo::Aresta *adjacente = new Grafo::Aresta;
        for(int i=0;i<this->tamanho;i++){
            if(!this->listaAdjVazia(i)){
                adjacente = this->primeiraAresta(i);
                while(adjacente != NULL){
                    grafoTransposto->inserirAresta(new Aresta(adjacente->getV2(),adjacente->getV1(),adjacente->getPeso()));
                    adjacente = this->proximaAresta(i);
                }
            }
        }
        adjacente = NULL;
        delete adjacente;
        return grafoTransposto;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Grafo::Aresta *Grafo::arestaMenorPeso(int vertice)
{
    try{
        if(!listaAdjVazia(vertice)){
            Aresta *aux = this->primeiraAresta(vertice);
            Aresta *menorPeso = aux;
            while(aux != NULL){
                if(menorPeso->getPeso()>aux->getPeso())
                    menorPeso = aux;
                aux = this->proximaAresta(vertice);
            }
            aux=NULL;
            delete aux;
            return menorPeso;
        }return NULL;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

void Grafo::imprime()
{
    try{
        Celula *item = NULL;
        for(int i=0;i<tamanho;i++){
            cout<<"\nVertice "<<i<<" :";
            item = vetor[i]->primeiro();
            while(item!=NULL){
                cout<<item;
                item=vetor[i]->proximo();
            }
        }item=NULL;
        delete item;

    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

void Grafo::profundidade()
{
    int *cor = new int[getTamanho()];
    int i;
    for(i=0;i<getTamanho();i++){
        cor[i]=BRANCO;
    }
    for(i=0;i<getTamanho();i++){
        if(cor[i]==BRANCO)
            visitaDFS(i,cor);
    }
    cor=NULL;
    delete[]cor;
    cout<<"Visita completada com exito!";
}

void Grafo::visitaDFS(int vertice, int *cor)
{
    try{
        cor[vertice]=CINZA;
        Grafo::Aresta *aux = primeiraAresta(vertice);
        while(aux){
            if(cor[aux->getV2()]==BRANCO)
                visitaDFS(aux->getV2(),cor);
            cout<<aux;
            aux = proximaAresta(vertice);
        }
        aux=NULL;
        delete aux;
        cor[vertice]=PRETO;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

int *Grafo::largura()
{
    try{
        int *cor = new int[getTamanho()];
        int *antecessor = new int[getTamanho()];
        int i;
        for(i=0;i<getTamanho();i++){
            cor[i]=BRANCO;
            antecessor[i]=-1;
        }
        for(i=0;i<getTamanho();i++){
            if(cor[i]==BRANCO)
                visitaLargura(i,cor,antecessor);
        }
        cor=NULL;
        delete[]cor;
        cout<<"Visita completada com exito!";
        return antecessor;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

void Grafo::visitaLargura(int vertice, int *cor, int *antecessor)
{
    try{
        cor[vertice]=CINZA;
        Lista<int> *fila = new Lista<int>;
        fila->inserirFinal(&vertice);
        while(!fila->listaVazia()){
            int i = *(fila->removerInicio());
            if(!listaAdjVazia(i)){
                Grafo::Aresta *aux = primeiraAresta(i);
                while(aux){
                    if(cor[aux->getV2()]==BRANCO){
                        cor[aux->getV2()]=CINZA;
                        fila->inserirFinal(new int(aux->getV2()));
                        antecessor[aux->getV2()] = i;
                    }
                    cout<<aux;
                    aux = proximaAresta(i);
                }
                aux=NULL;
                delete aux;
            }
        }
        fila->~Lista();
        fila=NULL;
        delete fila;
        cor[vertice]=PRETO;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

void Grafo::imprimeMenorCaminho(int origem, int destino, int *largura)
{
    try{
        Lista<Grafo::Aresta> *caminho = new Lista<Grafo::Aresta>;
        int aux = largura[destino];
        int aux2 = destino;
        while(aux2!=origem){
            if(aux!=-1){
                if(existeAresta(aux,aux2))
                    caminho->inserirInicio(new Grafo::Aresta(aux,aux2,vetor[aux]->buscar(new Celula(aux2,0.0))->getPeso()));
                aux2 = aux;
                aux = largura[aux];
            }else break;
        }
        if(aux==-1 && aux2!=origem)
            cout<<"\nNao existe caminho do vertice "<<origem<<" ate o vertice "<<destino<<"."<<endl;
        else{
            cout<<"\nArestas percorridas no menor caminho de "<<origem<<" ate "<<destino<<": "<<endl;
            while(!caminho->listaVazia()){
                cout<<caminho->removerInicio();
            }
        }
        caminho->~Lista();
        caminho=NULL;
        delete caminho;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Pair<int,float> *Grafo::dijkstra(int origem)
{
    try{
        Pair<int,float> *p = new Pair<int,float>[getTamanho()]; //primeiro=antecessor; segundo=custo minimo ate a celula da posição no vetor
        int *aberto = new int[getTamanho()];
        Lista<Pair<int,float>> *FPMinima = new Lista<Pair<int,float>>; //primeiro=vertice; segundo=custo minimo
        for(int i=0;i<getTamanho();i++){
            aberto[i]=true;
            p[i].setI1(-1);
            p[i].setI2(FLT_MAX/2);
        }
        p[origem].setI2(0.0);
        FPMinima->inserirCrescente(new Pair<int,float>(origem,0.0));
        while(!FPMinima->listaVazia()){
            int u = FPMinima->removerInicio()->getI1();
            if(aberto[u]==true){
                aberto[u]=false;
                for(Grafo::Aresta *aux = primeiraAresta(u);aux;aux=proximaAresta(u)){
                    int v = aux->getV2();
                    if(p[v].getI2() > (p[u].getI2()+aux->getPeso())){
                        p[v].setI2(p[u].getI2()+aux->getPeso());
                        p[v].setI1(u);
                        FPMinima->inserirCrescente(new Pair<int,float>(v,p[v].getI2()));
                    }
                }
            }
        }
        FPMinima->~Lista();
        FPMinima=NULL;
        aberto=NULL;
        delete FPMinima;
        delete[] aberto;
        return p;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

void Grafo::imprimeCaminhoMinimo(int origem, int destino,Pair<int, float> *pair)
{
    try{
        Lista<Grafo::Aresta> *caminho = new Lista<Grafo::Aresta>;
        int aux = pair[destino].getI1();
        int aux2 = destino;
        while(aux2!=origem){
            if(aux!=-1){
                if(existeAresta(aux,aux2))
                    caminho->inserirInicio(new Grafo::Aresta(aux,aux2,vetor[aux]->buscar(new Celula(aux2,0.0))->getPeso()));
                aux2 = aux;
                aux = pair[aux].getI1();
            }else break;
        }
        if(aux==-1 && aux2!=origem)
            cout<<"\nNao existe caminho do vertice "<<origem<<" ate o vertice "<<destino<<"."<<endl;
        else{
            cout<<"\nArestas percorridas no caminho minimo de "<<origem<<" ate "<<destino<<" com peso acumulado de "<<pair[destino].getI2()<<": "<<endl;
            while(!caminho->listaVazia()){
                cout<<caminho->removerInicio();
            }
        }
        pair=NULL;
        caminho->~Lista();
        caminho=NULL;
        delete[] pair;
        delete pair;
        delete caminho;
    }
    catch(bad_alloc &){
        throw string("Memoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

Pair<int, float> *Grafo::pDinamica()
{
    Pair<int,float> *p = new Pair<int,float>[getTamanho()]; //primeiro=antecessor; segundo=custo minimo ate a celula da posição no vetor
    int *aberto = new int[getTamanho()];
    //Lista<Pair<int,float>> *FPMinima = new Lista<Pair<int,float>>; //primeiro=vertice; segundo=custo minimo
    for(int i=0;i<getTamanho();i++){
        aberto[i]=true;
        p[i].setI1(-1);
        p[i].setI2(FLT_MAX/2);
    }
    p[sizeof(p)-1].setI1(0);
    for(int i=sizeof(p);i>0;i--)
    {
        for(int j=0;j<tamanho;j++)
        {
            Grafo::Aresta *aux = existeAresta(j,i);
            if(aux)
            {
                if(aux->getPeso()<p[i].getI2())
                {
                    p[i].setI1(j);
                    p[i].setI2(aux->getPeso());
                }
            }
        }
    }
    return p;
}

//Grafo::Aresta *Grafo::imprimeRecursivo(Pair<int, float> *pair, int origem, int destino)
//{
//    if(origem!=pair[destino].getI1()){
//        cout<<imprimeRecursivo(pair, origem, pair[destino].getI1());
//    }else{
//        if(destino!=-1){
//            Aresta *aux = new Aresta(origem,destino,vetor[origem]->buscar(new Celula(destino,0.0))->getPeso());
//            //cout<<aux;
//            return aux;
//        }
//    }
//}
