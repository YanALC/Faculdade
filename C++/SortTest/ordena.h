#ifndef ORDENA_H
#define ORDENA_H
#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

template <class Item> class Ordena{
private:
    long int tam;
    Item **vetor;
    void mergeSort(Item **, int inicio, int final);
    void merge(Item **, int inicio, int meio, int final) const;
    void quickSort(int inicio, int final) const;
    void heap(int inicio, int final) const;
public:
    Ordena(){vetor=NULL;}
    ~Ordena(){
        if(vetor){
            for(int i=0;i<this->getTam();i++){
                vetor[i]=NULL;
                delete vetor[i];
            }
            vetor=NULL;
            delete [] vetor;
        }else throw string("O vetor não existe!");
    }
    void copiaVetor(const Ordena *aux);
    Item *getItem(int pos) const;
    void setItem(int pos, Item *aux);
    void selectionSort() const;
    void insertionSort() const;
    void bubbleSort() const;
    void bubbleSort2() const;
    void shellSort() const;
    void mergeSort();
    void quickSort() const;
    void heapSort() const;
    Item *buscaBinaria(Item *aux) const;
    int getTam() const;
    bool setTam(int value);
};

template <class Item> void Ordena<Item>::selectionSort() const
{
    int i,j,imin;
    for(i=0;i<tam-1;i++){
        imin=i;
        for(j=i+1;j<tam;j++){
            if(vetor[j] < vetor[imin])
                imin=j;
        }
        if(i!=imin)
            swap(vetor[i],vetor[imin]);
    }
}

template <class Item> void Ordena<Item>::insertionSort() const
{
    try{
        int i,j;
        Item *T=NULL;
        for(i=1;i<tam;i++){
            T=vetor[i];
            for(j=i-1;j>=0 && vetor[j]>T;j--){
                vetor[j+1]=vetor[j];
            }
            vetor[j+1]=T;
        }
        T=NULL;
        delete T;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template <class Item> void Ordena<Item>::bubbleSort() const
{
    int i,j;
    for(int bubble=tam;bubble!=0;bubble--){
        for(i=1;i<bubble;i++){
            j=i-1;
            if(vetor[j]>vetor[i])
                swap(vetor[i],vetor[j]);
        }
    }
}

template <class Item> void Ordena<Item>::bubbleSort2() const
{
    int i,j,lastswap;
    for(int bubble=tam;bubble!=0;bubble=lastswap){
        lastswap=0;
        for(i=1;i<bubble;i++){
            j=i-1;
            if(vetor[j]>vetor[i]){
                swap(vetor[i],vetor[j]);
                lastswap=i;
            }
        }
    }
}

template <class Item> void Ordena<Item>::shellSort() const
{
    Item *aux=NULL;
    for(int gap=tam/2;gap>0;gap=gap/2){
        for(int i=gap;i<tam;i++){
            aux=vetor[i];
            int j;
            for(j=i;j>=gap && aux<vetor[j-gap];j=j-gap)
                vetor[j]=vetor[j-gap];
            vetor[j]=aux;
        }
    }
    aux=NULL;
    delete aux;
}

template <class Item> void Ordena<Item>::merge(Item **B, int inicio, int meio, int final) const
{
    int i=inicio,j=meio+1,k=inicio;
    while(i<meio+1 && j<final+1){
        if(vetor[i]<vetor[j]){
            B[k]=vetor[i];
            i++;
            k++;
        }else{
            B[k]=vetor[j];
            j++;
            k++;
        }
    }
    while(i<meio+1){
        B[k]=vetor[i];
        i++;
        k++;
    }
    while(j<final+1){
        B[k]=vetor[j];
        j++;
        k++;
    }
    for(k=inicio;k<final+1;k++)
        vetor[k]=B[k];
}

template <class Item> void Ordena<Item>::mergeSort(Item **B,int inicio,int final)
{
    if(inicio<final){
        int meio = (inicio+final)/2;
        mergeSort(B,inicio,meio);
        mergeSort(B,meio+1,final);
        merge(B,inicio,meio,final);
    }
}

template <class Item> void Ordena<Item>::mergeSort()
{
    try{
        Item **B = new Item *[tam];
        int inicio=0,final=tam-1;
        mergeSort(B,inicio,final);
        B=NULL;
        delete [] B;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template <class Item> void Ordena<Item>::quickSort(int inicio, int final) const
{
    try{
        int i,j;
        Item *pivo=vetor[(inicio+final)/2];
        for(i=inicio,j=final;i<=j;i++,j--){
            while(vetor[i]<pivo) i++;
            while(vetor[j]>pivo) j--;
            if(i<j){
                swap(vetor[i],vetor[j]);
            }
        }
        if(j>inicio)
            quickSort(inicio,j);
        if(i<final)
            quickSort(j+1,final);
        pivo=NULL;
        delete pivo;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template <class Item> void Ordena<Item>::quickSort() const
{
    try{
        int inicio=0,final=tam-1;
        quickSort(inicio,final);
    }
    catch(string &erro){
        throw erro;
    }
}

template <class Item> void Ordena<Item>::heap(int inicio, int final) const
{
    for(int pai=inicio,filho=2*pai+1;filho<=final;pai++,filho=2*pai+1){
        if(filho<final && vetor[filho]<vetor[filho+1])
            filho++;
        if(vetor[pai]<vetor[filho])
            swap(vetor[pai],vetor[filho]);
    }
}

template <class Item> void Ordena<Item>::heapSort() const
{
    for(int i=(tam-1)/2;i>=0;i--)
        heap(i,tam-1);
    for(int i=tam-1;i>0;i--){
        swap(vetor[0],vetor[i]);
        heap(0,i-1);
    }
}

template <class Item> Item *Ordena<Item>::buscaBinaria(Item *aux) const
{
    try {
        int i=(inicio+final)/2;
        if(vetor[i]==aux) return i;
        if(inicio==final) throw string("\nItem não encontrado!");
        if(aux>vetor[i])
            buscaBinaria(aux,i+1,final);
        else
            buscaBinaria(aux,inicio,i-1);
    } catch (string &erro) {
        throw erro;
    }
}

template <class Item> void Ordena<Item>::copiaVetor(const Ordena *aux)
{
    try{
        if(this->tam!=aux->tam){
            this->vetor=NULL;
            delete [] this->vetor;
            this->tam = aux->tam;
            this->vetor = new Item *[this->tam];
        }
        for(int i = 0; i < this->tam; i++)
            this->vetor[i] = aux->vetor[i];
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}

template <class Item> Item *Ordena<Item>::getItem(int pos) const
{
    try{
        if(pos>=0 && pos<this->tam){
            return this->vetor[pos];
        }else throw string("\nA posição não existe no vetor!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class Item> void Ordena<Item>::setItem(int pos, Item *aux)
{
    try{
        if(!aux) throw string("\nO objeto não existe!");
        if(pos >= 0 && pos < this->tam){
            this->vetor[pos] = aux;
        }else throw string("\nA posição não existe no vetor!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class Item> int Ordena<Item>::getTam() const
{
    return tam;
}

template <class Item> bool Ordena<Item>::setTam(int value)
{
    try{
        if(value>2){
            tam = value;
            vetor = new Item *[tam];
            for(int i=0; i<tam; i++){
                vetor[i] = NULL;
            }return true;
        }return false;
    }
    catch(bad_alloc &){
        throw string("\nMemória Insuficiente!");
    }
}


#endif // ORDENA_H
