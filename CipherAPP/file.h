#pragma once
#include<QFile>
#include<QString>
#include<QFileDialog>
#include "cipher.h"
class file
{
	public:
	file(QString path);
	~file();
	void fencrypt(QString key);
	void fdecrypt(QString key);
	private:
	QString path;

};


