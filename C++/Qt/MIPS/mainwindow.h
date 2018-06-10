#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QWidget>
#include <QMainWindow>
#include<ciclo.h>
#include<QString>
#include<QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void lerArquivo();
    bool DPforwarding(vector<int> *atual, instrucao &verificar);
    bool verificarDependencia(vector<int> &exAtual, instrucao &verificar);
    void writeBack(vector<ciclo> & cicle,int qtdWB, int numeroCiclo,int qtdEX);
    void writeBackInIn(vector<ciclo> & cicle,int qtdWB, int numeroCiclo,int qtdEX);
    void executar(vector<ciclo> & cicle,int qtdEX, int qtdID, int numeroCiclo);
    void executarInIn(vector<ciclo> & cicle,int qtdEX, int qtdID,int numeroCiclo);
    void instructionDecode(int qtdID,int qtdIF,vector<ciclo> & cicle,int numeroCiclo);
    void instructionFetch(int qtdIF,int qtdID,vector<ciclo> & cicle,int numeroCiclo,int &parou);
    void escalonadorDependencias(instrucao inst, int *visitados);
    void escalonador();
    bool find(vector<int> & procurar, int Instrucao);
    bool terminou();
    bool tanoWb(vector<int> &wb, int instrucao);
    void atualizarTabelasInIn(int linhas, int qtdIF, int qtdEX, int qtdWB);
    void atualizarTabelasInOut(int linhas, int qtdIF, int qtdEX, int qtdWB);
    void atualizarTabelasOutOut(int linhas, int qtdIF, int qtdEX, int qtdWB);

private slots:
    void on_Processar_clicked();

private:
    Ui::MainWindow *ui;
    vector<instrucao> ordem;
    bool forwarding;
};

#endif // MAINWINDOW_H
