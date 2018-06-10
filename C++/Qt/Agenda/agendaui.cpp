#include "agendaui.h"
#include "ui_agendaui.h"
#include "contatoui.h"
#include "listartudo.h"
#include "teladeopcoes.h"
#include "arquivo.h"

Agenda::Agenda(bool editAgenda, string &autor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Agenda)
{
    ui->setupUi(this);
    this->Autor=autor;
    ui->NomeAutor->setText("Agenda de "+QString::fromStdString(Autor));
    try{
        if(editAgenda==true){
            agenda = Arquivo::lerArquivos(autor);
            agenda->listarUI(ui->ListaDeContatos);
        }
    }catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

Agenda::~Agenda()
{
    delete ui;
    agenda=NULL;
    delete agenda;
}

void Agenda::setPtAgenda(Lista<Contato> *aux)
{
    this->agenda=aux;
    if(edit) agenda->listarUI(ui->ListaDeContatos);
}

void Agenda::on_AdicionarContato_clicked()
{
    opContato=1;
    try {
        Contato *contato = new Contato;
        ContatoUI *adcContato = new ContatoUI(opContato);
        adcContato->setPtContato(contato);
        adcContato->setModal(true);
        int dialogcode = adcContato->exec();
        if(dialogcode==QDialog::Accepted){
            agenda->inserirOrdenado(contato);
            ui->ListaDeContatos->clear();
            agenda->listarUI(ui->ListaDeContatos);
        }
        contato=NULL;
        delete contato;
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void Agenda::on_EditarContato_clicked()
{
    opContato=2;
    try{
        ContatoUI *editContato = new ContatoUI(opContato);
        int i = ui->ListaDeContatos->currentRow();
        Contato *contato = new Contato;
        *contato=(*agenda)[i];
        editContato->setPtContato(contato);
        editContato->setModal(true);
        int dialogcode = editContato->exec();
        if(dialogcode==QDialog::Accepted){
            agenda->inserirOrdenado(contato);
            agenda->remover((*agenda)[i]);
            ui->ListaDeContatos->clear();
            agenda->listarUI(ui->ListaDeContatos);
        }
        contato=NULL;
        delete contato;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void Agenda::on_RemoverContato_clicked()
{
    try{
        agenda->remover((*agenda)[ui->ListaDeContatos->currentRow()]);
        ui->ListaDeContatos->clear();
        agenda->listarUI(ui->ListaDeContatos);
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void Agenda::on_ListaTudo_clicked()
{
    try{
        if(agenda->listaVazia()) throw QString("Agenda Vazia!");
        ListarTudo *listarTudo = new ListarTudo(agenda);
        listarTudo->show();
    }catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void Agenda::on_ListaDeContatos_itemDoubleClicked()
{
    ui->EditarContato->click();
}

void Agenda::on_Sair_clicked()
{
    try{
        QMessageBox::StandardButton resposta;
        resposta = QMessageBox::question(this,"ATENÇÃO","Tem certeza que deseja sair sem salvar?",QMessageBox::Yes | QMessageBox::No);
        if(resposta == QMessageBox::Yes){
            this->hide();
            TelaDeOpcoes *aux = new TelaDeOpcoes;
            aux->show();
            ui->~Agenda();
            this->close();
        }else ui->Salvar->setFocus();
    }catch(QString &erro){
        QMessageBox::warning(this,"ATENÇÃO",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void Agenda::on_Salvar_clicked()
{
    try{
        if(Arquivo::gravar(agenda,Autor)){
            QMessageBox::StandardButton resposta = QMessageBox::question(this,"Êxito","A Agenda foi salva em arquivo com êxito!\nQuer continuar editando sua agenda "+QString::fromStdString(this->Autor)+"?",QMessageBox::Yes | QMessageBox::No);
            if(resposta == QMessageBox::No){
                TelaDeOpcoes *aux = new TelaDeOpcoes;
                aux->show();
                this->hide();
                ui->~Agenda();
                this->close();
            }
        }
    }catch(QString &erro){
        QMessageBox::warning(this,"ATENÇÃO",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}
