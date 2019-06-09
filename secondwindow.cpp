#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <vector>
#include <QDebug>
using namespace std;



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


    client_socket = new QTcpSocket(this);
    client_socket->connectToHost("127.0.0.1",33333);

    QDate date = QDate::currentDate();
    QString dateString = date.toString("dd.MM.yyyy");
    ui->labelCurrentDate->setText( dateString );

    connect(client_socket,SIGNAL(readyRead()),this,SLOT(slot_readyRead()));
    connect(client_socket,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
    hideButton();
}

secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::slot_disconnect()
{
    client_socket->deleteLater();
}

void secondWindow::slot_readyRead()
{  
    //    client_socket->waitForReadyRead(500);
    //    QByteArray data = client_socket->readAll();
    //    QString str = QString::fromStdString(data.toStdString());
}

void secondWindow::on_pushButton_5_clicked() // отобразить базу данных
{
    QString ID = ui->lineEditID->text();
    string Id = ID.toStdString();


    string message="show&";
    QByteArray tarray=QByteArray::fromStdString(message);

    client_socket->write(tarray);
    client_socket->waitForBytesWritten(200);
    qDebug() << tarray;

    client_socket->waitForReadyRead(500);
    QByteArray array = client_socket->readAll();

    string str = array.toStdString();
    if(str=="База данных пуста")
    {
        QMessageBox::critical(this,tr("1"),tr(array));
    }
    else{
        //vector<dataa> db;
        int k;
        string temp;
        int n,m = 0;

        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList verticalHeader;
        QStringList horizontalHeader;
        horizontalHeader.append("Имя");
        horizontalHeader.append("Фамилия");
        horizontalHeader.append("Телефон");
        horizontalHeader.append("Абонемент");
        horizontalHeader.append("Дата посещения");
        horizontalHeader.append("Количество посещений");

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);
        while(!str.empty())
        {
            k = str.find("&");
            temp = str.substr(0,k);
            str.erase(0,k+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));

            model->setItem(n, 0, item);
            for(int i = 1;i<6;i++)
            {
                k = str.find("&");
                temp = str.substr(0,k);
                str.erase(0,k+1);

                item = new QStandardItem(QString(QString::fromStdString(temp)));
                model->setItem(n, i, item);
            }
            n++;
        }
        ui->tableView->setModel(model);
    }
}

void secondWindow::on_pushButton_clicked() // добавить в базу
{

    QString id,name,tel,date,currentDate;
    id=ui->lineEditID->text();
    name=ui->lineEditFIO->text();
    tel=ui->lineEditTEL->text();
    date=ui->lineEditDATE->text();
    currentDate=ui->labelCurrentDate->text();
    QString message = "add&" +id + "&"+name+"&"+tel+"&" + date;

    QByteArray mes = QByteArray::fromStdString(message.toStdString());
    client_socket->write(mes);
    client_socket->waitForBytesWritten(100);

    client_socket->waitForReadyRead(500);

    QString rez = client_socket->readAll();
    //string rezu = rez.toStdString();

    QMessageBox::critical(this,tr("1"),tr(rez.toUtf8()));

    Sleep(1000);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButton_4_clicked() // найти пользователя
{

    QString id,fio,abonement,pos;
    id=ui->lineEditID->text(); // идентификатор
    fio=ui->lineEditFIO->text(); // фамилия
    abonement = ui->lineEditDATE->text(); // срок абонемента
    pos = ui->lineEditPos->text(); // дата посещения
    QString tel = ui->lineEditTEL->text(); // телефон
    string temp;
    QString message = "find&" +id + "&" + fio + "&" + tel + "&" + abonement + "&" + pos + "&";

    client_socket->write(QByteArray::fromStdString(message.toStdString()));
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(500);

    QString array = client_socket->readAll();

    string str = array.toStdString();

    int i = str.find("&");
    string rezult = str.substr(0,i);
    str.erase(0,i+1);
    QString rez = QString::fromStdString(rezult);
    if(rez=="Все поля пусты.\nПоиск невозможен" || rez=="Неправильный номер" || rez=="Пользователь не найден" || rez=="Неправильный формат поиска" || rez=="Неверная дата.\nДата не должна быть меньше сегодняшнего дня и иметь правильный формат." || rez=="Неверная дата.\nДата не должна быть больше сегодняшнего дня и иметь правильный формат.")
    {
        QMessageBox::critical(this,tr("1"),tr(rez.toUtf8()));
    }
    else{
        QMessageBox::critical(this,tr("1"),tr(rez.toUtf8()));

        QString ID = ui->lineEditID->text();
        string Id = ID.toStdString();

        int k;
        int n = 0;
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList verticalHeader;
        QStringList horizontalHeader;
        horizontalHeader.append("Имя");
        horizontalHeader.append("Фамилия");
        horizontalHeader.append("Телефон");
        horizontalHeader.append("Абонемент");
        horizontalHeader.append("Дата посещения");
        horizontalHeader.append("Количество посещений");

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);
        while(!str.empty())
        {
            k = str.find("&");
            temp = str.substr(0,k);
            str.erase(0,k+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));

            model->setItem(n, 0, item);
            for(int i = 1;i<6;i++)
            {
                k = str.find("&");
                temp = str.substr(0,k);
                str.erase(0,k+1);

                item = new QStandardItem(QString(QString::fromStdString(temp)));
                model->setItem(n, i, item);
            }
            n++;
        }
        ui->tableView->setModel(model);
    }
}

