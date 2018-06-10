#include "listaragendas.h"
#include "ui_listaragendas.h"
#include "arquivo.h"
#include "agendaui.h"

ListarAgendas::ListarAgendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListarAgendas)
{
    ui->setupUi(this);
    Arquivo::listarAgendasUI(ui->Agendas);
    ui->Agendas->update();
}

ListarAgendas::~ListarAgendas()
{
    delete ui;
}
void ListarAgendas::on_AbrirAgenda_clicked()
{
    try{
        string pessoa = ui->Agendas->currentItem()->text().toStdString();
        Agenda *agenda = new Agenda(true,pessoa);
        agenda->show();
        accept();
        this->hide();
        ui->~ListarAgendas();
        this->close();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ListarAgendas::on_Cancelar_clicked()
{
    this->hide();
    ui->~ListarAgendas();
    this->close();
}
void ListarAgendas::on_Remover_clicked()
{
    try{
        if(ui->Agendas->currentItem()){
            string pessoa = (ui->Agendas->currentItem()->text()).toStdString();
            fstream agendas;
            agendas.open("Agendas.txt",fstream::in);
            if(agendas.is_open()){
                QStringList aux;
                string aux2;
                getline(agendas,aux2);
                aux.push_back(QString::fromStdString(aux2));
                while(!agendas.eof()){
                    getline(agendas,aux2);
                    aux.push_back(QString::fromStdString(aux2));
                }agendas.close();
                for(int i=0;i<aux.size();i++){
                    if(pessoa==aux.at(i).toStdString()) aux.removeAt(i);
                }
                std::remove((pessoa+"Contatos.txt").c_str());
                std::remove((pessoa+"Telefones.txt").c_str());
                std::remove((pessoa+"Emails.txt").c_str());
                std::remove((pessoa+"Enderecos.txt").c_str());
                agendas.open("Agendas.txt",fstream::out);
                while(!aux.isEmpty()){
                    agendas<<aux.takeFirst().toStdString()<<endl;
                }agendas.close();
                QMessageBox::about(this,"Êxito","Agenda excluída com sucesso!");
                ui->Agendas->clear();
                Arquivo::listarAgendasUI(ui->Agendas);
            }else throw QString("Erro na abertura do arquivo!");
        }else throw QString("Selecione uma agenda para remover!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}
