#include "chequer.h"

Chequer::Chequer()
{
    init();
}

/**
 * 初始化游戏，所有数据都清空
 */
void Chequer::init()
{
    for (int i = 0; i < BOARD_SIZE_MAXN; i++)
        for (int j = 0; j < BOARD_SIZE_MAXN; j++)
        {
            board[i][j] = PIECE_NONE; // 没有落子
            board_static[i][j] = false; // 没有动画
        }

    turn = PIECE_NONE; // 初始化游戏回合
}

/**
 * 开始游戏
 * 黑子先下
 * 暂时没有双三禁手这一类规则
 */
void Chequer::start()
{
    init();
    turn = PIECE_BLACK; // 黑子先下
}

/**
 * 用来确定棋盘的边长 和 格子的边长
 */
void Chequer::setBoardLength(int x)
{
    board_length = x;
    grid_length = x / BOARD_SIZE;
    piece_radius = grid_length * 2 / 5;
}

/**
 * 将鼠标的坐标转到棋盘格子坐标
 * @param mouseX 鼠标X（相对控件）
 * @param mouseY 鼠标Y（相对控件）
 */
void Chequer::movesBoard(int mouseX, int mouseY)
{
    int x = (mouseX+grid_length/2) / grid_length;
    int y = (mouseY+grid_length/2) / grid_length;

    movesGrid(y, x); // X 和 Y 互相换一下……
    movesGridEvent(y, x); // 传给父类 boardWidget，接着发送信号给 boardWindow，用以发送数据给服务端，从而修改对手的棋子
}

/**
 * 棋盘格子落子
 * @param x 格子X
 * @param y 格子Y
 */
void Chequer::movesGrid(int x, int y)
{
    if (x <= 0 || y <= 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) // 超出边界
        return ;
    if (board[x][y] != PIECE_NONE) // 此处已经落子了
        return ;

    board[x][y] = turn; // 设置为当前玩家的棋子

    if (isGameOver(x, y)) // 检测到游戏出结果了
    {
        gameOver(turn);
        return ;
    }

    nextTurn(); // 下一回合
}

/**
 * 返回格子数量，用来 SOCKET 发送给服务端，来判断积分
 * @return 格子数量
 */
int Chequer::getBoardSize()
{
    return BOARD_SIZE;
}

/**
 * 下一个回合是谁
 * turn 用来判断要落子的玩家
 */
void Chequer::nextTurn()
{
    if (turn == PIECE_BLACK)
    {
        turn = PIECE_WHITE;
    }
    else if (turn == PIECE_WHITE)
    {
        turn = PIECE_BLACK;
    }
    // else // turn == PIECE_NONE，游戏未开始进行
}

/**
 * 判断是不是这个玩家落子
 * @return 如果是，返回真
 * 否则返回假，父类不进行操作
 */
bool Chequer::isTurn(int t)
{
    return turn == t;
}

/**
 * 是否形成五子连珠的情形
 * 也可能是棋盘满了，平局
 * @return 是否游戏结束
 */
bool Chequer::isGameOver(int x, int y)
{
    int dx[3] = { -1, 0, 1 };
    int dy[3] = { -1, 0, 1 };
    QString test = "";
    for (int dxx = 0; dxx < 3; dxx++)
        for (int dyy = 0; dyy < 3; dyy++)
            if (dx[dxx] || dy[dyy]) // 当两个不是同时为零的时候
            {
                int count = 1, dis = 0;
                while (count < 5 && ++dis < 5)
                {
                    int tx = x + dx[dxx]*dis, ty = y + dy[dyy]*dis;
                    if (tx <= 0 || tx >= BOARD_SIZE || ty <= 0 || ty >= BOARD_SIZE)
                        break;
                    if (board[tx][ty] != turn)
                        break;
                    test += QString("1(%1, %2) in (%3, %4, %5)\n").arg(tx).arg(ty).arg(dxx).arg(dyy).arg(dis);
                    count++;
                }
                dis = 0;
                while (count < 5 && ++dis < 5)
                {
                    int tx = x - dx[dxx]*dis, ty = y - dy[dyy]*dis;
                    if (tx <= 0 || tx >= BOARD_SIZE || ty <= 0 || ty >= BOARD_SIZE)
                        break;
                    if (board[tx][ty] != turn)
                        break;
                    test += QString("2(%1, %2) in (%3, %4, %5)\n").arg(tx).arg(ty).arg(dxx).arg(dyy).arg(dis);
                    count++;
                }

                if (count >= 5)
                {
                    //QMessageBox::information(NULL, "黑子位置", test);
                    return true;
                }
            }

    for (int i = 1; i < BOARD_SIZE; i++)
        for (int j = 1; j < BOARD_SIZE; j++)
            if (board[i][j] == PIECE_NONE)
                return false; // 棋盘未满

    // 棋盘居然满了……
    turn = PIECE_NONE;
    return true;
}

/**
 * 游戏结束
 * @param player 胜利玩家
 */
void Chequer::gameOver(int player)
{
    QString win_str = "";
    if (player == PIECE_BLACK)
        win_str = "本局已分出结果\n\n玩家一（黑棋）获胜！";
    else if (player == PIECE_WHITE)
        win_str = "本局已分出结果\n\n玩家二（白棋）获胜！";
    else
        win_str = "本局已结束，平局收场，其乐融融~";

    // QMessageBox::information(NULL, "GameOver", win_str);

    int nums = 0;
    for (int i = 1; i < BOARD_SIZE; i++)
        for (int j = 1; j < BOARD_SIZE; j++)
            if (board[i][j] == player)
                nums++;

    gameOverEvent(player, nums); // 显示结果用来交给父类
}

/**
 * 重绘游戏的界面，棋盘、棋子、动画等
 * @param e
 */
void Chequer::paint(QPainter& painter)
{
    // 画棋盘
    QBrush bg_brush(QColor(249, 214, 91), Qt::Dense4Pattern);
    painter.setBrush(bg_brush);
    painter.drawRect(0, 0, board_length, board_length);

    QBrush line_brush(QColor(249, 214, 91), Qt::Dense4Pattern);
    painter.setBrush(line_brush);
    for (int i = 0; i <= BOARD_SIZE; i++)
    {
        painter.drawLine(grid_length * i, 0, grid_length * i, board_length); // 竖线
        painter.drawLine(0, grid_length * i, board_length, grid_length * i); // 横线
    }

    // 画棋子
    for (int i = 0; i < BOARD_SIZE; i++) // 这个是竖着的
        for (int j = 0; j < BOARD_SIZE; j++) // 这个是横着的……
        {
            if (board[i][j] == PIECE_BLACK && !board_static[i][j]) // 画黑棋
            {
                QBrush brush(Qt::black, Qt::SolidPattern);
                painter.setBrush(brush);
            }
            else if (board[i][j] == PIECE_WHITE && !board_static[i][j]) // 画白棋
            {
                QBrush brush(Qt::white, Qt::SolidPattern);
                painter.setBrush(brush);
            }
            else continue;
            painter.drawEllipse(grid_length * j - piece_radius, grid_length * i - piece_radius, piece_radius << 1, piece_radius << 1);
        }

    // 画落子动画


    // 画按子动画


}
