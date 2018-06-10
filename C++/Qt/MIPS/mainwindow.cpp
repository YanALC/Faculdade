#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    forwarding=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void tirarVirgula(string &auxiliar)
{
    for(unsigned j = 0;j<auxiliar.size();++j){ // colocar espaço no lugar de ponto e virgula e virgula
        if(auxiliar[j]==';'||auxiliar[j]==',') auxiliar[j]=' ';
    }
}

void MainWindow::lerArquivo()
{
    try{
        int dp;
        fstream a("instrucao.txt",ios_base::in); // abri o arquivo para a leitura
        string aux;                         // string auxiliar para ler o arquivo
        while(!a.eof()){
            instrucao inst;
            getline(a,aux);					// pegar uma linha do arquivo
            tirarVirgula(aux);				// tirar virgula
            stringstream fluxo(aux);       // fluxo de string
            fluxo>>inst.id>>inst.numeroClock;
            while(fluxo>>dp)inst.dependencias.insert(dp);
            ordem.push_back(inst);
        }
        a.close();  // fechar o arquivo
    }catch(...){
        QMessageBox::warning(this,"Erro","Arquivo não foi aberto!");
    }
}

bool MainWindow::DPforwarding(vector<int> *atual,instrucao &verificar)
{
    int dp=verificar.dependencias.size()-1;
    for(set<int>::iterator it=verificar.dependencias.begin();it!=verificar.dependencias.end();it++){
        for(uint i=0;i<atual->size();i++){
            if((*atual)[i]==(*it)){
                dp--;
            }
        }
    }
    if(dp>-1) return false;
    else return true;
}

bool MainWindow::verificarDependencia(vector<int> &exAtual,instrucao &verificar)
{
    uint n = exAtual.size(); // tamanho do vetor ex atual , vamos percorrer ele e verificar se a instrução pode ser colocada
    set<int>::iterator it;
    for(uint i = 0 ;i<n;i++){
        if(exAtual[i]!=-1) {// significa que contem instrução no EX
            if(!verificar.dependencias.empty()){
                it = verificar.dependencias.find((exAtual[i]));
                if((*it) != 0)
                    return true;
            }
        }
    }
    return false;
}

void MainWindow::writeBack(vector<ciclo> &cicle,int qtdWB,int numeroCiclo,int qtdEX)
{
    int  i,j=0; // contadores
    vector<int> exAnterior = cicle[(numeroCiclo-1)].EX; // pegando o vetor do ciclo anterior
    vector<instrucao>::iterator it;
    for( i = 0 ; i<qtdEX&&j<qtdWB;++i){
        if(exAnterior[i]!=-1){ // tem alguma coisa executando
            it = (std::find(ordem.begin(),ordem.end(),*(new instrucao(exAnterior[i]))));
            it->numeroClock-=1;
            if(it->numeroClock==0){ // verifica se pode ser escrita a instrução que estava sendo executada no ciclo anterior
                cicle[numeroCiclo].WB[j]=exAnterior[i];
                j++;// passar para proxima posição do wb
            }
        }
    }
}

void MainWindow::writeBackInIn(vector<ciclo> &cicle,int qtdWB,int numeroCiclo,int qtdEX)
{
     set<int> inst ;
     set<int>::iterator it;
     int j =0;
     for(int i = 0;i<qtdEX;i++){
         if(cicle[(numeroCiclo-1)].EX[i]!=-1)inst.insert((cicle[(numeroCiclo-1)].EX[i]));
     }
     for(it = inst.begin();it!=inst.end();++it){
         if(ordem[((*it)-1)].numeroClock>0){ordem[((*it)-1)].numeroClock--;}
     }
    for(j=0;j<qtdWB;)
    {
        if(!inst.empty()){
             it = inst.begin();
             //ordem[((*it)-1)].numeroClock--;
             if(ordem[((*it)-1)].numeroClock==0){
                 cicle[numeroCiclo].WB[j]=(*it);
                 inst.erase(it);
                 j++;
             }else{
                 j = qtdWB;
             }
        }
        else{
            j = qtdWB;
        }
    }
}

