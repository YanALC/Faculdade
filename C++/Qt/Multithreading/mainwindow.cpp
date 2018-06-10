#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tirarVirgula(string &aux)
{
    for(unsigned j = 0;j<aux.size();++j)
        if(aux[j]==';'||aux[j]==',') aux[j]=' ';
}

void MainWindow::lerArquivo()
{
    try{
        int dp;
        fstream a("thread.txt",ios_base::in); // abre o arquivo para a leitura
        string aux;                         // string auxiliar para ler o arquivo
        while(!a.eof()){
            Thread thd;
            getline(a,aux);					// pegar uma linha do arquivo
            tirarVirgula(aux);				// tirar virgula
            stringstream fluxo(aux);       // fluxo de string
            fluxo>>thd.identificacao>>thd.tempoTotal;
            while(fluxo>>dp && dp)thd.paradas.insert(dp);
            ordem.push_back(thd);
        }
        a.close();  // fechar o arquivo
    }catch(...){
        QMessageBox::warning(this,"Erro","Arquivo não foi aberto!");
    }
}

bool MainWindow::verificaBloqueio(Thread &aux)
{
    if(aux.paradas.empty()) return false;
    if((*aux.paradas.begin())==(aux.tempoAtual))
    {
        aux.paradas.erase(aux.paradas.begin());
        return true;
    }
    return false;
}

ciclo *MainWindow::bloqueado(int qtdFilas, int time)
{
    deque<Thread> copia = ordem;
    ciclo * tabela  = new ciclo;
    vector<int> linha;
    linha.reserve(qtdFilas);
    int i;
    while(!copia.empty())
    {
        i=0;
        while(i < qtdFilas && !copia.empty())
        {
            if(!verificaBloqueio(copia[0]))
            {
                copia[0].tempoAtual+=time;
                linha.push_back(copia[0].identificacao);
                i++;
                if(copia[0].tempoAtual>=copia[0].tempoTotal){
                    copia.pop_front();
                    while(i<qtdFilas){
                        linha.push_back(-1);
                        i++;
                    }
                }
            }else{
                while(i<qtdFilas){
                    linha.push_back(-1);
                    i++;
                }
            }
        }
        tabela->push_back(linha);
        linha.clear();
    }
    return tabela;
}

ciclo *MainWindow::intercalado(int qtdFilas, int time)
{
    deque<Thread> copia = ordem;
    ciclo * tabela  = new ciclo;
    vector<int> linha;
    linha.reserve(qtdFilas);
    while(!copia.empty())
    {
        for(int i=0;(i < qtdFilas && !copia.empty());i++)
        {
            if(!verificaBloqueio(copia[0]))
            {
                copia[0].tempoAtual+=time;
                linha.push_back(copia[0].identificacao);
                if(copia[0].tempoAtual>=copia[0].tempoTotal){
                    while(i<qtdFilas){
                        linha.push_back(-1);
                        i++;
                    }
                }
            }else
            {
                while(i<qtdFilas){
                    linha.push_back(-1);
                    i++;
                }
            }
        }
        if(copia[0].tempoAtual<copia[0].tempoTotal){
            copia.push_back(copia[0]);
            copia.pop_front();
        }else copia.pop_front();
        tabela->push_back(linha);
        linha.clear();
    }
    return tabela;
}

ciclo *MainWindow::SMT(int qtdFilas, int time)
{
    ciclo *tabela = new ciclo;
    vector<int> linha;
    set<int> bloqueio;
    set<int>::iterator it;
    linha.reserve(qtdFilas);
    deque<Thread> copia = ordem;
    int i;
    while(!copia.empty())
    {
        i=0;
        while(i < qtdFilas && !copia.empty())
        {
            if(!verificaBloqueio(copia[0])&&(bloqueio.find(copia[0].identificacao)==bloqueio.end()))
            {
                copia[0].tempoAtual+=time;
                linha.push_back(copia[0].identificacao);
                if(copia[0].tempoAtual<copia[0].tempoTotal)
                {
                    copia.push_back(copia[0]);
                }
                copia.pop_front();
                i++;
            }else
            {
                bloqueio.insert(copia[0].identificacao);
                copia.push_back(copia[0]);
                copia.pop_front();
                if(bloqueio.size()==copia.size())
                {
                    linha.push_back(-1);
                    i++;
                }
            }
        }
        bloqueio.clear();
        tabela->push_back(linha);
        linha.clear();
    }(*tabela)[tabela->size()-1].push_back(-1);
    return tabela;
}

bool MainWindow::terminou(bool *aux)
{
    for(uint i=0; i<sizeof(aux); i++){
        if(aux[i]==false) return false;
    }return true;
}

