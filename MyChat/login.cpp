#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->regBtn,SIGNAL(clicked(bool)),this,SLOT(register_clicked()));
    connect(ui->loginBtn,SIGNAL(clicked(bool)),this,SLOT(login_clicked()));
    connect(ui->nameCmBox,SIGNAL(editTextChanged(QString)),this,SLOT(getUserInfo(QString)));

    tableFlag=false;

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");



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

        //database.close();
    }
}

Login::~Login()
{
    delete ui;
}

void Login::register_clicked()
{
    //QApplication b();
    Register r(this);
    this->hide();
    r.show();
    transmitdb(database);
    r.exec();
    this->show();
}

void Login::login_clicked()
{
    if(matchFlag==false)
    {
        //用户名错误
        qDebug()<<"name invalid";
    }
    else
    {
        if(usr_passwd!=ui->passwdLineEdit->text())
        {
            //密码错误
            qDebug()<<"passwd not match";
        }
        else
        {
            //用户名和密码均正确
            ChatWindow cw(this);
            this->hide();
            cw.show();
            cw.exec();
            this->close();
        }
    }
}

//chatid,passwd,name,email,history
void Login::getUserInfo(QString name)
{

    QSqlQuery sql_query;        //改变量必须在成功打开数据库后定义才有效

    //查询部分数据(name)

    QString tempstring="select * from user where name='"+name+"'";
    qDebug()<<tempstring;
    if(!sql_query.exec(tempstring))
    {
        qDebug()<<sql_query.lastError();
        matchFlag=false;
    }
    else
    {
        while(sql_query.next())
        {
            usr_id = sql_query.value(0).toInt();
            usr_passwd = sql_query.value(1).toString();
            usr_name = sql_query.value(2).toString();
            usr_email = sql_query.value(3).toString();
            usr_history = sql_query.value(4).toInt();

            qDebug()<<QString("chatid=%1    passwd=%2     name=%3       email=%4    history=%5").arg(usr_id).arg(usr_passwd).arg(usr_name).arg(usr_email).arg(usr_history);

        }
        if(usr_name==name)  matchFlag=true;
        else                matchFlag=false;
    }

    qDebug()<<matchFlag;
    if(matchFlag==true)
    {
        QString path=":/image/userx.png";
        QString diff="user"+QString::number(usr_id);
        path.replace("userx",diff);
        //qDebug()<<path;

        QImage img;
        img.load(path);
        QPixmap pic=QPixmap::fromImage(img.scaled(ui->userPic->width(),ui->userPic->height()));
        ui->userPic->setPixmap(pic);
    }
    else
    {

        QPixmap pic;
        ui->userPic->setPixmap(pic);
    }


}
