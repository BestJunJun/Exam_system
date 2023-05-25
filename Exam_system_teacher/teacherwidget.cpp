#include "teacherwidget.h"
#include "ui_teacherwidget.h"

teacherwidget::teacherwidget(QString s ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherwidget)
{
    ui->setupUi(this);
    server = new QTcpServer;

    //监听8000端口
    server->listen(QHostAddress::AnyIPv4,8000);

    //客户端发起连接，server发出信号
    connect(server,&QTcpServer::newConnection,this,&teacherwidget::newClientHandler);


    //设置欢迎语
    QString sql;
    QSqlQuery query;
    sql = QString("select * from users where id = '%1';").arg(s);
    if(query.exec(sql))
    {
        query.next();
        QString wel;
        wel = QString("欢迎你，%1老师!").arg(query.value(3).toString());
        ui->welcomelabel->setText(wel);
    }
    on_exampushButton_clicked();
}

teacherwidget::~teacherwidget()
{
    delete ui;
}

void teacherwidget::newClientHandler()
{
    QTcpSocket *socket = server->nextPendingConnection();//建立tcp连接

    //socket->peerAddress();  //获取客户端ip地址
    //socket->peerPort();     //获取客户端端口号

    //服务器收到客户端发送的信息，socket发出readyread信号
    connect(socket,&QTcpSocket::readyRead,this,&teacherwidget::clientinfo);
    connect(socket,&QTcpSocket::disconnected,this,&teacherwidget::clientdisconnect);


}

void teacherwidget::clientinfo()
{
    QTcpSocket *s = (QTcpSocket *)sender();//获取信号发出者
    QString clientmessage = QString(s->readAll());
    ui->textBrowser->insertPlainText(clientmessage);
    //如果是连接信息记录连接
    QString c = "连入";
    if(clientmessage.indexOf(c) != -1)//说明信息中包含“连入”
    {
        int index = clientmessage.indexOf(c);
        QString studentid = clientmessage.left(index);//截取学生id
        sockets[studentid] = s;//绑定学生id和连接对应关系
    }

}

void teacherwidget::clientdisconnect()
{
    QTcpSocket *s = (QTcpSocket *)sender();//获取信号发出者
    QString studentid;
    for(auto so : sockets)
    {
        if(so.second == s)
        {
            studentid = so.first;
        }
    }
    ui->textBrowser->insertPlainText(QString("%1断开连接").arg(studentid));
}

void teacherwidget::on_exampushButton_clicked()//考试管理按钮
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->studentscomboBox->clear();
    ui->newexamsubjectlineEdit->clear();
    ui->studentnamelineEdit->clear();
    ui->lengthlineEdit->clear();
    ui->paperidlineEdit->clear();
    ui->studentscomboBox->addItem("所有学生");
    //查询记录所有学生
    vector<QString> students;
    QString sql;
    QSqlQuery query;
    sql = QString("select * from users where identify = 'student';");
    if(query.exec(sql))
    {
        while(query.next())
        {
            students.push_back(query.value(0).toString());
        }
    }
    int n = students.size();
    for(int i = 0; i < n ; ++i)
    {
        ui->studentscomboBox->addItem(students[i]);
    }
}

void teacherwidget::on_questionpushButton_clicked()//题目管理按钮
{
    ui->stackedWidget->setCurrentIndex(1);
    //清屏
    ui->newquestionidlineEdit->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->newquestionidlineEdit_2->clear();
    ui->lineEdit_A->clear();
    ui->lineEdit_B->clear();
    ui->lineEdit_C->clear();
    ui->lineEdit_D->clear();
    ui->newanswerlineEdit_3->clear();
    ui->questionidlineEdit_2->clear();
    ui->questionidlineEdit_2->setEnabled(true);
    ui->questiontypelineEdit->clear();
    ui->questionidlineEdit->clear();
    ui->lineEdit_A_2->clear();
    ui->lineEdit_B_2->clear();
    ui->lineEdit_C_2->clear();
    ui->lineEdit_D_2->clear();
    ui->answerlineEdit->clear();
}

