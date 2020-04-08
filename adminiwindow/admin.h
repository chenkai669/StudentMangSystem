#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include "database/database.h"
#include "adminiwindow/addperson.h"
namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    void setNmae(QString);
    void setJob(QString);
    bool eventFilter( QObject *object, QEvent *event );
    void deletePerson();
    ~Admin();

public slots:
    void peopleInforMation();
    void accountInformation();
    void onTaskBoxContextMenuEvent();
    void onTaskBoxContextMenuEvent2();
    void onTaskBoxContextMenuEvent3();
    void onTaskBoxContextMenuEvent4();

private:
    Ui::Admin *ui;
    QString m_Name;
    QString m_Job;
    QList<person> m_List;
    QList<Account> m_Acclist;
    AddPerson *add;
};

#endif // ADMIN_H
