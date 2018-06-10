#include "emailui.h"
#include "ui_emailui.h"
#include <QInputDialog>

EmailUI::EmailUI(int op, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmailUI)
{
    ui->setupUi(this);
    this->opcao=op;
}

EmailUI::~EmailUI()
{
    delete ui;
    ptEmail=NULL;
    delete ptEmail;
}

void EmailUI::setPtEmail(Email *aux)
{
    try{
        this->ptEmail = aux;
        if(opcao==2){
            ui->EmailID->setText(QString::fromStdString(ptEmail->getEmailID()));
            ui->EmailDominio->setText(QString::fromStdString(ptEmail->getEmailDominio()));
        }
    }
    catch(QString &erro){
        throw erro;
    }
}

void EmailUI::editarObjeto(Email *aux)
{
    try{
        if((ui->EmailID->text())!="") aux->setEmailID(ui->EmailID->text().toStdString());
        else throw QString("Insira o ID do email!");
        if((ui->EmailDominio->text())!="") aux->setEmailDominio(ui->EmailDominio->text().toStdString());
        else throw QString("Insira o domínio do email!");
    }
    catch(QString &erro){
        throw erro;
    }
}

void EmailUI::on_OK_clicked()
{
    try{
        editarObjeto(ptEmail);
        accept();
        this->hide();
        ui->~EmailUI();
        this->close();
    }
    catch(QString &erro){
        QMessageBox::about(this,"Atenção",erro);
    }
}

void EmailUI::on_Cancelar_clicked()
{
    this->hide();
    ui->~EmailUI();
    this->close();
}
