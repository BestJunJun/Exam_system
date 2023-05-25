#include <vector>

using namespace std;

#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDateTime>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class studentwidget;
}

class studentwidget : public QWidget
{
    Q_OBJECT

public:
    explicit studentwidget(QString s,QWidget *parent = nullptr);
    ~studentwidget();

private slots:

    void studentbegin();

    void serverinfo();

    void on_querypushButton_clicked();

    void on_surechangeButton_clicked();

    void on_backButton_clicked();

    void on_beginpushButton_clicked();

    void on_surechangeButton_2_clicked();

    void on_connectButton_clicked();


private:
    Ui::studentwidget *ui;
    QString name;
    QTcpSocket *socket;
};

#endif // STUDENTWIDGET_H
