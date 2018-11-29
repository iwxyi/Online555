#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "globals.h"

class GameTableWidget : public QWidget
{
    Q_OBJECT
public:
    GameTableWidget(QWidget *parent);

    void setId(int i);
    void setSeat(int seat, QString name, int state);

    int getPlayer();
    bool isPlaying();

protected:
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent* e);

signals:
    void signalPressed(int id, QString player1, QString player2);

private:
    QString player1, player2;
    bool ready1, ready2;
    int col, row, id;
};

#endif // GAMETABLE_H
