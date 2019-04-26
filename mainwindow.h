#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include <QFile>
#include <QString>
#include<iostream>
#include <string>
#include<QTcpSocket>
#include<QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readFile();

public slots:
    void on_pushButton_clicked();

    void on_actionClose_triggered();

    void slot_connected(int);
    QByteArray slot_readyRead(string,string);
    void slot_send_to_server(QString message);
    void slot_disconnect();

private:
    Ui::MainWindow *ui;
    secondWindow *window;
    QTcpSocket *client_socket;
    QByteArray data;
    int n = 0;
};

#endif // MAINWINDOW_H
