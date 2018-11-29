#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGridLayout>
#include <QLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include "globals.h"
#include "loginwindow.h"
#include "boardwindow.h"
#include "gametablewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void slotUserInfo(QString username, int integral, int rank);
    void slotEnterTable(int id, QString player1, QString player2);

    void slotSwitchRecv(QString str);

private:
    LoginWindow* loginWindow; // 积分窗口
    BoardWindow* boardWindow; // 游戏窗口
    QList<GameTableWidget*>tableWidgets; // 每个游戏桌的集合

    QPushButton* loginButton, *nameButton; // 登录按钮、用户名按钮
    QLabel* integralLabel, *rankLabel; // 积分标签、排名标签
};

#endif // MAINWINDOW_H
