#include "matrizui.h"
#include "ui_matrizui.h"
#include "resultado.h"
#include "definirescalar.h"
#include <QMessageBox>

MatrizUI::MatrizUI(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MatrizUI)
{
    ui->setupUi(this);
    ui->MatrizA->setItemDelegate(new SpinBoxDelegate(this));
    ui->MatrizA->installEventFilter(this);
    ui->MatrizB->setItemDelegate(new SpinBoxDelegate(this));
    ui->MatrizB->installEventFilter(this);
}

MatrizUI::~MatrizUI()
{
    delete ui;
    A=B=C=nullptr;
    delete A;
    delete B;
    delete C;
}

void MatrizUI::on_linhasA_valueChanged(int linhasA)
{
    ui->MatrizA->setRowCount(linhasA);
    ui->MatrizA->verticalHeader()->hide();
    ui->MatrizA->gridStyle();
    ui->MatrizA->setAlternatingRowColors(true);
    ui->MatrizA->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->MatrizA->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->MatrizA->clear();
}

void MatrizUI::on_colunasA_valueChanged(int colunasA)
{
    ui->MatrizA->setColumnCount(colunasA);
    ui->MatrizA->horizontalHeader()->hide();
    ui->MatrizA->gridStyle();
    ui->MatrizA->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->MatrizA->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->MatrizA->clear();
}

void MatrizUI::on_linhasB_valueChanged(int linhasB)
{
    ui->MatrizB->setRowCount(linhasB);
    ui->MatrizB->verticalHeader()->hide();
    ui->MatrizB->gridStyle();
    ui->MatrizB->setAlternatingRowColors(true);
    ui->MatrizB->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->MatrizB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->MatrizB->clear();
}

void MatrizUI::on_colunasB_valueChanged(int colunasB)
{
    ui->MatrizB->setColumnCount(colunasB);
    ui->MatrizB->horizontalHeader()->hide();
    ui->MatrizB->gridStyle();
    ui->MatrizB->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->MatrizB->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->MatrizB->clear();
}

void MatrizUI::gravarA()
{
    try{
        if(ui->MatrizA->rowCount()==0 && ui->MatrizA->columnCount()==0)
            throw QString("Dimensões inválidas!");
        A = new TP2::Matriz<double>(ui->MatrizA->rowCount(),ui->MatrizA->columnCount());
        A->setMatriz(ui->MatrizA);
    }
    catch(QString &erro){
        throw QString("Erro na Matriz A: "+erro);
    }

}
void MatrizUI::gravarB(){
    try{
        if(ui->MatrizB->rowCount()==0 && ui->MatrizB->columnCount()==0)
            throw QString("Dimensões inválidas!");
        B = new TP2::Matriz<double>(ui->MatrizB->rowCount(),ui->MatrizB->columnCount());
        B->setMatriz(ui->MatrizB);
    }
    catch(QString &erro){
        throw QString("Erro na Matriz B: "+erro);
    }
}

void MatrizUI::enableA(){
    ui->MultiplicacaoPorEscalarA->setEnabled(true);
    ui->PotenciacaoA->setEnabled(true);
    ui->TranspostaA->setEnabled(true);
    ui->TriangularA->setEnabled(true);
    ui->SimetricaA->setEnabled(true);
    ui->IdentidadeA->setEnabled(true);
    ui->PermutacaoA->setEnabled(true);
    ui->OrtogonalA->setEnabled(true);
    boolA=true;
}

void MatrizUI::disableA(){
    ui->MultiplicacaoPorEscalarA->setDisabled(true);
    ui->PotenciacaoA->setDisabled(true);
    ui->TranspostaA->setDisabled(true);
    ui->TriangularA->setDisabled(true);
    ui->SimetricaA->setDisabled(true);
    ui->IdentidadeA->setDisabled(true);
    ui->PermutacaoA->setDisabled(true);
    ui->OrtogonalA->setDisabled(true);
    boolA=false;
}

void MatrizUI::enableB(){
    ui->MultiplicacaoPorEscalarB->setEnabled(true);
    ui->PotenciacaoB->setEnabled(true);
    ui->TranspostaB->setEnabled(true);
    ui->TriangularB->setEnabled(true);
    ui->SimetricaB->setEnabled(true);
    ui->IdentidadeB->setEnabled(true);
    ui->PermutacaoB->setEnabled(true);
    ui->OrtogonalB->setEnabled(true);
    boolB=true;
}

