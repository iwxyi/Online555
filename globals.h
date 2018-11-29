#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include "fileutil.h"
#include "socketutil.h"

extern QString AppPath;
extern QString DataPath;

extern QString SERVER_IP;
extern int SERVER_PORT;

extern SocketUtil* SOCKET;

extern QString USERID;
extern QString USERNAME;
extern QString PASSWORD;
extern int INTEGRAL;

extern int TABLE_WIDTH;
extern int TABLE_HEIGHT;
extern int TABLE_H_SPACE;
extern int TABLE_V_SPACE;
extern int TABLE_ROW;
extern int TABLE_COL;
extern int TABLE_ALL;

extern bool deb(QVariant str, QString name);
extern bool deb(QVariant str);
extern QString Path(QString str);

void initGlobal();
void deleteGlobal();

#endif // GLOBAL_H
