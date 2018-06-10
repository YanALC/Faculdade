#ifndef ARVOREBINARIADEPESQUISA_H
#define ARVOREBINARIADEPESQUISA_H
#include "noab.h"
template <class item> class ABP{
private:
    NoAB<item> *raiz,*nulo;
    NoAB<item> *buscar(item *pItem) const;
    void imprimePreOrdem(NoAB<item> *,string &);
    void imprimeEmOrdem(NoAB<item> *,string &);
    void imprimePosOrdem(NoAB<item> *,string &);
    void testaIntegridadeABP(NoAB<item> *,string &);
public:
    ABP(){
        nulo=new NoAB<item>;
        raiz=nulo;
    }
    ~ABP(){
        NoAB<item> *aux=raiz;
        while(aux!=nulo){
            remover(aux->getDados());
            aux=raiz;
        }
        raiz->~NoAB();
        aux->~NoAB();
        nulo->~NoAB();
        raiz=aux=nulo=NULL;
        delete raiz;
        delete aux;
        delete nulo;
    }
    bool arvoreVazia()const{return raiz==nulo;}
    void inserir(const item *pItem);
    item *remover(item *pItem);
    item *pesquisar(item *pItem) const;
    NoAB<item> *minimo(const NoAB<item> *aux);
    NoAB<item> *maximo(const NoAB<item> *aux);
    NoAB<item> *antecessor(const NoAB<item> *aux);
    NoAB<item> *sucessor(const NoAB<item> *aux);
    void imprimePreOrdem(string &preOrdem){imprimePreOrdem(raiz,preOrdem);}
    void imprimeEmOrdem(string &emOrdem){imprimeEmOrdem(raiz,emOrdem);}
    void imprimePosOrdem(string &posOrdem){imprimePosOrdem(raiz,posOrdem);}
    void testaIntegridadeABP(string &aux){
        aux="";
        testaIntegridadeABP(raiz,aux);
        if(aux=="") aux="\nA Arvore nao tem erros em sua integridade!\n";
    }
};

