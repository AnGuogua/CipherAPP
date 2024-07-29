#pragma once
#ifndef CIPHERAPP_H_

#define CIPHERAPP_H_

#include <QtWidgets/QMainWindow>
#include <QWidget>
#include<QTextCursor>
#include<Qstring>
#include<QClipboard>
#include <QMessageBox>
#include <QRegularExpression>
#include<QFileDialog>
#include "ui_CipherAPP.h"
#include "cipher.h"
#include"setting.h"

class Setting;//前向声明
class CipherAPP : public QMainWindow
{
	Q_OBJECT

	public:
	CipherAPP(QWidget *parent = nullptr);
	~CipherAPP();
	void closeEvent(QCloseEvent *event) override
	{
		// 自定义关闭行为（如果有）
		QApplication::quit();
	}

	private:
	Ui::CipherAPPClass ui;
	Setting* sets;
	public slots:
	void Encrypt_click();
	void Decrypt_click();
	void Setting_click();
	void Copy_click();
	void Autocopy(bool checked);
};
#endif // !CIPHERAPP_H_