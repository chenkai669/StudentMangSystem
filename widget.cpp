#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    l_Ptr = new Login();
    l_Ptr->show();

}

Widget::~Widget()
{
    delete ui;
}

