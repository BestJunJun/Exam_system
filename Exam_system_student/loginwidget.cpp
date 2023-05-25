#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "studentwidget.h"

Loginwidget::Loginwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loginwidget)
{
    ui->setupUi(this);


    //连接信号与槽

    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");    //加载mysql数据库驱动

    db.setDatabaseName("exam");
    db.setPort(3306);
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("123456");


    if(db.open())
    {
        QMessageBox::information(this,"连接提示","连接成功");
    }
    else
    {
        QMessageBox::warning(this,"连接提示","连接失败");
    }
    //显示用户名和密码规则
    ui->LogPslineEdit->setEchoMode(QLineEdit::Password);
    ui->RegPslineEdit1->setEchoMode(QLineEdit::Password);
    ui->RegPslineEdit2->setEchoMode(QLineEdit::Password);
    ui->LogPslineEdit->setMaxLength(16);
    ui->RegPslineEdit1->setMaxLength(16);
    ui->RegPslineEdit2->setMaxLength(16);
    on_RegBackbutton_clicked();


}

Loginwidget::~Loginwidget()
{
    delete ui;
}

void Loginwidget::on_ToRegButton_clicked()//登陆界面点击注册跳转注册界面
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Loginwidget::on_RegBackbutton_clicked()//注册界面点击返回登陆界面
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Loginwidget::on_LogButton_clicked()//登陆界面登陆
{
    if(ui->LogNamelineEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"登陆提示","请输入用户名");
        return;
    }

    //获取登陆信息
    QString name = ui->LogNamelineEdit->text();
    QString psword = ui->LogPslineEdit->text();
    QSqlQuery query;
    QString sql = QString("select * from users where id = '%1';").arg(name);
    if(query.exec(sql))
    {
        if(query.size() < 1)//用户名不存在
        {
            QMessageBox::warning(this,"登陆提示","用户名不存在");
            ui->LogNamelineEdit->clear();
            ui->LogPslineEdit->clear();
            return;
        }
        //用户存在
        if(ui->LogPslineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"登陆提示","请输入密码");
            return;
        }
        QString pw ;//记录正确密码
        QString u ;//记录正确用户类型
        while(query.next())
        {
            pw = query.value(1).toString();
            u = query.value(2).toString();
        }

        //用户类型匹配

        //查询密码是否正确
        if(psword != pw)
        {
            QMessageBox::warning(this,"登陆提示","密码错误");
            ui->LogPslineEdit->clear();
            return;
        }


        ui->LogNamelineEdit->clear();
        ui->LogPslineEdit->clear();
        this->hide();
        studentwidget *r = new studentwidget(name);
        r->show();


    }
}


void Loginwidget::on_Regbutton_clicked()//注册界面注册
{
    //获取输入信息
    QString regname = ui->RegNamelineEdit->text();
    QString regpasswd1 = ui->RegPslineEdit1->text();
    QString regpasswd2 = ui->RegPslineEdit2->text();
    bool ok = true;
    //判断用户名是否合法
    if(regname.size() < 6 || regname.size() > 12)
    {
        QMessageBox::warning(this,"注册提示","用户名长度不合法");
        ok = false;
        ui->RegNamelineEdit->clear();
        ui->RegPslineEdit1->clear();
        ui->RegPslineEdit2->clear();
        return;
    }
    //查询用户名称是否存在

    QSqlQuery query;
    QString sql = QString("select * from users where id = '%1';").arg(regname);
    if(query.exec(sql))
    {
        if(query.size() == 1)
        {
            QMessageBox::warning(this,"注册提示","用户名已注册");
            ok = false;
            ui->RegNamelineEdit->clear();
            ui->RegPslineEdit1->clear();
            ui->RegPslineEdit2->clear();
            return;
        }
    }
    //判断两次密码是否一致
    if(regpasswd1 != regpasswd2)
    {
        QMessageBox::information(this,"密码提示","两次输入密码不一致");
        ok = false;
        ui->RegNamelineEdit->clear();
        ui->RegPslineEdit1->clear();
        ui->RegPslineEdit2->clear();
        return;
    }
    //判断密码是否合法
    if(regpasswd1.size() < 6 || regpasswd1.size() > 16)
    {
        QMessageBox::warning(this,"注册提示","密码长度不合法");
        ok = false;
        ui->RegPslineEdit1->clear();
        ui->RegPslineEdit2->clear();
        return;
    }
    //判断真实名称是否合法
    QString realname = ui->RegNamelineEdit_2->text();
    if(realname.size() > 5)
    {
        QMessageBox::warning(this,"提示","真实姓名过长");
        ok = false;
        ui->RegNamelineEdit_2->clear();
        return;
    }
    //没有问题插入数据库

    if(ok)
    {
        sql = QString("insert into users values('%1','%2','student','%3');").arg(regname).arg(regpasswd1).arg(realname);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"注册提示","注册成功");
        }
        else
        {
            QMessageBox::warning(this,"注册提示","注册失败");

        }
    }
    ui->RegNamelineEdit->clear();
    ui->RegPslineEdit1->clear();
    ui->RegPslineEdit2->clear();

}


void Loginwidget::on_forgetpwbutton_clicked()
{
    QMessageBox::information(this,"提示","请联系管理员找回密码");
}

