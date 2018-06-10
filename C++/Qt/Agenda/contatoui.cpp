#include "contatoui.h"
#include "ui_contatoui.h"
#include "telefoneui.h"
#include "emailui.h"
#include "enderecoui.h"

ContatoUI::ContatoUI(int op,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContatoUI)
{
    ui->setupUi(this);
    this->opContato=op;
    this->setHeaders();
    this->atualizarTabelas();
}

ContatoUI::~ContatoUI()
{
    delete ui;
    contato=nullptr;
    delete contato;
    ptContato=nullptr;
    delete ptContato;
}

void ContatoUI::setPtContato(Contato *aux)
{
    try{
        this->ptContato = aux;
        if(opContato==2){
            ui->Nome->setText(QString::fromStdString(ptContato->getNome()));
            ui->AdicionarContato->setText("Salvar");
            ptContato->getEmails()->listarUI(ui->Emails);
            contato->operator=(ptContato);
            this->atualizarTabelas();
        }
    }
    catch(QString &erro){
        throw erro;
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::atualizarTabelas()
{
    try{
        ui->Telefones->clear();
        ui->Telefones->setRowCount(contato->getTelefones()->getI());
        for(int i=0;i<contato->getTelefones()->getI();i++){
            ui->Telefones->setItem(i,0,new QTableWidgetItem(QString::number(contato->getTelefones()->operator[](i)->getDDD())));
            ui->Telefones->setItem(i,1,new QTableWidgetItem(QString::number(contato->getTelefones()->operator[](i)->getTelefone())));
            if(contato->getTelefones()->operator[](i)->getTipo()==1) ui->Telefones->setItem(i,2,new QTableWidgetItem("Celular"));
            else{
                if(contato->getTelefones()->operator[](i)->getTipo()==2) ui->Telefones->setItem(i,2,new QTableWidgetItem("Residencial"));
                else ui->Telefones->setItem(i,2,new QTableWidgetItem("Profissional"));
            }
        }
        ui->Enderecos->clear();
        ui->Enderecos->setRowCount(contato->getEnderecos()->getI());
        for(int i=0;i<contato->getEnderecos()->getI();i++){
            ui->Enderecos->setItem(i,0,new QTableWidgetItem(QString::fromStdString(contato->getEnderecos()->operator[](i)->getLogradouro())));
            ui->Enderecos->setItem(i,1,new QTableWidgetItem(QString::number(contato->getEnderecos()->operator[](i)->getNumero())));
            ui->Enderecos->setItem(i,2,new QTableWidgetItem(QString::number(contato->getEnderecos()->operator[](i)->getCep())));
            if(contato->getEnderecos()->operator[](i)->getTipo()==1) ui->Enderecos->setItem(i,3,new QTableWidgetItem("Residencial"));
            else{
                if(contato->getEnderecos()->operator[](i)->getTipo()==2) ui->Enderecos->setItem(i,3,new QTableWidgetItem("Profissional"));
                else ui->Enderecos->setItem(i,3,new QTableWidgetItem("Outro"));
            }
        }
        this->setHeaders();
    }
    catch(QString &erro){
        throw erro;
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::setHeaders()
{
    try{
        ui->Telefones->setColumnCount(3);
        ui->Enderecos->setColumnCount(4);
        QStringList aux = QString::fromStdString("DDD,Telefone,Tipo").split(",");
        ui->Telefones->setHorizontalHeaderLabels(aux);
        aux = QString::fromStdString("Logradouro,Número,CEP,Tipo").split(",");
        ui->Enderecos->setHorizontalHeaderLabels(aux);
        ui->Telefones->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Telefones->verticalHeader()->hide();
        ui->Telefones->gridStyle();
        ui->Telefones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->Enderecos->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Enderecos->verticalHeader()->hide();
        ui->Enderecos->gridStyle();
        ui->Enderecos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    catch(QString &erro){
        throw erro;
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_AdicionarTelefone_clicked()
{
    try{
        op=1;
        Telefone *telefone = new Telefone;
        TelefoneUI *adcTelefone = new TelefoneUI(op);
        adcTelefone->setPtTelefone(telefone);
        adcTelefone->setModal(true);
        int dialogcode = adcTelefone->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setTelefone(telefone);
            this->atualizarTabelas();
        }
        telefone=NULL;
        delete telefone;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_EditarTelefone_clicked()
{
    try{
        op=2;
        Telefone *telefone = new Telefone;
        TelefoneUI *editTelefone = new TelefoneUI(op);
        int i = ui->Telefones->currentRow();
        *(telefone) = *(contato->getTelefones()->operator[](i));
        editTelefone->setPtTelefone(telefone);
        editTelefone->setModal(true);
        int dialogcode = editTelefone->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setTelefone(telefone);
            contato->getTelefones()->remover(contato->getTelefones()->operator[](i));
            this->atualizarTabelas();
        }
        telefone=NULL;
        delete telefone;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_RemoverTelefone_clicked()
{
    try{
        int i = ui->Telefones->currentRow()+1;
        contato->getTelefones()->remover(contato->getTelefones()->operator[](i));
        this->atualizarTabelas();
    }catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
}

void ContatoUI::on_AdicionarEmail_clicked()
{
    try{
        op=1;
        Email *email = new Email;
        EmailUI *adcEmail = new EmailUI(op);
        adcEmail->setPtEmail(email);
        adcEmail->setModal(true);
        int dialogcode = adcEmail->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setEmail(email);
            ui->Emails->clear();
            contato->getEmails()->listarUI(ui->Emails);
        }
        email=NULL;
        delete email;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_EditarEmail_clicked()
{
    try{
        op=2;
        Email *telefone = new Email;
        EmailUI *editEmail = new EmailUI(op);
        int i = ui->Emails->currentRow();
        *(telefone) = *(contato->getEmails()->operator[](i));
        editEmail->setPtEmail(telefone);
        editEmail->setModal(true);
        int dialogcode = editEmail->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setEmail(telefone);
            contato->getEmails()->remover(contato->getEmails()->operator[](i));
            ui->Emails->clear();
            contato->getEmails()->listarUI(ui->Emails);
        }
        telefone=NULL;
        delete telefone;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_RemoverEmail_clicked()
{
    try{
        int i = ui->Emails->currentRow();
        contato->getEmails()->remover(contato->getEmails()->operator[](i));
        ui->Emails->clear();
        contato->getEmails()->listarUI(ui->Emails);
    }catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
}

void ContatoUI::on_AdicionarEndereco_clicked()
{
    try{
        op=1;
        Endereco *endereco = new Endereco;
        EnderecoUI *adcEndereco = new EnderecoUI(op);
        adcEndereco->setPtEndereco(endereco);
        adcEndereco->setModal(true);
        int dialogcode = adcEndereco->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setEndereco(endereco);
            ui->Enderecos->clear();
            this->atualizarTabelas();
        }
        endereco=NULL;
        delete endereco;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_EditarEndereco_clicked()
{
    try{
        op=2;
        Endereco *endereco = new Endereco;
        EnderecoUI *editEndereco = new EnderecoUI(op);
        int i = ui->Enderecos->currentRow();
        *(endereco) = *(contato->getEnderecos()->operator[](i));
        editEndereco->setPtEndereco(endereco);
        editEndereco->setModal(true);
        int dialogcode = editEndereco->exec();
        if(dialogcode==QDialog::Accepted){
            contato->setEndereco(endereco);
            contato->getEnderecos()->remover(contato->getEnderecos()->operator[](i));
            ui->Enderecos->clear();
            this->atualizarTabelas();
        }
        endereco=NULL;
        delete endereco;
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_RemoverEndereco_clicked()
{
    try{
        int i = ui->Enderecos->currentRow();
        contato->getEnderecos()->remover(contato->getEnderecos()->operator[](i));
        ui->Enderecos->clear();
        this->atualizarTabelas();
    }catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
}

void ContatoUI::on_AdicionarContato_clicked()
{
    try{
        if(ui->Nome->text()!="") contato->setNome(ui->Nome->text().toStdString());
        else throw QString("Insira o nome do contato!");
        if(ui->Telefones->rowCount()==0) throw QString("Adicione ao menos um telefone \npara incluir o contato na agenda!");
        ptContato->operator=(contato);
        accept();
        this->hide();
        ui->~ContatoUI();
        this->close();
    }
    catch(QString &erro){
        QMessageBox::about(this,"Erro",erro);
    }
    catch(std::bad_alloc&){
        QMessageBox::warning(this,"Erro","Memória Insuficiente!");
    }
}

void ContatoUI::on_Cancelar_clicked()
{
    this->hide();
    ui->~ContatoUI();
    this->close();
}
