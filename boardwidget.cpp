#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent), Chequer()
{
    int w = parent->width();
    int h = parent->height();

    Chequer::setBoardLength(w>h?h:w);
}

/**
 * 重绘事件
 * 交给父类Chequer的paint函数来做
 */
void BoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Chequer::paint(painter);
}

/**
 * 鼠标点击事件
 * @param e 鼠标事件
 */
void BoardWidget::mousePressEvent(QMouseEvent *e)
{
    int x = e->x(), y = e->y();

    if (Chequer::isTurn(me)) // 是我的回合，点击有效
    {
        movesBoard(x, y);
    }
    else
    {
        ;
    }

    update();
    QWidget::mousePressEvent(e);
}

/**
 * 子类传过来的落子事件
 * @param x
 * @param y
 */
void BoardWidget::movesGridEvent(int x, int y)
{
    emit signalMovesGridEvent(x, y);
}

/**
 * 子类传过来的游戏结束事件
 * 如果是胜利者，则发消息给服务器，获取增长的积分
 * @param player 当前的玩家，即最后一个落子的玩家，即胜利者
 * @param nums   胜利者下了几个棋，越少的话分数越高
 */
void BoardWidget::gameOverEvent(int player, int nums)
{
    //emit signalGameOverEvent(player, nums); // QT 框架的bug，信号总是发不过去……所以干脆就在这个地方弄了
    if (player == me) // 赢的人发送数据
    {
        QString str = makeXml(player, "WINNER") + makeXml(BOARD_SIZE, "BOARD_SIZE") + makeXml(nums, "PIECE_NUM");
        SOCKET->sendData("over", str);
    }
}

/**
 * 设置本机的玩家是谁
 * @param x 玩家序号（1/0）
 */
void BoardWidget::setMe(int x)
{
    me = x;
}

/**
 * 外部调用的游戏结束信号（对手离开）
 * protected 提权
 * 保护gameOver函数
 * @param p 胜利者
 */
void BoardWidget::toGameOver(int p)
{
    Chequer::gameOver(p);
}
