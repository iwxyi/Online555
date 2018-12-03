#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("多人在线五子棋");
    this->setFixedSize(1000, 600);

    QWidget* scrollWidget = new QWidget;
    QScrollArea* scrollArea = new QScrollArea(this);
    QGridLayout* tablesLayout = new QGridLayout();
    scrollWidget->setLayout(tablesLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setGeometry(this->geometry());
    scrollArea->viewport()->setBackgroundRole(QPalette::Dark); // 修改背景色
    scrollArea->viewport()->setAutoFillBackground(true);       // 促使上一句生效
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true); // 允许控件重新调整大小
    scrollArea->show();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* btnsLayout = new QHBoxLayout();
    mainLayout->addLayout(btnsLayout);
    mainLayout->addWidget(scrollWidget);

    QWidget* widget = new QWidget;
    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);

    loginWindow = new LoginWindow(this);
    connect(SOCKET, SIGNAL(signalToLoginWindow(QString)), loginWindow, SLOT(slotSwitchRecv(QString)));

    boardWindow = new BoardWindow(this);
    connect(SOCKET, SIGNAL(signalToBoardWindow(QString)), boardWindow, SLOT(slotSwitchRecv(QString)));

    // 网格列表
    int table_id = 1;
    for (int i = 0; i < TABLE_ROW; i++)
        for (int j = 0; j < TABLE_COL; j++)
        {
            GameTableWidget* table = new GameTableWidget(this);
            table->setId(table_id++);
            tablesLayout->addWidget(table, i, j, 1, 1);
            tableWidgets.append(table);
            connect(table, SIGNAL(signalPressed(int,QString,QString)), this, SLOT(slotEnterTable(int,QString,QString)));
        }
    for (int i = 0; i < TABLE_COL; i++) {
        tablesLayout->setColumnStretch(i, 1);
        tablesLayout->setColumnMinimumWidth(i, TABLE_WIDTH);
    }
    for (int i = 0; i < TABLE_ROW; i++){
        tablesLayout->setRowStretch(i, 1);
        tablesLayout->setRowMinimumHeight(i, TABLE_HEIGHT);
    }
    tablesLayout->setHorizontalSpacing(TABLE_H_SPACE);
    tablesLayout->setVerticalSpacing(TABLE_V_SPACE);

    connect(SOCKET, SIGNAL(signalToMainWindow(QString)), this, SLOT(slotSwitchRecv(QString)));

    // 按钮列表
    loginButton = new QPushButton("未登录");
    nameButton = new QPushButton("用户名");
    integralLabel = new QLabel("积分：0");
    rankLabel = new QLabel("排名：1");
    btnsLayout->addWidget(loginButton);
    btnsLayout->addWidget(nameButton);
    btnsLayout->addWidget(integralLabel);
    btnsLayout->addWidget(rankLabel);
    btnsLayout->addStretch(1);

    nameButton->setVisible(false);
    integralLabel->setVisible(false);
    rankLabel->setVisible(false);

    connect(loginButton, QPushButton::clicked, [=]{
        loginWindow->show();
    });
    connect(nameButton, QPushButton::clicked, [=]{
        SOCKET->sendData("rank", "");
    });
    connect(loginWindow, SIGNAL(signalUserInfo(QString,int,int)), this, SLOT(slotUserInfo(QString,int,int)));
    connect(boardWindow, SIGNAL(signalUserInfo(QString,int,int)), this, SLOT(slotUserInfo(QString,int,int)));
}

MainWindow::~MainWindow()
{

}

/**
 * 收到的用户信息信号槽
 * @param username 用户名
 * @param integral 积分
 * @param rank     排名
 */
void MainWindow::slotUserInfo(QString username, int integral, int rank)
{
    if (username != "")
        nameButton->setText(username);
    else if (USERNAME != "")
        nameButton->setText(USERNAME);

    if (integral != 0)
        integralLabel->setText(QString("积分：%1").arg(integral));
    else if (INTEGRAL != 0)
        integralLabel->setText(QString("积分：%1").arg(INTEGRAL));

    if (rank != 0)
        rankLabel->setText(QString("排名：%1").arg(rank));

    loginButton->setVisible(false);
    nameButton->setVisible(true);
    integralLabel->setVisible(true);
    rankLabel->setVisible(true);
}

/**
 * gameTableWidget点击事件触发的加入房间事件
 * @param id      房间ID
 * @param player1 玩家1名称
 * @param player2 玩家2名称
 */
void MainWindow::slotEnterTable(int id, QString player1, QString player2)
{
    if (USERID == "") // 是否需要登录
    {
        loginWindow->show();
        return ;
    }

    boardWindow->enterTable(id, player1, player2, player1=="");
}

/**
 * 判断socket收到的数据
 * @param str 数据
 */
void MainWindow::slotSwitchRecv(QString str)
{
    //QMessageBox::information(this, "receive", str);
    QString kind = getXml(str, "KIND");

    if (kind == "refresh")
    {
        str = getXml(str, "TABLES");
        QStringList tables = getStrMids(str, "<T>", "</T>");
        int len = tables.size()>TABLE_ALL ? TABLE_ALL : tables.size();
        for (int i = 0; i < len; i++)
        {
            QString table = tables.at(i);
            int state1 = getXml(table, "STATE1").toInt();
            QString name1 = getXml(table, "USERNAME1");
            tableWidgets.at(i)->setSeat(1, name1, state1);
            int state2 = getXml(table, "STATE2").toInt();
            QString name2 = getXml(table, "USERNAME2");
            tableWidgets.at(i)->setSeat(2, name2, state2);
        }
        this->update();
    }
    else if (kind == "rank")
    {
        QStringList names = getStrMids(str, "<N>", "</N>");
        QStringList ranks = getStrMids(str, "<R>", "</R>");
        QStringList intes = getStrMids(str, "<I>", "</I>");

        QString msg = "排名\t昵称\t积分\n";
        for (int i = 0; i < names.size(); i++)
            msg += ranks.at(i) + "\t" + names.at(i) + "\t" + intes.at(i) + "\n";
        QMessageBox::information(this, tr("游戏排名"), msg);
    }
}