void MainWindow::executar(vector<ciclo> &cicle,int qtdEX,int qtdID,int numeroCiclo)
{
    int i,j =0;// j  é o indice do ciclo atual
    instrucao aux;
    vector<int> exAnterior = cicle[(numeroCiclo-1)].EX; // ciclo anterior.Verificar se tem istrução para terminar
    for(i=0;i<qtdEX;i++){
        if(exAnterior[i]!=-1){// tem alguma instrução no ciclo anterior
            aux = (*(std::find(ordem.begin(),ordem.end(),*(new instrucao(exAnterior[i])))));
            if(aux.numeroClock != 0 || (!tanoWb(cicle[numeroCiclo].WB,exAnterior[i]))){// quer dizer que a instrução não terminou
                cicle[numeroCiclo].EX[j]=exAnterior[i];
                j++;
            }
        }
    }
    vector<int> idAnterior = cicle[numeroCiclo-1].ID;  // pegando o Instruction decode do ciclo anterior
    vector<int> *wb = new vector<int>;
    if(!forwarding){
        for(int i=0;i<numeroCiclo;i++){
            for(int k=0;k<cicle[0].WB.size();k++){
                if(cicle[i].WB[k]!=-1)
                    wb->push_back(cicle[i].WB[k]);
            }
        }
    }else free(wb);
    for(i=0;j<qtdEX&&i<qtdID;i++){
        if(idAnterior[i]!=-1){
            aux = (*(std::find(ordem.begin(),ordem.end(),*(new instrucao(idAnterior[i])))));
            if(forwarding){
                if(!verificarDependencia(cicle[numeroCiclo].EX,aux)){ // se der falso é porque não tem dependencia insere
                    cicle[numeroCiclo].EX[j] = idAnterior[i];	// coloca a instrução no ciclo atual
                    j++;// passa para proxima posição
                }
            }else if(DPforwarding(wb,aux)){
                if(!verificarDependencia(cicle[numeroCiclo].EX,aux)){ // se der falso é porque não tem dependencia insere
                    cicle[numeroCiclo].EX[j] = idAnterior[i];	// coloca a instrução no ciclo atual
                    j++;// passa para proxima posição
                }
            }
        }
    }free(wb);
}

void MainWindow::executarInIn(vector<ciclo> &cicle, int qtdEX, int qtdID, int numeroCiclo)
{
    int i,j =0;// j  é o indice do ciclo atual
    vector<int> exAnterior = cicle[(numeroCiclo-1)].EX; // ciclo anterior.Verificar se tem istrução para terminar
    for(i=0;i<qtdEX;i++){
        if(exAnterior[i]!=-1){// tem alguma instrução no ciclo anterior
            if(ordem[(exAnterior[i]-1)].numeroClock!=0){// quer dizer que a instrução não terminou
                cicle[numeroCiclo].EX[j]=exAnterior[i];
                j++;
            }
        }
    }
    vector<int> idAnterior = cicle[(numeroCiclo-1)].ID;  // pegando o Instruction decode do ciclo anterior
    vector<int> *wb = new vector<int>;
    if(!forwarding){
        for(int i=0;i<numeroCiclo;i++){
            for(int k=0;k<cicle[0].WB.size();k++){
                if(cicle[i].WB[k]!=-1)
                    wb->push_back(cicle[i].WB[k]);
            }
        }
    }else free(wb);
    for(i=0;j<qtdEX&&i<qtdID;i++){
        if(forwarding){
            if(!(verificarDependencia(cicle[numeroCiclo].EX,ordem[(idAnterior[i]-1)]))){
                if(cicle[numeroCiclo].EX[j] == -1){
                    cicle[numeroCiclo].EX[j] = idAnterior[i];	// coloca a instrução no ciclo atual
                }
                else{
                    j++;
                    if(cicle[numeroCiclo].EX[j-1] < idAnterior[i] && ordem[j-1].numeroClock==0){
                        cicle[numeroCiclo].EX[j] = idAnterior[i];
                    }
                }
            }i=qtdID+1;
        }else if(idAnterior[i]!=-1){
            if(DPforwarding(wb,ordem[(idAnterior[i]-1)])){
                if(!(verificarDependencia(cicle[numeroCiclo].EX,ordem[(idAnterior[i]-1)]))){
                    if(cicle[numeroCiclo].EX[j] == -1){
                        cicle[numeroCiclo].EX[j] = idAnterior[i];	// coloca a instrução no ciclo atual
                    }
                    else{
                        j++;
                        if(cicle[numeroCiclo].EX[j-1] < idAnterior[i] && ordem[j-1].numeroClock==0){
                            cicle[numeroCiclo].EX[j] = idAnterior[i];
                        }
                    }
                }i=qtdID+1;
            }
        }
    }free(wb);
}

