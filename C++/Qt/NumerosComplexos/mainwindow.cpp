#include<iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "complex.h"
using namespace std;
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

void MainWindow::on_lineEdit_returnPressed()
{
    ui->lineEdit_2->setFocus();
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    a.set(ui->lineEdit->text().toFloat(), ui->lineEdit_2->text().toFloat());
    ui->lineEdit_3->setFocus();
}

void MainWindow::on_lineEdit_3_returnPressed()
{
    ui->lineEdit_4->setFocus();
}

void MainWindow::on_lineEdit_4_returnPressed()
{
    b.set(ui->lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat());
    ui->pushButton->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    c=a+b;
    ui->lineEdit_5->setText(c.get());
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_pressed()
{
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButton_2_clicked(){
    c=b-a;
    ui->lineEdit_5->setText(c.get());
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_2_pressed()
{
    MainWindow::on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_3_clicked(){
    c=a*b;
    ui->lineEdit_5->setText(c.get());
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_3_pressed()
{
    MainWindow::on_pushButton_3_clicked();
}

void MainWindow::on_pushButton_4_clicked(){
    c=b/a;
    ui->lineEdit_5->setText(c.get());
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_4_pressed()
{
    MainWindow::on_pushButton_4_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(a==b){
        ui->lineEdit_6->setText("Os números complexos são iguais!");
    }else{
        ui->lineEdit_6->setText("Os números complexos não são iguais!");
    }
}

void MainWindow::on_pushButton_5_pressed(){
    MainWindow::on_pushButton_5_clicked();
}

void MainWindow::on_pushButton_6_clicked()
{
    if((a|b)==1){
        ui->lineEdit_7->setText("As partes reais diferem.");
    }else{
        if((a|b)==2){
            ui->lineEdit_7->setText("As partes imaginárias diferem.");
        }else
            if((a|b)==3){
                ui->lineEdit_7->setText("Os números complexos não são diferentes.");
            }else
                ui->lineEdit_7->setText("Os números complexos são diferentes.");
    }


}
void MainWindow::on_pushButton_6_pressed(){
    MainWindow::on_pushButton_6_clicked();
}