void teacherwidget::on_paperpushButton_clicked()//试卷管理按钮
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->newpaperidlineEdit->clear();
    ui->comboBox_3->clear();
    ui->comboBox_5->clear();
    ui->comboBox_8->clear();
    ui->comboBox_9->clear();
    ui->comboBox_10->clear();
    ui->newquestionnumlineEdit->clear();
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->newpaperidlineEdit_4->clear();
    ui->questionidlineEdit_3->clear();
    ui->questionidlineEdit_4->clear();
    ui->questionidlineEdit_5->clear();
    ui->questionidlineEdit_6->clear();
    ui->questionidlineEdit_7->clear();
    ui->questionnumlineEdit->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->newpaperidlineEdit_4->setEnabled(true);

    //记录所有题目
    QString sql;
    QSqlQuery query;
    vector<QString> ques;
    sql = QString("select * from questions;");
    if(query.exec(sql))
    {
        while(query.next())
        {
            ques.push_back(query.value(0).toString());
        }
    }
    for(int i = 0; i < ques.size(); ++i)
    {
        ui->comboBox_3->addItem(ques[i]);
        ui->comboBox_5->addItem(ques[i]);
        ui->comboBox_8->addItem(ques[i]);
        ui->comboBox_9->addItem(ques[i]);
        ui->comboBox_10->addItem(ques[i]);
    }
}

void teacherwidget::on_markpushButton_clicked()//阅卷管理按钮
{
    ui->stackedWidget->setCurrentIndex(3);
    int papernum;
    QString sql;
    QSqlQuery query;
    sql = QString("select * from exams where hastaken = '待阅卷';");
    if(query.exec(sql))
    {
        papernum = query.size();
    }
    ui->papenumlabel->setNum(papernum);
    ui->label_34->clear();
    ui->label_39->clear();
    ui->studentanstextBrowser->clear();
    ui->curanstextBrowser->clear();
    ui->scorelineEdit->clear();
    ui->paperidlabel->clear();
}

void teacherwidget::on_exitpushButton_clicked()//退出按钮
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定退出?"),tr("是"),tr("否"))))
    {
        QApplication* app;
        app->exit(0);
    }
}


void teacherwidget::on_studentscomboBox_activated(const QString &arg1)//选择学号对应姓名
{
    ui->studentnamelineEdit->clear();
    if(arg1 != "所有学生")
    {
        QString sql;
        QSqlQuery query;
        sql = QString("select * from users where id = '%1';").arg(arg1);
        if(query.exec(sql))
        {
            query.next();
            QString studentname;
            studentname = query.value(3).toString();
            ui->studentnamelineEdit->setText(studentname);
        }
    }
}

void teacherwidget::on_pushButton_clicked()//确定组织考试
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定发布考试?"),tr("是"),tr("否"))))
    {
        bool ok = true;
        QString subject,examlength,paperid;
        QString studentid,studentname;
        subject = ui->newexamsubjectlineEdit->text();
        studentid = ui->studentscomboBox->currentText();
        studentname = ui->studentnamelineEdit->text();
        examlength = ui->lengthlineEdit->text();
        paperid = ui->paperidlineEdit->text();

        if(ui->newexamsubjectlineEdit->text().isEmpty())
        {
            ok = false;
            QMessageBox::information(this,"提示","请输入考试科目");
            return;
        }
        if(ui->lengthlineEdit->text().isEmpty())
        {
            ok = false;
            QMessageBox::information(this,"提示","请输入考试时长");
            return;
        }
        if(ui->paperidlineEdit->text().isEmpty())
        {
            ok = false;
            QMessageBox::information(this,"提示","请输入试卷编号");
            return;
        }
        if(ok)
        {
            //先判断试卷是否存在
            QString sql;
            QSqlQuery query;
            sql = QString("select * from testpapers where paperid = '%1';").arg(paperid);
            if(query.exec(sql))
            {
                if(query.size() < 1)
                {
                    QMessageBox::information(this,"提示","试卷编号不存在");
                    return;
                }
            }
            if(studentid == "所有学生")
            {
                //查询记录所有学生
                vector<QString> students;
                studentsofexam.clear();
                sql = QString("select * from users where identify = 'student';");

                if(query.exec(sql))
                {
                    while(query.next())
                    {
                        students.push_back(query.value(0).toString());
                        studentsofexam.push_back(query.value(0).toString());
                    }
                }
                int n = students.size();
                for(int i = 0; i < n; ++i)
                {
                    sql = QString("insert into exams (subject,student,length,paperid,hastaken) values ('%1','%2','%3','%4','未参加');"
                                  ).arg(subject).arg(students[i]).arg(examlength).arg(paperid);
                    if(query.exec(sql))
                    {

                    }
                    else {
                        ok = false;
                    }
                }
            }
            else {
                studentsofexam.clear();
                studentsofexam.push_back(studentid);
                sql = QString("insert into exams (subject,student,length,paperid,hastaken) values('%1','%2','%3','%4','未参加');"
                              ).arg(subject).arg(studentid).arg(examlength).arg(paperid);
                if(query.exec(sql))
                {

                }
                else {
                    ok = false;
                }
            }
        }
        if(ok)
        {
            QMessageBox::information(this,"提示","考试发布成功");
            //给学生发送考试消息
            for(int i = 0; i < studentsofexam.size(); ++i)
            {
                for(auto so : sockets)
                {
                    if(so.first == studentsofexam[i])
                    {
                        QByteArray ba;
                        ba.append(studentsofexam[i]);//封装
                        so.second->write(ba);//发送
                        qDebug()<<"发送"<<endl;
                    }

                }
            }
            on_exampushButton_clicked();

        }
        else {
            QMessageBox::information(this,"提示","考试发布失败");
        }
    }
}

