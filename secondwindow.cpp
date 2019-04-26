#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <mainwindow.h>
#include <mainwindow.cpp>
#include "database.h"
#include <vector>

using namespace std;

string _id;
string _fio;
string _tel;
string _date;


secondWindow::secondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\repos\\lab1\\img\\57432b27acfd4154de60931d.jpg");
    bkgnd = bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkgnd);
    this->setPalette(palette);

}

secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::on_pushButton_5_clicked() // отобразить базу данных
{
    int m,n = 0;
    fstream file;
    file.open("C:\\repos\\lab1\\base.txt",ios::binary| ios::in);
    if(!file.is_open())
    {
        m = 10;
        n = 20;
    }
    char * ptr;
    char buff[256];
    QStringList verticalHeader;

    QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList horizontalHeader;
        horizontalHeader.append("ID");
        horizontalHeader.append("FIO");
        horizontalHeader.append("Tel");
        horizontalHeader.append("Date");

        while(!file.eof()){
            file.getline(buff,256);
            if(buff[0] =='{' || buff[0]=='}')
                continue;

            ptr = strtok(buff,":");
            while(ptr!=nullptr)
            {
            ptr = strtok(nullptr,"\"");
            ptr = strtok(nullptr,"\"");
            //verticalHeader.append(n); // заголовок строки


        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        //Первый ряд
        item = new QStandardItem(QString(ptr));

        model->setItem(n, m, item);
        ptr = strtok(nullptr,":");
        ptr = strtok(nullptr,"\"");
        ptr = strtok(nullptr,"\"");
        item = new QStandardItem(QString(ptr));

        model->setItem(n, m+1, item);
        ptr = strtok(nullptr,":");
        ptr = strtok(nullptr,"\"");
        ptr = strtok(nullptr,"\"");
        item = new QStandardItem(QString(ptr));

        model->setItem(n, m+2, item);
        ptr = strtok(nullptr,":");
        ptr = strtok(nullptr,"\"");
        ptr = strtok(nullptr,"\"");
        item = new QStandardItem(QString(ptr));

        model->setItem(n, m+3, item);
        ptr = nullptr;
            }


        ui->tableView->setModel(model);

        //ui->tableView->resizeRowsToContents();
       // ui->tableView->resizeColumnsToContents();
        n++;
        }
}

void secondWindow::on_pushButton_clicked() // добавить в базу
{
    QString ID = ui->lineEditID->text();
    int Id = ID.toInt();

    QString FIO = ui->lineEditFIO->text();
    string Fio = FIO.toStdString();

    QString TEL = ui->lineEditTEL->text();
    string Tel = TEL.toStdString();

    QString DATE = ui->lineEditDATE->text();
    string Date = DATE.toStdString();

    DataBase *obj;
    vector<dataa> db;
    db = obj->read();
    db = obj->add(db,Id,Fio,Tel,Date);
    obj->write(db);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButton_4_clicked()// найти пользователя
{
    int num;

    QString ID = ui->lineEditID->text();
    int Id = ID.toInt();


    DataBase *obj;
    vector<dataa> db;
    db = obj->read();
    num = obj->find(db,Id);
    if(num!=-1)
    {

        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList horizontalHeader;
        char *temp_id = new char[256];
        _itoa_s(db[num].id,temp_id,256,10);
        item = new QStandardItem(QString(QString::fromUtf8(temp_id)));
        model->setItem(0, 0, item);
        item = new QStandardItem(QString(QString::fromStdString(db[num].fio)));

        model->setItem(0, 1, item);
        item = new QStandardItem(QString(QString::fromStdString(db[num].tel)));

        model->setItem(0, 2, item);

        item = new QStandardItem(QString(QString::fromStdString(db[num].date)));
        model->setItem(0, 3, item);

        ui->tableView->setModel(model);

       // ui->tableView->resizeRowsToContents();
       //ui->tableView->resizeColumnsToContents();
    }
}

void secondWindow::on_pushButton_3_clicked()// удаление пользователя
{
    DataBase *obj;
    vector<dataa> db;

    QString ID = ui->lineEditID->text();
    int Id = ID.toInt();

    db = obj->read();
    db = obj->del(db,Id);
    obj->write(db);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButton_2_clicked() // замена пользователей
{
    DataBase *obj;
    vector<dataa> db;

    QString ID = ui->lineEditID->text();
    int Id = ID.toInt();

    QString FIO = ui->lineEditFIO->text();
    string Fio = FIO.toStdString();

    QString TEL = ui->lineEditTEL->text();
    string Tel = TEL.toStdString();

    QString DATE = ui->lineEditDATE->text();
    string Date = DATE.toStdString();

    db = obj->read();
    db = obj->change(db,Id,Fio,Tel,Date);
    obj->write(db);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButtonSort_clicked()
{
    DataBase *obj;
    vector<dataa> db;

    db = obj->read();
    db = obj->sort(db);

    obj->write(db);
}
