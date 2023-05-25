#include "studentwidget.h"
#include "ui_studentwidget.h"
#include "examwidget.h"

studentwidget::studentwidget(QString s ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentwidget)
{

    ui->setupUi(this);

    socket = new QTcpSocket;
    //客户端收到服务器发送的信息，socket发出readyread信号
    connect(socket,&QTcpSocket::readyRead,this,&studentwidget::serverinfo);

    ui->changenamelineEdit->setEchoMode(QLineEdit::Password);
    ui->changenamelineEdit->setMaxLength(16);
    ui->subjectlineEdit->setEnabled(false);
    ui->scorelineEdit->setEnabled((false));

    name = s;
    studentbegin();
}

studentwidget::~studentwidget()
{
    delete ui;
}

void studentwidget::studentbegin()
{
    QString sql;
    QSqlQuery query;
    //设置欢迎语
    sql = QString("select * from users where id = '%1';").arg(name);
    if(query.exec(sql))
    {
        query.next();
        QString wel;
        wel = QString("欢迎你，%1同学!").arg(query.value(3).toString());
        ui->welcomelabel->setText(wel);
    }

    //查询待考试数量

    int examsnum = 0;
    sql = QString("select * from exams where student = '%1' and hastaken = '未参加';").arg(name);
    if(query.exec(sql))
    {
        examsnum = query.size();
        while(query.next())
        {
            QString a;
            a = query.value(0).toString();
            ui->subjectcomboBox->addItem(a);
        }
    }
    ui->examnumlabel->setNum(examsnum);
    //查询考试成绩
    sql = QString("select * from exams where student = '%1' and hastaken = '已批改';").arg(name);
    if(query.exec(sql))
    {
        examsnum = query.size();
        while(query.next())
        {
            QString a;
            a = query.value(0).toString();
            ui->subjectcomboBox_2->addItem(a);
        }
    }
}


void studentwidget::on_querypushButton_clicked()//查询成绩
{
    QString sql;
    QSqlQuery query;
    QString subject = ui->subjectcomboBox_2->currentText();
    sql = QString("select * from exams where student = '%1' and subject = '%2' and hastaken = '已批改';").arg(name).arg(subject);
    if(query.exec(sql))
    {
        if(query.size() == 0)
        {
            QMessageBox::warning(this,"提示","请选择需要查询的考试科目");
        }
        float score = 0;
        query.next();
        for(int i = 10;i < 15; ++i)
        {
            score += query.value(i).toFloat();
        }
        ui->subjectlineEdit->setText(subject);
        ui->scorelineEdit->setText(QString("%1").arg(score));
    }
}

void studentwidget::on_surechangeButton_clicked()//修改密码
{
    bool ok = true;
    QString newpw = ui->changepwlineEdit->text();
    if(newpw.size() < 6 || newpw.size() > 16)
    {
        QMessageBox::warning(this,"密码提示","密码长度不合法");
        ok = false;
        ui->changepwlineEdit->clear();
        return;
    }
    if(ok)
    {
        QString sql;
        QSqlQuery query;
        sql = QString("update users set passwd = '%1' where id = '%2';").arg(newpw).arg(name);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","修改成功");
        }
        else
        {
            QMessageBox::warning(this,"提示","修改失败");
        }
    }
}

void studentwidget::on_backButton_clicked()//退出
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定退出?"),tr("是"),tr("否"))))
    {
        QApplication* app;
        app->exit(0);
    }
}

void studentwidget::on_beginpushButton_clicked()//开始考试
{
    if(ui->subjectcomboBox->currentText().isNull())
    {
        QMessageBox::warning(this,"提示","请先选择考试科目");
        return;
    }
    QString subject = ui->subjectcomboBox->currentText();
    QString sql;
    QSqlQuery query;
    QString paperid;
    sql = QString("select * from exams where student = '%1' and subject = '%2' and hastaken = '未参加';").arg(name).arg(subject);
    if(query.exec(sql))
    {
        query.next();
        paperid = query.value(3).toString();
    }
    //向服务器发送开始考试消息
    QByteArray ba;
    ba.append(QString("%1开始%2考试\n").arg(name).arg(subject));//封装
    socket->write(ba);//发送

    this->hide();
    examwidget *e = new examwidget(socket,name,paperid);
    e->show();

}

void studentwidget::on_surechangeButton_2_clicked()
{
    bool ok = true;
    QString newname = ui->changenamelineEdit->text();
    if(newname.size() > 5)
    {
        QMessageBox::warning(this,"提示","姓名过长");
        ok = false;
        ui->changenamelineEdit->clear();
        return;
    }
    if(ok)
    {
        QString sql;
        QSqlQuery query;
        sql = QString("update users set name = '%1' where id = '%2';").arg(newname).arg(name);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","修改成功");
            sql = QString("select * from users where id = '%1';").arg(name);
            if(query.exec(sql))
            {
                query.next();
                QString wel;
                wel = QString("欢迎你，%1同学!").arg(query.value(3).toString());
                ui->welcomelabel->setText(wel);
            }
        }
        else
        {
            QMessageBox::warning(this,"提示","修改失败");
        }
    }
}

void studentwidget::on_connectButton_clicked()//连接服务器
{
    //获取ip地址和端口号
    QString IP = ui->iplineEdit->text();
    QString port = ui->portlineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP),port.toShort());

    //连接服务器成功,socket对象会发出信号
    connect(socket,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this,"连接提示","连接服务器成功");
    });
    //连接服务器成功，发送学生id;
    connect(socket,&QTcpSocket::connected,[this]()
    {
        QByteArray ba;
        ba.append(QString("%1连入服务器\n").arg(name));//封装
        socket->write(ba);//发送
    });
    //连接断开
    connect(socket,&QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this,"连接提示","连接断开");
    });


}

void studentwidget::serverinfo()
{
    QString servermessage = QString(socket->readAll());
    qDebug()<<"收到\n"<<servermessage;
    if(name == servermessage)
    {
        QMessageBox::information(this,"考试提示","收到新的考试");
        studentbegin();
    }
}