void teacherwidget::on_newpushButton_clicked()// 新增题目确定按钮
{
    QString sql;
    QSqlQuery query;
    QString questionid,questiontype,question,questionanswer;
    QString A,B,C,D;
    bool ok = true;
    if(ui-> newquestionidlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入题目编号");
        ok = false;
        return;
    }
    else
    {
        questionid = ui->newquestionidlineEdit->text();
        sql = QString("select * from questions where questionid = '%1';").arg(questionid);
        if(query.exec(sql))
        {
            if(query.size()>0)
            {
                QMessageBox::information(this,"提示","题目编号已使用");
                ok = false;
                return;
            }
        }
    }
    if(ui-> newquestionidlineEdit_2->text().isEmpty())//检测题干
    {
        QMessageBox::information(this,"提示","请输入题目题干");
        ok = false;
        return;
    }
    else {
        question = ui-> newquestionidlineEdit_2->text();
    }
    questiontype = ui->comboBox_2->currentText();
    if(questiontype == "选择题")
    {

        if(ui->lineEdit_A->text().isEmpty())//检测A选项
        {
            QMessageBox::information(this,"提示","请输入A选项内容");
            ok = false;
            return;
        }
        else {
            A = ui->lineEdit_A->text();
        }
        if(ui->lineEdit_B->text().isEmpty())//检测B选项
        {
            QMessageBox::information(this,"提示","请输入B选项内容");
            ok = false;
            return;
        }
        else {
            B = ui->lineEdit_B->text();
        }
        if(ui->lineEdit_C->text().isEmpty())//检测C选项
        {
            QMessageBox::information(this,"提示","请输入C选项内容");
            ok = false;
            return;
        }
        else {
            C = ui->lineEdit_C->text();
        }
        if(ui->lineEdit_D->text().isEmpty())//检测D选项
        {
            QMessageBox::information(this,"提示","请输入D选项内容");
            ok = false;
            return;
        }
        else {
            D = ui->lineEdit_D->text();
        }
    }
    //判断答案
    if(ui->newanswerlineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入正确答案");
        ok = false;
        return;
    }
    else if(questiontype == "选择题"
            &&ui->newanswerlineEdit_3->text()!="A"
            &&ui->newanswerlineEdit_3->text()!="B"
            &&ui->newanswerlineEdit_3->text()!="C"
            &&ui->newanswerlineEdit_3->text()!="D")
    {
        QMessageBox::information(this,"提示","答案应为A/B/C/D");
        ok = false;
        return;
    }
    else if(questiontype == "判断题"
            &&ui->newanswerlineEdit_3->text()!="right"
            &&ui->newanswerlineEdit_3->text()!="wrong")
    {
        QMessageBox::information(this,"提示","答案应为right/wrong");
        ok = false;
        return;
    }

    else {
        questionanswer = ui->newanswerlineEdit_3->text();
    }

    //检查完毕

    if(ok)
    {
        if(questiontype == "选择题")
        {
            sql = QString("insert into questions values ('%1','%2','%3','%4','%5','%6','%7','%8');"
                          ).arg(questionid).arg(questiontype).arg(question).arg(A).arg(B).arg(C).arg(D).arg(questionanswer);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增题目成功");
                on_questionpushButton_clicked();
            }
            else {
                QMessageBox::information(this,"提示","新增题目失败");
            }
        }
        else
        {
            sql = QString("insert into questions (questionid,type,question,answer) values ('%1','%2','%3','%4');"
                          ).arg(questionid).arg(questiontype).arg(question).arg(questionanswer);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增题目成功");
                on_questionpushButton_clicked();
            }
            else {
                QMessageBox::information(this,"提示","新增题目失败");
            }
        }
    }
}

