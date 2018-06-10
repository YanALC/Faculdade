#include "ordena.h"
#include <ctime>
#include <iomanip>
#include <cstdlib>
int main()
{
    try{
        Ordena<short int> *vetor1=new Ordena<short int>,*vetor2=new Ordena<short int>;
        vetor1->setTam(std::numeric_limits<short int>::max());
        for(short int i=0;i<std::numeric_limits<short int>::max();i++){
            vetor1->setItem(i,&i);
        }
        cout<<"\n\t\t\tMELHOR CASO\n";
        vetor2->copiaVetor(vetor1);
        clock_t startTime,endTime;
        startTime = clock();
        vetor2->selectionSort();
        endTime = clock();
        long double pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nselection sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->insertionSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\ninsertion sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort2();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort inteligente. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->shellSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nshell sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->mergeSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nmerge sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->heapSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nheap sort. Tempo: "<<pTime;

        vetor2=new Ordena<short int>;
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->quickSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nquick sort. Tempo: "<<pTime;
        vetor1=new Ordena<short int>;
        vetor1->setTam(std::numeric_limits<short int>::max());
        short int j=0;
        for(short int i=std::numeric_limits<short int>::max()-1;i>-1;i--){
            vetor1->setItem(j,&i);
            j++;
        }
        vetor2=new Ordena<short int>;
        cout<<"\n\t\t\tPIOR CASO\n";
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->selectionSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nselection sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/1000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->insertionSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\ninsertion sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort2();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort inteligente. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->shellSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nshell sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->mergeSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nmerge sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->heapSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nheap sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->quickSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nquick sort. Tempo: "<<pTime;
        for(int i=0;i<vetor2->getTam()/10000;i++){
            cout<<*(vetor2->getItem(i))<<endl;
        }
        for(short int i=0;i<std::numeric_limits<short int>::max();i++){
            short int a=rand()%std::numeric_limits<short int>::max();
            vetor1->setItem(i,&a);
        }
        cout<<"\n\t\t\tALEATORIO\n";
        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->selectionSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nselection sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->insertionSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\ninsertion sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->bubbleSort2();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nbubble sort inteligente. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->shellSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nshell sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->mergeSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nmerge sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->heapSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nheap sort. Tempo: "<<pTime;

        vetor2->copiaVetor(vetor1);
        startTime = clock();
        vetor2->quickSort();
        endTime = clock();
        pTime = (endTime-startTime);
        pTime=pTime/CLOCKS_PER_SEC;
        cout<<"\nquick sort. Tempo: "<<pTime;
    }
    catch(string &erro){
        cout<<erro;
    }
    return 0;
}
