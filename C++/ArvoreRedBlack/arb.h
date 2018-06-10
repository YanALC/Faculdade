#ifndef ARB_H
#define ARB_H
#include "noarb.h"
template <class item> class ARB{
private:
    NoARB<item> *raiz,*nulo;
    NoARB<item> *buscar(item *busca) const;
    void inserirCorrecao(NoARB<item> *z);
    void removerCorrecao(NoARB<item> *x);
    void transplante(NoARB<item> *u, NoARB<item> *v);
    void imprimePreOrdem(NoARB<item> *aux, string &preordem);
    void imprimeEmOrdem(NoARB<item> *aux, string &emordem);
    void imprimePosOrdem(NoARB<item> *aux, string &posordem);
    void testaIntegridadeARB(NoARB<item> *aux, string &saida);
public:
    ARB(){
        nulo=new NoARB<item>;
        raiz=nulo;
    }
    ~ARB(){
        NoARB<item> *aux=raiz;
        while(aux!=nulo){
            remover(aux->getDados());
            aux=raiz;
        }
        raiz->~NoARB();
        aux->~NoARB();
        nulo->~NoARB();
        raiz=aux=nulo=NULL;
        delete raiz;
        delete aux;
        delete nulo;
    }
    bool arvoreVazia()const {return raiz==nulo;}
    void inserir(const item *pItem);
    item *remover(item *pItem);
    item *pesquisar(item *busca) const;
    NoARB<item> *minimo(const NoARB<item> *aux);
    NoARB<item> *maximo(const NoARB<item> *aux);
    NoARB<item> *antecessor(const NoARB<item> *aux);
    NoARB<item> *sucessor(const NoARB<item> *aux);
    void rotacaoAEsquerda(NoARB<item> *x);
    void rotacaoADireita(NoARB<item> *x);
    void imprimePreOrdem(string &preOrdem){imprimePreOrdem(raiz,preOrdem);}
    void imprimeEmOrdem(string &emOrdem){imprimeEmOrdem(raiz,emOrdem);}
    void imprimePosOrdem(string &posOrdem){imprimePosOrdem(raiz,posOrdem);}
    void testaIntegridadeARB(string &aux){
        aux="";
        testaIntegridadeARB(raiz,aux);
        if(aux=="") aux="\nA Arvore nao tem erros em sua integridade!\n";
    }
};

