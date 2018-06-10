#ifndef ENDERECOUI_H
#define ENDERECOUI_H
#include "contatoui.h"
#include <QDialog>

namespace Ui {
class EnderecoUI;
}

class EnderecoUI : public QDialog
{
    Q_OBJECT

public:
    explicit EnderecoUI(int op, QWidget *parent = 0);
    ~EnderecoUI();
    void setPtEndereco(Endereco *aux);
    void editarObjeto(Endereco *aux);

private slots:

    void on_OK_clicked();

    void on_Cancelar_clicked();

private:
    Ui::EnderecoUI *ui;
    Endereco *ptEndereco = new Endereco;
    int opcao;
};

#endif // ENDERECOUI_H
