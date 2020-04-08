#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "../database/database.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(500,300);
    ui->rb_stu->setChecked(true);
    ad = new Admin(this);
    connect(ui->btn_login,&QPushButton::clicked,this,&Login::login);

}

Login::~Login()
{
    delete ui;
}

int Login::isCheck()
{
    if(ui->rb_adm->isChecked() && !ui->rb_tec->isChecked() && !ui->rb_stu->isChecked())
    {
        return 1;//管理员被选中
    }
    if(!ui->rb_adm->isChecked() && ui->rb_tec->isChecked() && !ui->rb_stu->isChecked())
    {
        return 2;//老师被选中
    }
    if(!ui->rb_adm->isChecked() && !ui->rb_tec->isChecked() && ui->rb_stu->isChecked())
    {
        return 3;//学生被选中
    }
    return 0;
}

void Login::login()
{
    QString str_a = ui->le_acc->text();
    QString str_p = ui->le_pas->text();
    if(str_a.isEmpty() || str_p.isEmpty())
    {
        return ;
    }
    //数据库操作
    QString str = "select *from dbo.logintable";
    QString name;
    QString job;
    bool ret = DataBase::getDataBasePtr()->queryTable(str,str_a,str_p,name,job);
    if(!ret)
    {
        QMessageBox::information(NULL, "Title", "查询失败");
        return ;
    }
    if(job == ui->rb_adm->text() && ui->rb_adm->isChecked())
    {
        this->hide();
        ad->setNmae(name);
        ad->setJob(job);
        ad->show();
    }
    if(job == ui->rb_tec->text() && ui->rb_tec->isChecked())
    {

    }
    if(job == ui->rb_stu->text() && ui->rb_stu->isChecked())
    {

    }
}