void MainWindow::instructionDecode(int qtdID,int qtdIF,vector<ciclo> &cicle,int numeroCiclo)
{
    vector<int> exAtual = cicle[numeroCiclo].EX; // pegando o execultar do cliclo atual
    vector<int> idAnterior = cicle[(numeroCiclo-1)].ID; // Instruction decode do ciclo anterior
    vector<int> ifAnterior = cicle[(numeroCiclo-1)].IF;
    int i,j=0;
    for(i = 0 ; i<qtdID&&j<qtdID;i++){ // verificando se a instrução anterior esta no EX atual
        if(idAnterior[i]!=-1){
            if(!find(exAtual,idAnterior[i])){ // se não estiver no EX então ele esperou
                cicle[numeroCiclo].ID[j] = idAnterior[i];
                j++;
            }
        }
    }
    for(i=0;i<qtdIF&&j<qtdID;i++){
        if(ifAnterior[i]!=-1){ // tem alguma instrução para passar para decode
            cicle[numeroCiclo].ID[j] = ifAnterior[i];
            j++;
        }
    }
}

void MainWindow::instructionFetch(int qtdIF,int qtdID,vector<ciclo> &cicle,int numeroCiclo,int &parou)
{
    vector<int> idAtual = cicle[numeroCiclo].ID; // verificar se as instruções do ciclo passado esta no ID
    vector<int> ifAnterior = cicle[(numeroCiclo-1)].IF;
    int tamOrdem = ordem.size();
    int i,j=0;
    for(i = 0;i<qtdIF&&j<qtdID;i++){
        if(ifAnterior[i]!=-1){
            if(!find(idAtual,ifAnterior[i])){ // verificando se as isntrucoes do IF anterior esta no ID atual
                cicle[numeroCiclo].IF[j] = ifAnterior[i];
                j++;
            }
        }
    }
    instrucao aux;
    for(;j<qtdIF&&(parou<tamOrdem);j++,parou++){ // parou é uma variavel para saber qual foi a ultima instrução buscada
        cicle[numeroCiclo].IF[j] = ordem[parou].id;
    }
}

void MainWindow::escalonadorDependencias(instrucao inst, int *visitados)
{
    if(!inst.dependencias.empty() && visitados[(inst.id)-1]==0){
        visitados[(inst.id)-1]=1;
        for(set<int>::iterator it=inst.dependencias.begin();it!=(inst.dependencias.end());it++){
            vector<instrucao>::iterator it2 = (std::find(ordem.begin(),ordem.end(),inst));
            if(it2!=ordem.begin())it2--;
            vector<instrucao>::iterator inst2 = std::find(ordem.begin(),ordem.end(),*(new instrucao(*it)));
            if(it2!=ordem.begin())
                if(!forwarding && (*inst2).numeroClock>=(*(it2-1)).numeroClock)it2--;
            if((*inst2).id==*it){
                instrucao aux = *inst2;
                ordem.erase(inst2);
                ordem.insert(it2,aux);
                escalonadorDependencias(aux,visitados);
            }
        }
    }
}

void MainWindow::escalonador()
{
    uint j,lastswap;
    for(uint bubble=ordem.size();bubble!=0;bubble=lastswap){
        lastswap=0;
        for(uint i=1;i<bubble;i++){
            j=i-1;
            if(ordem[j].numeroClock < ordem[i].numeroClock){
                swap(ordem[i],ordem[j]);
                lastswap=i;
            }
        }
    }

    for(uint i=0;i<ordem.size();i++){
        int *visitados = (int *) calloc(ordem.size(),sizeof(int));
        escalonadorDependencias(ordem[i],visitados);
    }
    for(int i=0;i<ordem.size();i++) qDebug()<<ordem[i].id<<"\t"<<ordem[i].numeroClock<<endl;
}

bool MainWindow::find(vector<int> &procurar,int Instrucao)
{
    for(uint i=0;i<procurar.size();i++){
        if(procurar[i]==Instrucao)return true;// achou
    }
    return false;
}

bool MainWindow::terminou()
{
    int aux=0;
    for(unsigned i=0;i<ordem.size();i++){
        if(ordem[i].numeroClock<1)
            aux++;
    }
    return(aux==ordem.size());
}

