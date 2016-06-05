#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
//#include <QSqlDatabase>
#include <QtSql>
#include "login.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    void dboperation();

private:
    Ui::Register *ui;

    QSqlDatabase database;
    //QSqlQuery类提供执行和操作的SQL语句的方法。
    //可以用来执行DML（数据操作语言）语句，如SELECT、INSERT、UPDATE、DELETE，
    //以及DDL（数据定义语言）语句，例如CREATE TABLE。
    //也可以用来执行那些不是标准的SQL的数据库特定的命令。

    bool tableFlag;
    int max_id;

private slots:
    void okBtn_clicked();
    void closeBtn_clicked();
    void receivedb(QSqlDatabase db);
};

#endif // REGISTER_H
