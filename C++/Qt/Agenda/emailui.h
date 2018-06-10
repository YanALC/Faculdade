#ifndef EMAILUI_H
#define EMAILUI_H
#include "contatoui.h"
#include <QDialog>

namespace Ui {
class EmailUI;
}

class EmailUI : public QDialog
{
    Q_OBJECT

public:
    explicit EmailUI(int op, QWidget *parent = 0);
    ~EmailUI();
    void setPtEmail(Email *aux);
    void editarObjeto(Email *aux);

private slots:
    void on_OK_clicked();

    void on_Cancelar_clicked();

private:
    Ui::EmailUI *ui;
    Email *ptEmail = new Email;
    int opcao;
};

#endif // EMAILUI_H
