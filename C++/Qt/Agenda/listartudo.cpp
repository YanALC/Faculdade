#include "listartudo.h"
#include "ui_listartudo.h"

ListarTudo::ListarTudo(Lista<Contato> *aux, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListarTudo)
{
    ui->setupUi(this);
    ui->Tudo->setText(aux->listar());
}

ListarTudo::~ListarTudo()
{
    delete ui;
}

void ListarTudo::on_Fechar_clicked()
{
    this->hide();
    ui->~ListarTudo();
    this->close();
}