template <class item> void ABP<item>::inserir(const item *pItem)
{
    try{
        NoAB<item> *novo = new NoAB<item>(pItem);
        novo->setDireita(nulo);
        novo->setEsquerda(nulo);
        if(arvoreVazia()){
            raiz=novo;
            novo->setPai(nulo);
        }else{
            NoAB<item> *aux=raiz,*anterior=raiz;
            while(aux!=nulo){
                if(*pItem < (aux->getDados())){
                    anterior=aux;
                    aux=aux->getEsquerda();
                }else{
                    if(*pItem > (aux->getDados())){
                        anterior=aux;
                        aux=aux->getDireita();
                    }else{
                        novo=aux=anterior=NULL;
                        delete novo;
                        delete anterior;
                        delete aux;
                        throw string("\nJa existe um elemento!");
                    }
                }
            }
            if(*pItem < (anterior->getDados())){
                anterior->setEsquerda(novo);
                novo->setPai(anterior);
            }else{
                anterior->setDireita(novo);
                novo->setPai(anterior);
            }
            aux=anterior=NULL;
            delete anterior;
            delete aux;
        }
        novo=NULL;
        delete novo;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> item *ABP<item>::remover(item *pItem)
{
    if(arvoreVazia()) throw string("\nArvore Vazia!");
    try{
        NoAB<item> *aux = buscar(pItem);
        if(aux==nulo) throw string("\nElemento nao encontrado na arvore!");
        *pItem = *aux->getDados();
        NoAB<item> *aux2=nulo, *aux3=nulo;
        if((aux->getEsquerda()==nulo)||(aux->getDireita()==nulo))
            aux3=aux;
        else
            aux3=sucessor(aux);//aux tem filhos!
        if(aux3->getEsquerda()!=nulo)
            aux2 = aux3->getEsquerda();
        else
            aux2 = aux3->getDireita();
        if(aux2!=nulo)
            aux2->setPai(aux3->getPai());
        if(aux3->getPai()==nulo)
            raiz = aux2;
        else{
            if(aux3==aux3->getPai()->getEsquerda())
                aux3->getPai()->setEsquerda(aux2);
            else
                aux3->getPai()->setDireita(aux2);
        }
        if(aux3!=aux)
            aux->setDados(NoAB<item>::desmontarNo(aux3));
        pItem = NoAB<item>::desmontarNo(aux);
        aux=NULL;
        delete aux;
        return pItem;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> item *ABP<item>::pesquisar(item *pItem) const
{
    try{
        if(arvoreVazia()) throw string("\nArvore Vazia!");
        NoAB<item> *aux = raiz;
        while(aux!=nulo){
            if(*pItem < (aux->getDados()))
                aux=aux->getEsquerda();
            else{
                if(*pItem > (aux->getDados()))
                    aux=aux->getDireita();
                else{
                    pItem = NoAB<item>::desmontarNo(aux);
                    return pItem;
                }
            }
        }
        if(aux==nulo) throw string("\nElemento nao encontrado na arvore!");
        aux=NULL;
        delete aux;
        return NULL;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoAB<item> *ABP<item>::buscar(item *pItem) const
{
    try{
        if(arvoreVazia()) throw string("\nArvore Vazia!");
        NoAB<item> *aux = raiz;
        while(aux!=nulo){
            if(*pItem < (aux->getDados()))
                aux = aux->getEsquerda();
            else{
                if(*pItem > (aux->getDados()))
                    aux = aux->getDireita();
                else return aux;
            }
        }
        return aux;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoAB<item> *ABP<item>::minimo(const NoAB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoAB<item> *min = aux;
        while(min->getEsquerda()!=nulo){
            min=min->getEsquerda();
        }
        return min;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoAB<item> *ABP<item>::maximo(const NoAB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoAB<item> *max;
        for(max=aux; max->getDireita()!=nulo; max=max->getDireita());
        return max;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoAB<item> *ABP<item>::antecessor(const NoAB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoAB<item> *ant=aux;
        if(ant->getEsquerda()!=nulo) return maximo(ant);
        while(ant->getPai()!=nulo){
            if(ant->getPai()->getDireita()==ant)
                return ant->getPai();
            else
                ant=ant->getPai();
        }return NULL;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoAB<item> *ABP<item>::sucessor(const NoAB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoAB<item> *ant=aux;
        if(ant->getDireita()!=nulo) return minimo(ant);
        while(ant->getPai()!=nulo){
            if(ant->getPai()->getEsquerda()==ant)
                return ant->getPai();
            else
                ant=ant->getPai();
        }return NULL;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> void ABP<item>::imprimePreOrdem(NoAB<item> *aux, string &preordem)
{
    if(aux==nulo) return;
    if(aux==raiz) preordem=preordem+aux->getDados()->empacotaItem()+"\t\tRaiz";
    else preordem=preordem+aux->getDados()->empacotaItem();
    imprimePreOrdem(aux->getEsquerda(),preordem);
    imprimePreOrdem(aux->getDireita(),preordem);
}

template <class item> void ABP<item>::imprimeEmOrdem(NoAB<item> *aux, string &emordem)
{
    if(aux==nulo) return;
    imprimeEmOrdem(aux->getEsquerda(),emordem);
    if(aux==raiz) emordem=emordem+aux->getDados()->empacotaItem()+"\t\tRaiz";
    else emordem=emordem+aux->getDados()->empacotaItem();
    imprimeEmOrdem(aux->getDireita(),emordem);
}

template <class item> void ABP<item>::imprimePosOrdem(NoAB<item> *aux, string &posordem)
{
    if(aux==nulo) return;
    imprimePosOrdem(aux->getEsquerda(),posordem);
    imprimePosOrdem(aux->getDireita(),posordem);
    if(aux==raiz) posordem=posordem+aux->getDados()->empacotaItem()+"\t\tRaiz";
    else posordem=posordem+aux->getDados()->empacotaItem();
}

template <class item> void ABP<item>::testaIntegridadeABP(NoAB<item> *aux, string &saida)
{
    if(aux==nulo) return;
    if(aux->getEsquerda()!=nulo){
        if(*(aux->getEsquerda()->getDados())>(aux->getDados())){
            saida=saida+"\nErro: Filho da esquerda eh maior do que o Pai!\n";
            saida=saida+aux->getEsquerda()->getDados()->empacotaItem();
        }
    }
    if(aux->getDireita()!=nulo){
        if(*(aux->getDireita()->getDados())<(aux->getDados())){
            saida=saida+"\nErro: Filho da direita eh menor do que o Pai!\n";
            saida=saida+aux->getDireita()->getDados()->empacotaItem();
        }
    }
//    saida=saida+aux->getDados()->empacotaItem();
    testaIntegridadeABP(aux->getEsquerda(),saida);
    testaIntegridadeABP(aux->getDireita(),saida);
}

#endif // ARVOREBINARIADEPESQUISA_H
