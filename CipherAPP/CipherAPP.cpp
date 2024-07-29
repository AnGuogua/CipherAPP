#include "CipherAPP.h"

CipherAPP::CipherAPP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.encrypt, SIGNAL(clicked()), this, SLOT(Encrypt_click()));
	connect(ui.decrypt, SIGNAL(clicked()), this, SLOT(Decrypt_click()));
	connect(ui.setting, SIGNAL(clicked()), this, SLOT(Setting_click()));
	connect(ui.copy, SIGNAL(clicked()), this, SLOT(Copy_click()));
	connect(ui.radioButton, SIGNAL(toggled()), this, SLOT(Autocopy()));
	sets = new Setting();
}

CipherAPP::~CipherAPP()
{

	delete sets;
}
void CipherAPP::Encrypt_click()
{
	ui.Status->setText("Working");
	QString pt = ui.input->toPlainText();
	pt.replace("\n", "");
	pt.replace("\\n", "\n");
	if (pt == "")
	{
		ui.Status->setText("Error");
		ui.output->setPlainText("Please enter PlainText");
	}
	QString key = ui.key->text();
	QRegularExpression regex("[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>]");
	key = key.remove(regex);
	QString ci = encrypt(pt, key);
	ui.output->setPlainText(ci);
	if (autocopy)
	{
		QClipboard *clipboard = QApplication::clipboard();
		// 复制文本到剪贴板
		clipboard->setText(ci);
	}
	ui.Status->setText("Done");
}
void CipherAPP::Decrypt_click()
{
	ui.Status->setText("Working");
	QString ci = ui.input->toPlainText();
	QString key = ui.key->text();
	QRegularExpression regex("[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>]");
	key = key.remove(regex);
	if (ci == "")
	{
		ui.Status->setText("Error");
		ui.output->setPlainText("Please enter CipherText");
	}
	QString pt = decrypt(ci, key);
	ui.output->setPlainText(pt);
	if (autocopy)
	{
		QClipboard *clipboard = QApplication::clipboard();
		// 复制文本到剪贴板
		clipboard->setText(pt);
	}
	ui.Status->setText("Done");
}

void CipherAPP::Setting_click()
{
	
	sets->show();
}

void CipherAPP::Copy_click()
{
	QClipboard *clipboard = QApplication::clipboard();
	// 复制文本到剪贴板
	clipboard->setText(ui.output->toPlainText());
}
void CipherAPP::Autocopy(bool checked)
{
	if (checked)
	{
		autocopy = true;
	}
	else
	{
		autocopy = false;
	}
}
