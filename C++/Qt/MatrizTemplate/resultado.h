#ifndef RESULTADO_H
#define RESULTADO_H
#include <QTableWidget>
#include <QWidget>
#include <QString>
#include "matriz.h"

namespace Ui {
class Resultado;
}

class Resultado : public QWidget
{
    Q_OBJECT

public:
    explicit Resultado(QWidget *parent = 0);
    ~Resultado();
    void setResultado(TP2::Matriz<double> *mat);
    void setTitulo(QString par);
private slots:

    void on_Fechar_clicked();

private:
    Ui::Resultado *ui;
};

#endif // RESULTADO_H
