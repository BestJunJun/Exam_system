#include "examwidget.h"
#include "ui_examwidget.h"
using namespace std;

examwidget::examwidget(QTcpSocket *socket1,QString n,QString s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::examwidget)
{
    ui->setupUi(this);
    name = n;
    paperid = s;
    socket = socket1;

    currentpage = 0;//记录当前页码
    ui->stackedWidget->setCurrentIndex(0);//从第一题开始显示

    //记录试卷题目数量
    QString sql;
    QSqlQuery query;
    sql = QString("select * from testpapers where paperid = '%1';").arg(paperid);
    if(query.exec(sql))
    {
        query.next();
        questionnum = 0;
        for(int i = 1; i < 6; ++i)
        {
            if(query.value(i).toString().isEmpty())
            {
                break;
            }
            else {
                questionnum++;
                questions.push_back(query.value(i).toString());
            }
        }
    }


    //记录每道题分值
    sql = QString("select * from testpapers where paperid = '%1';").arg(paperid);
    if(query.exec(sql))
    {
        if(query.next())
        {
            for(int i = 0; i < questionnum;++i)
            {
                values.push_back(query.value(6+i).toString());
            }
        }
    }

    ui -> sumlabel->setText(QString("本试卷共%1道题").arg(questionnum));
    //显示每道题目
    if(questionnum >= 1)//第1道题
    {
        ui->valuelabel_1->setText(QString("(%1分)").arg(values[0]));
        sql = QString("select * from questions where questionid = '%1';").arg(questions[0]);
        if(query.exec(sql))
        {
            query.next();
            if(query.value(1).toString() == "选择题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_1->hide();
                ui->rightradioButton_1->hide();
                ui->wrongradioButton_1->hide();
                ui->questiontextBrowser_1->setText(query.value(2).toString());
                ui->label_A_1->setText(query.value(3).toString());
                ui->label_B_1->setText(query.value(4).toString());
                ui->label_C_1->setText(query.value(5).toString());
                ui->label_D_1->setText(query.value(6).toString());
            }
            else if(query.value(1).toString() == "判断题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_1->hide();
                ui->AradioButton_1->hide();
                ui->BradioButton_1->hide();
                ui->CradioButton_1->hide();
                ui->DradioButton_1->hide();
                ui->label_A_1->hide();
                ui->label_B_1->hide();
                ui->label_C_1->hide();
                ui->label_D_1->hide();
                ui->questiontextBrowser_1->setText(query.value(2).toString());
            }
            else {
                ui->AradioButton_1->hide();
                ui->BradioButton_1->hide();
                ui->CradioButton_1->hide();
                ui->DradioButton_1->hide();
                ui->label_A_1->hide();
                ui->label_B_1->hide();
                ui->label_C_1->hide();
                ui->label_D_1->hide();
                ui->rightradioButton_1->hide();
                ui->wrongradioButton_1->hide();
                ui->questiontextBrowser_1->setText(query.value(2).toString());
            }
        }
    }
    if(questionnum >= 2)//第2道题
    {
        ui->valuelabel_2->setText(QString("(%1分)").arg(values[1]));
        sql = QString("select * from questions where questionid = '%1';").arg(questions[1]);
        if(query.exec(sql))
        {
            query.next();
            if(query.value(1).toString() == "选择题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_2->hide();
                ui->rightradioButton_2->hide();
                ui->wrongradioButton_2->hide();
                ui->questiontextBrowser_2->setText(query.value(2).toString());
                ui->label_A_2->setText(query.value(3).toString());
                ui->label_B_2->setText(query.value(4).toString());
                ui->label_C_2->setText(query.value(5).toString());
                ui->label_D_2->setText(query.value(6).toString());
            }
            else if(query.value(1).toString() == "判断题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_2->hide();
                ui->AradioButton_2->hide();
                ui->BradioButton_2->hide();
                ui->CradioButton_2->hide();
                ui->DradioButton_2->hide();
                ui->label_A_2->hide();
                ui->label_B_2->hide();
                ui->label_C_2->hide();
                ui->label_D_2->hide();
                ui->questiontextBrowser_2->setText(query.value(2).toString());
            }
            else {
                ui->AradioButton_2->hide();
                ui->BradioButton_2->hide();
                ui->CradioButton_2->hide();
                ui->DradioButton_2->hide();
                ui->label_A_2->hide();
                ui->label_B_2->hide();
                ui->label_C_2->hide();
                ui->label_D_2->hide();
                ui->rightradioButton_2->hide();
                ui->wrongradioButton_2->hide();
                ui->questiontextBrowser_2->setText(query.value(2).toString());
            }
        }
    }
    if(questionnum >= 3)//第3道题
    {
        ui->valuelabel_3->setText(QString("(%1分)").arg(values[2]));
        sql = QString("select * from questions where questionid = '%1';").arg(questions[2]);
        if(query.exec(sql))
        {
            query.next();
            if(query.value(1).toString() == "选择题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_3->hide();
                ui->rightradioButton_3->hide();
                ui->wrongradioButton_3->hide();
                ui->questiontextBrowser_3->setText(query.value(2).toString());
                ui->label_A_3->setText(query.value(3).toString());
                ui->label_B_3->setText(query.value(4).toString());
                ui->label_C_3->setText(query.value(5).toString());
                ui->label_D_3->setText(query.value(6).toString());
            }
            else if(query.value(1).toString() == "判断题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_3->hide();
                ui->AradioButton_3->hide();
                ui->BradioButton_3->hide();
                ui->CradioButton_3->hide();
                ui->DradioButton_3->hide();
                ui->label_A_3->hide();
                ui->label_B_3->hide();
                ui->label_C_3->hide();
                ui->label_D_3->hide();
                ui->questiontextBrowser_3->setText(query.value(2).toString());
            }
            else {
                ui->AradioButton_3->hide();
                ui->BradioButton_3->hide();
                ui->CradioButton_3->hide();
                ui->DradioButton_3->hide();
                ui->label_A_3->hide();
                ui->label_B_3->hide();
                ui->label_C_3->hide();
                ui->label_D_3->hide();
                ui->rightradioButton_3->hide();
                ui->wrongradioButton_3->hide();
                ui->questiontextBrowser_3->setText(query.value(2).toString());
            }
        }
    }
    if(questionnum>=4)//第4道题
    {
        ui->valuelabel_4->setText(QString("(%1分)").arg(values[3]));
        sql = QString("select * from questions where questionid = '%1';").arg(questions[3]);
        if(query.exec(sql))
        {
            query.next();
            if(query.value(1).toString() == "选择题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_4->hide();
                ui->rightradioButton_4->hide();
                ui->wrongradioButton_4->hide();
                ui->questiontextBrowser_4->setText(query.value(2).toString());
                ui->label_A_4->setText(query.value(3).toString());
                ui->label_B_4->setText(query.value(4).toString());
                ui->label_C_4->setText(query.value(5).toString());
                ui->label_D_4->setText(query.value(6).toString());
            }
            else if(query.value(1).toString() == "判断题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_4->hide();
                ui->AradioButton_4->hide();
                ui->BradioButton_4->hide();
                ui->CradioButton_4->hide();
                ui->DradioButton_4->hide();
                ui->label_A_4->hide();
                ui->label_B_4->hide();
                ui->label_C_4->hide();
                ui->label_D_4->hide();
                ui->questiontextBrowser_4->setText(query.value(2).toString());
            }
            else {
                ui->AradioButton_4->hide();
                ui->BradioButton_4->hide();
                ui->CradioButton_4->hide();
                ui->DradioButton_4->hide();
                ui->label_A_4->hide();
                ui->label_B_4->hide();
                ui->label_C_4->hide();
                ui->label_D_4->hide();
                ui->rightradioButton_4->hide();
                ui->wrongradioButton_4->hide();
                ui->questiontextBrowser_4->setText(query.value(2).toString());
            }
        }
    }
    if(questionnum>=5)//第5道题
    {
        ui->valuelabel_5->setText(QString("(%1分)").arg(values[4]));
        sql = QString("select * from questions where questionid = '%1';").arg(questions[4]);
        if(query.exec(sql))
        {
            query.next();
            if(query.value(1).toString() == "选择题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_5->hide();
                ui->rightradioButton_5->hide();
                ui->wrongradioButton_5->hide();
                ui->questiontextBrowser_5->setText(query.value(2).toString());
                ui->label_A_5->setText(query.value(3).toString());
                ui->label_B_5->setText(query.value(4).toString());
                ui->label_C_5->setText(query.value(5).toString());
                ui->label_D_5->setText(query.value(6).toString());
            }
            else if(query.value(1).toString() == "判断题")
            {
                ++Objectivequestionnum;
                ui->answertextEdit_5->hide();
                ui->AradioButton_5->hide();
                ui->BradioButton_5->hide();
                ui->CradioButton_5->hide();
                ui->DradioButton_5->hide();
                ui->label_A_5->hide();
                ui->label_B_5->hide();
                ui->label_C_5->hide();
                ui->label_D_5->hide();
                ui->questiontextBrowser_5->setText(query.value(2).toString());
            }
            else {
                ui->AradioButton_5->hide();
                ui->BradioButton_5->hide();
                ui->CradioButton_5->hide();
                ui->DradioButton_5->hide();
                ui->label_A_5->hide();
                ui->label_B_5->hide();
                ui->label_C_5->hide();
                ui->label_D_5->hide();
                ui->rightradioButton_5->hide();
                ui->wrongradioButton_5->hide();
                ui->questiontextBrowser_5->setText(query.value(2).toString());
            }
        }
    }
    if(Objectivequestionnum == questionnum)
    {
        state = "已批改";
    }
    else {
        state = "待阅卷";
    }
    //设置倒计时
    timer = new QTimer;
    m_secCnt = 0;
    m_minCnt = 0;

    sql = QString("select * from exams where paperid = '%1';").arg(paperid);
    if(query.exec(sql))
    {
        query.next();
        minute = query.value(2).toInt();
    }
    ui->lcdNumber->display(QString("%1:00").arg(minute));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);

}




