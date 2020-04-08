#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>



struct Account
{
    QString account;
    QString passward;
    QString name;
    QString job;
};


struct person
{
    QString name;
    int age;
    QString sex;
    QString clas;
};

class DataBase
{
private:
    DataBase();
    ~DataBase();
public:
    static DataBase *getDataBasePtr();
    bool OpenDataBase();
    void CloseDataBase();
    bool SentenceExec(QString Sentence);
    bool quertLogintable(QString Sentence,QList<Account>&);
    bool queryTable(QString Sentence,QString accout,QString pass,QString &name,QString &job);
    bool quertPersonInformation(QString Sentence,QList<person>&);
    bool PermissionQuery(QString,QString&);
    bool PersonInformationInsert(QString);
    bool PersonInformationDelete(QString);

private:

private:
     QSqlDatabase db;
     QSqlQuery query;
     static DataBase *db_ptr;
};

#endif // DATABASE_H