void MainWindow::atualizarTabelasInIn(int linhas, int qtdIF, int qtdEX, int qtdWB)
{
    ui->InInIF->setRowCount(linhas);
    ui->InInIF->setColumnCount(qtdIF);
    ui->InInIF->gridStyle();
    ui->InInIF->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InInIF->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInIF->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInIF->clear();
    ui->InInID->setRowCount(linhas);
    ui->InInID->setColumnCount(qtdIF);
    ui->InInID->gridStyle();
    ui->InInID->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InInID->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInID->clear();
    ui->InInEX->setRowCount(linhas);
    ui->InInEX->setColumnCount(qtdEX);
    ui->InInEX->gridStyle();
    ui->InInEX->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InInEX->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInEX->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInEX->clear();
    ui->InInWB->setRowCount(linhas);
    ui->InInWB->setColumnCount(qtdWB);
    ui->InInWB->gridStyle();
    ui->InInWB->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InInWB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInWB->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InInWB->clear();
}

void MainWindow::atualizarTabelasInOut(int linhas, int qtdIF, int qtdEX, int qtdWB)
{
    ui->InOutIF->setRowCount(linhas);
    ui->InOutIF->setColumnCount(qtdIF);
    ui->InOutIF->gridStyle();
    ui->InOutIF->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InOutIF->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutIF->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutIF->clear();
    ui->InOutID->setRowCount(linhas);
    ui->InOutID->setColumnCount(qtdIF);
    ui->InOutID->gridStyle();
    ui->InOutID->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InOutID->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutID->clear();
    ui->InOutEX->setRowCount(linhas);
    ui->InOutEX->setColumnCount(qtdEX);
    ui->InOutEX->gridStyle();
    ui->InOutEX->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InOutEX->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutEX->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutEX->clear();
    ui->InOutWB->setRowCount(linhas);
    ui->InOutWB->setColumnCount(qtdWB);
    ui->InOutWB->gridStyle();
    ui->InOutWB->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->InOutWB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutWB->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->InOutWB->clear();
}

void MainWindow::atualizarTabelasOutOut(int linhas, int qtdIF, int qtdEX, int qtdWB)
{
    ui->OutOutIF->setRowCount(linhas);
    ui->OutOutIF->setColumnCount(qtdIF);
    ui->OutOutIF->gridStyle();
    ui->OutOutIF->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->OutOutIF->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutIF->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutIF->clear();
    ui->OutOutID->setRowCount(linhas);
    ui->OutOutID->setColumnCount(qtdIF);
    ui->OutOutID->gridStyle();
    ui->OutOutID->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->OutOutID->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutID->clear();
    ui->OutOutEX->setRowCount(linhas);
    ui->OutOutEX->setColumnCount(qtdEX);
    ui->OutOutEX->gridStyle();
    ui->OutOutEX->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->OutOutEX->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutEX->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutEX->clear();
    ui->OutOutWB->setRowCount(linhas);
    ui->OutOutWB->setColumnCount(qtdWB);
    ui->OutOutWB->gridStyle();
    ui->OutOutWB->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->OutOutWB->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutWB->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->OutOutWB->clear();
}

bool MainWindow::tanoWb(vector<int> &wb, int instrucao)
{
    for(uint i=0;i<wb.size();i++){
        if(wb[i]==instrucao)return true;
    }
    return false;
}

