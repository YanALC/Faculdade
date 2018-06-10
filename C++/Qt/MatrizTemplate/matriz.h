#ifndef MATRIZ_H
#define MATRIZ_H
#include <QString>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
namespace TP2{//inicio
template <class tipo> class Matriz{
private:
    int quantidadeDeLinhas,quantidadeDeColunas;
    tipo *ptMatriz;
public:
    Matriz(int qLinhas, int qColunas):
        quantidadeDeLinhas(0),
        quantidadeDeColunas(0),
        ptMatriz(0)
    {
        if(qLinhas<=0) throw QString("Quantidade de Linhas somente positiva");
        if(qColunas<=0) throw QString("Quantidade de Colunas somente positiva");
        try{
            ptMatriz = new tipo[qLinhas*qColunas];
        }catch(std::bad_alloc&){
            throw QString("Memória Insuficiente!");
        }
        quantidadeDeLinhas = qLinhas;
        quantidadeDeColunas = qColunas;
    }
    ~Matriz(){if(ptMatriz) delete[] ptMatriz;}
    int getQuantidadeDeLinhas()const{return quantidadeDeLinhas;}
    int getQuantidadeDeColunas()const{return quantidadeDeColunas;}
    void setElemento(tipo elemento, int linha, int coluna)const;
    tipo getElemento(int linha, int coluna)const;
    void setMatriz(QTableWidget *tab)const;
    void operator = (Matriz const * const mat) const;
    Matriz * operator + (Matriz const * const mat) const;
    Matriz * operator - (Matriz const * const mat) const;
    Matriz * operator * (Matriz const * const mat) const;
    Matriz * operator ^ (int i) const;//calcular potenciação da matriz (por sobrecarga)
    Matriz * Transposta () const;//calcular matriz transposta
    Matriz * MultiplicacaoPorEscalar (int) const;//multiplicação da matriz por escalar
    bool operator == (Matriz const * const mat) const;//igualdade de matrizes
    bool TriangularSuperior () const;//verificar se é matriz triangular superior
    bool TriangularInferior () const;//verificar se é matriz triangular inferior
    bool Simetrica () const;//verificar se é matriz simétrica
    bool Identidade () const;//verificar se é matriz identidade
    bool Ortogonal () const;//verificar se é matriz ortogonal
    bool Permutacao () const;//verificar se é matriz de permutação
};

template <class tipo> void Matriz<tipo>::setElemento(tipo elemento, int linha, int coluna)const{
    if(linha<0 && linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo válido");
    if(coluna<0 && coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo válido");
    int pos = linha*quantidadeDeColunas+coluna;
    *(ptMatriz+pos) = elemento;
}

template <class tipo> tipo Matriz<tipo>::getElemento(int linha, int coluna)const{
    if(linha<0 && linha>=quantidadeDeLinhas)
        throw QString("Linha fora do intervalo válido");
    if(coluna<0 && coluna>=quantidadeDeColunas)
        throw QString("Coluna fora do intervalo válido");
    int pos = linha*quantidadeDeColunas+coluna;
    return *(ptMatriz+pos);
}

template <class tipo> void Matriz<tipo>::setMatriz(QTableWidget *tab)const
{
    try{
        for(int linha = 0; linha < quantidadeDeLinhas; linha++)
        {
            for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
            {
                if(tab->item(linha,coluna)){
                    tipo valor = std::stod(tab->item(linha,coluna)->text().toStdString());
                    if(valor==0 && tab->item(linha,coluna)->text()!="0"){
                        throw QString("Valor inválido em "+QString::number(linha+1)+"x"+QString::number(coluna+1));
                    }
                    setElemento(valor, linha, coluna);
                }else{
                    throw QString("Elemento "+QString::number(linha+1)+"x"+QString::number(coluna+1)+" não inserido!");
                }
            }
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

template <class tipo> void Matriz<tipo>::operator = (const Matriz<tipo> * const mat) const{
    for(int linha = 0; linha < this->getQuantidadeDeLinhas(); linha++)
    {
        for(int coluna = 0; coluna < this->getQuantidadeDeColunas(); coluna++)
        {
            tipo valor = mat->getElemento(linha, coluna);
            this->setElemento(valor, linha, coluna);
        }
    }
}

template <class tipo> Matriz<tipo> *Matriz<tipo>::operator + (Matriz<tipo> const * const mat)const{
    if( quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() || quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Não podem ser somadas matrizes de tamanhos diferentes!");
    try{
        Matriz<tipo> *aux = new Matriz<tipo>(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                tipo valor = this->getElemento(linha,coluna) + mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> Matriz<tipo> *Matriz<tipo>::operator - (Matriz<tipo> const * const mat)const{
    if(quantidadeDeLinhas  != mat->getQuantidadeDeLinhas() || quantidadeDeColunas != mat->getQuantidadeDeColunas())
        throw QString("Não podem ser subtraídas matrizes de tamanhos diferentes!");
    try{
        Matriz<tipo>* aux = new Matriz<tipo>(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                tipo valor = this->getElemento(linha,coluna) - mat->getElemento(linha,coluna);
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> Matriz<tipo> *Matriz<tipo>::operator * (Matriz<tipo> const * const mat) const
{
    if(this->getQuantidadeDeColunas()!=mat->getQuantidadeDeLinhas()){
        throw QString("Para ser possível a multiplicação, o número de colunas \nda primeira matriz têm que ser igual ao número de linhas \nda segunda matriz!");
    }
    try{
        Matriz<tipo> *aux = new Matriz<tipo>(this->getQuantidadeDeLinhas(),mat->getQuantidadeDeColunas());
        for(int linha=0; linha<this->getQuantidadeDeLinhas(); linha++){
            for(int coluna=0; coluna<mat->getQuantidadeDeColunas(); coluna++){
                tipo valor=0;
                for(int x=0; x<quantidadeDeColunas; x++){
                    valor=valor+(this->getElemento(linha,x)*mat->getElemento(x,coluna));
                }
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> Matriz<tipo> * Matriz<tipo>::operator ^ (int i) const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        throw QString("A matriz tem que ser quadrada!");
    if(i<0) throw QString("O expoente deve ser positivo!");
    try{
        Matriz<tipo> *aux = new Matriz<tipo>(this->getQuantidadeDeLinhas(),this->getQuantidadeDeColunas());
        if(i==0){
            Matriz<tipo> * id = new Matriz<tipo>(this->getQuantidadeDeLinhas(),this->getQuantidadeDeColunas());
            for(int linha = 0; linha < quantidadeDeLinhas; linha++)
            {
                for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
                {
                    if(linha==coluna)
                        id->setElemento(1,linha,coluna);
                    else
                        id->setElemento(0,linha,coluna);
                }
            }
            aux=id;
            id=NULL;
            delete id;
            return aux;
        }else {
            if(i==1){
                (*aux)=this;
                return aux;
            }
            else{
                Matriz<tipo> *aux2 = NULL;
                aux=(*this)*this;
                for(int j=2;j<i;j++){
                    aux2=(*aux)*this;
                    aux=NULL;
                    delete aux;
                    aux=aux2;
                    aux2=NULL;
                    delete aux2;
                }return aux;
            }
        }
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> bool Matriz<tipo>::operator == (const Matriz<tipo> * const mat)const
{
    if(quantidadeDeLinhas!=mat->getQuantidadeDeLinhas() || quantidadeDeColunas!=mat->getQuantidadeDeColunas())
        return false;
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if(this->getElemento(linha,coluna)!=mat->getElemento(linha,coluna)) return false;
        }
    }
    return true;
}

template <class tipo> Matriz<tipo> * Matriz<tipo>::MultiplicacaoPorEscalar (int k) const
{
    try{
        Matriz<tipo>* aux = new Matriz<tipo>(quantidadeDeLinhas,quantidadeDeColunas);
        for(int linha=0; linha<quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<quantidadeDeColunas; coluna++){
                tipo valor = this->getElemento(linha,coluna)*k;
                aux->setElemento(valor,linha,coluna);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> Matriz<tipo> * Matriz<tipo>::Transposta () const
{
    try{
        Matriz<tipo> *aux = new Matriz<tipo>(quantidadeDeColunas,quantidadeDeLinhas);
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            for(int linha = 0; linha < quantidadeDeLinhas; linha++)
            {
                tipo valor = this->getElemento(linha,coluna);
                aux->setElemento(valor, coluna, linha);
            }
        }
        return aux;
    }
    catch(std::bad_alloc&){
        throw QString("Memória Insuficiente!");
    }
}

template <class tipo> bool Matriz<tipo>::TriangularSuperior () const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if(linha==coluna){
                if(getElemento(linha,coluna)==0) return false;
            }else{
                if(linha>coluna)
                    if(getElemento(linha,coluna)!=0) return false;
            }
        }
    }return true;
}

template <class tipo> bool Matriz<tipo>::TriangularInferior () const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if(linha==coluna){
                if(getElemento(linha,coluna)==0) return false;
            }else{
                if(linha<coluna)
                    if(getElemento(linha,coluna)!=0) return false;
            }
        }
    }return true;
}

template <class tipo> bool Matriz<tipo>::Simetrica () const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if (this->getElemento(linha,coluna)!=this->getElemento(coluna,linha)) return false;
        }
    }return true;
}

template <class tipo> bool Matriz<tipo>::Identidade () const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if (linha==coluna){
                if(getElemento(linha,coluna)!=1) return false;
            }else{
                if(getElemento(linha,coluna)!=0) return false;
            }
        }
    }
    return true;
}

template <class tipo> bool Matriz<tipo>::Permutacao() const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
    {
        int i=0;
        for(int linha = 0; linha < quantidadeDeLinhas; linha++)
        {
            i=i+getElemento(linha,coluna);
        }if(i!=1) return false;
    }
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        int j=0;
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            j=j+getElemento(linha,coluna);
        }if(j!=1) return false;
    }
    return true;
}

template <class tipo> bool Matriz<tipo>::Ortogonal () const
{
    if(quantidadeDeColunas!=quantidadeDeLinhas)
        return false;
    Matriz<tipo> *id = new Matriz<tipo>(quantidadeDeLinhas,quantidadeDeColunas);
    for(int linha = 0; linha < quantidadeDeLinhas; linha++)
    {
        for(int coluna = 0; coluna < quantidadeDeColunas; coluna++)
        {
            if(linha==coluna)
                id->setElemento(1,linha,coluna);
            else
                id->setElemento(0,linha,coluna);
        }
    }
    Matriz<tipo> *aux = this->Transposta();
    Matriz<tipo> *aux2 = (*this)*aux;
    aux=NULL;
    delete aux;
    if((*aux2)==id){
        aux2=id=NULL;
        delete aux2;
        delete id;
        return true;
    }aux2=id=NULL;
    delete aux2;
    delete id;
    return false;
}
}//fim

#endif // MATRIZ_H