void secondWindow::on_pushButton_3_clicked() // удаление пользователя
{
    QString id = ui->lineEditID->text();
    QString fio=ui->lineEditFIO->text();
    QString tel=ui->lineEditTEL->text();

    QString message = "del&" + id + "&" + fio +"&" + tel + "&";

    client_socket->write(QByteArray::fromStdString(message.toStdString()));
    client_socket->waitForBytesWritten(100);

    client_socket->waitForReadyRead(500);
    QString rezult = client_socket->readAll();

    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));
    Sleep(1000);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButton_2_clicked() // замена пользователей
{
    QString id = ui->lineEditID->text();
    QString fio = ui->lineEditFIO->text();
    QString tel = ui->lineEditTEL->text();
    QString date = ui->lineEditDATE->text();

    QString message = "change&" +id + "&" + fio + "&" + tel + "&" + date;
    client_socket->write(QByteArray::fromStdString(message.toStdString()));
    client_socket->waitForBytesWritten();

    client_socket->waitForReadyRead(500);
    QString rezult = client_socket->readAll();

    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButtonAuth_clicked() // авторизация
{

    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    client_socket->waitForReadyRead(200);
    client_socket->readAll();
    QString log = ui->lineEditLog->text();
    QString pass = ui->lineEditPass->text();
    QString sum = log+pass;
    QByteArray str = sum.toUtf8();

    QString password  = QCryptographicHash::hash(str,QCryptographicHash::Sha256).toHex();

    QString message = "autho&"+log+"&"+password;
    QByteArray mes = QByteArray::fromStdString(message.toStdString());
    QByteArray shifr = crypto.encryptToByteArray(mes);

    client_socket->write("shifr&" + shifr);
    client_socket->waitForBytesWritten(5000);

    client_socket->waitForReadyRead(5000);
    QByteArray stat = client_socket->readAll();
    QString status = crypto.decryptToString(stat);

    QMessageBox msgBox;
    msgBox.setText(status);
    msgBox.exec();
    if(status == "admin")
    {
        hidelog();
        hideButton();
        showButton();
    }
    if(status == "manager")
    {
        hidelog();
        hideButton();
        showManagPanel();
    }
    if(status == "user")
    {
        hidelog();
        hideButton();
        showUserPanel();
    }
}

void secondWindow::showButton()
{
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->lineEditID->show();
    ui->lineEditFIO->show();
    ui->lineEditTEL->show();
    ui->lineEditDATE->show();
    ui->tableView->show();
    ui->pushButtonLogPass->show();
    ui->lineEditStatus->show();
    ui->lineEditChangeLog->show();
    ui->lineEditChangePass->show();
    ui->pushButtonChangeLog->show();
    ui->pushButtonDelLogin->show();
    ui->pushButtonAddLogin->show();
    ui->pushButtonVisit->show();
    ui->pushButtonOtmetka->show();
    ui->frame->show();
    ui->pushButtonClearLienEdit->show();
    ui->lineEditPos->show();
    ui->label_3->show();
    ui->label_4->show();
}

void secondWindow::hideButton()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();
    ui->lineEditID->hide();
    ui->lineEditFIO->hide();
    ui->lineEditTEL->hide();
    ui->lineEditDATE->hide();
    ui->tableView->hide();
    ui->pushButtonLogPass->hide();
    ui->lineEditStatus->hide();
    ui->lineEditChangeLog->hide();
    ui->lineEditChangePass->hide();
    ui->pushButtonChangeLog->hide();
    ui->pushButtonDelLogin->hide();
    ui->pushButtonAddLogin->hide();
    ui->pushButton_changePassUserOnly->hide();
    ui->pushButtonVisit->hide();
    ui->pushButtonOtmetka->hide();
    ui->frame->hide();
    ui->pushButtonClearLienEdit->hide();
    ui->lineEditPos->hide();
    ui->label_3->hide();
    ui->label_4->hide();
}

