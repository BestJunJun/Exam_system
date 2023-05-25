#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTimer>
#include <QDebug>

namespace Ui {
class adminwidget;
}

class adminwidget : public QWidget
{
    Q_OBJECT

public:
    explicit adminwidget(QWidget *parent = nullptr);
    ~adminwidget();

private slots:
    void on_regpushButton_clicked();

    void countusersNum();

    void on_useridcomboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_deletepushButton_clicked();

    void on_changepushButton_clicked();

private:
    Ui::adminwidget *ui;
};

#endif // ADMINWIDGET_H
