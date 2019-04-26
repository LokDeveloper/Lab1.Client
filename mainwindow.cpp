#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include<QPixmap>
#include <iostream>
#include<QIODevice>
#include<QTextStream>
#include<fstream>
#include<cstring>
#include<QString>
#pragma warning(disable:4996)
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QPixmap bkgnd("C:\\repos\\lab1\\img\\s1200.jpg");
    bkgnd = bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkgnd);
    this->setPalette(palette);

    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("127.0.0.1",33333);
    connect(client_socket,SIGNAL(connected()),SLOT(slot_connected));
    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_readyRead));
    connect(client_socket,SIGNAL(disconnected()),SLOT(slot_disconnect()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_connected(int socketDescriptor)
{
    client_socket = new QTcpSocket(this);
    client_socket->setSocketDescriptor(socketDescriptor);

    connect(client_socket,SIGNAL(readyRead()),SLOT(slot_readyRead));
    connect(client_socket,SIGNAL(disconnected()),SLOT(slot_disconnect()));
}
QByteArray MainWindow::slot_readyRead(string log,string pass)
{
    if(client_socket->waitForConnected(500))
    {

       // client_socket->waitForReadyRead(500);
        QByteArray array;
        string temp;
        string message="auth&" + log + "&" + pass;
        array=QByteArray::fromStdString(message);

        client_socket->write(array);
        client_socket->waitForBytesWritten(200);
        client_socket->waitForReadyRead(200);


        while(client_socket->bytesAvailable() > 0)
        {
            data = client_socket->readAll();
        }

        return data;
    }
}
void MainWindow::slot_send_to_server(QString message)//
{

}
void MainWindow::slot_disconnect()
{
    client_socket->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPass->text();

    client_socket->connectToHost("127.0.0.1",33333);

    data = slot_readyRead(login.toStdString(),password.toStdString());





    //msgBox.setText(data);
    //msgBox.exec();

        if(data == "administrator")
        {
            msgBox.setText(data);
            msgBox.exec();
            hide();
            window = new secondWindow(this);
            window->show();
        }
        else if(data == "manager")
        {
            msgBox.setText(data);
            msgBox.exec();
            hide();
            window = new secondWindow(this);
            window->show();
        }
        else if(login =="" || password =="")
        {
        msgBox.setText("Имеются пустые строчки");
        msgBox.exec();
        }
        else if(data == "login or password is incorrect")
        {
            msgBox.setText(data);
            msgBox.exec();
        }
        else{
            msgBox.setText(data);
            msgBox.exec();
          hide();
          window = new secondWindow(this);
          window->show();
        }
}
void MainWindow::on_actionClose_triggered()
{
    close();
}
