#pragma once
#ifndef Cipher_
#define Cipher_
#include "parent.h"
#include <math.h>
#include <QRandomGenerator>
#include <QDateTime>
//compress headfiles
struct ciblock
{
	QString pt;
	QString ci;
	QString key;
	int id;
	ciblock *next;
};

QString encrypt( QString pt, QString key);
QString decrypt(QString ci, QString key);
ciblock *mergeSort(ciblock *head);
ciblock *mergeTwoLists(ciblock *l1, ciblock *l2);
ciblock *mergeSort2(ciblock *head);
ciblock *mergeTwoLists2(ciblock *l1, ciblock *l2);
QString xor_(QString a, QString b);
QString xand_(QString a, QString b);
#endif // !Cipher_

