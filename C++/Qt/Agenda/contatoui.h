#ifndef CONTATOUI_H
#define CONTATOUI_H
#include "agendaui.h"
#include <QDialog>

namespace Ui {
class ContatoUI;
}

class ContatoUI : public QDialog
{
    Q_OBJECT

public:
    explicit ContatoUI(int op, QWidget *parent = 0);
    ~ContatoUI();
    void setPtContato(Contato *aux);
    void atualizarTabelas();
    void setHeaders();

private slots:
    void on_AdicionarTelefone_clicked();

    void on_EditarTelefone_clicked();

    void on_AdicionarEmail_clicked();

    void on_EditarEmail_clicked();

    void on_AdicionarEndereco_clicked();

    void on_AdicionarContato_clicked();

    void on_Cancelar_clicked();

    void on_RemoverTelefone_clicked();

    void on_RemoverEmail_clicked();

    void on_EditarEndereco_clicked();

    void on_RemoverEndereco_clicked();

private:
    Ui::ContatoUI *ui;
    Contato *contato = new Contato;
    Contato *ptContato = new Contato;
    int opContato;//1=Adicionar ; 2=Editar
    int op;//1=Adicionar ; 2=Editar
};

#endif // CONTATOUI_H