examwidget::~examwidget()
{
    delete ui;
}

void examwidget::on_backpushButton_clicked()//上一题按钮
{
    if(currentpage > 0)
    {
        currentpage--;
        ui->stackedWidget->setCurrentIndex(currentpage);
    }

}

void examwidget::on_nextpushButton_clicked()
{
    if(currentpage < questionnum - 1)
    {
        currentpage++;
        ui->stackedWidget->setCurrentIndex(currentpage);
    }
}

void examwidget::handinpaper()//交卷操作
{
    if(questionnum >= 1)
    {
        QString sql;
        QSqlQuery query;
        QString curanswer;
        sql = QString("select * from questions where questionid = '%1';").arg(questions[0]);
        if(query.exec(sql))
        {
            query.next();
            curanswer = query.value(7).toString();
            QString answer;
            if(query.value(1).toString() == "选择题")
            {
                if(ui->AradioButton_1->isChecked())  answer = QString("A");
                else if(ui->BradioButton_1->isChecked())  answer = QString("B");
                else if(ui->CradioButton_1->isChecked())  answer = QString("C");
                else if(ui->DradioButton_1->isChecked())  answer = QString("D");
                //选择题自动阅卷
                QString v;
                if(answer == curanswer)//如果选择正确
                {
                    v = values[0];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score1 = '%1' where paperid = '%2' and student = '%3';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else if(query.value(1).toString() == "判断题")
            {
                if(ui->rightradioButton_1->isChecked()) answer = QString("right");
                else if(ui->wrongradioButton_1->isChecked()) answer = QString("wrong");
                //判断题自动阅卷
                QString v;
                if(answer == curanswer)
                {
                    v = values[0];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score1 = '%1' where paperid = '%2' and student = '%3';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else answer = ui->answertextEdit_1->toPlainText();

            sql = QString("update exams set answer1 = '%1' where student = '%2' and paperid = '%3'").arg(answer).arg(name).arg(paperid);
            query.exec(sql);
        }
        if(questionnum == 1)
        {
            sendhandmessage();
            sql = QString("update exams set hastaken = '%1' where student = '%2' and paperid = '%3'").arg(state).arg(name).arg(paperid);
            query.exec(sql);
            QMessageBox::information(this,"提示","交卷成功");
            QApplication* app;
            app->exit(0);

        }
    }
    if(questionnum >= 2)
    {
        QString sql;
        QSqlQuery query;
        QString curanswer;
        sql = QString("select * from questions where questionid = '%1';").arg(questions[1]);
        if(query.exec(sql))
        {
            query.next();
            QString answer;
            curanswer = query.value(7).toString();
            if(query.value(1).toString() == "选择题")
            {
                if(ui->AradioButton_2->isChecked())  answer = QString("A");
                else if(ui->BradioButton_2->isChecked())  answer = QString("B");
                else if(ui->CradioButton_2->isChecked())  answer = QString("C");
                else if(ui->DradioButton_2->isChecked())  answer = QString("D");
                //选择题自动阅卷
                QString v;
                if(answer == curanswer)//如果选择正确
                {
                    v = values[1];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score2 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else if(query.value(1).toString() == "判断题")
            {
                if(ui->rightradioButton_2->isChecked()) answer = QString("right");
                else if(ui->wrongradioButton_2->isChecked()) answer = QString("wrong");
                //判断题自动阅卷
                QString v;
                if(answer == curanswer)
                {
                    v = values[1];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score2 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else answer = ui->answertextEdit_2->toPlainText();
            sql = QString("update exams set answer2 = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(answer).arg(name).arg(paperid);
            query.exec(sql);
        }
        if(questionnum == 2)
        {
            sendhandmessage();
            sql = QString("update exams set hastaken = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(state).arg(name).arg(paperid);
            query.exec(sql);
            QMessageBox::information(this,"提示","交卷成功");
            QApplication* app;
            app->exit(0);
        }
    }
    if(questionnum >= 3)
    {
        QString sql;
        QSqlQuery query;
        QString curanswer;
        sql = QString("select * from questions where questionid = '%1';").arg(questions[2]);
        if(query.exec(sql))
        {
            query.next();
            QString answer;
            curanswer = query.value(7).toString();
            if(query.value(1).toString() == "选择题")
            {
                if(ui->AradioButton_3->isChecked())  answer = QString("A");
                else if(ui->BradioButton_3->isChecked())  answer = QString("B");
                else if(ui->CradioButton_3->isChecked())  answer = QString("C");
                else if(ui->DradioButton_3->isChecked())  answer = QString("D");
                //选择题自动阅卷
                QString v;
                if(answer == curanswer)//如果选择正确
                {
                    v = values[2];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score3 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else if(query.value(1).toString() == "判断题")
            {
                if(ui->rightradioButton_3->isChecked()) answer = QString("right");
                else if(ui->wrongradioButton_3->isChecked()) answer = QString("wrong");
                //判断题自动阅卷
                QString v;
                if(answer == curanswer)
                {
                    v = values[2];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score3 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else answer = ui->answertextEdit_3->toPlainText();
            sql = QString("update exams set answer3 = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(answer).arg(name).arg(paperid);
            query.exec(sql);
        }
        if(questionnum == 3)
        {
            sendhandmessage();
            sql = QString("update exams set hastaken = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(state).arg(name).arg(paperid);
            query.exec(sql);
            QMessageBox::information(this,"提示","交卷成功");
            QApplication* app;
            app->exit(0);

        }
    }
    if(questionnum >= 4)
    {
        QString sql;
        QSqlQuery query;
        QString curanswer;
        sql = QString("select * from questions where questionid = '%1';").arg(questions[3]);
        if(query.exec(sql))
        {
            query.next();
            QString answer;
            curanswer = query.value(7).toString();
            if(query.value(1).toString() == "选择题")
            {
                if(ui->AradioButton_4->isChecked())  answer = QString("A");
                else if(ui->BradioButton_4->isChecked())  answer = QString("B");
                else if(ui->CradioButton_4->isChecked())  answer = QString("C");
                else if(ui->DradioButton_4->isChecked())  answer = QString("D");
                //选择题自动阅卷
                QString v;
                if(answer == curanswer)//如果选择正确
                {
                    v = values[3];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score4 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else if(query.value(1).toString() == "判断题")
            {
                if(ui->rightradioButton_4->isChecked()) answer = QString("right");
                else if(ui->wrongradioButton_4->isChecked()) answer = QString("wrong");
                //判断题自动阅卷
                QString v;
                if(answer == curanswer)
                {
                    v = values[3];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score4 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else answer = ui->answertextEdit_4->toPlainText();
            sql = QString("update exams set answer4 = '%1' where student = '%2' and paperid = '%3' and hastaken = '未参加';").arg(answer).arg(name).arg(paperid);
            query.exec(sql);
        }
        if(questionnum == 4)
        {
            sendhandmessage();
            sql = QString("update exams set hastaken = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(state).arg(name).arg(paperid);
            query.exec(sql);
            QMessageBox::information(this,"提示","交卷成功");
            QApplication* app;
            app->exit(0);

        }
    }
    if(questionnum >= 5)
    {
        QString sql;
        QSqlQuery query;
        QString curanswer;
        sql = QString("select * from questions where questionid = '%1';").arg(questions[4]);
        if(query.exec(sql))
        {
            query.next();
            QString answer;
            curanswer = query.value(7).toString();
            if(query.value(1).toString() == "选择题")
            {
                if(ui->AradioButton_5->isChecked())  answer = QString("A");
                else if(ui->BradioButton_5->isChecked())  answer = QString("B");
                else if(ui->CradioButton_5->isChecked())  answer = QString("C");
                else if(ui->DradioButton_5->isChecked())  answer = QString("D");
                //选择题自动阅卷
                QString v;
                if(answer == curanswer)//如果选择正确
                {
                    v = values[3];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score5 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else if(query.value(1).toString() == "判断题")
            {
                if(ui->rightradioButton_5->isChecked()) answer = QString("right");
                else if(ui->wrongradioButton_5->isChecked()) answer = QString("wrong");
                //判断题自动阅卷
                QString v;
                if(answer == curanswer)
                {
                    v = values[3];
                }
                else {
                    v = "0";
                }
                sql = QString("update exams set score5 = '%1' where paperid = '%2' and student = '%3'and hastaken = '未参加';"
                              ).arg(v).arg(paperid).arg(name);
                query.exec(sql);
            }
            else answer = ui->answertextEdit_5->toPlainText();
            sql = QString("update exams set answer5 = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(answer).arg(name).arg(paperid);
            query.exec(sql);
        }
        if(questionnum == 5)
        {
            sendhandmessage();
            sql = QString("update exams set hastaken = '%1' where student = '%2' and paperid = '%3'and hastaken = '未参加';").arg(state).arg(name).arg(paperid);
            query.exec(sql);
            QMessageBox::information(this,"提示","交卷成功");
            QApplication* app;
            app->exit(0);

        }
    }
}

void examwidget::on_handpushButton_2_clicked()//交卷按钮
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定交卷?"),tr("是"),tr("否"))))
    {
       handinpaper();
    }
}

void examwidget::updateTime()//倒计时
{
    m_secCnt++;
    if(m_secCnt >= 60) {
        m_secCnt = 0;
        m_minCnt++;
    }
    if(m_minCnt >= minute) {
        timer->stop();
        m_secCnt = 0;
        m_minCnt = 0;
        QMessageBox::information(this,"提示","考试时间到，自动交卷");
        handinpaper();
    }
    QString min = QString::number(minute - 1 - m_minCnt);
    QString sec = QString::number(60 - m_secCnt);
    if(min.length() == 1) min = "0" + min;
    if(sec.length() == 1) sec = "0" + sec;
    QString timeToShow = min + ":" + sec;
    ui->lcdNumber->display(timeToShow);
}

void examwidget::sendhandmessage()
{
    //向服务器发送完成考试消息
    QByteArray ba;
    ba.append(QString("%1完成考试\n").arg(name));//封装
    socket->write(ba);//发送
}