void teacherwidget::on_selectpushButton_clicked()//查找题目
{
    QString sql;
    QSqlQuery query;
    QString questionid,questiontype,question,questionanswer;
    QString A,B,C,D;
    bool ok = true;
    if(ui->questionidlineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入题目编号");
        ok = false;
        return;
    }
    else {
        questionid = ui->questionidlineEdit_2->text();
        sql = QString("select * from questions where questionid = '%1';").arg(questionid);
        if(query.exec(sql))
        {
            if(query.size() < 1)
            {
                QMessageBox::information(this,"提示","题目不存在");
                ok = false;
                return;
            }
            else {
                ui->questionidlineEdit_2->setEnabled(false);
                query.next();
                questiontype = query.value(1).toString();
                question = query.value(2).toString();
                A = query.value(3).toString();
                B = query.value(4).toString();
                C = query.value(5).toString();
                D = query.value(6).toString();
                questionanswer = query.value(7).toString();
            }
        }
    }
    if(ok)
    {
        ui->questiontypelineEdit->setText(questiontype);
        ui->questionidlineEdit->setText(question);
        ui->answerlineEdit->setText(questionanswer);
        if(questiontype == "选择题")
        {
            ui->lineEdit_A_2->setText(A);
            ui->lineEdit_B_2->setText(B);
            ui->lineEdit_C_2->setText(C);
            ui->lineEdit_D_2->setText(D);
        }
        else {
            ui->lineEdit_A_2->clear();
            ui->lineEdit_B_2->clear();
            ui->lineEdit_C_2->clear();
            ui->lineEdit_D_2->clear();
        }
    }
}

void teacherwidget::on_updatepushButton_clicked()//修改题目按钮
{
    QString sql;
    QSqlQuery query;
    QString questionid,questiontype,question,questionanswer;
    QString A,B,C,D;
    questionid = ui->questionidlineEdit_2->text();
    bool ok = true;
    if(ui->questionidlineEdit->text().isEmpty())//记录题干
    {
        QMessageBox::information(this,"提示","请输入题目题干");
        ok = false;
        return;
    }
    else {
        question = ui->questionidlineEdit->text();
    }
    //检查题目类型
    if(ui->questiontypelineEdit->text() == "选择题"
            ||ui->questiontypelineEdit->text() == "判断题"
            ||ui->questiontypelineEdit->text() == "填空题"
            ||ui->questiontypelineEdit->text() == "简答题")
    {
        questiontype = ui->questiontypelineEdit->text();
    }
    else {
        QMessageBox::information(this,"提示","请输入正确的题目类型");
        ok = false;
        return;
    }
    //检查ABCD
    if(ui->questiontypelineEdit->text() == "选择题")
    {
        if(ui->lineEdit_A_2->text().isEmpty())//检测A选项
        {
            QMessageBox::information(this,"提示","请输入A选项内容");
            ok = false;
            return;
        }
        else {
            A = ui->lineEdit_A_2->text();
        }
        if(ui->lineEdit_B_2->text().isEmpty())//检测B选项
        {
            QMessageBox::information(this,"提示","请输入B选项内容");
            ok = false;
            return;
        }
        else {
            B = ui->lineEdit_B_2->text();
        }
        if(ui->lineEdit_C_2->text().isEmpty())//检测C选项
        {
            QMessageBox::information(this,"提示","请输入C选项内容");
            ok = false;
            return;
        }
        else {
            C = ui->lineEdit_C_2->text();
        }
        if(ui->lineEdit_D_2->text().isEmpty())//检测D选项
        {
            QMessageBox::information(this,"提示","请输入D选项内容");
            ok = false;
            return;
        }
        else {
            D = ui->lineEdit_D_2->text();
        }
    }
    //检查答案
    if(ui->answerlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入正确答案");
        ok = false;
        return;
    }
    else if(questiontype == "选择题"
            &&ui->answerlineEdit->text()!="A"
            &&ui->answerlineEdit->text()!="B"
            &&ui->answerlineEdit->text()!="C"
            &&ui->answerlineEdit->text()!="D")
    {
        QMessageBox::information(this,"提示","答案应为A/B/C/D");
        ok = false;
        return;
    }
    else if(questiontype == "判断题"
            &&ui->answerlineEdit->text()!="right"
            &&ui->answerlineEdit->text()!="wrong")
    {
        QMessageBox::information(this,"提示","答案应为right/wrong");
        ok = false;
        return;
    }

    else {
        questionanswer = ui->answerlineEdit->text();
    }
    //检查完毕

    if(ok)
    {
        if(questiontype == "选择题")
        {
            sql = QString("update questions set type = '%1',question = '%2',A = '%3',B = '%4',C = '%5',D ='%6',answer = '%7' where questionid = '%8';"
                          ).arg(questiontype).arg(question).arg(A).arg(B).arg(C).arg(D).arg(questionanswer).arg(questionid);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","题目修改成功");
                on_questionpushButton_clicked();
            }
            else {
                QMessageBox::information(this,"提示","题目修改失败");
            }
        }
        else
        {
            sql = QString("update questions set type = '%1',question = '%2',answer = '%3' where questionid = '%4';"
                          ).arg(questiontype).arg(question).arg(questionanswer).arg(questionid);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","题目修改成功");
                on_questionpushButton_clicked();
            }
            else {
                QMessageBox::information(this,"提示","题目修改失败");
            }
        }
    }
}

