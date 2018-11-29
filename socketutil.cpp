#include "socketutil.h"

SocketUtil::SocketUtil(QString ip, int port)
{
    isConnect = false;

    initAndConnect(ip, port);
}

/**
 * 收到数据
 */
void SocketUtil::slotRecvData()
{
    char buffer[10240] = {0};
    this->read(buffer, 10240);
    if (strlen(buffer) > 0)
    {
        QString str(buffer);
        switchRecv(str);
    }
    else
    {
        QMessageBox::information(NULL, "五子棋", "读取收到的数据失败！");
    }
}

/**
 * 连接服务端
 * @param ip   地址
 * @param port 端口
 */
void SocketUtil::initAndConnect(QString ip, int port)
{
    if (isConnect == true) return ;
    this->connectToHost(ip, port);

    if (!this->waitForConnected(30000))
    {
        QMessageBox::information(NULL, "五子棋", "连接服务端失败！");
        isConnect = false;
        return ;
    }

    connect(this, SIGNAL(readyRead()), this, SLOT(slotRecvData()));

    isConnect = true;
}

/**
 * 发送数据给服务器
 * @param str [description]
 */
void SocketUtil::sendData(QString str)
{
    if (str == "") return ;
    char sendChars[1024] = {0};
    strcpy_s(sendChars, str.toStdString().c_str());
    if (isConnect)
    {
        int rst = this->write(sendChars, strlen(sendChars));
        if (rst == -1)
        {
            QMessageBox::information(NULL, "五子棋", "服务端发送数据失败！");
        }
    }
    else
    {
        QMessageBox::information(NULL, "五子棋", "套接字无效，请重新连接！");
    }
}

/**
 * 发送数据给服务器
 * @param kind 发送的信息类型
 * @param str  其余数据
 */
void SocketUtil::sendData(QString kind, QString str)
{
    sendData(QString("<KIND>%1</KIND>%2").arg(kind).arg(str));
}

/**
 * 判断服务端收到的数据
 * 并且按种类分发给本程序的各个对象
 * @param str 收到的数据
 */
void SocketUtil::switchRecv(QString str)
{
    QString kind = getXml(str, "KIND");

    if (kind == "refresh")
    {
        emit signalToMainWindow(str);
    }
    else if (kind == "register")
    {
        emit signalToLoginWindow(str);
    }
    else if (kind == "login")
    {
        emit signalToLoginWindow(str);
    }
    else if (kind == "enter")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "leave")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "come")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "alone")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "ready")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "notready")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "start")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "moves")
    {
        emit signalToBoardWindow(str);
    }
    else if (kind == "over")
    {
        emit signalToBoardWindow(str);
    }
}
