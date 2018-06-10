#include "teladeopcoes.h"
#include "ui_teladeopcoes.h"
#include "arquivo.h"
#include "listaragendas.h"
#include <QInputDialog>
TelaDeOpcoes::TelaDeOpcoes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TelaDeOpcoes)
{
    ui->setupUi(this);
}

TelaDeOpcoes::~TelaDeOpcoes()
{
    delete ui;
    agenda=NULL;
    delete agenda;
}

void TelaDeOpcoes::on_AbrirAgenda_clicked()
{
    try{
        ListarAgendas *agendas = new ListarAgendas;
        int code = agendas->exec();
        agendas->setModal(true);
        if(code==QDialog::Accepted){
            this->hide();
            ui->~TelaDeOpcoes();
            this->close();
        }else this->show();
    }
    catch(QString &erro){
        QMessageBox::about(this,"Atenção",erro);
    }

}

void TelaDeOpcoes::on_CriarNovaAgenda_clicked()
{
    try{
        QInputDialog *input = new QInputDialog;
        input->setLabelText("Insira seu nome: ");
        int code = input->exec();
        input->setModal(true);
        if(code == QDialog::Accepted){
            string pessoa = input->textValue().toStdString();
            if(Arquivo::agendaExiste(pessoa)) throw QString("Esta agenda já existe!\nPara abrí-la clique em Cancelar e\nem Abrir Agenda na Tela de Opções.");
            Agenda *agendaUI = new Agenda(false,pessoa);
            agendaUI->show();
            this->hide();
            ui->~TelaDeOpcoes();
            this->close();
        }else{
            input=NULL;
            delete input;
        }
    }
    catch(QString &erro){
        QMessageBox::about(this,"Atenção",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void TelaDeOpcoes::on_Sair_clicked()
{
    this->hide();
    ui->~TelaDeOpcoes();
    this->close();
    qApp->quit();
}