void secondWindow::showManagPanel()
{
    ui->lineEditID->show();
    ui->lineEditFIO->show();
    ui->lineEditTEL->show();
    ui->lineEditDATE->show();
    ui->tableView->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_4->show();
    ui->pushButton_5->show();
    ui->pushButtonVisit->show();
    ui->pushButtonOtmetka->show();
    ui->frame->show();
    ui->pushButtonClearLienEdit->show();
    ui->lineEditPos->show();
    ui->label_3->show();
    ui->label_4->show();
}

void secondWindow::showUserPanel()
{
    ui->tableView->show();
    ui->pushButton_5->show();
    ui->lineEditChangeLog->show();
    ui->lineEditChangePass->show();
    ui->lineEditChangePass->setPlaceholderText("New password");
    ui->lineEditChangeLog->setPlaceholderText("Password");
    ui->pushButton_changePassUserOnly->show();
    ui->frame->show();
    ui->pushButtonClearLienEdit->show();
    ui->lineEditPos->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->lineEditID->show();
    ui->lineEditFIO->show();
    ui->lineEditDATE->show();
    ui->lineEditTEL->show();
    ui->pushButton_4->show();
}

void secondWindow::hidelog()
{
    ui->lineEditLog->hide();
    ui->lineEditPass->hide();
    ui->pushButtonAuth->hide();
}

void secondWindow::on_pushButtonLogPass_clicked() // показать базу данных логинов
{

    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    QByteArray message = "logBase&";
    client_socket->write(message);
    client_socket->waitForBytesWritten(1000);

    client_socket->waitForReadyRead(5000);
    QByteArray array = client_socket->readAll();
    QString temp = crypto.decryptToString(array);

    string str_temp = temp.toStdString();
    if(str_temp == "База данных пуста")
    {
        QString ras = QString::fromStdString(str_temp);
        QMessageBox::critical(this,tr("1"),tr(ras.toUtf8()));
    }
    else{
        string str = str_temp;
        //vector<dataa> db;
        int k;
        string temp;
        int n = 0;

        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        //Заголовки столбцов
        QStringList verticalHeader;
        QStringList horizontalHeader;
        horizontalHeader.append("Login");
        horizontalHeader.append("Password");
        horizontalHeader.append("Status");

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        for(int i = 0;str[i];)
        {
            k = str.find("&");
            temp = str.substr(0,k);
            str.erase(0,k+1);

            item = new QStandardItem(QString(QString::fromUtf8(temp.c_str())));
            model->setItem(n, 0, item);

            k = str.find("&");
            temp = str.substr(0,k);
            str.erase(0,k+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(n, 1, item);

            k = str.find("&");
            temp = str.substr(0,k);
            str.erase(0,k+1);

            item = new QStandardItem(QString(QString::fromStdString(temp)));
            model->setItem(n, 2, item);

            n++;
        }
        ui->tableView->setModel(model);
    }
}

void secondWindow::on_pushButtonChangeLog_clicked() // сменить логин/пароль
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    QString pass = ui->lineEditChangePass->text();
    QString log = ui->lineEditChangeLog->text();
    QString stat = ui->lineEditStatus->text();
    QString sum = log + pass;
    QString password="";

    if(pass !="")
    {
        QByteArray str = sum.toUtf8();
        password  = QCryptographicHash::hash(str,QCryptographicHash::Sha256).toHex();
    }

    QString message = "changeLog&" + log + "&" + password + "&" + stat;
    QByteArray mes = crypto.encryptToByteArray(message);


    client_socket->write("shifr&"+mes);
    client_socket->waitForBytesWritten(1000);


    client_socket->waitForReadyRead(5000);
    QByteArray rez = client_socket->readAll();

    QString rezult = QString::fromStdString(rez.toStdString());

    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButtonLogPass_clicked();
}

