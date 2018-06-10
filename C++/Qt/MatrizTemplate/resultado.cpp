#include "resultado.h"
#include "ui_resultado.h"

Resultado::Resultado(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultado)
{
    ui->setupUi(this);
}

Resultado::~Resultado()
{
    delete ui;
}

void Resultado::setResultado(TP2::Matriz<double> *mat)
{
    try{
        ui->MatrizC->setRowCount(mat->getQuantidadeDeLinhas());
        ui->MatrizC->setColumnCount(mat->getQuantidadeDeColunas());
        for(int linha = 0; linha < mat->getQuantidadeDeLinhas(); linha++)
        {
            for(int coluna = 0; coluna < mat->getQuantidadeDeColunas(); coluna++)
            {
//                double elemento = mat->getElemento(linha,coluna);
                QString item = QString("%1").arg(mat->getElemento(linha,coluna));
                ui->MatrizC->setItem(linha,coluna, new QTableWidgetItem(item));
                ui->MatrizC->item(linha,coluna)->setFlags(Qt::ItemIsEditable);
            }
        }
        mat=nullptr;
        delete mat;
        ui->MatrizC->verticalHeader()->hide();
        ui->MatrizC->horizontalHeader()->hide();
        ui->MatrizC->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->MatrizC->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    catch(QString &erro){
        throw erro;
    }
}

void Resultado::setTitulo(QString par){
    ui->Titulo->setText(par);
}

void Resultado::on_Fechar_clicked()
{
    this->close();
    this->~Resultado();
}
