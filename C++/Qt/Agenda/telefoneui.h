#ifndef TELEFONEUI_H
#define TELEFONEUI_H
#include "contatoui.h"
#include <QDialog>

namespace Ui {
class TelefoneUI;
}

class TelefoneUI : public QDialog
{
    Q_OBJECT

public:
    explicit TelefoneUI(int op,QWidget *parent = 0);
    ~TelefoneUI();
    void setPtTelefone(Telefone *aux);
    void editarObjeto(Telefone *aux);

private slots:
    void on_OK_clicked();

    void on_Cancelar_clicked();

private:
    Ui::TelefoneUI *ui;
    Telefone *ptTelefone = new Telefone;
    int opcao;
};

#endif // TELEFONEUI_H