template <class item> void ARB<item>::inserir(const item *pItem)
{
    try{
        NoARB<item> *z = new NoARB<item>(pItem);
        if(z==nulo) throw string("\nElemento vazio!");
        NoARB<item> *y = nulo;
        NoARB<item> *x = raiz;
        while(x!=nulo){
            y=x;
            if(z->getDados()->getKey() < x->getDados()->getKey())
                x = x->getEsquerda();
            else
                x = x->getDireita();
        }
        z->setPai(y);
        if(y==nulo){
            raiz=z;
            z->setPai(nulo);
        }
        else{
            if(z->getDados()->getKey() < y->getDados()->getKey())
                y->setEsquerda(z);
            else y->setDireita(z);
        }
        z->setEsquerda(nulo);
        z->setDireita(nulo);
        z->setCor(VERMELHO);
        if(z->getPai()->getCor() == VERMELHO)
            inserirCorrecao(z);
        else
            raiz->setCor(PRETO);
        x=y=z=NULL;
        delete x;
        delete y;
        delete z;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> item *ARB<item>::remover(item *pItem)
{
    if(arvoreVazia()) throw string("\nArvore Vazia!");
    try{
        NoARB<item> *z = buscar(pItem);
        if(z==nulo){
            throw string("\nElemento nao encontrado na arvore!");
        }
        NoARB<item> *y = z;
        NoARB<item> *x = new NoARB<item>;
        char yCorOriginal = y->getCor();
        if(z->getEsquerda() == nulo){
            x = z->getDireita();
            transplante(z,z->getDireita());
        }else{
            if(z->getDireita() == nulo){
                x = z->getEsquerda();
                transplante(z,z->getEsquerda());
            }else{
                y = minimo(z->getDireita());
                yCorOriginal = y->getCor();
                x = y->getDireita();
                if(y->getPai() == z)
                    x->setPai(y);
                else{
                    transplante(y,y->getDireita());
                    y->setDireita(z->getDireita());
                    y->getDireita()->setPai(y);
                }
                transplante(z,y);
                y->setEsquerda(z->getEsquerda());
                y->getEsquerda()->setPai(y);
                y->setCor(z->getCor());
            }
        }
        if(yCorOriginal == PRETO)
            removerCorrecao(x);
        raiz->setCor(PRETO);
        x=y=NULL;
        delete x;
        delete y;
        pItem = NoARB<item>::desmontarNo(z);
        return pItem;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> item *ARB<item>::pesquisar(item *busca) const
{
    try{
        if(arvoreVazia()) throw string("\nArvore Vazia!");
        NoARB<item> *aux = raiz;
        while(aux!=nulo){
            if(*busca < (aux->getDados()))
                aux=aux->getEsquerda();
            else{
                if(*busca > (aux->getDados()))
                    aux=aux->getDireita();
                else{
                    busca = NoARB<item>::desmontarNo(aux);
                    return busca;
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

template <class item> NoARB<item> *ARB<item>::buscar(item *busca) const
{
    try{
        if(arvoreVazia()) throw string("\nArvore Vazia!");
        NoARB<item> *aux = raiz;
        while(aux!=nulo){
            if(*busca < (aux->getDados()))
                aux = aux->getEsquerda();
            else{
                if(*busca > (aux->getDados()))
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

template <class item> void ARB<item>::inserirCorrecao(NoARB<item> *z)
{
    try{
        while(z->getPai()->getCor() == VERMELHO){
            NoARB<item> *y;
            if(z->getPai() == z->getPai()->getPai()->getEsquerda()){
                y = z->getPai()->getPai()->getDireita();
                if(y->getCor() == VERMELHO){
                    z->getPai()->setCor(PRETO);
                    y->setCor(PRETO);
                    z->getPai()->getPai()->setCor(VERMELHO);
                    z = z->getPai()->getPai();
                }else{
                    if(z==z->getPai()->getDireita()){
                        z = z->getPai();
                        rotacaoAEsquerda(z);
                    }
                    z->getPai()->setCor(PRETO);
                    z->getPai()->getPai()->setCor(VERMELHO);
                    rotacaoADireita(z->getPai()->getPai());
                }
            }else{
                y = z->getPai()->getPai()->getEsquerda();
                if(y->getCor() == VERMELHO){
                    z->getPai()->setCor(PRETO);
                    y->setCor(PRETO);
                    z->getPai()->getPai()->setCor(VERMELHO);
                    z = z->getPai()->getPai();
                }else{
                    if(z==z->getPai()->getEsquerda()){
                        z = z->getPai();
                        rotacaoADireita(z);
                    }
                    z->getPai()->setCor(PRETO);
                    z->getPai()->getPai()->setCor(VERMELHO);
                    rotacaoAEsquerda(z->getPai()->getPai());
                }
            }y=NULL;
            delete y;
        }
        raiz->setCor(PRETO);
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
}

template <class item> void ARB<item>::removerCorrecao(NoARB<item> *x)
{
    try{
        while((x != raiz) && (x->getCor() == PRETO)){
            NoARB<item> *w = new NoARB<item>;
            if(x == x->getPai()->getEsquerda()){
                w = x->getPai()->getDireita();
                if(w->getCor() == VERMELHO){
                    w->setCor(PRETO);
                    x->getPai()->setCor(VERMELHO);
                    rotacaoAEsquerda(x->getPai());
                    w = x->getPai()->getDireita();
                }
                if((w->getEsquerda()->getCor() == PRETO)&&(w->getDireita()->getCor() == PRETO)){
                    w->setCor(VERMELHO);
                    x = x->getPai();
                }else{
                    if(w->getDireita()->getCor() == PRETO){
                        w->getEsquerda()->setCor(PRETO);
                        w->setCor(VERMELHO);
                        rotacaoADireita(w);
                        w = x->getPai()->getDireita();
                    }
                    w->setCor(x->getPai()->getCor());
                    x->getPai()->setCor(PRETO);
                    w->getDireita()->setCor(PRETO);
                    rotacaoAEsquerda(x->getPai());
                    x = raiz;
                }
            }else{
                w = x->getPai()->getEsquerda();
                if(w->getCor() == VERMELHO){
                    w->setCor(PRETO);
                    x->getPai()->setCor(VERMELHO);
                    rotacaoADireita(x->getPai());
                    w = x->getPai()->getEsquerda();
                }
                if((w->getDireita()->getCor() == PRETO)&&(w->getEsquerda()->getCor() == PRETO)){
                    w->setCor(VERMELHO);
                    x = x->getPai();
                }else{
                    if(w->getEsquerda()->getCor() == PRETO){
                        w->getDireita()->setCor(PRETO);
                        w->setCor(VERMELHO);
                        rotacaoAEsquerda(w);
                        w = x->getPai()->getEsquerda();
                    }
                    w->setCor(x->getPai()->getCor());
                    x->getPai()->setCor(PRETO);
                    w->getEsquerda()->setCor(PRETO);
                    rotacaoADireita(x->getPai());
                    x = raiz;
                }
            }NoARB<item>::desmontarNo(w);
        }
        raiz->setCor(PRETO);

    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
}

template <class item> void ARB<item>::transplante(NoARB<item> *u, NoARB<item> *v)
{
    if(u->getPai() == nulo)
        raiz = v;
    else{
        if(u == u->getPai()->getEsquerda())
            u->getPai()->setEsquerda(v);
        else
            u->getPai()->setDireita(v);

    }
    v->setPai(u->getPai());
}

template <class item> NoARB<item> *ARB<item>::minimo(const NoARB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoARB<item> *min = aux;
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

template <class item> NoARB<item> *ARB<item>::maximo(const NoARB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoARB<item> *max = aux;
        while(max->getDireita()!=nulo){
            max=max->getDireita();
        }
        return max;
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
    catch(string &erro){
        throw erro;
    }
}

template <class item> NoARB<item> *ARB<item>::antecessor(const NoARB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoARB<item> *ant=aux;
        if(ant->getEsquerda()!=nulo) return maximo(ant->getEsquerda());
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

template <class item> NoARB<item> *ARB<item>::sucessor(const NoARB<item> *aux)
{
    try{
        if(aux==nulo) throw string("\nElemento vazio!");
        NoARB<item> *ant=aux;
        if(ant->getDireita()!=nulo) return minimo(ant->getDireita());
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

template <class item> void ARB<item>::rotacaoAEsquerda(NoARB<item> *x)
{
    try{
        NoARB<item> *y = x->getDireita(); //Define y.
        x->setDireita(y->getEsquerda()); //Faz da subarvore esquerda de y a subarvore direita de x.
        if(y->getEsquerda() != nulo)
            y->getEsquerda()->setPai(x);
        y->setPai(x->getPai()); //Liga o pai de x a y.
        if(x->getPai() == nulo)
            raiz = y;
        else{
            if(x == x->getPai()->getEsquerda())
                x->getPai()->setEsquerda(y);
            else
                x->getPai()->setDireita(y);
        }
        y->setEsquerda(x); //Coloca x a esquerda de y.
        x->setPai(y);
        NoARB<item>::desmontarNo(y);
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
}

template <class item> void ARB<item>::rotacaoADireita(NoARB<item> *x)
{
    try{
        NoARB<item> *y = x->getEsquerda(); //Define y.
        x->setEsquerda(y->getDireita()); //Faz da subarvore esquerda de y a subarvore direita de x.
        if(y->getDireita() != nulo)
            y->getDireita()->setPai(x);
        y->setPai(x->getPai()); //Liga o pai de x a y.
        if(x->getPai() == nulo)
            raiz = y;
        else{
            if(x == x->getPai()->getDireita())
                x->getPai()->setDireita(y);
            else
                x->getPai()->setEsquerda(y);
        }
        y->setDireita(x); //Coloca x a esquerda de y.
        x->setPai(y);
        NoARB<item>::desmontarNo(y);
    }
    catch(bad_alloc &){
        throw string("\nMemoria Insuficiente!");
    }
}

template <class item> void ARB<item>::imprimePreOrdem(NoARB<item> *aux, string &preordem)
{
    if(aux==nulo) return;
    if(aux==raiz) preordem=preordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor()+"\tRaiz";
    else preordem=preordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor();
    imprimePreOrdem(aux->getEsquerda(),preordem);
    imprimePreOrdem(aux->getDireita(),preordem);
}

template <class item> void ARB<item>::imprimeEmOrdem(NoARB<item> *aux, string &emordem)
{
    if(aux==nulo) return;
    imprimeEmOrdem(aux->getEsquerda(),emordem);
    if(aux==raiz) emordem=emordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor()+"\tRaiz";
    else emordem=emordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor();
    imprimeEmOrdem(aux->getDireita(),emordem);
}

template <class item> void ARB<item>::imprimePosOrdem(NoARB<item> *aux, string &posordem)
{
    if(aux==nulo) return;
    imprimePosOrdem(aux->getEsquerda(),posordem);
    imprimePosOrdem(aux->getDireita(),posordem);
    if(aux==raiz) posordem=posordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor()+"\tRaiz";
    else posordem=posordem+aux->getDados()->empacotaItem()+"\t\tCor: "+aux->getCor();
}

template <class item> void ARB<item>::testaIntegridadeARB(NoARB<item> *aux, string &saida)
{
    if(aux==nulo) return;
    if(aux->getEsquerda()!=nulo){
        if(aux->getEsquerda()->getDados()->getKey()>aux->getDados()->getKey()){
            saida=saida+"\nErro: Filho da esquerda eh maior do que o Pai!\n";
            saida=saida+aux->getEsquerda()->getDados()->empacotaItem();
        }
    }
    if(aux->getDireita()!=nulo){
        if(aux->getDireita()->getDados()->getKey()<aux->getDados()->getKey()){
            saida=saida+"\nErro: Filho da direita eh menor do que o Pai!\n";
            saida=saida+aux->getDireita()->getDados()->empacotaItem();
        }
    }
//    saida=saida+aux->getDados()->empacotaItem();
    testaIntegridadeARB(aux->getEsquerda(),saida);
    testaIntegridadeARB(aux->getDireita(),saida);
}

#endif // ARB_H
