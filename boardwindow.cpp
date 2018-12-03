#include "boardwindow.h"

BoardWindow::BoardWindow(QWidget *parent) : QDialog(parent)
{
    this->setModal(true);
    this->setGeometry(100, 100,900, 500);
    move( parent->geometry().left()+parent->width()/2-this->width()/2, parent->geometry().top()+parent->height()/2-this->height()/2 );

    btn_static_player1 = new QPushButton("准备完毕");
    btn_static_player2 = new QPushButton("准备完毕");
    lb_static_player1 = new QLabel("未准备好");
    lb_static_player2 = new QLabel("未准备好");
    head_player1 = new QLabel();
    head_player2 = new QLabel();

    QPixmap head_black(":/image/head_black.png");
    QPixmap head_white(":/image/head_white.png");
    head_player1->setPixmap(head_black);
    head_player2->setPixmap(head_white);
    head_player1->setAlignment(Qt::AlignCenter);
    head_player2->setAlignment(Qt::AlignCenter);
    lb_static_player1->setAlignment(Qt::AlignCenter);
    lb_static_player2->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(20);
    lb_static_player1->setFont(font);
    lb_static_player2->setFont(font);
    ready1 = ready2 = false;
    connect(btn_static_player1, QPushButton::clicked,[=](){
        if (!ready1)
        {
            ready1 = true;
            lb_static_player1->setText("等待开始");
            btn_static_player1->setText("取消准备");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::red);
            lb_static_player1->setPalette(pe);

            QString res = makeXml(table_id, "TABLE_ID") + makeXml(1, "TEABLE_SEAT");
            SOCKET->sendData("ready", res);
        }
        else
        {
            ready1 = false;
            lb_static_player1->setText("未准备好");
            btn_static_player1->setText("准备完毕");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::black);
            lb_static_player1->setPalette(pe);

            QString res = makeXml(table_id, "TABLE_ID") + makeXml(1, "TEABLE_SEAT");
            SOCKET->sendData("notready", res);
        }
    });
    connect(btn_static_player2, QPushButton::clicked,[=](){
        if (!ready2)
        {
            ready2 = true;
            lb_static_player2->setText("等待开始");
            btn_static_player2->setText("取消准备");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::red);
            lb_static_player2->setPalette(pe);

            QString res = makeXml(table_id, "TABLE_ID") + makeXml(2, "TEABLE_SEAT");
            SOCKET->sendData("ready", res);
        }
        else
        {
            ready2 = false;
            lb_static_player2->setText("未准备好");
            btn_static_player2->setText("准备完毕");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::black);
            lb_static_player2->setPalette(pe);

            QString res = makeXml(table_id, "TABLE_ID") + makeXml(2, "TEABLE_SEAT");
            SOCKET->sendData("notready", res);
        }
    });

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    boardWidget = new BoardWidget(this);

    leftLayout->addWidget(head_player1);
    leftLayout->addWidget(lb_static_player1);
    leftLayout->addWidget(btn_static_player1);
    leftLayout->setAlignment(Qt::AlignCenter);
    leftLayout->setSpacing(20);

    rightLayout->addWidget(head_player2);
    rightLayout->addWidget(lb_static_player2);
    rightLayout->addWidget(btn_static_player2);
    rightLayout->setAlignment(Qt::AlignCenter);
    rightLayout->setSpacing(20);

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(boardWidget);
    mainLayout->addLayout(rightLayout);

    mainLayout->setStretch(0, 2);
    mainLayout->setStretch(1, 5);
    mainLayout->setStretch(2, 2);

    this->setLayout(mainLayout);

    connect(boardWidget, SIGNAL(signalMovesGridEvent(int,int)), this, SLOT(slotMovesGridEvent(int,int)));
    //connect(boardWidget, SIGNAL(signalGameOverEvent(int,int)), this, SLOT(slotGameOverEvent(int,int)));
}

/**
 * 设置游戏桌玩家的信息
 * @param seat     座位号
 * @param username 用户名
 * @param state    状态（是否准备）
 */
void BoardWindow::setSeat(int seat, QString username, int state)
{
    if (seat == 1)
    {
        player1 = username;
        ready1 = state==2 ? true : false;
    }
    else
    {
        player2 = username;
        ready2 = state==2 ? true : false;
    }
}

