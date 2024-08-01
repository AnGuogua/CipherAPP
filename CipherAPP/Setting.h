#pragma once
#ifndef SETTING_H_
#define SETTING_H_
#include <QWidget>
#include<QButtonGroup>
#include <QAbstractButton>
#include "ui_Setting.h"

#include "parent.h"

class Setting : public QWidget
{
	Q_OBJECT

public:
	Setting(QWidget *parent = nullptr);
	~Setting();
	void closeEvent(QCloseEvent *event) override
	{
		// 自定义关闭行为（如果有）
		setting_start = false;
	}

private:
	Ui::SettingClass ui;
	QButtonGroup *hash;

private slots:
void hash_type_set(QAbstractButton *button);
void skipbase64(bool checked);
void blocksizechange();
void characterschange();
};

#endif // !SETTING_H_
