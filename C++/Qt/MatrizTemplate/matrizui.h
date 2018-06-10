#ifndef MATRIZUI_H
#define MATRIZUI_H
#include <QMainWindow>
#include <QMessageBox>
#include "matriz.h"
#include "spinboxdelegate.h"
#include <QTableWidget>
#include <QtWidgets>

namespace Ui {
class MatrizUI;
class TableWidgets;
}
class MatrizUI: public QMainWindow
{
    Q_OBJECT
public:
    explicit MatrizUI(QWidget *parent = nullptr);
    ~MatrizUI();
    void gravarA();
    void gravarB();
    void enableA();
    void disableA();
    void enableB();
    void disableB();
    void enableOthers();
    void disableOthers();

private slots:

    void on_linhasA_valueChanged(int arg1);

    void on_colunasA_valueChanged(int arg1);

    void on_linhasB_valueChanged(int arg1);

    void on_colunasB_valueChanged(int arg1);

    void on_Adicao_clicked();

    void on_Subtracao_clicked();

    void on_Multiplicacao_clicked();

    void on_Igualdade_clicked();

    void on_MultiplicacaoPorEscalarA_clicked();

    void on_PotenciacaoA_clicked();

    void on_TranspostaA_clicked();

    void on_TriangularA_clicked();

    void on_SimetricaA_clicked();

    void on_IdentidadeA_clicked();

    void on_PermutacaoA_clicked();

    void on_OrtogonalA_clicked();

    void on_MultiplicacaoPorEscalarB_clicked();

    void on_PotenciacaoB_clicked();

    void on_TranspostaB_clicked();

    void on_TriangularB_clicked();

    void on_SimetricaB_clicked();

    void on_IdentidadeB_clicked();

    void on_PermutacaoB_clicked();

    void on_OrtogonalB_clicked();

    void on_Encerrar_clicked();

    void on_SalvarA_clicked();

    void on_SalvarB_clicked();

    void on_MatrizA_itemChanged(QTableWidgetItem *item);

    void on_MatrizB_itemChanged(QTableWidgetItem *item);

    bool eventFilter(QObject *editor, QEvent *event);

private:
    Ui::MatrizUI *ui;
    TP2::Matriz<double> *A,*B,*C;
    bool boolA=false,boolB=false;
};

#endif // MATRIZUI_H
