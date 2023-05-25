#include <vector>

using namespace std;

#ifndef EXAMWIDGET_H
#define EXAMWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTimer>
#include <QDebug>
#include <QTcpSocket>

namespace Ui {
class examwidget;
}

class examwidget : public QWidget
{
    Q_OBJECT

public:
    explicit examwidget(QTcpSocket *socket1,QString n,QString s,QWidget *parent = nullptr);
    ~examwidget();

private slots:
    void on_backpushButton_clicked();

    void on_nextpushButton_clicked();

    void on_handpushButton_2_clicked();

    void updateTime();

    void handinpaper();

    void sendhandmessage();

private:
    Ui::examwidget *ui;
    QString name,paperid;
    int questionnum;//记录题目数量
    int Objectivequestionnum;//记录客观题数量
    QString state;//记录交卷后状态
    int minute ;//考试时长(单位分钟)
    vector<QString> questions;//记录每道题编号
    vector<QString> values;//记录每道题分值
    int currentpage;
    QTimer *timer;
    int m_secCnt;
    int m_minCnt;
    QTcpSocket *socket;
};

#endif // EXAMWIDGET_H
