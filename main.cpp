#include "login/login.h"
#include <QApplication>
#include"database/database.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!(DataBase::getDataBasePtr()->OpenDataBase()))
    {
        qDebug("111");
        return 0;
    }
    Login w;
    w.show();
    return a.exec();
}
