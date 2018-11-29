
#include <QString>
#include <QDebug>
#include <QApplication>
#include "fileutil.h"
#include "stringutil.h"
#include "socketutil.h"

QString AppPath = "";
QString DataPath = "";

QString SERVER_IP = "127.0.0.1";
int SERVER_PORT = 7878;

SocketUtil* SOCKET;

QString USERID = "";
QString USERNAME = "";
QString PASSWORD = "";
int INTEGRAL = 0;

int TABLE_WIDTH = 200;
int TABLE_HEIGHT = 110;
int TABLE_V_SPACE = 30;
int TABLE_H_SPACE = 30;
int TABLE_ROW = 3;
int TABLE_COL = 20;
int TABLE_ALL = 60;

bool deb(QVariant str, QString name)
{
    qDebug() << "-------【" << name << "】-------";
    qDebug() << str.toString() << endl;
    return true;
}

bool deb(QVariant str)
{
    qDebug() << "------------------------";
    qDebug() << str.toString() << endl;
    return true;
}

QString Path(QString str)
{
    if (str.endsWith("/"))
	return DataPath + str;
    else
	return DataPath + str + "/";
}

void initGlobal()
{
    AppPath = QCoreApplication::applicationDirPath();
    DataPath = AppPath + "/Data/";
    ensureDirExist(DataPath);

    SOCKET = new SocketUtil(SERVER_IP, SERVER_PORT);
}

void deleteGlobal()
{

}
