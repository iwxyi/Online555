#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include "boardwidget.h"
#include "globals.h"

class BoardWindow : public QDialog
{
    Q_OBJECT
public:
    BoardWindow(QWidget* parent = 0);

    void setSeat(int seat, QString username, int state);
    void enterTable(int id, QString s1, QString s2, bool is1);
    void closeEvent(QCloseEvent *e);

signals:
    void signalUserInfo(QString username, int integral, int rank);

public slots:
    void slotSwitchRecv(QString str);
    void slotMovesGridEvent(int x, int y);
    void slotGameOverEvent(int winner, int nums);

public:
    BoardWidget* boardWidget;
    QString player1, player2; // 玩家的名称
    int table_id, table_seat;
    bool ready1, ready2;

private:
    QPushButton* btn_static_player1, *btn_static_player2;
    QLabel* lb_static_player1, *lb_static_player2;
    QLabel* head_player1, *head_player2;
};

#endif // BOARDWINDOW_H
