#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <adminiwindow/admin.h>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
public:
    int isCheck();
    void login();
private:
    Ui::Login *ui;
    Admin * ad;
};

#endif // LOGIN_H