void MainWindow::on_Processar_clicked()
{
    forwarding = ui->forwarding->isChecked();
    qDebug()<<forwarding<<endl;
    ordem.clear();
    //IN-IN
    lerArquivo();
    int qtdIF=ui->qtdIF->value(),
            qtdID=ui->qtdIF->value(),
            qtdEX=ui->qtdEX->value(),
            qtdWB=ui->qtdWB->value(),
            cicloatual=1,parou=0;
    vector<ciclo> tabela;
    tabela.reserve(100);
    ciclo primeiro(qtdIF,qtdID,qtdEX,qtdWB);
    tabela.push_back(primeiro);
    do{
        ciclo auxiliar(qtdIF,qtdID,qtdEX,qtdWB);
        tabela.push_back(auxiliar);
        writeBackInIn(tabela,qtdWB,cicloatual,qtdEX);
        executar(tabela,qtdEX,qtdID,cicloatual);
        instructionDecode(qtdID,qtdIF,tabela,cicloatual);
        instructionFetch(qtdIF,qtdID,tabela,cicloatual,parou);
        ++cicloatual;
    }while(!terminou());
    tabela.erase(tabela.begin());
    atualizarTabelasInIn(tabela.size(),qtdIF,qtdEX,qtdWB);
    for(uint i = 0; i < tabela.size(); i++)
    {
        for(uint j = 0; j < tabela[i].IF.size(); j++){
            if(!(tabela[i].IF[j] == -1))
                ui->InInIF->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].IF[j])));
        }
        for(uint j = 0; j < tabela[i].ID.size(); j++){
            if(!(tabela[i].ID[j] == -1))
                ui->InInID->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].ID[j])));
        }
        for(uint j = 0; j < tabela[i].EX.size(); j++){
            if(!(tabela[i].EX[j] == -1))
                ui->InInEX->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].EX[j])));
        }
        for(uint j = 0; j < tabela[i].WB.size(); j++){
            if(!(tabela[i].WB[j] == -1))
                ui->InInWB->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].WB[j])));
        }
    }
    tabela.clear();
    cicloatual=1;
    parou=0;
    //IN-OUT
    ordem.clear();
    lerArquivo();
    tabela.reserve(100);
    tabela.push_back(primeiro);
    do{
        ciclo auxiliar(qtdIF,qtdID,qtdEX,qtdWB);
        tabela.push_back(auxiliar);
        writeBack(tabela,qtdWB,cicloatual,qtdEX);
        executar(tabela,qtdEX,qtdID,cicloatual);
        instructionDecode(qtdID,qtdIF,tabela,cicloatual);
        instructionFetch(qtdIF,qtdID,tabela,cicloatual,parou);
        ++cicloatual;
    }while(!terminou());
    tabela.erase(tabela.begin());
    atualizarTabelasInOut(tabela.size(),qtdIF,qtdEX,qtdWB);
    for(uint i = 0; i < tabela.size(); i++)
    {
        for(uint j = 0; j < tabela[i].IF.size(); j++){
            if(!(tabela[i].IF[j] == -1))
                ui->InOutIF->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].IF[j])));
        }
        for(uint j = 0; j < tabela[i].ID.size(); j++){
            if(!(tabela[i].ID[j] == -1))
                ui->InOutID->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].ID[j])));
        }
        for(uint j = 0; j < tabela[i].EX.size(); j++){
            if(!(tabela[i].EX[j] == -1))
                ui->InOutEX->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].EX[j])));
        }
        for(uint j = 0; j < tabela[i].WB.size(); j++){
            if(!(tabela[i].WB[j] == -1))
                ui->InOutWB->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].WB[j])));
        }
    }
    tabela.clear();
    cicloatual=1;
    parou=0;
    //OUT-OUT
    ordem.clear();
    lerArquivo();
    escalonador();
    tabela.reserve(100);
    tabela.push_back(primeiro);
    do{
        ciclo auxiliar(qtdIF,qtdID,qtdEX,qtdWB);
        tabela.push_back(auxiliar);
        writeBack(tabela,qtdWB,cicloatual,qtdEX);
        executar(tabela,qtdEX,qtdID,cicloatual);
        instructionDecode(qtdID,qtdIF,tabela,cicloatual);
        instructionFetch(qtdIF,qtdID,tabela,cicloatual,parou);
        ++cicloatual;
    }while(!terminou());
    tabela.erase(tabela.begin());
    atualizarTabelasOutOut(tabela.size(),qtdIF,qtdEX,qtdWB);
    for(uint i = 0; i < tabela.size(); i++)
    {
        for(uint j = 0; j < tabela[i].IF.size(); j++){
            if(!(tabela[i].IF[j] == -1))
                ui->OutOutIF->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].IF[j])));
        }
        for(uint j = 0; j < tabela[i].ID.size(); j++){
            if(!(tabela[i].ID[j] == -1))
                ui->OutOutID->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].ID[j])));
        }
        for(uint j = 0; j < tabela[i].EX.size(); j++){
            if(!(tabela[i].EX[j] == -1))
                ui->OutOutEX->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].EX[j])));
        }
        for(uint j = 0; j < tabela[i].WB.size(); j++){
            if(!(tabela[i].WB[j] == -1))
                ui->OutOutWB->setItem(i,j,new QTableWidgetItem(QString::number(tabela[i].WB[j])));
        }
    }
    tabela.clear();
}
