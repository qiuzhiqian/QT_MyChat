#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->regBtn,SIGNAL(clicked(bool)),this,SLOT(register_clicked()));
    connect(ui->loginBtn,SIGNAL(clicked(bool)),this,SLOT(login_clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::register_clicked()
{
    //QApplication b();
    Register r;
    this->hide();
    r.show();
    r.exec();
    this->show();
}

void Login::login_clicked()
{
//    Form f;
//    f.show();
//    f.
}
