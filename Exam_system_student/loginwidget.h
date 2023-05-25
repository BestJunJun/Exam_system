#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>


namespace Ui {
class Loginwidget;
}

class Loginwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Loginwidget(QWidget *parent = nullptr);
    ~Loginwidget();

private slots:
    void on_RegBackbutton_clicked();
    void on_ToRegButton_clicked();
    void on_LogButton_clicked();
    void on_Regbutton_clicked();
    void on_forgetpwbutton_clicked();
private:
    Ui::Loginwidget* ui;
    QSqlDatabase db;
//    QString namerequire = "请输入用户名";
//    QString pswdrequire = "请输入密码";
};

#endif // LOGINWIDGET_H
