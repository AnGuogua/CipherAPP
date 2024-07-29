#include "Setting.h"
Setting::Setting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.blocksize->setValue(blocksize);
	ui.skipBase64->setChecked(skipBase64);
	QString qs = characters;
	ui.characters->setPlainText(qs);
	hash = new QButtonGroup;
	hash->addButton(ui.SHA3_224, 1);
	hash->addButton(ui.SHA3_256, 2);
	hash->addButton(ui.SHA3_384, 3);
	hash->addButton(ui.SHA3_512, 4);
	hash->addButton(ui.SHA2_224, 5);
	hash->addButton(ui.SHA2_256, 6);
	hash->addButton(ui.SHA2_384, 7);
	hash->addButton(ui.SHA2_512, 8);
	hash->addButton(ui.SHA1, 9);
	hash->addButton(ui.MD5, 10);
	hash->addButton(ui.MD4, 11);
	hash->addButton(ui.BLAKE2, 12);
	hash->button(static_cast<int>(ht) + 1)->click();
	connect(hash,&QButtonGroup::buttonClicked, this, &Setting::hash_type_set);//°´Å¥×é
	connect(ui.blocksize, &QSpinBox::editingFinished, this, &Setting::blocksizechange);//blocksize
	connect(ui.skipBase64, &QRadioButton::clicked, this, &Setting::skipbase64);
	connect(ui.characters, &QTextEdit::textChanged, this, &Setting::characterschange);

}

Setting::~Setting()
{}

void Setting::skipbase64(bool checked)
{
	skipBase64 = ui.skipBase64->isChecked();
}

void Setting::blocksizechange()
{
	blocksize = ui.blocksize->value();
}

void Setting::characterschange()
{
	QString input = ui.characters->toPlainText();
	QString result;
	QString allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.+-*;:`~!@#$%^&/|[]{}()<>";
	for (const QChar &c : input) {
		if (allowedChars.contains(c)) {
			result.append(c);
		}
	}
	characters = result;
}



void Setting::hash_type_set(QAbstractButton * button)
{
	switch (hash->checkedId())
	{
	case 1:
		ht = SHA1;
		break;
	case 2:
		ht = SHA2_224;
		break;
	case 3:
		ht = SHA2_256;
		break;
	case 4:
		ht = SHA2_384;
		break;
	case 5:
		ht = SHA2_512;
		break;
	case 6:
		ht = SHA3_224;
		break;
	case 7:
		ht = SHA3_256;
		break;
	case 8:
		ht = SHA3_384;
		break;
	case 9:
		ht = SHA3_512;
		break;
	case 10:
		ht = MD4;
		break;
	case 11:
		ht = MD5;
		break;
	case 12:
		ht = BLAKE2;
		break;
	}
}