void teacherwidget::on_deletepushButton_clicked()//删除题目按钮
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定删除题目?"),tr("是"),tr("否"))))
    {
        QString sql;
        QSqlQuery query;
        QString questionid;
        questionid = ui->questionidlineEdit_2->text();
        sql = QString("delete from questions where questionid = '%1';").arg(questionid);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","删除成功");
            on_questionpushButton_clicked();
        }
    }
}

void teacherwidget::on_pushButton_3_clicked()//随机抽取一份试卷
{
    QString sql;
    QSqlQuery query,query1,query2;
    QString paperid;
    sql = QString("select * from exams where hastaken = '待阅卷';");
    if(query.exec(sql))
    {
        if(query.size() > 0)
        {
            query.next();
            paperid = query.value(3).toString();
            choosepaperid = paperid;
            choosestudent = query.value(1).toString();
            ui->paperidlabel->setText(paperid);
            //根据试卷编号找到试卷
            sql = QString("select * from testpapers where paperid = '%1';").arg(paperid);
            if(query1.exec(sql))
            {
                number.clear();
                questions.clear();
                values.clear();
                query1.next();
                for(int i = 0; i < 5; ++i)
                {
                    if(query1.value(i + 1).toString().isEmpty())
                    {
                        break;
                    }
                    else {
                        QString v = query1.value(i + 6).toString();
                        QString qid = query1.value(i + 1).toString();
                        sql = QString("select * from questions where questionid = '%1';").arg(qid);
                        if(query2.exec(sql))
                        {
                            query2.next();
                            if(query2.value(1).toString() == "填空题"
                                    ||query2.value(1).toString() == "简答题")
                            {
                                number.push_back(i);
                                questions.push_back(qid);
                                values.push_back(v);
                            }
                        }
                    }
                }

            }
            //显示第一个未批改的题目
            id = 0;
            ui->label_34->setText(QString("第%1题/共%2题").arg(id + 1).arg(number.size()));
            ui->label_39->setText(QString("本题满分%1分").arg(values[id]));
            ui->studentanstextBrowser->setText(query.value(5 + number[id]).toString());
            sql = QString("select * from questions where questionid = '%1';").arg(questions[id]);
            query1.exec(sql);
            query1.next();
            ui->curanstextBrowser->setText(query1.value(7).toString());
        }
        else {
            QMessageBox::information(this,"提示","没有待阅试卷");
            return;
        }
    }
    ui->paperidlineEdit->setText(paperid);
    sql = QString("select * from testpapers where paperid = '%1';");
}

