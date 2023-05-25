#include <vector>
#include <map>

using namespace std;

#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDateTime>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class teacherwidget;
}

class teacherwidget : public QWidget
{
    Q_OBJECT

public:
    explicit teacherwidget(QString s,QWidget *parent = nullptr);
    ~teacherwidget();

private slots:

    void newClientHandler();

    void clientinfo();

    void clientdisconnect();

    void on_exampushButton_clicked();

    void on_questionpushButton_clicked();

    void on_paperpushButton_clicked();

    void on_markpushButton_clicked();

    void on_exitpushButton_clicked();

    void on_studentscomboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_newpushButton_clicked();

    void on_selectpushButton_clicked();

    void on_updatepushButton_clicked();

    void on_deletepushButton_clicked();

    void on_pushButton_3_clicked();

    void on_scaorepushButton_clicked();

    void on_pushButton_2_clicked();

    void on_selectpushButton_2_clicked();

    void on_deletepushButton_2_clicked();

    void on_updatepushButton_2_clicked();

    void on_serverButton_clicked();

private:
    Ui::teacherwidget *ui;
    QString name;
    QString choosepaperid,choosestudent;//记录抽取试卷信息
    vector<int> number;//记录主观题试卷题目序号
    vector<QString> questions;//记录主观题编号
    vector<QString> values;//记录分值
    vector<QString> studentsofexam;//记录发布考试涉及的学生
    map<QString,QTcpSocket*> sockets;//记录tcp连接和学生对应关系
    int id;//记录当前展示的是第几题
    QTcpServer *server;
};

#endif // TEACHERWIDGET_H
