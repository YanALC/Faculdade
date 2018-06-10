#include "definirescalar.h"
#include "ui_definirescalar.h"
#include "resultado.h"

DefinirEscalar::DefinirEscalar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefinirEscalar)
{
    ui->setupUi(this);
    aux=NULL;
}

DefinirEscalar::~DefinirEscalar()
{
    delete ui;
    aux=NULL;
    delete aux;
}

void DefinirEscalar::on_Escalar_valueChanged(int arg1)
{
    if(get_i==2){
        if(arg1>7){
            QMessageBox::about(this,"Atenção","O limite para o expoente da potenciação é 7!");
            ui->Escalar->setValue(7);
            escalar=7;
            arg1=escalar;
        }escalar=arg1;
    }else escalar=arg1;
}

void DefinirEscalar::gerarMatriz(TP2::Matriz<double> *mat, int i, QString matriz){
    aux = new TP2::Matriz<double>(mat->getQuantidadeDeLinhas(),mat->getQuantidadeDeColunas());
    *aux = mat;
    mat=nullptr;
    delete mat;
    get_i=i;
    get_matriz=matriz;
    if(get_i==1){
        ui->Escalar->setMinimum(-999);
        ui->Escalar->setMaximum(+999);
    }
}

void DefinirEscalar::on_Confirmacao_accepted()
{
    try{
        if(get_i==1) *aux = aux->MultiplicacaoPorEscalar(escalar);
        else *aux = (*aux)^escalar;//if(get_i==2): Potenciação
        Resultado *res = new Resultado;
        if(get_i==1) res->setTitulo(QString("Multiplicação por Escalar:\n"+QString::number(escalar)+"*"+get_matriz));
        else res->setTitulo(QString("Potenciação: "+get_matriz+"^"+QString::number(escalar)));//get_i==2
        res->setResultado(aux);
        res->show();
        close();
        this->~DefinirEscalar();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void DefinirEscalar::on_Confirmacao_rejected()
{
    close();
    this->~DefinirEscalar();
}


