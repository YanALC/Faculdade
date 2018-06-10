#ifndef DEFINIRESCALAR_H
#define DEFINIRESCALAR_H
#include "matriz.h"
#include <QDialog>

namespace Ui {
class DefinirEscalar;
}

class DefinirEscalar : public QDialog
{
    Q_OBJECT

public:
    explicit DefinirEscalar(QWidget *parent = 0);
    ~DefinirEscalar();
    void gerarMatriz(TP2::Matriz<double> *mat, int i, QString matriz);
    //i=1: Multiplicação por escalar/i=2: Potenciação
    //A QString matriz refere-se se a operação é na matriz A ou na matriz B, para fins de mostrar na tela de resultado.

private slots:
    void on_Confirmacao_accepted();

    void on_Confirmacao_rejected();

    void on_Escalar_valueChanged(int arg1);

private:
    Ui::DefinirEscalar *ui;
    TP2::Matriz<double> *aux;
    int get_i,escalar=0;
    QString get_matriz;
};

#endif // DEFINIRESCALAR_H