void teacherwidget::on_scaorepushButton_clicked()//打分并下一题
{
    QString sql;
    QSqlQuery query,query1;
    //检查分数
    if(ui->scorelineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入分数");
        return;
    }
    else if(ui->scorelineEdit->text() > values[id]
            ||ui->scorelineEdit->text() < "0")
    {
        QMessageBox::information(this,"提示","打分不合理");
        return;
    }
    else {
        sql = QString("update exams set score%1 = '%2' where paperid = '%3' and student = '%4';"
                      ).arg(number[id] + 1).arg(ui->scorelineEdit->text()).arg(choosepaperid).arg(choosestudent);
        query.exec(sql);
        sql = QString("select * from exams where paperid = '%1' and student = '%2' and hastaken = '待阅卷';"
                      ).arg(choosepaperid).arg(choosestudent);
        if(query.exec(sql))
        {
            query.next();
            if(id < number.size() - 1)
            {
                ++id;
                ui->label_34->setText(QString("第%1题/共%2题").arg(id + 1).arg(number.size()));
                ui->label_39->setText(QString("本题满分%1分").arg(values[id]));
                ui->studentanstextBrowser->setText(query.value(5 + number[id]).toString());
                sql = QString("select * from questions where questionid = '%1';").arg(questions[id]);
                query1.exec(sql);
                query1.next();
                ui->curanstextBrowser->setText(query1.value(7).toString());
                ui->scorelineEdit->clear();
            }
            else {
                sql = QString("update exams set hastaken = '已批改' where paperid = '%1' and student = '%2';"
                              ).arg(choosepaperid).arg(choosestudent);
                if(query1.exec(sql))
                {
                    QMessageBox::information(this,"提示","试卷批改完成");
                    on_markpushButton_clicked();
                }
            }
        }
    }
}

void teacherwidget::on_pushButton_2_clicked()//新增试卷
{
    QString sql;
    QSqlQuery query;
    QString paperid,ques1,ques2,ques3,ques4,ques5,value1,value2,value3,value4,value5;
    int quesnum;
    bool ok = true;
    //检查试卷编号
    if(ui->newpaperidlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入试卷编号");
        ok = false;
        return;
    }
    else {
        sql = QString("select * from testpapers where paperid = '%1';").arg(ui->newpaperidlineEdit->text());
        if(query.exec(sql))
        {
            if(query.size() > 0)
            {
                QMessageBox::information(this,"提示","试卷编号已使用");
                ok = false;
                return;
            }
            else {
                paperid = ui->newpaperidlineEdit->text();
            }
        }
    }
    //检查题目数量
    if(ui->newquestionnumlineEdit->text().toInt() <= 0
            || ui->newquestionnumlineEdit->text().toInt() > 5)
    {
        QMessageBox::information(this,"提示","题目数量不合规");
        ok = false;
        return;
    }
    else {
        quesnum = ui->newquestionnumlineEdit->text().toInt();
    }
    //检查分值
    if(quesnum >= 1)
    {
        if(ui->lineEdit_1->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第1题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_1->text().toInt() <= 0
                || ui->lineEdit_1->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第1题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value1 = ui->lineEdit_1->text();
        }
    }
    if(quesnum >= 2)
    {
        if(ui->lineEdit_2->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_2->text().toInt() <= 0
                || ui->lineEdit_2->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第2题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value2 = ui->lineEdit_2->text();
        }
    }
    if(quesnum >= 3)
    {
        if(ui->lineEdit_3->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第3题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_3->text().toInt() <= 0
                || ui->lineEdit_3->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第3题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value3 = ui->lineEdit_3->text();
        }
    }
    if(quesnum >= 4)
    {
        if(ui->lineEdit_4->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第4题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_4->text().toInt() <= 0
                || ui->lineEdit_4->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第4题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value4 = ui->lineEdit_4->text();
        }
    }
    if(quesnum == 5)
    {
        if(ui->lineEdit_5->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第5题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_5->text().toInt() <= 0
                || ui->lineEdit_5->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第5题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value5 = ui->lineEdit_5->text();
        }
    }
    ques1 = ui->comboBox_3->currentText();
    ques2 = ui->comboBox_5->currentText();
    ques3 = ui->comboBox_8->currentText();
    ques4 = ui->comboBox_9->currentText();
    ques5 = ui->comboBox_10->currentText();
    if(ok)
    {
        if(quesnum == 1)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1) values ('%1','%2','%3');"
                          ).arg(paperid).arg(ques1).arg(value1);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 2)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1,question2id,value2) values ('%1','%2','%3','%4','%5');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 3)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1,question2id,value2,question3id,value3) "
                          "values ('%1','%2','%3','%4','%5','%6','%7');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 4)
        {
            sql = QString("insert into testpapers "
                          "(paperid , question1id, value1,question2id,value2,question3id,value3,"
                          "question4id,value4) "
                          "values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3)
                    .arg(ques4).arg(value4);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 5)
        {
            sql = QString("insert into testpapers "
                          "(paperid , question1id, value1,question2id,value2,question3id,value3,"
                          "question4id,value4,question5id,value5) "
                          "values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3)
                    .arg(ques4).arg(value4).arg(ques5).arg(value5);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","新增试卷成功");
                on_paperpushButton_clicked();
            }
        }
    }
}