ciclo **MainWindow::multicore(int qtdCores, int qtdFilas, int time)
{
    ciclo **tabela = new ciclo *[qtdCores];
    for(int i=0; i<qtdCores; i++)
        tabela[i] = new ciclo;
    vector<int> linha;
    linha.reserve(qtdFilas);
    deque<Thread> copia = ordem;
    int i;
    uint core;
    bool *monitor;
    monitor = (bool *) malloc(copia.size());
    while(!terminou(monitor))
    {
        core=0;
        while(core<qtdCores)
        {
            i=0;
            while(i < qtdFilas)
            {
                if(copia[core].tempoAtual>=copia[core].tempoTotal)
                {
                    while(i<qtdFilas){
                        linha.push_back(-1);
                        i++;
                    }break;
                }else
                {
                    if(!verificaBloqueio(copia[core]))
                    {
                        copia[core].tempoAtual+=time;
                        linha.push_back(copia[core].identificacao);
                        i++;
                        if(copia[core].tempoAtual>=copia[core].tempoTotal)
                        {
                            monitor[(copia[core].identificacao)-1] = true;
                            if(copia.size()>qtdCores)
                            {
                                deque<Thread>::iterator it = std::find(copia.begin(),copia.end(),copia[qtdCores]);
                                copia[core] = copia[qtdCores];
                                copia.erase(it);
                            }
                            while(i<qtdFilas){
                                linha.push_back(-1);
                                i++;
                            }
                        }
                    }else
                    {
                        while(i<qtdFilas){
                            linha.push_back(-1);
                            i++;
                        }break;
                    }
                }
            }
            (tabela[core])->push_back(linha);
            linha.clear();
            core++;
        }
    }
    return tabela;
}

void imprimir(ciclo *aux)
{
    for(uint j=0;j<aux->size();j++)
    {
        for(uint i=0; i<(*aux)[j].size();i++)
        {
            cout<<(*aux)[j][i]<<" ";
        }
        cout<<endl;
    }
}

void MainWindow::atualizarBloqueado(int tempo, int qtdFilas)
{
    ciclo *aux = bloqueado(qtdFilas,tempo);
    ui->bloqueado->clear();
    ui->bloqueado->setRowCount(aux->size());
    ui->bloqueado->setColumnCount(qtdFilas);
    ui->bloqueado->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->bloqueado->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(uint i=0; i<aux->size(); i++)
    {
        if(!(*aux)[i].empty()){
            for(uint j=0; j<qtdFilas;j++)
            {
                if((*aux)[i][j])
                    if((*aux)[i][j]!=-1)
                        ui->bloqueado->setItem(i,j,new QTableWidgetItem(QString::number((*aux)[i][j])));
            }
        }
    }
    free(aux);
}

void MainWindow::atualizarIntercalado(int tempo, int qtdFilas)
{
    ciclo *aux = intercalado(qtdFilas,tempo);
    ui->intercalado->clear();
    ui->intercalado->setRowCount(aux->size());
    ui->intercalado->setColumnCount(qtdFilas);
    ui->intercalado->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->intercalado->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(uint i=0; i<aux->size(); i++)
    {
        if(!(*aux)[i].empty()){
            for(uint j=0; j<qtdFilas;j++)
            {
                if((*aux)[i][j])
                    if((*aux)[i][j]!=-1)
                        ui->intercalado->setItem(i,j,new QTableWidgetItem(QString::number((*aux)[i][j])));
            }
        }
    }
    free(aux);
}

void MainWindow::atualizarSMT(int tempo, int qtdFilas)
{
    ciclo *aux = SMT(qtdFilas,tempo);
    ui->SMT->clear();
    ui->SMT->setRowCount(aux->size());
    ui->SMT->setColumnCount(qtdFilas);
    ui->SMT->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SMT->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(uint i=0; i<aux->size(); i++)
    {
        if(!(*aux)[i].empty()){
            for(uint j=0; j<qtdFilas;j++)
            {
                if((*aux)[i][j])
                    if((*aux)[i][j]!=-1)
                        ui->SMT->setItem(i,j,new QTableWidgetItem(QString::number((*aux)[i][j])));
            }
        }
    }free(aux);
}

void MainWindow::atualizarMultiCore(int tempo, int qtdFilas, int qtdCores)
{
    ciclo **aux = multicore(qtdCores,qtdFilas,tempo);
    int linhas = aux[0]->size();
    ui->multicore->clear();
    ui->multicore->setRowCount(linhas);
    ui->multicore->setColumnCount((qtdFilas*qtdCores)+qtdCores-1);
    ui->multicore->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->multicore->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(uint c=0; c<qtdCores; c++)
    {
        for(uint i=0; i<linhas; i++)
        {
            if(c>0){
                ui->multicore->setItem(i,(c*qtdFilas)+c-1,new QTableWidgetItem);
                ui->multicore->item(i,(c*qtdFilas)+c-1)->setBackgroundColor(Qt::black);
            }
            for(uint j=0; j<qtdFilas; j++){
                if(!((*(aux[c]))[i][j]==-1)){
                    ui->multicore->setItem(i,(c*qtdFilas)+j+c,new QTableWidgetItem(QString::number((*(aux[c]))[i][j])));
                }
            }
        }
    }
//    for(uint i=0; i<sizeof(aux); i++)
//        free(aux[i]);
//    free(aux);
}

void MainWindow::on_executar_clicked()
{
    lerArquivo();
    ordem.pop_back();
    atualizarBloqueado(ui->tempo->value(), ui->filas->value());
    atualizarIntercalado(ui->tempo->value(), ui->filas->value());
    atualizarSMT(ui->tempo->value(), ui->filas->value());
    atualizarMultiCore(ui->tempo->value(), ui->filas->value(), ui->cores->value());
    ordem.clear();
}
