#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include "chatwindow.h"
#include <QPainter>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

signals:
    void transmitdb(QSqlDatabase db);

private slots:
    void login_clicked();   //登录按键槽函数
    void register_clicked();    //注册按键槽函数
    void getUserInfo(QString name);

private:
    Ui::Login *ui;
    QSqlDatabase database;
    bool tableFlag;

    int usr_id;
    QString usr_passwd;
    QString usr_name;
    QString usr_email;
    int usr_history;
    bool matchFlag;

    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    QString create_sql = "create table user (chatid int primary key, passwd varchar(30), name varchar(30), email varchar(30), history int)";
    QString select_max_sql = "select max(chatid) from user";
    QString insert_sql = "insert into user values (?, ?, ?, ? ?)";
    //QString update_sql = "update user set name = :name where chatid = :chatid";
    QString select_sql = "select name from user";
    //QString select_all_sql = "select * from user";
    //QString delete_sql = "delete from user where chatid = ?";
    //QString clear_sql = "delete from user";

    QString select_nameInfo = "selcet * from user wher name=";


};

#endif // LOGIN_H
