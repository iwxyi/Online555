#include "gametablewidget.h"

GameTableWidget::GameTableWidget(QWidget* parent) : QWidget(parent)
{
    this->setFixedSize(TABLE_WIDTH, TABLE_HEIGHT);
}

/**
 * 设置游戏桌的ID
 * @param i ID
 */
void GameTableWidget::setId(int i)
{
    id = i;
}

/**
 * 设置游戏桌的玩家信息
 * @param seat  座位
 * @param name  用户名
 * @param state 状态（0/1/2）
 */
void GameTableWidget::setSeat(int seat, QString name, int state)
{
    if (seat == 1)
    {
        player1 = name;
        ready1 = state==2? true : false;
    }
    else
    {
        player2 = name;
        ready2 = state==2? true : false;
    }
    update();
}

/**
 * 获取用户的状态：0,1,2,3
 * @return 用户状态
 */
int GameTableWidget::getPlayer()
{
    return (player1==""?0:1) + (player2==""?0:2);
}

/**
 * 是否在游戏中，例如关闭窗口时会询问一下
 * @return 是否正在游戏中
 */
bool GameTableWidget::isPlaying()
{
    return ready1 && ready2;
}

/**
 * 重绘事件
 * 画游戏桌和玩家状态
 * @param e
 */
void GameTableWidget::paintEvent(QPaintEvent *e)
{
    int width = this->width();
    int height = this->height();

    int side_length = width >> 1;
    if (side_length >= height)
	side_length = height >> 1;

    int player_length = side_length >> 1;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(width/2-side_length/2, height/2-side_length/2, side_length, side_length);

    if (player1 == "") {
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
	painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    }
    painter.drawEllipse(width/2-side_length/2-player_length, height/2-player_length/2, player_length, player_length);

    if (player2 == "") {
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
	painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    }
    painter.drawEllipse(width/2+side_length/2, height/2-player_length/2, player_length, player_length);

    return QWidget::paintEvent(e);
}

/**
 * 鼠标点击事件
 * @param e [description]
 */
void GameTableWidget::mousePressEvent(QMouseEvent* e)
{
    emit signalPressed(id, player1, player2);
}
