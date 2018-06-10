#include "telefoneui.h"
#include "ui_telefoneui.h"

TelefoneUI::TelefoneUI(int op, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelefoneUI)
{
    ui->setupUi(this);
    ui->Celular->setChecked(true);
    this->opcao=op;
    ui->DDD->setValidator(new QIntValidator(0,999,this));
    ui->Numero->setValidator(new QIntValidator(0,999999999,this));
}

TelefoneUI::~TelefoneUI()
{
    delete ui;
    ptTelefone=NULL;
    delete ptTelefone;
}

void TelefoneUI::setPtTelefone(Telefone *aux)
{
    try{
        this->ptTelefone = aux;
        if(opcao==2){
            ui->DDD->setText(QString::number(ptTelefone->getDDD()));
            ui->Numero->setText(QString::number(ptTelefone->getTelefone()));
            if(ptTelefone->getTipo()==1) ui->Celular->setChecked(true);
            else {
                if(ptTelefone->getTipo()==2) ui->Residencial->setChecked(true);
                else ui->Profissional->setChecked(true);
            }
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

void TelefoneUI::editarObjeto(Telefone *aux)
{
    try{
        if((ui->DDD->text())!="") aux->setDDD(ui->DDD->text().toInt());
        else throw QString("Insira o DDD!");
        if((ui->Numero->text())!="") aux->setTelefone(ui->Numero->text().toLong());
        else throw QString("Insira o número do telefone!");
        if(ui->Celular->isChecked()) aux->setTipo(1);
        else{
            if(ui->Residencial->isChecked()) aux->setTipo(2);
            else aux->setTipo(3);
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

void TelefoneUI::on_OK_clicked()
{
    try{
        editarObjeto(ptTelefone);
        accept();
        this->hide();
        ui->~TelefoneUI();
        this->close();
    }
    catch(QString &erro){
        QMessageBox::about(this,"Atenção",erro);
    }
}

void TelefoneUI::on_Cancelar_clicked()
{
    this->hide();
    ui->~TelefoneUI();
    this->close();
}
