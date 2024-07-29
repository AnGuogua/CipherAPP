#include "CipherAPP.h"
#include <QtWidgets/QApplication>
#include "parent.h"
#pragma comment(lib,"cryptlib.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CipherAPP w;
    w.show();
    return a.exec();
}