void secondWindow::on_pushButtonAddLogin_clicked() // добавить логин/пароль
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    QString log = ui->lineEditChangeLog->text();
    QString pass = ui->lineEditChangePass->text();
    QString stat = ui->lineEditStatus->text();
    QString sum = log + pass;
    QByteArray str = sum.toUtf8();
    QString password  = QCryptographicHash::hash(str,QCryptographicHash::Sha256).toHex();

    QString message = "addLog&" + log + "&" + password + "&" + stat;
    QByteArray mes = crypto.encryptToByteArray(message);


    client_socket->write("shifr&" +mes);
    client_socket->waitForBytesWritten(1000);

    client_socket->waitForReadyRead(5000);
    QByteArray rez = client_socket->readAll();

    QString rezult = QString::fromStdString(rez.toStdString());
    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButtonLogPass_clicked();
}

void secondWindow::on_pushButtonDelLogin_clicked() // удалить логин
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    QString log = ui->lineEditChangeLog->text();

    QString message = "delLog&" + log;
    QByteArray mes=QByteArray::fromStdString(message.toStdString());
    client_socket->write(mes);
    client_socket->waitForBytesWritten(1000);

    client_socket->waitForReadyRead(5000);
    QByteArray rez = client_socket->readAll();

    QString rezult = QString::fromStdString(rez.toStdString());


    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButtonLogPass_clicked();
}

void secondWindow::on_pushButton_changePassUserOnly_clicked() // сменить пароль (только для пользователя)
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023));
    QString log = ui->lineEditLog->text();
    QString pass = ui->lineEditChangeLog->text(); // пароль
    QString reppass = ui->lineEditChangePass->text(); // новый пароль

    QByteArray str = pass.toUtf8() + log.toUtf8();
    QString password = QCryptographicHash::hash(str,QCryptographicHash::Sha256).toHex();
    QByteArray str_rep = reppass.toUtf8() + log.toUtf8();
    QString reppas = QCryptographicHash::hash(str_rep,QCryptographicHash::Sha256).toHex();

    QString message = "changeForUser&" + log + "&" +  password + "&" + reppas;
    QByteArray mes = QByteArray::fromStdString(message.toStdString());

    client_socket->write( mes);
    client_socket->waitForBytesWritten(200);
    Sleep(200);
    client_socket->waitForReadyRead(500);
    QString rezult = client_socket->readAll();
}

void secondWindow::on_pushButtonVisit_clicked() // абонемент
{
    QString date = ui->lineEditDATE->text();
    QString id = ui->lineEditID->text();
    QString fio = ui->lineEditFIO->text();
    QString tel = ui->lineEditTEL->text();


    QString message = "abonement&" + tel + "&" + date + "&";

    client_socket->write(QByteArray::fromStdString(message.toStdString()));
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(500);
    QString rezult = client_socket->readAll();

    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButtonOtmetka_clicked() // отметить посещение
{
    QString date = ui->labelCurrentDate->text();
    QString id = ui->lineEditID->text();
    QString fio = ui->lineEditFIO->text();
    QString tel = ui->lineEditTEL->text();

    QString message = "Adddate&" + id + "&" + fio + "&" + tel + "&" + date + "&";

    client_socket->write(QByteArray::fromStdString(message.toStdString()));
    client_socket->waitForBytesWritten(200);

    client_socket->waitForReadyRead(500);
    QString rezult = client_socket->readAll();

    QMessageBox::critical(this,tr("1"),tr(rezult.toUtf8()));

    Sleep(1000);
    on_pushButton_5_clicked();
}

void secondWindow::on_pushButtonClearLienEdit_clicked() // очистить все поля
{
    ui->lineEditID->clear();
    ui->lineEditFIO->clear();
    ui->lineEditTEL->clear();
    ui->lineEditPos->clear();
    ui->lineEditDATE->clear();
}
