#ifndef LISTARAGENDAS_H
#define LISTARAGENDAS_H
#include <QListWidget>
#include <QDialog>

namespace Ui {
class ListarAgendas;
}

class ListarAgendas : public QDialog
{
    Q_OBJECT

public:
    explicit ListarAgendas(QWidget *parent = 0);
    ~ListarAgendas();

private slots:
    void on_AbrirAgenda_clicked();

    void on_Cancelar_clicked();

    void on_Remover_clicked();

private:
    Ui::ListarAgendas *ui;
};

#endif // LISTARAGENDAS_H
