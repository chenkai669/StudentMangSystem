#include "admin.h"
#include "ui_admin.h"
#include<QMessageBox>
#include <QDialog>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    m_List = {};
    m_Acclist = {};
    add = new AddPerson();
    this->setFixedSize(1500,800);
    ui->groupBox_infor->move(1310,10);
    {
        //查询界面初始化
        ui->widget_2->setFixedSize(1000,600);
        ui->widget_2->move(10,100);
        ui->tableWidget->setColumnCount(4);
        //设置水平头
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Age"<<"Sex"<<"Class");
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格不可编辑
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(2,20,130);color: white;}");//设置表头背景和字体颜色
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //均分各列
        ui->tableWidget->installEventFilter(this);
        ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
        ui->tableWidget->verticalHeader()->setHidden(true);
        QStringList m_list1 =(QStringList()<<"查询全部"<<"姓名查询");
        ui->cb_serch->addItems(m_list1);
        //首先隐藏主界面
        ui->widget_2->hide();
    }
    {
        //查询界面初始化
        ui->widget_3->setFixedSize(1000,600);
        ui->widget_3->move(10,100);
        ui->tableWidget_2->setColumnCount(4);
        //设置水平头
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Account"<<"Passeard"<<"name"<<"Job");
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格不可编辑
        ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(2,20,130);color: white;}");//设置表头背景和字体颜色
        ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true); //均分各列
        ui->tableWidget_2->installEventFilter(this);
        ui->tableWidget_2->setSelectionBehavior ( QAbstractItemView::SelectRows);
        ui->tableWidget_2->verticalHeader()->setHidden(true);
        QStringList m_list2 =(QStringList()<<"查询全部"<<"姓名查询");
        ui->cb_cond1->addItems(m_list2);
        //首先隐藏主界面
        ui->widget_3->hide();

    }
    connect(ui->action_add,&QAction::triggered,this,[=](){
        add->exec();
    });
    connect(ui->btn_serch,&QPushButton::clicked,this,&Admin::peopleInforMation);
    connect(ui->btn_serch1,&QPushButton::clicked,this,&Admin::accountInformation);

    connect(ui->action_queryPerson,&QAction::triggered,this,[=](){
        ui->widget_3->hide();
        ui->widget_2->show();
    });
    connect(ui->action_queryAccout,&QAction::triggered,this,[=](){
        ui->widget_2->hide();
        ui->widget_3->show();
    });

}

Admin::~Admin()
{
    delete ui;
}

void Admin::setNmae(QString name)
{
    m_Name = name;
    ui->lb_name->setText(name);
}
void Admin::setJob(QString job)
{
    m_Job = job;
    ui->lb_job->setText(job);
}

void Admin::peopleInforMation()
{
    //先判断当前的权限
    QString Sentence;
    if(ui->cb_serch->currentText() == "查询全部")
        Sentence = QString("select *from dbo.personinformation");
    else
    {
        QString conten = ui->le_serch->text();
        if(conten.isEmpty())
        {
            ui->tableWidget->clearContents();
            QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
            QMessageBox::information(NULL, "Title", "姓名查询输入为空");
            return ;
        }
        Sentence = QString("select *from dbo.personinformation where name = '%1'").arg(conten);
    }
    bool ret = DataBase::getDataBasePtr()->quertPersonInformation(Sentence,m_List);
    if(!ret)
    {
        return ;
    }
    for(int i = 0;i< m_List.length();i++)
    {
        ui->tableWidget->setRowCount(m_List.length());
        for(QList<person>::iterator it = m_List.begin();it!=m_List.end();it++)
        {
            int col = 0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->name));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(it->age)));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->sex));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->clas));
            i++;

        }
        //设置行列居中
        for(int j = 0;j<m_List.length();j++ )
        {
            for(int k = 0;k<4;k++)
            {
                ui->tableWidget->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }

        }

    }
    if(m_List.isEmpty())
    {
        ui->tableWidget->clearContents();
    }
    m_List.clear();
}

