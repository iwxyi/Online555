#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include "chequer.h"

class BoardWidget : public QWidget, public Chequer
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = 0);

    void setMe(int x);
    void toGameOver(int p);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* e);
    void movesGridEvent(int x, int y);
    void gameOverEvent(int player, int nums);

signals:
    void signalMovesGridEvent(int x, int y);
    void signalGameOverEvent(bool win, int y);

public slots:

private:
    int me;
};

#endif // BOARDWIDGET_H
