#pragma once

#include <QWidget>
#include <QFileDialog>
#include "ui_File.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "cipher.h"
#include "Setting.h"
class File : public QWidget
{
	Q_OBJECT

public:
	File(QWidget *parent = nullptr);
	~File();
	const int BufferSize = 9192;

private:
	Setting *sets;
	Ui::FileClass ui;
	QString path;
	private slots:
	void open_click();
	void encrypt_click(); 
	void decrypt_click();
	void setting_click();
};
