#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include "globals.h"

class LoginWindow : public QDialog
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = 0);


private:
    void initWindow();

signals:
    void signalUserInfo(QString username, int integral, int rank);

public slots:
    void slotRegister();
    void slotLogin();

    void slotSwitchRecv(QString str);

private:
    QString username;
    QString password;

    QLineEdit* edit_username;
    QLineEdit* edit_password;
    QPushButton* btn_register;
    QPushButton* btn_login;

};

#endif // LOGINWINDOW_H
