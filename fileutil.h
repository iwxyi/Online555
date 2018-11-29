#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>

QString readTextFile(QString path, QTextCodec* codec = QTextCodec::codecForName("utf-8"));
QString readTextFile(QString path, QString codec);
QString readExistedTextFile(QString path); // 文件不存在则创建
bool writeTextFile(QString path, QString text, QTextCodec* codec = QTextCodec::codecForName("utf-8"));
bool writeTextFile(QString path, QString text, QString codec);

bool isFileExist(QString path);
bool isDir(QString path);
bool ensureFileExist(QString path);
bool ensureDirExist(QString path);
bool ensureFileNotExist(QString path);

#endif // FILEUTIL_H
