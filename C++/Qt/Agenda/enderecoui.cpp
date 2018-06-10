#include "enderecoui.h"
#include "ui_enderecoui.h"

EnderecoUI::EnderecoUI(int op, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnderecoUI)
{
    ui->setupUi(this);
    ui->Residencial->setChecked(true);
    this->opcao=op;
    ui->Numero->setValidator(new QIntValidator(0,9999,this));
    ui->CEP->setValidator(new QIntValidator(0,999999999,this));
}

EnderecoUI::~EnderecoUI()
{
    delete ui;
    ptEndereco=NULL;
    delete ptEndereco;
}

void EnderecoUI::setPtEndereco(Endereco *aux)
{
    try{
        this->ptEndereco = aux;
        if(opcao==2){
            ui->Logradouro->setText(QString::fromStdString(ptEndereco->getLogradouro()));
            ui->Numero->setText(QString::number(ptEndereco->getNumero()));
            ui->CEP->setText(QString::number(ptEndereco->getCep()));
            if(ptEndereco->getTipo()==1) ui->Residencial->setChecked(true);
            else {
                if(ptEndereco->getTipo()==2) ui->Profissional->setChecked(true);
                else ui->Outro->setChecked(true);
            }
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

void EnderecoUI::editarObjeto(Endereco *aux)
{
    try{
        if((ui->Logradouro->text())!="") aux->setLogradouro(ui->Logradouro->text().toStdString());
        else throw QString("Insira o Logradouro!");
        if((ui->Numero->text())!="") aux->setNumero(ui->Numero->text().toInt());
        else aux->setNumero(0);//throw QString("Insira o número!")
        if((ui->CEP->text())!="") aux->setCep(ui->CEP->text().toLong());
        else aux->setCep(0);//throw QString("Insira o CEP!")
        if(ui->Residencial->isChecked()) aux->setTipo(1);
        else{
            if(ui->Profissional->isChecked()) aux->setTipo(2);
            else aux->setTipo(3);
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

void EnderecoUI::on_OK_clicked()
{
    try{
        editarObjeto(ptEndereco);
        accept();
        this->hide();
        ui->~EnderecoUI();
        this->close();
    }
    catch(QString &erro){
        QMessageBox::about(this,"Atenção",erro);
    }
}

void EnderecoUI::on_Cancelar_clicked()
{
    this->hide();
    ui->~EnderecoUI();
    this->close();
}
