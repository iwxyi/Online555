#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include "stringutil.h"
#include "fileutil.h"

class SocketUtil : public QTcpSocket
{
    Q_OBJECT
public:
    SocketUtil(QString ip, int port);

signals:
    void signalToBoardWindow(QString str);
    void signalToMainWindow(QString str);
    void signalToLoginWindow(QString str);

public slots:
    void slotRecvData();

public:
    void initAndConnect(QString ip, int port);
    void sendData(QString str);
    void sendData(QString kind, QString str);

    void switchRecv(QString str);

private:
    bool isConnect;
};

#endif // SOCKETUTIL_H
