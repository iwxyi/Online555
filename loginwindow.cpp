#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent)
{
    initWindow();
}

void LoginWindow::initWindow()
{
    this->setFixedSize(200, 200);
    edit_username = new QLineEdit("");
    edit_password = new QLineEdit("");
    btn_register = new QPushButton("注册");
    btn_login = new QPushButton("登录");

    QRegExp rx("^\\w{3,50}$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);
    edit_username->setValidator(pReg);
    edit_password->setValidator(pReg);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch(1);
    mainLayout->addWidget(edit_username);
    mainLayout->addWidget(edit_password);

    QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addWidget(btn_register);
    btnLayout->addWidget(btn_login);

    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch(1);

    mainLayout->setMargin(30);

    this->setLayout(mainLayout);
    this->setModal(true);

    connect(btn_register, SIGNAL(clicked(bool)), this, SLOT(slotRegister()));
    connect(btn_login, SIGNAL(clicked(bool)), this, SLOT(slotLogin()));
}

/**
 * 注册事件
 */
void LoginWindow::slotRegister()
{
    QString username = edit_username->text();
    QString password = edit_password->text();
    if (username == "" || password == "") return ;

    SOCKET->sendData(makeXml("register", "KIND") + makeXml(username, "USERNAME") + makeXml(password, "PASSWORD"));
}

/**
 * 登录事件
 */
void LoginWindow::slotLogin()
{
    QString username = edit_username->text();
    QString password = edit_password->text();
    if (username == "" || password == "") return ;

    SOCKET->sendData(makeXml("login", "KIND") + makeXml(username, "USERNAME") + makeXml(password, "PASSWORD"));
}

/**
 * 判断socket收到的数据
 * @param str 数据
 */
void LoginWindow::slotSwitchRecv(QString str)
{
    QString kind = getXml(str, "KIND");

    if (kind == "register") // 注册
    {
        QString rst = getXml(str, "RESULT");
        if (rst != "1")
        {
            QMessageBox::information(this, "注册失败", "很抱歉，注册失败！\n请换一个用户名试试。");
        }
        else
        {
            QMessageBox::information(this, "注册成功", "注册成功！\n请牢记您的账号密码。");
            USERID = getXml(str, "USERID");
            USERNAME = edit_username->text();
            PASSWORD = edit_password->text();
            INTEGRAL = 0;
            this->hide(); // 隐藏本窗口

            int integral = getXml(str, "INTEGRAL").toInt();
            int rank = getXml(str, "RANK").toInt();

            emit signalUserInfo(username, integral, rank);
        }
    }
    else if (kind == "login") // 登录
    {
        QString rst = getXml(str, "RESULT");
        if (rst != "1")
        {
            QMessageBox::information(this, "登录失败", "用户名或者密码错误，或者已在其他设备登录");
        }
        else
        {
            QMessageBox::information(this, "登录成功", "欢迎回来！");
            USERID = getXml(str, "USERID");
            USERNAME = edit_username->text();
            PASSWORD = edit_password->text();
            INTEGRAL = getXml(str, "INTEGRAL").toInt();
            this->hide(); // 隐藏本窗口

            int integral = getXml(str, "INTEGRAL").toInt(); // 用户积分
            int rank = getXml(str, "RANK").toInt(); // 用户排名

            emit signalUserInfo(username, integral, rank);
        }
    }
}