void teacherwidget::on_selectpushButton_2_clicked()//查找试卷
{
    QString sql;
    QSqlQuery query;
    QString paperid;
    vector<QString> ques,vals;
    int quesnum = 0;
    if(ui->newpaperidlineEdit_4->text().isEmpty())
    {
        QMessageBox::information(this,"提示","请输入试卷编号");
        return;
    }
    else {
        sql = QString("select * from testpapers where paperid = '%1';").arg(ui->newpaperidlineEdit_4->text());
        if(query.exec(sql))
        {
            if(query.size() == 0)
            {
                QMessageBox::information(this,"提示","试卷不存在");
                return;
            }
            else {
                paperid = ui->newpaperidlineEdit_4->text();
                ui->newpaperidlineEdit_4->setEnabled(false);
                query.next();
                for(int i = 1; i < 6; ++i)
                {
                    if(query.value(i).toString().isEmpty())
                    {
                        break;
                    }
                    else {
                        ++quesnum;
                        ques.push_back(query.value(i).toString());
                        vals.push_back(query.value(5+i).toString());
                    }
                }
                if(quesnum >= 1)
                {
                    ui->questionidlineEdit_7->setText(ques[0]);
                    ui->lineEdit_8->setText(vals[0]);
                }
                if(quesnum >= 2)
                {
                    ui->questionidlineEdit_3->setText(ques[1]);
                    ui->lineEdit_12->setText(vals[1]);
                }
                if(quesnum >= 3)
                {
                    ui->questionidlineEdit_4->setText(ques[2]);
                    ui->lineEdit_10->setText(vals[2]);
                }
                if(quesnum >= 4)
                {
                    ui->questionidlineEdit_5->setText(ques[3]);
                    ui->lineEdit_13->setText(vals[3]);
                }
                if(quesnum >= 5)
                {
                    ui->questionidlineEdit_6->setText(ques[4]);
                    ui->lineEdit_11->setText(vals[4]);
                }
                ui->questionnumlineEdit->setText(QString("%1").arg(quesnum));
            }
        }
    }
}

void teacherwidget::on_deletepushButton_2_clicked()//删除试卷
{
    if(!(QMessageBox::information(this,tr("提示"),tr("确定删除试卷?"),tr("是"),tr("否"))))
    {
        QString sql;
        QSqlQuery query;
        QString paperid;
        paperid = ui->newpaperidlineEdit_4->text();
        sql = QString("delete from testpapers where paperid = '%1';").arg(paperid);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示","删除成功");
            on_paperpushButton_clicked();
        }
    }
}