void Admin::accountInformation()
{
    //先判断当前的权限
    QString Sentence;
    if(ui->cb_cond1->currentText() == "查询全部")
        Sentence = QString("select *from dbo.logintable");
    else
    {
        QString conten = ui->le_cont1->text();
        if(conten.isEmpty())
        {
            ui->tableWidget_2->clearContents();
            QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
            QMessageBox::information(NULL, "Title", "姓名查询输入为空");
            return ;
        }
        Sentence = QString("select *from dbo.logintable where name = '%1'").arg(conten);
    }
    bool ret = DataBase::getDataBasePtr()->quertLogintable(Sentence,m_Acclist);
    if(!ret)
    {
        return ;
    }
    for(int i = 0;i< m_Acclist.length();i++)
    {
        ui->tableWidget_2->setRowCount(m_Acclist.length());
        for(QList<Account>::iterator it = m_Acclist.begin();it!=m_Acclist.end();it++)
        {
            int col = 0;
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(it->account));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(it->passward));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(it->name));
            ui->tableWidget_2->setItem(i,col++,new QTableWidgetItem(it->job));
            i++;

        }
        //设置行列居中
        for(int j = 0;j<m_Acclist.length();j++ )
        {
            for(int k = 0;k<4;k++)
            {
                ui->tableWidget_2->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }

        }

    }
    if(m_Acclist.isEmpty())
    {
        ui->tableWidget_2->clearContents();
    }
    m_Acclist.clear();
}



bool Admin::eventFilter( QObject *object, QEvent *event)
{
    if (object == ui->tableWidget)
    {

        if( event->type() ==82)  // 82  鼠标右击事件 ContextMenu
        {
            if(ui->tableWidget->item(0,0)==NULL||(ui->tableWidget->item(0,0)&&ui->tableWidget->item(0,0)->text()==tr("")))
            {

            }
            else
            {
                qDebug()<<"ui->tableWidget";
                deletePerson();
            }

        }
    }
    // 注意这里，未处理的事件，要返还给上一级的事件处理函数。
    return QWidget::eventFilter(object, event);
}

void Admin::deletePerson()
{

    if(ui->tableWidget->item(0,0)==NULL||(ui->tableWidget->item(0,0)&&ui->tableWidget->item(0,0)->text()==tr("")))
    {
        return ;
    }
    QMenu *pMenu = new QMenu(this);
    QAction *pCom1 = new QAction(tr("删除"), ui->tableWidget);
    QAction *pCom2 = new QAction(tr("只显示老师"), ui->tableWidget);
    QAction *pCom3 = new QAction(tr("只显示管理员"), ui->tableWidget);
    QAction *pCom4 = new QAction(tr("只显示学生"), ui->tableWidget);
    pMenu->addAction(pCom1);
    pMenu->addAction(pCom2);
    pMenu->addAction(pCom3);
    pMenu->addAction(pCom4);
    connect(pCom1, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pCom2, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent2()));
    connect(pCom3, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent3()));
    connect(pCom4, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent4()));
    pMenu->exec(cursor().pos());
    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}


void Admin::onTaskBoxContextMenuEvent()
{
    if(ui->tableWidget->item(0,0)==NULL||(ui->tableWidget->item(0,0)&&ui->tableWidget->item(0,0)->text()==tr("")))
    {
        qDebug()<<"eee";
        return ;
    }
    QString str = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();//取出字符串
    QString Sentence;
    Sentence = QString("delete from dbo.personinformation where name ='%1' ").arg(str);
    bool ret = DataBase::getDataBasePtr()->PersonInformationDelete(Sentence);
    if(!ret)
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "数据库查询失败");
        return;
    }
    Sentence = QString("delete from dbo.logintable where name ='%1' ").arg(str);
    ret = DataBase::getDataBasePtr()->PersonInformationDelete(Sentence);
    if(!ret)
    {
        QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
        QMessageBox::information(NULL, "Title", "数据库查询失败");
        return;
    }
    ui->tableWidget->update();
    QApplication::setQuitOnLastWindowClosed(false);//解决QMessageBox对话框关闭后整个程序退出
    QMessageBox::information(NULL, "Title", "删除成功");
}

