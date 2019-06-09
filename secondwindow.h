#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include<iostream>
#include<string>
#include<cstring>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QString>
#include <QStringList>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>
#include<QTcpSocket>
#include<QtSql>
#include"windows.h"
#include<QDebug>
#include<QFileInfo>
#include<QMessageBox>
#include<QPalette>
#include "crypto.h"

using namespace std;
namespace Ui {
class secondWindow;
}

class secondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    ~secondWindow();

    void showButton();
    void hideButton();
    void hidelog();
    void showManagPanel();
    void showUserPanel();

    bool baseOpen();
    void baseClose();

private slots:
    void slot_disconnect();
    void on_pushButton_clicked(); // добавить в базу

    void on_pushButton_5_clicked(); // отобразить базу данных

    void on_pushButton_4_clicked(); // найти пользователя

    void on_pushButton_3_clicked(); // удалить пользователя

    void on_pushButton_2_clicked(); // замена пользователя


    void on_pushButtonAuth_clicked(); // авторизация

    void slot_readyRead();

    void on_pushButtonLogPass_clicked(); // показать базу данных логинов

    void on_pushButtonChangeLog_clicked(); // сменить логин/пароль

    void on_pushButtonAddLogin_clicked(); // добавить логин/пароль

    void on_pushButtonDelLogin_clicked(); // удалить логин

    void on_pushButton_changePassUserOnly_clicked(); // сменить пароль(только для пользователя)

    void on_pushButtonVisit_clicked(); // абонемент

    void on_pushButtonOtmetka_clicked();

    void on_pushButtonClearLienEdit_clicked();

private:
    Ui::secondWindow *ui;
    QTableView view;
    QStandardItemModel model;
    QTcpSocket *client_socket;
    QByteArray data;
    std::string key;
    QSqlDatabase mydb;
    QMessageBox msg;
};

#endif // SECONDWINDOW_H
