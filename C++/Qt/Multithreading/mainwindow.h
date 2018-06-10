#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "thread.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include <QWidget>
typedef vector<vector<int>> ciclo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void tirarVirgula(string &aux);
    void lerArquivo();
    bool verificaBloqueio(Thread &aux);
    ciclo *bloqueado(int qtdFilas, int time);
    ciclo *intercalado(int qtdFilas,int time);
    ciclo *SMT(int qtdFilas,int time);
    bool terminou(bool *aux);
    ciclo **multicore(int qtdCores, int qtdFilas, int time);
    void atualizarBloqueado(int tempo, int qtdFilas);
    void atualizarIntercalado(int tempo, int qtdFilas);
    void atualizarSMT(int tempo, int qtdFilas);
    void atualizarMultiCore(int tempo, int qtdFilas, int qtdCores);

private slots:
    void on_executar_clicked();

private:
    Ui::MainWindow *ui;
    deque<Thread> ordem;
};

#endif // MAINWINDOW_H
