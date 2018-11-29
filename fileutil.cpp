#include "fileutil.h"

QString readTextFile(QString path)
{
    return readTextFile(path, QTextCodec::codecForName(QByteArray("utf-8")));
}

QString readTextFile(QString path, QString codec)
{
    return readTextFile(path, QTextCodec::codecForName(QString(codec).toLatin1()));
}

QString readTextFile(QString path, QTextCodec *codec)
{
    QString text;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
	QMessageBox::critical(NULL, QObject::tr("错误"), QObject::tr("无法打开文件\n路径：%1").arg(path));
	return "";
    }
    if (!file.isReadable())
    {
	QMessageBox::critical(NULL, QObject::tr("错误"), QObject::tr("该文件不可读\n路径：%1").arg(path));
	return "";
    }
    QTextStream textStream(&file);
    textStream.setCodec(codec);
    while(!textStream.atEnd())
    {
	text = textStream.readAll();
    }
    file.close();

    return text;
}

bool writeTextFile(QString path, QString text)
{
    return writeTextFile(path, text, QTextCodec::codecForName(QByteArray("utf-8")));
}

bool writeTextFile(QString path, QString text, QTextCodec *codec)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
	QMessageBox::critical(NULL, QObject::tr("保存失败"), QObject::tr("打开文件失败\n路径：%1").arg(path));
	return false;
    }
    QTextStream textStream(&file);
    textStream.setCodec(codec);
    textStream << text;
    file.close();

    return true;
}

bool writeTextFile(QString path, QString text, QString codec)
{
    return writeTextFile(path, text, QTextCodec::codecForName(QString(codec).toLatin1()));
}


bool isFileExist(QString path)
{
    QFileInfo fileInfo(path);
    return fileInfo.exists();
}

bool isDir(QString path)
{
    QFileInfo fileInfo(path);
    if (!fileInfo.exists()) // 需要确保存在……
	return false;
    return fileInfo.isDir();
}

bool ensureFileExist(QString path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.exists())
    {
	if (fileInfo.isDir())
	{
	    QDir dir(path);
	    dir.rmdir(path); // 删除目录


	    QFile file(path);
	    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // 创建文件
		QMessageBox::critical(NULL, QObject::tr("创建失败"), QObject::tr("创建文件失败\n路径：%1").arg(path));
	    file.close();

	    return false;
	}
	return true;
    }
    else
    {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // 创建文件
	    QMessageBox::critical(NULL, QObject::tr("创建失败"), QObject::tr("创建文件失败\n路径：%1").arg(path));
	file.close();

	return false;
    }
}

bool ensureDirExist(QString path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.exists() && fileInfo.isFile())
    {
	QFile file(path);
	file.remove(); // 删除文件


	QDir dir(path); // 创建目录
	dir.mkpath(path);

	return false;
    }

    QDir dir(path);
    if (dir.exists())
    {
	return true;
    }
    else
    {
	// dir.mkdir(path) ;// 创建文件夹
	dir.mkpath(path); // 创建多级目录

	return false;
    }
}

QString readExistedTextFile(QString path)
{
    ensureFileExist(path);
    return readTextFile(path, QTextCodec::codecForName(QByteArray("utf-8")));
}

bool ensureFileNotExist(QString path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.exists())
    {
	if (fileInfo.isDir())
	{
	    QDir dir(path);
	    dir.rmdir(path); // 删除目录
	}
	else
	{
	    QFile file(path);
	    file.remove();
	}
	return false;
    }
    return true;
}
