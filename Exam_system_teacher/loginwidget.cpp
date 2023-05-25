#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "adminwidget.h"
#include "teacherwidget.h"

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
    ui->LogPslineEdit->setMaxLength(16);
    ui->stackedWidget->setCurrentIndex(0);

}

Loginwidget::~Loginwidget()
{
    delete ui;
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
    bool cheaku = true;
    //查询用户是否存在
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

        //检查用户类型是否正确

        if(ui->LogAdminRadioButton->isChecked() == false
                && ui->LogTeacherRadioButton->isChecked() == false)
        {
            cheaku = false;
        }
        else
        {
            if(ui->LogTeacherRadioButton->isChecked() == true)//教师
            {
                if(u != "teacher")
                {
                    cheaku = false;
                }
            }
            if(ui->LogAdminRadioButton->isChecked() == true)//管理员
            {
                if(u != "admin")
                {
                    cheaku = false;
                }
            }

        }
        if(cheaku == false)//用户类型不匹配
        {
            QMessageBox::warning(this,"登陆提示","请选择正确的用户类型");
            return;
        }
        //用户类型匹配

        //查询密码是否正确
        if(psword != pw)
        {
            QMessageBox::warning(this,"登陆提示","密码错误");
            ui->LogPslineEdit->clear();
            return;
        }
        else if(ui->LogAdminRadioButton->isChecked())//管理员界面
        {
            ui->LogNamelineEdit->clear();
            ui->LogPslineEdit->clear();
            this->hide();
            adminwidget *a = new adminwidget();
            a->show();
        }
        else if(ui->LogTeacherRadioButton->isChecked())//教师界面
        {
            ui->LogNamelineEdit->clear();
            ui->LogPslineEdit->clear();
            this->hide();
            teacherwidget *t = new teacherwidget(name);
            t->show();
        }
    }
}



void Loginwidget::on_forgetpwbutton_clicked()
{
    QMessageBox::information(this,"提示","请联系管理员找回密码");
}


