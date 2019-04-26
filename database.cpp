#include <vector>
#include <string>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <fstream>
#include <cstring>
#include<iostream>
#include<stdio.h>
#include "database.h"

using namespace std;

/*
Функция проверки имени. С 65 по 122 находятся строчные и прописные буквы,за пределами 65 и 122 находятся различные символы,
поэтому они нам не подходят. isalpha проверяет символ и возвращает ненулевое значение, если символ является буквой алфавита,
,поэтому ! вернет 0 в случае,если это не буква.с 65 по 90 находятся заглавные буквы,а с 97 по 122 строчные,поэтому
если встречаются строчные,то мы переводим их в заглавные
*/
string checkFio(string fio)//Используемые символы - только буквы; Если регистр не тот, меняем на правильный.
{

    for(int i = 0; i < fio.size();i++)
    {
        if(fio[i] < 65 || fio[i] > 122 ||  !isalpha(fio[i]) )
        {
            fio.erase(i,1);
            i--;
            continue;
        }
        if(fio[0] > 97 && fio[0] < 122)
        {
            fio[0]-=32;
            continue;
        }
        if(fio[i] >= 65 && fio[i] <= 90)
        {
            fio[i]+=32;
        }
        if(fio[i] >= 97 && fio[i] < 122 )
        {
            continue;
        }


    }
        return fio;
}
/*
isdigit проверяет является ли символ числом и возвращает 1,если это цифра.Счётчик k считает количество цифр в номере
и если количество равно 10 то функция вернёт 1.
*/
bool checkTel(string tel)//длина строки 10 символов, все из которых цифры;
{
    int k = 0;
    for(int i = 0;i < tel.size();i++)
    {
        if(isdigit(tel[i]))
        {
            k++;
        }
        else {
            return 0;
        }
    }
    if(k == 10)
    {
        return 1;
    }
}

    DataBase::DataBase()
    {

    }
    DataBase::~DataBase()
    {

    }

    vector<dataa> DataBase::add(vector<dataa> db,int temp_id,string temp_fio,string temp_tel,string temp_date) // Добавить в базу
    {
        dataa temp_data;
        fstream file;
        file = openFile();
        if(temp_id==0)
        {
            vector<dataa>::iterator it = db.end() - 1;
            temp_id = it->id + 1;
        }
        temp_data.id = temp_id;
        temp_data.fio = checkFio(temp_fio);
        temp_data.tel = temp_tel;
        temp_data.date = temp_date;

        db.push_back(temp_data);
        file = closeFile();
        return db;
    }

    vector<dataa> DataBase::del(vector<dataa> db,int temp_id) // удалить пользователя
    {
        for (vector<dataa>::iterator it = db.begin();it!=db.end();it++)
        {   
            if(it->id == temp_id)
            {               
               db.erase(it);
               break;
            }
        }
        return db;
    }
    vector<dataa> DataBase::change(vector<dataa> db,int id,string FIO,string TEL,string DATE)// меняем данные с заданным id, на заданные данные temp_data
    {
        int n = 0;
        n = find(db,id);
        int k = -1;
        for(vector<dataa>::iterator it = db.begin();it!=db.end();it++)
        {
            k++;
            if(k == n)
            {
                if(!FIO.empty())
                it->fio = checkFio(FIO);

                if(!TEL.empty() && checkTel(TEL))
                it->tel = TEL;

                if(!DATE.empty())
                it->date = DATE;
            }
        }
        return db;

    }
    int DataBase::find(vector<dataa> db,int num)
    {

        int k = 0;

            for (vector<dataa>::iterator it = db.begin(); it != db.end(); it++)
            {

                k++;
                if (it->id == num)
                {

                    return k - 1;
                }

            }
            return -1;
    }

    vector<dataa> DataBase::sort(vector<dataa> db)
    {
        int n = 0;
        vector<dataa> temp;
        vector<dataa>::iterator temp_it;
        for(vector<dataa>::iterator it = db.begin();it!=db.end();it++)
        {
            n++;
            if(it->id > (it+1)->id)
            {
                temp.push_back(db[n]);
                temp_it=temp.begin();
                swap(db[n],db[n + 1]);
                //assign(db[n + 1],temp[0]);
                db.erase(it);
                db.emplace(temp_it);
                n = 0;
                temp.pop_back();
                it = db.begin();
            }
        }
        return db;
    }
    template<typename temptype>
    vector<dataa> find(int crit, temptype Znach);

    vector<dataa> DataBase::read() //считывает всю БД из файла
    {
        vector<dataa> temp_db;
        fstream file = openFile();
        char buff[256];
        dataa temp;
        while(!file.eof())
        {

            file.getline(buff,256);

            if(buff[0] == '{' || buff[0] == '}' || buff[0] == '\r' || buff[0] =='\0')
                continue;

            temp = parsing(buff);

            temp_db.push_back(temp);
        }

        file = closeFile();

        return temp_db;
    }
    void DataBase::write(vector<dataa> db) //запись всей БД в файл
    {
        string buff;
        fstream file;
        file.open("C:\\repos\\lab1\\base.txt",ios::binary | ios::out | ios::trunc);


        for(vector<dataa>::iterator it = db.begin();it!=db.end();it++)
        {
            buff = data2string(it);
            file << buff;
        }
        file = closeFile();
    }

    fstream DataBase::openFile()
    {
        fstream file;
        file.open("C:\\repos\\lab1\\base.txt",ios::binary | ios::in | ios::out);
        if(!file.is_open())
        {
            int n = 0;
        int m = 0;
        n++;
        m++;
        int c = m+n;
        }
        return file;

    }
    fstream DataBase::closeFile()
    {
        fstream file;
        if(file.is_open())
            file.close();
        return file;
    }



    dataa DataBase::parsing(string temp_line)
    {
        dataa temp;
        char buff[256];
        strcpy(buff,temp_line.c_str());
                    char*ptr = strtok(buff, ":");
                    while (ptr != nullptr)
                    {
                        ptr = strtok(nullptr,"\"");
                        ptr = strtok(nullptr,"\"");
                        temp.id = atoi(ptr);

                        ptr = strtok(nullptr,":");
                        ptr = strtok(nullptr, "\"");
                        ptr = strtok(nullptr, "\"");


                        temp.fio = checkFio(ptr);

                        ptr = strtok(nullptr, ":");
                        ptr = strtok(nullptr, "\"");
                        ptr = strtok(nullptr, "\"");
                        if(checkTel(ptr) == 0)
                        {
                            temp.tel = "";
                        }
                        temp.tel = ptr;

                        ptr = strtok(nullptr, ":");
                        ptr = strtok(nullptr, "\"");
                        ptr = strtok(nullptr, "\"");

                        if(ptr!=nullptr)
                        {
                        temp.date = ptr;
                        }
                        else
                        temp.date ="";

                        ptr = nullptr;
                    }
          return temp;
    }
    string DataBase::data2string(vector<dataa>::iterator it)
    {
        string _temp;
       _temp.append("{\r\n\t\"id\": \"");
        string ID = to_string(it->id);
       _temp.append(ID);
       //if(checkFio(it->fio))


        _temp.append("\", \"fio\": \"");
        _temp.append(it->fio);

       _temp.append("\", \"tel\": \"");


      // if(checkTel(it->tel))
           _temp.append(it->tel);

       _temp.append("\", \"date\": \"");
       _temp.append(it->date);
       _temp.append("\"\r\n}\r\n");

       return _temp;
    }


