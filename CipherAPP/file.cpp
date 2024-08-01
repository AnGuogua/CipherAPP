#include "File.h"


File::File(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.open, SIGNAL(clicked()), this, SLOT(open_click()));
	connect(ui.encrypt, SIGNAL(clicked()), this, SLOT(encrypt_click()));
	connect(ui.decrypt, SIGNAL(clicked()), this, SLOT(decrypt_click())); 
	connect(ui.Setting, SIGNAL(clicked()), this, SLOT(setting_click()));
	sets = new Setting();
}

File::~File()
{
	delete sets;
}


void File::encrypt_click()
{	
	if (path == "")
	{
		QMessageBox::warning(this, "Error", "Please open a file", QMessageBox::Ok);
		return;
	}
	QString outpath = QFileDialog::getOpenFileName(this, "Open a file to save the Ciphertext/Plaintext", "./", "All Files (*.*)");
	if (outpath.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Please select a file", QMessageBox::Ok);
		return;
	}
	QFile output(outpath);
	if (!output.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(this, "Error", "Failed to open file" + outpath, QMessageBox::Ok);
		return;
	}
	QString pt = ui.textEdit->toPlainText();
	QString key = ui.key->text();
	QRegularExpression regex("[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>]");
	key = key.remove(regex);
	QString ci = encrypt(pt, key,false);
	output.write(ci.toUtf8());
	return;
}

void File::decrypt_click()
{
	if (path == "")
	{
		QMessageBox::warning(this, "Error", "Please open a file", QMessageBox::Ok);
		return;
	}
	QString outpath = QFileDialog::getSaveFileName(this, "Open a file to save the Ciphertext/Plaintext", "./", "All Files (*.*)");
	if (outpath.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Please select a file", QMessageBox::Ok);
		return;
	}
	QFile output(outpath);
	if (!output.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(this, "Error", "Failed to open file" + outpath, QMessageBox::Ok);
		return;
	}
	QString ci = ui.textEdit->toPlainText();
	QString key = ui.key->text();
	QRegularExpression regex("[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>]");
	key = key.remove(regex);
	QString pt = decrypt(ci, key, false);
	output.write(pt.toUtf8());
	return;
}

void File::setting_click()
{
	if (!setting_start)
	{
		sets->show();
		setting_start = true;
	}
}

void File::open_click()
{
	path = QFileDialog::getOpenFileName(this, "Open a file to encrypt", "./", "All Files (*.*)");
	if (path.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Please select a file");
		return;
	}
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(this, "Error", "Failed to open file " + path, QMessageBox::Ok);
		return;
	}	
	QByteArray buff = file.read(BufferSize);
	ui.path->setText("Current File: " + path);
	ui.textEdit->setText("");
	while(1){
		
		QString pt(buff);
		ui.textEdit->setText(ui.textEdit->toPlainText() + pt);
		if (!file.atEnd())
		{
			buff = file.read(BufferSize);
		}
		else
		{
			break;
		}
	}
	
}
