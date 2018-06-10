#ifndef TELADEOPCOES_H
#define TELADEOPCOES_H
#include "agendaui.h"
#include <QWidget>

namespace Ui {
class TelaDeOpcoes;
}

class TelaDeOpcoes : public QWidget
{
    Q_OBJECT

public:
    explicit TelaDeOpcoes(QWidget *parent = 0);
    ~TelaDeOpcoes();

private slots:
    void on_AbrirAgenda_clicked();

    void on_CriarNovaAgenda_clicked();

    void on_Sair_clicked();

private:
    Ui::TelaDeOpcoes *ui;
    Lista<Contato> *agenda;
};

#endif // TELADEOPCOES_H
