#include "adminwidget.h"
#include "ui_adminwidget.h"

adminwidget::adminwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwidget)
{
    ui->setupUi(this);
    countusersNum();
}

adminwidget::~adminwidget()
{
    delete ui;
}

void adminwidget::countusersNum()//统计用户数量
{
    QString sql;
    QSqlQuery query;
    ui->useridcomboBox->clear();
    sql = QString("select * from users where identify = 'student';");
    if(query.exec(sql))
    {
        ui->studentnumlabel->setText(QString("%1名").arg(query.size()));
    }
    sql = QString("select * from users where identify = 'teacher';");
    if(query.exec(sql))
    {
        ui->teachernumlabel->setText(QString("%1名").arg(query.size()));
    }
    sql = QString("select * from users where identify = 'student' or identify = 'teacher';");
    if(query.exec(sql))
    {
        while(query.next())
        {
            ui->useridcomboBox->addItem(query.value(0).toString());
        }
    }
}

void adminwidget::on_regpushButton_clicked()//注册用户
{
    //获取输入信息
    QString regname = ui->regnamelineEdit->text();
    QString regpasswd = ui->regpswdlineEdit->text();
    bool ok = true;
    //判断用户名是否合法
    if(regname.size() < 6 || regname.size() > 12)
    {
        QMessageBox::warning(this,"注册提示","用户名长度不合法");
        ok = false;
        ui->regnamelineEdit->clear();
        ui->regpswdlineEdit->clear();
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
            ui->regnamelineEdit->clear();
            ui->regpswdlineEdit->clear();
            return;
        }
    }
    //判断密码是否合法
    if(regpasswd.size() < 6 || regpasswd.size() > 16)
    {
        QMessageBox::warning(this,"注册提示","密码长度不合法");
        ok = false;
        ui->regnamelineEdit->clear();
        ui->regpswdlineEdit->clear();
        return;
    }
    //判断真实名称是否合法
    QString realname = ui->regrealnamelineEdit->text();
    if(realname.size() > 5)
    {
        QMessageBox::warning(this,"提示","真实姓名过长");
        ok = false;
        ui->regrealnamelineEdit->clear();
        return;
    }
    //判断用户类型
    QString identify;
    if(ui->studentradioButton->isChecked())
    {
        identify = "student";
    }
    if(ui->teacherradioButton->isChecked())
    {
        identify = "teacher";
    }
    //没有问题插入数据库

    if(ok)
    {
        sql = QString("insert into users values('%1','%2','%3','%4');").arg(regname).arg(regpasswd).arg(identify).arg(realname);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"注册提示","注册成功");
            ui->regnamelineEdit->clear();
            ui->regpswdlineEdit->clear();
            ui->regrealnamelineEdit->clear();
            countusersNum();
        }
        else
        {
            QMessageBox::warning(this,"注册提示","注册失败");

        }
    }

}

void adminwidget::on_useridcomboBox_activated(const QString &arg1)//选用户名刷新用户信息
{
    QString sql;
    QSqlQuery query;
    sql = QString("select * from users where id = '%1';").arg(arg1);
    if(query.exec(sql))
    {
        query.next();
        ui->pswdlineEdit->setText(query.value(1).toString());
        ui->realnamelineEdit->setText(query.value(3).toString());
        if(query.value(2).toString() == "student")
        {
            ui->identifylineEdit->setText("学生");
        }
        else if (query.value(2).toString() == "teacher") {
            ui->identifylineEdit->setText("教师");
        }
    }
}

void adminwidget::on_pushButton_clicked()//退出按钮
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定退出?"),tr("是"),tr("否"))))
    {
        QApplication* app;
        app->exit(0);
    }
}

void adminwidget::on_deletepushButton_clicked()//删除账户
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定删除用户吗?"),tr("是"),tr("否"))))
    {
        QString sql;
        QSqlQuery query;
        sql = QString("delete from users where id = '%1';").arg(ui->useridcomboBox->currentText());
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","删除成功");
            ui->pswdlineEdit->clear();
            ui->realnamelineEdit->clear();
            ui->identifylineEdit->clear();
            countusersNum();
        }
        else {
            QMessageBox::information(this,"提示","删除失败");
        }
    }
}

void adminwidget::on_changepushButton_clicked()//修改账户
{
    QString regname = ui->useridcomboBox->currentText();
    QString regpasswd = ui->pswdlineEdit->text();
    bool ok = true;
    //判断密码是否合法
    if(regpasswd.size() < 6 || regpasswd.size() > 16)
    {
        QMessageBox::warning(this,"注册提示","密码长度不合法");
        ok = false;
        return;
    }
    //判断真实名称是否合法
    QString realname = ui->realnamelineEdit->text();
    if(realname.size() > 5)
    {
        QMessageBox::warning(this,"提示","真实姓名过长");
        ok = false;
        return;
    }
    //判断用户类型
    QString identify;
    if(ui->identifylineEdit->text() == "学生")
    {
        identify = "student";
    }
    else if (ui->identifylineEdit->text() == "教师") {
        identify = "teacher";
    }
    else {
        QMessageBox::warning(this,"提示","请输入合法身份");
        ok = false;
        return;
    }
    if(ok)
    {
        QString sql;
        QSqlQuery query;
        sql = QString("update users set passwd = '%1', identify = '%2', name = '%3' where id = '%4';")
                .arg(regpasswd).arg(identify).arg(realname).arg(regname);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","修改成功");
            ui->pswdlineEdit->clear();
            ui->realnamelineEdit->clear();
            ui->identifylineEdit->clear();
            countusersNum();
        }
        else {
            QMessageBox::information(this,"提示","修改失败");
        }
    }
}
