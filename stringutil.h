#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QString>
#include <QStringList>

QStringList getStrMids(QString text, QString l, QString r); // 取中间文本数组
QString getStrMid(QString text, QString l, QString r); // 取中间文本2

QString fnEncode(QString text); // 可使用的文件名编码
QString fnDecode(QString text); // 文件名解码

bool canRegExp(QString str, QString pat);

QString getXml(QString str, QString pat);
QString makeXml(QString str, QString pat);
QString makeXml(int i, QString pat);

#endif // STRINGUTIL_H
