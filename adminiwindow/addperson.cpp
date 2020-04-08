#include "addperson.h"
#include "ui_addperson.h"
#include <QList>
#include <database/database.h>
#include <QMessageBox>


AddPerson::AddPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPerson)
{
    ui->setupUi(this);
    this->setFixedSize(440,532);
    connect(ui->btn_add,&QPushButton::clicked,this,&AddPerson::addPerson);
    connect(ui->btn_clear,&QPushButton::clicked,this,&AddPerson::clearInput);

}

AddPerson::~AddPerson()
{
    delete ui;
}
void AddPerson::addPerson()
{
    QList<person> per = {};

    QString name = ui->le_name->text();
    QString age = ui->le_age->text();
    QString sex = ui->le_sex->text();
    QString clas = ui->le_class->text();
    QString acc = ui->le_acc->text();
    QString pass = ui->le_pass->text();
    QString t_job = ui->le_job->text();

    if(name.isEmpty() || age.isEmpty() || sex.isEmpty() ||acc.isEmpty() ||pass.isEmpty()||t_job.isEmpty())
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "姓名 年龄 性别 账号 密码 职业 不能为空");
        return ;
    }
    QString Sentence;
    Sentence = QString("select *from dbo.personinformation where name ='%1' and age =%2 and  sex ='%3' ")
            .arg(name).arg(age.toInt(),0,10).arg(sex);
    bool ret = DataBase::getDataBasePtr()->quertPersonInformation(Sentence,per);
    if(!ret)
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "数据库查询失败");
        return;
    }
    if(!per.isEmpty())
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "将要插入的人员信息已存在,请仔细核对");
        return;
    }
    //INSERT INTO 表名称 VALUES (值1, 值2,....)
    if(!clas.isEmpty())
        Sentence = QString("insert into dbo.personinformation values('%1',%2,'%3','%4')").arg(name).arg(age.toInt(),0,10).arg(sex).arg(clas);
    else
        Sentence = QString("insert into dbo.personinformation values('%1',%2,'%3',%4)").arg(name).arg(age.toInt(),0,10).arg(sex).arg("null");
    ret = DataBase::getDataBasePtr()->PersonInformationInsert(Sentence);
    if(!ret)
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "数据库插入失败");
        return;
    }
    //插入账号
    Sentence = QString("insert into dbo.logintable values('%1','%2','%3','%4')").arg(acc).arg(pass).arg(name).arg(t_job);
    ret = DataBase::getDataBasePtr()->PersonInformationInsert(Sentence);
    if(!ret)
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "数据库插入失败");
        return;
    }
    QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
    QMessageBox::information(NULL, "Title", "插入成功");
    this->close();

}
void AddPerson::clearInput()
{
    ui->le_name->clear();
    ui->le_sex->clear();
    ui->le_age->clear();
    ui->le_class->clear();
    ui->le_acc->clear();
    ui->le_pass->clear();
    ui->le_job->clear();
}