void teacherwidget::on_updatepushButton_2_clicked()//修改试卷
{
    QString sql;
    QSqlQuery query;
    QString paperid,ques1,ques2,ques3,ques4,ques5,value1,value2,value3,value4,value5;
    int quesnum;
    bool ok = true;
    paperid = ui->newpaperidlineEdit_4->text();
    //检查题目数量
    if(ui->questionnumlineEdit->text().toInt() <= 0
            || ui->questionnumlineEdit->text().toInt() > 5)
    {
        QMessageBox::information(this,"提示","题目数量不合规");
        ok = false;
        return;
    }
    else {
        quesnum = ui->questionnumlineEdit->text().toInt();
    }
    //检查题号和分值
    if(quesnum >= 1)
    {
        if(ui->questionidlineEdit_7->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第1题的编号");
            ok = false;
            return;
        }
        else {
            sql = QString("select * from questions where questionid = '%1';").arg(ui->questionidlineEdit_7->text());
            if(query.exec(sql))
            {
                if(query.size() == 0)
                {
                    QMessageBox::information(this,"提示","第1题的编号不存在");
                    ok = false;
                    return;
                }
                else {
                    ques1 = ui->questionidlineEdit_7->text();
                }
            }
        }
        if(ui->lineEdit_8->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第1题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_8->text().toInt() <= 0
                || ui->lineEdit_8->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第1题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value1 = ui->lineEdit_8->text();
        }
    }
    if(quesnum >= 2)
    {
        if(ui->questionidlineEdit_3->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的编号");
            ok = false;
            return;
        }
        else {
            sql = QString("select * from questions where questionid = '%1';").arg(ui->questionidlineEdit_3->text());
            if(query.exec(sql))
            {
                if(query.size() == 0)
                {
                    QMessageBox::information(this,"提示","第2题的编号不存在");
                    ok = false;
                    return;
                }
                else {
                    ques2 = ui->questionidlineEdit_3->text();
                }
            }
        }
        if(ui->lineEdit_12->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_12->text().toInt() <= 0
                || ui->lineEdit_12->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第2题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value2 = ui->lineEdit_12->text();
        }
    }
    if(quesnum >= 3)
    {
        if(ui->questionidlineEdit_4->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的编号");
            ok = false;
            return;
        }
        else {
            sql = QString("select * from questions where questionid = '%1';").arg(ui->questionidlineEdit_4->text());
            if(query.exec(sql))
            {
                if(query.size() == 0)
                {
                    QMessageBox::information(this,"提示","第2题的编号不存在");
                    ok = false;
                    return;
                }
                else {
                    ques3 = ui->questionidlineEdit_4->text();
                }
            }
        }
        if(ui->lineEdit_10->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_10->text().toInt() <= 0
                || ui->lineEdit_10->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第2题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value3 = ui->lineEdit_10->text();
        }
    }
    if(quesnum >= 4)
    {
        if(ui->questionidlineEdit_5->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的编号");
            ok = false;
            return;
        }
        else {
            sql = QString("select * from questions where questionid = '%1';").arg(ui->questionidlineEdit_5->text());
            if(query.exec(sql))
            {
                if(query.size() == 0)
                {
                    QMessageBox::information(this,"提示","第2题的编号不存在");
                    ok = false;
                    return;
                }
                else {
                    ques4 = ui->questionidlineEdit_5->text();
                }
            }
        }
        if(ui->lineEdit_13->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_13->text().toInt() <= 0
                || ui->lineEdit_13->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第2题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value4 = ui->lineEdit_13->text();
        }
    }
    if(quesnum >= 5)
    {
        if(ui->questionidlineEdit_6->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的编号");
            ok = false;
            return;
        }
        else {
            sql = QString("select * from questions where questionid = '%1';").arg(ui->questionidlineEdit_6->text());
            if(query.exec(sql))
            {
                if(query.size() == 0)
                {
                    QMessageBox::information(this,"提示","第2题的编号不存在");
                    ok = false;
                    return;
                }
                else {
                    ques5 = ui->questionidlineEdit_6->text();
                }
            }
        }
        if(ui->lineEdit_11->text().isEmpty())
        {
            QMessageBox::information(this,"提示","请输入第2题的分值");
            ok = false;
            return;
        }
        else if(ui->lineEdit_11->text().toInt() <= 0
                || ui->lineEdit_11->text().toInt() > 100)
        {
            QMessageBox::information(this,"提示","第2题的分值设置不合理（应在1-100之间）");
            ok = false;
            return;
        }
        else {
            value5 = ui->lineEdit_11->text();
        }
    }
    if(ok)
    {
        sql = QString("delete from testpapers where paperid = '%1';").arg(paperid);
        query.exec(sql);
        if(quesnum == 1)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1) values ('%1','%2','%3');"
                          ).arg(paperid).arg(ques1).arg(value1);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","修改试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 2)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1,question2id,value2) values ('%1','%2','%3','%4','%5');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","修改试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 3)
        {
            sql = QString("insert into testpapers (paperid , question1id, value1,question2id,value2,question3id,value3) "
                          "values ('%1','%2','%3','%4','%5','%6','%7');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","修改试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 4)
        {
            sql = QString("insert into testpapers "
                          "(paperid , question1id, value1,question2id,value2,question3id,value3,"
                          "question4id,value4) "
                          "values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3)
                    .arg(ques4).arg(value4);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","修改试卷成功");
                on_paperpushButton_clicked();
            }
        }
        if(quesnum == 5)
        {
            sql = QString("insert into testpapers "
                          "(paperid , question1id, value1,question2id,value2,question3id,value3,"
                          "question4id,value4,question5id,value5) "
                          "values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11');"
                          ).arg(paperid).arg(ques1).arg(value1).arg(ques2).arg(value2).arg(ques3).arg(value3)
                    .arg(ques4).arg(value4).arg(ques5).arg(value5);
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示","修改试卷成功");
                on_paperpushButton_clicked();
            }
        }
    }
}

void teacherwidget::on_serverButton_clicked()//服务器动态页
{
    ui->stackedWidget->setCurrentIndex(4);
}
