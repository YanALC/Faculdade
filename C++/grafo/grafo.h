#ifndef GRAFO_H
#define GRAFO_H
#include "lista.h"
#include <float.h>
#include <stack>
#define BRANCO 1
#define CINZA 2
#define PRETO 3

class Grafo
{
private:
    Lista<Celula> **vetor;
    int tamanho;
public:
    Grafo(int tam){
        try{
            vetor = new Lista<Celula> *[tam];
            tamanho=tam;
            for(int i=0;i<tamanho;i++){
                vetor[i] = new Lista<Celula>;
            }
        }
        catch(bad_alloc &){
            throw string("Memoria Insuficiente!");
        }
        catch(string &erro){
            throw erro;
        }
    }
    ~Grafo(){}
    class Aresta{
    private:
        int v1,v2;
        float peso;
    public:
        Aresta(){}
        Aresta(int v1,int v2,float peso){
            this->v1=v1;
            this->v2=v2;
            this->peso=peso;
        }
        int getV1() const{return v1;}
        int getV2() const{return v2;}
        float getPeso() const{return peso;}
        void setV1(int value) {v1 = value;}
        void setV2(int value) {v2 = value;}
        void setPeso(float value) {peso = value;}
        friend ostream &operator <<(ostream &saida, const Aresta *obj){
            if(obj){
                saida<<"\nVertice Origem: "<<obj->v1<<"\nVertice Destino: "<<obj->v2<<"\nPeso: "<<obj->peso<<endl;
                return saida;
            }else throw string("\nA aresta nao existe!\n");
        }
        friend istream &operator >>(istream &entrada, Aresta *obj){
            cout<<"\nVertice Origem: ";
            cin>>obj->v1;
            cout<<"\nVertice Destino: ";
            cin>>obj->v2;
            cout<<"\nPeso: ";
            cin>>obj->peso;
            return entrada;
        }
        bool operator != (Aresta aux){
            return ((this->v1==aux.v1)||(this->v2==aux.v2)||(unsigned(this->peso)==unsigned(aux.peso)));
        }
    };
    //PARTE 1: FUNCOES BASICAS
    int getTamanho() const {return tamanho;}
    void setTamanho(int value){tamanho=value;}
    bool inserirAresta(Grafo::Aresta *aux);
    Aresta *existeAresta(int v1,int v2);
    bool listaAdjVazia(int v){return vetor[v]->listaVazia();}
    Aresta *primeiraAresta(int v);//retorna a primeira aresta que o vertice participa
    Aresta *proximaAresta(int v);//retorna a proxima aresta que o vertice participa
    Aresta *retirarAresta(int v1,int v2);
    Grafo *grafoTransposto();
    Aresta *arestaMenorPeso(int vertice);
    void imprime();

    //PARTE 2: ALGORITMOS DE TRAVESSIA E BUSCA

    //PROFUNDIDADE
    void profundidade();
    void visitaDFS(int vertice, int *cor);

    //LARGURA
    int *largura();
    void visitaLargura(int vertice, int *cor, int *antecessor);
    void imprimeMenorCaminho(int origem, int destino, int *largura);

    //DIJKSTRA
    Pair<int, float> *dijkstra(int origem);
    void imprimeCaminhoMinimo(int origem, int destino, Pair<int, float> *pair);

    Pair<int, float> *pDinamica();
    void imprimeCaminhoMinimo(int origem, int destino);

    /*bool existeAberto(int *aberto)
    {
        for(int i=0;i<getTamanho();i++){
            if(aberto[i]) return true;
        }return false;
    }*/
    //Grafo::Aresta *imprimeRecursivo(Pair<int, float> *pair, int origem, int destino);
};

#endif // GRAFO_H