/**
 * 加入游戏桌的事件
 * @param id  游戏桌ID，从 1 开始
 * @param s1  用户名1
 * @param s2  用户名2
 * @param is1 是否是座位1（黑子）
 */
void BoardWindow::enterTable(int id, QString s1, QString s2, bool is1)
{
    table_id = id;
    player1 = s1;
    player2 = s2;
    if (is1 == true)
    {
        table_seat = 1;
        btn_static_player1->show();
        btn_static_player2->hide();
        head_player1->show();
        if (player2 == "")
            head_player2->hide();
        else
            head_player2->show();
    }
    else
    {
        table_seat = 2;
        btn_static_player1->hide();
        btn_static_player2->show();
        if (player1 == "")
            head_player1->hide();
        else
            head_player1->show();
        head_player2->show();   
    }
    ready1 = false;
    lb_static_player1->setText("未准备好");
    btn_static_player1->setText("准备完毕");
    ready2 = false;
    lb_static_player2->setText("未准备好");
    btn_static_player2->setText("准备完毕");
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::black);
    lb_static_player1->setPalette(pe);
    lb_static_player2->setPalette(pe);
    boardWidget->setMe(table_seat);

    boardWidget->init();
    this->show();

    SOCKET->sendData("enter", makeXml(table_id, "TABLE_ID")+makeXml(table_seat, "TABLE_SEAT"));
}

/**
 * 关闭窗口事件
 * 如果在游戏中，则打开询问对话框
 * 允许取消关闭
 * @param e 关闭窗口事件
 */