void MatrizUI::disableB(){
    ui->MultiplicacaoPorEscalarB->setDisabled(true);
    ui->PotenciacaoB->setDisabled(true);
    ui->TranspostaB->setDisabled(true);
    ui->TriangularB->setDisabled(true);
    ui->SimetricaB->setDisabled(true);
    ui->IdentidadeB->setDisabled(true);
    ui->PermutacaoB->setDisabled(true);
    ui->OrtogonalB->setDisabled(true);
    boolB=false;
}

void MatrizUI::enableOthers()
{
    if(boolA && boolB){
        ui->Multiplicacao->setEnabled(true);
        ui->Adicao->setEnabled(true);
        ui->Subtracao->setEnabled(true);
        ui->Igualdade->setEnabled(true);
    }
}

void MatrizUI::disableOthers()
{
    if(!(boolA && boolB)){
        ui->Multiplicacao->setDisabled(true);
        ui->Adicao->setDisabled(true);
        ui->Subtracao->setDisabled(true);
        ui->Igualdade->setDisabled(true);
    }
}

void MatrizUI::on_Adicao_clicked()
{
    try{
        C=(*A)+B;
        Resultado *res = new Resultado;
        res->setTitulo(QString("Soma: A+B"));
        res->setResultado(C);
        res->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_Subtracao_clicked()
{
    try{
        C=(*A)-B;
        Resultado *res = new Resultado;
        res->setTitulo(QString("Subtração: A-B"));
        res->setResultado(C);
        res->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_Multiplicacao_clicked()
{
    try{
        C=(*A)*B;
        Resultado *res = new Resultado;
        res->setTitulo(QString("Multiplicação: AxB"));
        res->setResultado(C);
        res->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_Igualdade_clicked()
{
    try{
        if(*A==B){
            QMessageBox::about(this,"Igualdade","As matrizes são iguais!");
        }else
            QMessageBox::about(this,"Igualdade","As matrizes são diferentes!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_MultiplicacaoPorEscalarA_clicked()
{
    try{
        DefinirEscalar *def = new DefinirEscalar;
        def->gerarMatriz(A,1,"A");
        def->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_PotenciacaoA_clicked()
{
    try{
        DefinirEscalar *def = new DefinirEscalar;
        def->gerarMatriz(A,2,"A");
        def->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_TranspostaA_clicked()
{
    try{
        C=A->Transposta();
        Resultado *res = new Resultado;
        res->setTitulo(QString("Matriz Transposta de A"));
        res->setResultado(C);
        res->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_TriangularA_clicked()
{
    try{
        if(!(A->TriangularSuperior()) && !(A->TriangularInferior()))
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz A NÃO é triangular!");
        if(A->TriangularSuperior() && !(A->TriangularInferior()))
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz A é triangular superior!");
        if(!(A->TriangularSuperior()) && A->TriangularInferior())
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz A é triangular inferior!");
        if(A->TriangularSuperior() && A->TriangularInferior())
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz A é triangular superior e inferior!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_SimetricaA_clicked()
{
    try{
        if(A->Simetrica())
            QMessageBox::about(this,"Consulta: Matriz Simétrica","A Matriz A é simétrica!");
        else
            QMessageBox::about(this,"Consulta: Matriz Simétrica","A Matriz A NÃO é simétrica!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_IdentidadeA_clicked()
{
    try{
        if(A->Identidade())
            QMessageBox::about(this,"Consulta: Matriz Identidade","A Matriz A é matriz identidade!");
        else
            QMessageBox::about(this,"Consulta: Matriz Identidade","A Matriz A NÃO é matriz identidade!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_PermutacaoA_clicked()
{
    try{
        if(A->Permutacao())
            QMessageBox::about(this,"Consulta: Matriz de Permutação","A Matriz A é matriz de permutação!");
        else
            QMessageBox::about(this,"Consulta: Matriz de Permutação","A Matriz A NÃO é matriz de permutação!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_OrtogonalA_clicked()
{
    try{
        if(A->Ortogonal())
            QMessageBox::about(this,"Consulta: Matriz Ortogonal","A Matriz A é matriz ortogonal!");
        else
            QMessageBox::about(this,"Consulta: Matriz Ortogonal","A Matriz A NÃO é matriz Ortogonal!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_MultiplicacaoPorEscalarB_clicked()
{
    try{
        DefinirEscalar *def = new DefinirEscalar;
        def->gerarMatriz(B,1,"B");
        def->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_PotenciacaoB_clicked()
{
    try{
        DefinirEscalar *def = new DefinirEscalar;
        def->gerarMatriz(B,2,"B");
        def->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_TranspostaB_clicked()
{
    try{
        C=B->Transposta();
        Resultado *res = new Resultado;
        res->setTitulo(QString("Matriz Transposta de B"));
        res->setResultado(C);
        res->show();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_TriangularB_clicked()
{
    try{
        if(!(B->TriangularSuperior()) && !(B->TriangularInferior()))
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz B NÃO é triangular!");
        if(B->TriangularSuperior() && !(B->TriangularInferior()))
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz B é triangular superior!");
        if(!(B->TriangularSuperior()) && B->TriangularInferior())
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz B é triangular inferior!");
        if(B->TriangularSuperior() && B->TriangularInferior())
            QMessageBox::about(this,"Consulta: Matriz Triangular","A Matriz B é triangular superior e inferior!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_SimetricaB_clicked()
{
    try{
        if(B->Simetrica())
            QMessageBox::about(this,"Consulta: Matriz Simétrica","A Matriz B é simétrica!");
        else
            QMessageBox::about(this,"Consulta: Matriz Simétrica","A Matriz B NÃO é simétrica!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_IdentidadeB_clicked()
{
    try{
        if(B->Identidade())
            QMessageBox::about(this,"Consulta: Matriz Identidade","A Matriz B é matriz identidade!");
        else
            QMessageBox::about(this,"Consulta: Matriz Identidade","A Matriz B NÃO é matriz identidade!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_PermutacaoB_clicked()
{
    try{
        if(B->Permutacao())
            QMessageBox::about(this,"Consulta: Matriz de Permutação","A Matriz B é matriz de permutação!");
        else
            QMessageBox::about(this,"Consulta: Matriz de Permutação","A Matriz B NÃO é matriz de permutação!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_OrtogonalB_clicked()
{
    try{
        if(B->Ortogonal())
            QMessageBox::about(this,"Consulta: Matriz Ortogonal","A Matriz B é matriz ortogonal!");
        else
            QMessageBox::about(this,"Consulta: Matriz Ortogonal","A Matriz B NÃO é matriz Ortogonal!");
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}
void MatrizUI::on_Encerrar_clicked()
{
    qApp->quit();
}

void MatrizUI::on_SalvarA_clicked()
{
    try{
        gravarA();
        enableA();
        enableOthers();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_SalvarB_clicked()
{
    try{
        gravarB();
        enableB();
        enableOthers();
    }
    catch(QString &erro){
        QMessageBox::warning(this,"Erro",erro);
    }
}

void MatrizUI::on_MatrizA_itemChanged(QTableWidgetItem *)
{
    ui->MatrizA->setToolTip("Clique no botão 'Salvar Matriz A'\npara fazer operações!");
    disableA();
    disableOthers();
}

void MatrizUI::on_MatrizB_itemChanged(QTableWidgetItem *)
{
    ui->MatrizB->setToolTip("Clique no botão 'Salvar Matriz B'\npara fazer operações!");
    disableB();
    disableOthers();
}

bool MatrizUI::eventFilter(QObject *editor, QEvent *event)
{
    if (editor == ui->MatrizA) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
                if(ui->MatrizA->currentColumn() == ui->MatrizA->columnCount()-1){
                    if(ui->MatrizA->currentRow() == ui->MatrizA->rowCount()-1) ui->MatrizA->setCurrentCell(0,0);
                    else ui->MatrizA->setCurrentCell(ui->MatrizA->currentRow()+1,0);
                }else
                    ui->MatrizA->setCurrentCell(ui->MatrizA->currentRow(),ui->MatrizA->currentColumn()+1);
                return true;
            }else return false;
        }else return false;
    } else {
        if (editor == ui->MatrizB) {
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return){
                    if(ui->MatrizB->currentColumn() == ui->MatrizB->columnCount()-1){
                        if(ui->MatrizB->currentRow() == ui->MatrizB->rowCount()-1) ui->MatrizB->setCurrentCell(0,0);
                        else ui->MatrizB->setCurrentCell(ui->MatrizB->currentRow()+1,0);
                    }else
                        ui->MatrizB->setCurrentCell(ui->MatrizB->currentRow(),ui->MatrizB->currentColumn()+1);
                    return true;
                }else return false;
            }else return false;
        }else{
            // pass the event on to the parent class
            return QMainWindow::eventFilter(editor, event);
        }
    }
}
