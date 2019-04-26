#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include <QDialog>
#include<iostream>
#include<string>
#include<cstring>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QString>
#include <QStringList>
#include "database.h"
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>

namespace Ui {
class secondWindow;
}

class secondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    ~secondWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonSort_clicked();

private:
    Ui::secondWindow *ui;
    QTableView view;
    QStandardItemModel model;

};

#endif // SECONDWINDOW_H
