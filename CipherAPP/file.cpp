#include"file.h"
file::file(QString qpath)
{
	path = qpath;
}

file::~file()
{

}

void file::fencrypt(QString key)
{
	QFile rfile;
	rfile.setFileName(path);
    QFile wfile;
    QString wpath = QFileDialog::getSaveFileName(nullptr, "Save your Plaintext/Ciphertext as a file", "./", "Text Files(*.txt);;ALL Files(*.*)");
    wfile.setFileName(wpath);
    
    bool rok = rfile.open(QIODevice::ReadOnly | QIODevice::Text);
    bool wok = wfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream write(&wfile);
	if (rok && wok)
	{
        const int bufferSize = 16384; // Define buffer size (16 KB in this case)
        char buffer[bufferSize];
        QString result;
        while (!rfile.atEnd()) {
            qint64 bytesRead = rfile.read(buffer, bufferSize);
            if (bytesRead > 0) {
                // Convert the buffer to QString
                QString chunk = QString::fromUtf8(buffer, bytesRead);
                result = encrypt(chunk, key);
            }
            write << result;
            result = "";
            write << "\n";
        }
	}
    else if (rok)
    {
        //Ð´ÈëÊ§°Ü
    }
    else
    {
        //¶ÁÈ¡Ê§°Ü
    }
    return;
}