void Admin::onTaskBoxContextMenuEvent2()
{
    if(m_List.isEmpty())
    {
        ui->tableWidget->clearContents();
    }
    QString Sentence = QString("select *from dbo.logintable where job ='老师'");
    bool ret = DataBase::getDataBasePtr()->quertLogintable(Sentence,m_Acclist);
    if(!ret)
    {
        return ;
    }
    QList<QString> list;
    for(QList<Account>::iterator it = m_Acclist.begin();it!=m_Acclist.end();it++)
    {
        list.push_back(it->name);
    }
    for(QList<QString>::iterator it = list.begin();it!=list.end();it++)
    {
        Sentence = QString("select *from dbo.personinformation where name = '%1'").arg(*it);
        bool ret = DataBase::getDataBasePtr()->quertPersonInformation(Sentence,m_List);
        if(!ret)
        {
            return ;
        }
    }
    for(int i = 0;i< m_List.length();i++)
    {
        ui->tableWidget->setRowCount(m_List.length());
        for(QList<person>::iterator it = m_List.begin();it!=m_List.end();it++)
        {
            int col = 0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->name));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(it->age)));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->sex));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->clas));
            i++;

        }
        //设置行列居中
        for(int j = 0;j<m_List.length();j++ )
        {
            for(int k = 0;k<4;k++)
            {
                ui->tableWidget->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }

        }

    }
    m_Acclist.clear();
    m_List.clear();

}


void Admin::onTaskBoxContextMenuEvent3()
{
    if(m_List.isEmpty())
    {
        ui->tableWidget->clearContents();
    }
    QString Sentence = QString("select *from dbo.logintable where job ='管理员'");
    bool ret = DataBase::getDataBasePtr()->quertLogintable(Sentence,m_Acclist);
    if(!ret)
    {
        return ;
    }
    QList<QString> list;
    for(QList<Account>::iterator it = m_Acclist.begin();it!=m_Acclist.end();it++)
    {
        list.push_back(it->name);
    }
    for(QList<QString>::iterator it = list.begin();it!=list.end();it++)
    {
        Sentence = QString("select *from dbo.personinformation where name = '%1'").arg(*it);
        bool ret = DataBase::getDataBasePtr()->quertPersonInformation(Sentence,m_List);
        if(!ret)
        {
            return ;
        }
    }
    for(int i = 0;i< m_List.length();i++)
    {
        ui->tableWidget->setRowCount(m_List.length());
        for(QList<person>::iterator it = m_List.begin();it!=m_List.end();it++)
        {
            int col = 0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->name));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(it->age)));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->sex));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->clas));
            i++;

        }
        //设置行列居中
        for(int j = 0;j<m_List.length();j++ )
        {
            for(int k = 0;k<4;k++)
            {
                ui->tableWidget->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }

        }

    }
    m_Acclist.clear();
    m_List.clear();

}
void Admin::onTaskBoxContextMenuEvent4()
{
    if(m_List.isEmpty())
    {
        ui->tableWidget->clearContents();
    }
    QString Sentence = QString("select *from dbo.logintable where job ='学生'");
    bool ret = DataBase::getDataBasePtr()->quertLogintable(Sentence,m_Acclist);
    if(!ret)
    {
        return ;
    }
    QList<QString> list;
    for(QList<Account>::iterator it = m_Acclist.begin();it!=m_Acclist.end();it++)
    {
        list.push_back(it->name);
    }
    for(QList<QString>::iterator it = list.begin();it!=list.end();it++)
    {
        Sentence = QString("select *from dbo.personinformation where name = '%1'").arg(*it);
        bool ret = DataBase::getDataBasePtr()->quertPersonInformation(Sentence,m_List);
        if(!ret)
        {
            return ;
        }
    }
    for(int i = 0;i< m_List.length();i++)
    {
        ui->tableWidget->setRowCount(m_List.length());
        for(QList<person>::iterator it = m_List.begin();it!=m_List.end();it++)
        {
            int col = 0;
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->name));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(it->age)));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->sex));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(it->clas));
            i++;

        }
        //设置行列居中
        for(int j = 0;j<m_List.length();j++ )
        {
            for(int k = 0;k<4;k++)
            {
                ui->tableWidget->item(j,k)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }

        }

    }
    m_Acclist.clear();
    m_List.clear();

}






