void BoardWindow::closeEvent(QCloseEvent *e)
{
    if (ready1 && ready2)
    {
        if (QMessageBox::question(NULL, "退出", "当前您正在对战，如果现在退出将会默认对方胜利，并且扣除自己的积分，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes)
        {
            e->ignore();
            return ;
        }
        e->accept();
    }
    else
    {
        e->accept();
    }
    SOCKET->sendData(makeXml("leave", "KIND"));
}

/**
 * 由SocketUtil传过来的信号
 * 判断数据中的内容，并进行对应的操作
 * @param str [description]
 */
void BoardWindow::slotSwitchRecv(QString str)
{
    QString kind = getXml(str, "KIND");

    if (kind == "come") // 对手加入
    {
        if (table_seat == 1)
        {
            // 显示2
            head_player2->show();

            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player2->setPalette(pe);
            lb_static_player2->setText("未准备好");
        }
        else
        {
            // 显示1
            head_player1->show();

            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player1->setPalette(pe);
            lb_static_player1->setText("未准备好");
        }
    }
    else if (kind == "leave") // 离开
    {
        ;
    }
    else if (kind == "alone") // 对手离开
    {
        if (table_seat == 1)
        {
            head_player2->hide();

            lb_static_player1->setText("未准备好");
            btn_static_player1->setText("准备下一局");
            btn_static_player1->show();
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player1->setPalette(pe);

            pe.setColor(QPalette::WindowText, Qt::gray);
            lb_static_player2->setPalette(pe);
            if (ready2 == true)
                lb_static_player2->setText("对手已放弃");
            else
                lb_static_player2->setText("对手已离开");
        }
        else
        {
            head_player1->hide();

            if (ready1 == true)
                lb_static_player1->setText("对手已放弃");
            else
                lb_static_player1->setText("对手已离开");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::gray);
            lb_static_player1->setPalette(pe);

            lb_static_player2->setText("未准备好");
            btn_static_player2->setText("准备下一局");
            btn_static_player2->show();
            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player2->setPalette(pe);
        }
        ready1 = false;
        ready2 = false;
        // Chequer::init(); // 离开后继续显示棋局（回顾）
    }
    else if (kind == "ready") // 对手准备完毕
    {
        if (table_seat == 1)
        {
            ready2 = true;
            lb_static_player2->setText("等待开始");
            btn_static_player2->setText("取消准备");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::red);
            lb_static_player2->setPalette(pe);
        }
        else
        {
            ready1 = true;
            lb_static_player1->setText("等待开始");
            btn_static_player1->setText("取消准备");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::red);
            lb_static_player1->setPalette(pe);
        }
        if (ready1 && ready2)
        {
            // slotSwitchRecv(makeXml("start", "KIND")); // 服务端也会发送一个信号用来确认
        }
    }
    else if (kind == "notready") // 对手取消准备
    {
        if (table_seat == 1)
        {
            ready2 = false;
            lb_static_player2->setText("未准备好");
            btn_static_player2->setText("准备完毕");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::black);
            lb_static_player2->setPalette(pe);
        }
        else
        {
            ready1 = false;
            lb_static_player1->setText("未准备好");
            btn_static_player1->setText("准备完毕");
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::black);
            lb_static_player1->setPalette(pe);
        }
    }
    else if (kind == "start") // 开始游戏
    {
        boardWidget->start();
        btn_static_player1->hide();
        btn_static_player2->hide();
        lb_static_player1->setText("正在对战");
        lb_static_player2->setText("正在对战");
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::red);
        lb_static_player1->setPalette(pe);
        lb_static_player2->setPalette(pe);

        boardWidget->update();
    }
    else if (kind == "moves") // 落子
    {
        int id = getXml(str, "TABLE_ID").toInt();
        int seat = getXml(str, "TABLE_SEAT").toInt();
        int x = getXml(str, "PIECE_X").toInt();
        int y = getXml(str, "PIECE_Y").toInt();
        int p = getXml(str, "PLAYER").toInt();
        if (x <= 0 || y <= 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
            return ;
        if (id != table_id /*不是这一桌*/ || seat == table_seat /*是自己*/) return ;
        boardWidget->movesGrid(x, y);
        boardWidget->update();
    }
    else if (kind == "over") // 游戏结束，统计奖励
    {
        int winner = getXml(str, "WINNER").toInt();
        int reward = getXml(str, "REWARD").toInt();
        if (winner == 0) return ;

        if (winner == 1)
        {
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player1->setPalette(pe);
            lb_static_player1->setText("胜利");

            pe.setColor(QPalette::WindowText, Qt::gray);
            lb_static_player2->setPalette(pe);
            lb_static_player2->setText("失败");
        }
        else
        {
            QPalette pe;
            pe.setColor(QPalette::WindowText, Qt::gray);
            lb_static_player1->setPalette(pe);
            lb_static_player2->setText("失败");

            pe.setColor(QPalette::WindowText, Qt::darkYellow);
            lb_static_player2->setPalette(pe);
            lb_static_player2->setText("胜利");
        }
        btn_static_player1->setText("准备下一局");
        btn_static_player2->setText("准备下一局");
        ready1 = false;
        ready2 = false;
        if (table_seat == 1)
        {
            btn_static_player1->show();
        }
        else
        {
            btn_static_player2->show();
        }

        QString msg = "";
        if (winner == table_seat)
        {
            msg = QString("恭喜您获得胜利！\n获得 %1 积分奖励！").arg(reward);
        }
        else
        {
            msg = QString("请您再接再厉！\n获得 %1 积分安慰！").arg(reward);
        }
        QMessageBox::information(this, "结果", msg);

        int integral = getXml(str, "INTEGRAL").toInt();
        int rank = getXml(str, "RANK").toInt();
        emit signalUserInfo("", integral, rank);
    }
}

/**
 * 落子事件，用Socket发送给服务器，在另一台客户端落子
 * @param x
 * @param y
 */
void BoardWindow::slotMovesGridEvent(int x, int y)
{
    QString str = makeXml(table_id, "TABLE_ID") + makeXml(table_seat, "TABLE_SEAT") + makeXml(table_seat, "PLAYER") + makeXml(x, "PIECE_X") + makeXml(y, "PIECE_Y");
    SOCKET->sendData("moves", str);
}

/**
 * 游戏结束信号，boardWidget传递过来的
 * 已废弃
 * @param winner 胜利者
 * @param nums   落子数量
 */
void BoardWindow::slotGameOverEvent(int winner, int nums)
{
    /*
     * 臭 bug，死 bug
     * 好好地信号槽机制
     * 就是死活发不过去
     * 框架的锅我才不背
     * 哼，不想用这厮了
     */
    // QMessageBox::information(this, "slotGameOverEvent", "");
    /*if (winner == table_seat) // 赢的人发送数据
    {
        QString str = makeXml(table_id, "TABLE_ID") + makeXml(table_seat, "TABLE_SEAT") + makeXml(winner, "WINNER") + makeXml(boardWidget->getBoardSize(), "BOARD_SIZE") + makeXml(nums, "PIECE_NUM");
        SOCKET->sendData("over", str);
    }*/
}

