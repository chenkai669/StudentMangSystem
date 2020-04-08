#include "database.h"
#include<stdio.h>

DataBase *DataBase::db_ptr = nullptr;

DataBase::DataBase()
{
}
DataBase::~DataBase()
{
    CloseDataBase();
}

bool DataBase::OpenDataBase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString::fromLocal8Bit("QTDSN");
    db.setHostName("127.0.0.1");
    db.setDatabaseName(dsn);
    db.setUserName("sa");
    db.setPassword("c123456");
    if(!db.open())
    {
        return false;
    }
    query = QSqlQuery(db);
    return true;
}

void DataBase::CloseDataBase()
{
    db.close();
}

bool DataBase::SentenceExec(QString Sentence)
{
    return query.exec(Sentence);
}

bool DataBase::queryTable(QString Sentence,QString accout,QString pass,QString &name,QString &job)
{
    QString str = Sentence;
    if(!query.exec(str))
    {
        return false;
    }
    while(query.next())
    {
        if(query.value(1).toString() == accout && query.value(2).toString() == pass)
        {
            name = query.value(3).toString();
            job = query.value(4).toString();
            return true;
        }
    }
}

bool DataBase::quertLogintable(QString Sentence,QList<Account>& m_Acclist)
{
    Account acc;
    if(!query.exec(Sentence))
    {
        qDebug()<<"111";
        return false;
    }
    while(query.next())
    {
        acc.account = query.value(1).toString();
        acc.passward = query.value(2).toString();
        acc.name = query.value(3).toString();
        acc.job = query.value(4).toString();
        m_Acclist.push_back(acc);
        //memset(&per,0,sizeof (person));
    }
    return true;
}


bool DataBase::quertPersonInformation(QString Sentence,QList<person>& m_Lsit)
{
    person per;
    if(!query.exec(Sentence))
    {
        qDebug()<<"111";
        return false;
    }
    while(query.next())
    {
        per.name = query.value(1).toString();
        per.age = query.value(2).toInt();
        per.sex = query.value(3).toString();
        per.clas = query.value(4).toString();
        m_Lsit.push_back(per);
        //memset(&per,0,sizeof (person));
    }
    return true;
}

bool DataBase::PermissionQuery(QString Sentence,QString& job)
{
    if(!query.exec(Sentence))
    {
        return false;
    }
    while(query.next())
    {
        job = query.value(4).toString();
    }
    return true;
}

bool DataBase::PersonInformationInsert(QString Sentence)
{
    if(!query.exec(Sentence))
    {
        return false;
    }
    return true;
}

bool DataBase:: PersonInformationDelete(QString Sentence)
{
    if(!query.exec(Sentence))
    {
        return false;
    }
    return true;
}


DataBase *DataBase::getDataBasePtr()
{
    if(db_ptr == nullptr)
        db_ptr = new DataBase();
    return db_ptr;
}
