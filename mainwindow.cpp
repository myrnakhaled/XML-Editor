#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QObject"
#include "QFileDialog"
#include "QMessageBox"
#include "QFile"
#include "QPlainTextEdit"
#include "QString"
#include<iostream>
#include"jsonwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_browsefile->setFixedWidth(300);
    ui->pushButton_compress->setFixedWidth(300);
    ui->pushButton_check->setFixedWidth(300);
    ui->pushButton_converttojson->setFixedWidth(300);
    ui->pushButton_format->setFixedWidth(300);
    ui->pushButton_minify->setFixedWidth(300);



}

MainWindow::~MainWindow()
{
    delete ui;
}














void MainWindow::on_pushButton_browsefile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;


        /* secDialog sec1;
         sec1.setModal(true);
         sec1.exec();
        */
         //to hide the parent

        // hide();
         sec = new secDialog(this,filepath);
         sec->show();

}


void MainWindow::on_pushButton_check_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;



        // hide();
       sub_string1 = new sub_string(this,filepath);
       sub_string1->show();

}


void MainWindow::on_pushButton_format_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;



        // hide();
         format1 = new format(this,filepath);
         format1->show();



}


void MainWindow::on_pushButton_converttojson_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;



        // hide();
         jsonwindow1 = new jsonwindow(this,filepath);
         jsonwindow1->show();
}


void MainWindow::on_pushButton_compress_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;



        // hide();
      compdialog = new compressiondialog(this,filepath);
      compdialog->show();

}


void MainWindow::on_pushButton_minify_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"choose a file",QDir::homePath());
    QFile xmlfile(filepath);
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    //QMessageBox::warning(this,"","cannot open the file");
        return;



        // hide();
         min1 = new minify(this,filepath);
         min1->show();
}

