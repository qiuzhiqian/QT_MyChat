#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtn_clicked()));
    connect(ui->closeBtn,SIGNAL(clicked(bool)),this,SLOT(closeBtn_clicked()));
    dboperation();
}

Register::~Register()
{
    delete ui;
}

QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
QString create_sql = "create table user (chatid int primary key, passwd varchar(30), name varchar(30), email varchar(30))";
QString select_max_sql = "select max(chatid) from user";
QString insert_sql = "insert into user values (?, ?, ?, ?)";
//QString update_sql = "update user set name = :name where chatid = :chatid";
QString select_sql = "select name from user";
//QString select_all_sql = "select * from user";
//QString delete_sql = "delete from user where chatid = ?";
//QString clear_sql = "delete from user";

//chatid,passwd,name,email
void Register::dboperation()
{
    tableFlag=false;

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    //database.setUserName("root");
    //database.setPassword("123456");

    //打开数据库
    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else
    {
        qDebug()<<"open seccess";
        QSqlQuery sql_query;        //改变量必须在成功打开数据库后定义才有效
        sql_query.prepare(select_table);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            QString tableName;
            while(sql_query.next())
            {
                tableName = sql_query.value(0).toString();
                qDebug()<<tableName;
                if(tableName.compare("user"))
                {
                    tableFlag=false;
                    qDebug()<<"table is not exist";
                }
                else
                {
                    tableFlag=true;
                    qDebug()<<"table is exist";
                }
            }
        }

        if(tableFlag==false)
        {
            sql_query.prepare(create_sql);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"table created!";
            }
        }

        database.close();
    }



    //删除数据库
    //QFile::remove("database.db");
}

void Register::okBtn_clicked()
{
    bool nameFlag=false;    //用户名有效标志
    bool passwdFlag=false;  //密码有效标志
    int newchatid=max_id+1;
    QString newpasswd=NULL;
    QString newname=NULL;
    QString newemail=ui->emailLineEdit->text();

    if(ui->passwd1LineEdit->text()==""||ui->passwd2LineEdit->text()=="")
    {
        passwdFlag=false;
    }
    else if(ui->passwd1LineEdit->text()==ui->passwd2LineEdit->text())    //两次密码相同
    {
        //newpasswd=ui->passwd1LineEdit->text();
        passwdFlag=true;
    }
    else
    {
        qDebug()<<"passwd err";
        passwdFlag=false;
        //return;
    }

    //以下为数据库的操作

    //打开数据库
    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else
    {
        QSqlQuery sql_query;

        //查询最大id
        max_id = 0;
        sql_query.prepare(select_max_sql);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                max_id = sql_query.value(0).toInt();
                qDebug()<<QString("max chatid:%1").arg(max_id);
            }
        }


        //查询部分数据(name)
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                QString name = sql_query.value("name").toString();
                qDebug()<<QString("name=%1").arg(name);

                if(ui->nameLineEdit->text()==name)    //用户名已经存在
                {
                    qDebug()<<"name existed";
                    nameFlag=false;
                    break;
                }
                else
                {
                    //newname=ui->nameLineEdit->text();
                    nameFlag=true;
                }

                //qDebug()<<QString("chatid:%1    name:%2").arg(id).arg(name);
            }
        }

        newchatid=max_id+1;
        if(nameFlag==true) newname=ui->nameLineEdit->text();
        else                return;
        if(passwdFlag==true)    newpasswd=ui->passwd1LineEdit->text();
        else                    return;

        //插入数据
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(newchatid);           //chatid
        sql_query.addBindValue(newpasswd);                //passwd
        sql_query.addBindValue(newname);             //name
        sql_query.addBindValue(newemail);    //email
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<<"inserted!";
        }
        database.close();
    }
    this->close();
}

void Register::closeBtn_clicked()
{
    this->close();
}

//void passwdChange()
//{
//    //更新数据
//    sql_query.prepare(update_sql);
//    sql_query.bindValue(":name", "xml");
//    sql_query.bindValue(":chatid", 1);
//    if(!sql_query.exec())
//    {
//        qDebug()<<sql_query.lastError();
//    }
//    else
//    {
//        qDebug()<<"updated!";
//    }
//}
