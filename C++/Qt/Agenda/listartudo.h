#ifndef LISTARTUDO_H
#define LISTARTUDO_H
#include "agendaui.h"
#include <QWidget>

namespace Ui {
class ListarTudo;
}

class ListarTudo : public QWidget
{
    Q_OBJECT

public:
    explicit ListarTudo(Lista<Contato> *aux, QWidget *parent = 0);
    ~ListarTudo();

private slots:

    void on_Fechar_clicked();

private:
    Ui::ListarTudo *ui;
};

#endif // LISTARTUDO_H
