#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include "form.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void login_clicked();   //登录按键槽函数
    void register_clicked();    //注册按键槽函数

private:
    Ui::Login *ui;


};

#endif // LOGIN_H
