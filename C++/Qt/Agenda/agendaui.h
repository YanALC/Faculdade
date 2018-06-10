#ifndef AGENDAUI_H
#define AGENDAUI_H
#include <QMainWindow>
#include <QMessageBox>
#include "contato.h"

namespace Ui {
class Agenda;
}

class Agenda : public QMainWindow
{
    Q_OBJECT

public:
    Agenda(bool editAgenda, string &autor, QWidget *parent = 0);
    ~Agenda();
    void setPtAgenda(Lista<Contato> *aux);

private slots:
    void on_AdicionarContato_clicked();

    void on_EditarContato_clicked();

    void on_RemoverContato_clicked();

    void on_ListaTudo_clicked();

    void on_ListaDeContatos_itemDoubleClicked();

    void on_Sair_clicked();

    void on_Salvar_clicked();

private:
    Ui::Agenda *ui;
    Lista<Contato> *agenda = new Lista<Contato>();
    int opContato;
    bool edit;
    string Autor;
};

#endif // AGENDAUI_H
