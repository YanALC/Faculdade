#include "lista.h"

Lista::Lista()
{
    tam=0;
    final=0;
    vet=NULL;
}

void Lista::free()
{
    Aluno *aux2 = NULL;
    short int i=0;
    while(!listaVazia()){
        aux2=vet[i];
        vet[i]=NULL;
        delete vet[i];
        delete aux2;
        i++;
    }
    aux2=NULL;
    delete[]vet;
    vet=NULL;
}

bool Lista::setTam(short int aux)
{
    if(aux>=2){
        tam=aux;
        if(vet){
            free();
        }
        vet=new Aluno*[tam];
        return true;
    }
    return false;
}

short Lista::getTam() const
{
    return tam;
}

bool Lista::inserirOrdenado(Aluno *aux)
{
    if(listaCheia()) return false;
    if(aux==NULL) return false;
    short int i,j;
    for(i=0;i<final && aux->getNome()>vet[i]->getNome();i++);
    for(j=final;j>i;j--)
    {
        vet[j]=vet[j-1];
    }
    vet[i]=aux;
    final++;
    return true;
}

bool Lista::inserirFinal(Aluno *aux)
{
    if(listaCheia()) return false;
    if(aux==NULL) return false;
    vet[final]=aux;
    final++;
    return true;
}

Aluno *Lista::remover(Aluno * aux)
{
    if (listaVazia()) return NULL;
    short int i;
    for(i=0;i<final && aux->getNome()!=vet[i]->getNome();i++)
    if(i==final) return NULL;
    aux=vet[i];
    for(;i<final-1;i++){
        vet[i]=vet[i+1];
    }
    final--;
    return aux;
}

bool Lista::listaVazia()const{
    return (final==0);
}

bool Lista::listaCheia()const{
    return (final==tam);
}

Aluno *Lista::buscar(string aux)
{
    for(short int i=0;i<final;i++){
        if(aux==vet[i]->getNome()) return vet[i];
    }return NULL;
}

void Lista::imprimirAluno(Aluno * objeto)
{
    cout<<"\nNome completo do aluno: "<<objeto->getNome();
    cout<<"\nCPF do aluno: "<<objeto->getCpf();
    cout<<"\nMatricula do aluno: "<<objeto->getMatricula();
    cout<<"\nTelefone do aluno: "<<objeto->getFone();
}

string Lista::imprimirTudo()
{
    string aux="";
    for(short int i=0;i<final;i++){
        aux=aux+"\nNome do Aluno: ";
        aux=aux+vet[i]->getNome();
        aux=aux+"\nMatrícula do Aluno: ";
        aux=aux+vet[i]->getMatricula();
        aux=aux+"\nCPF do Aluno: ";
        aux=aux+vet[i]->getCpf();
        aux=aux+"\nTelefone do Aluno: ";
        aux=aux+vet[i]->getFone();
        aux=aux+"\n";
    }
    return aux;
}

Lista::~Lista(){
    free();
}
