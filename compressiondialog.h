#ifndef COMPRESSIONDIALOG_H
#define COMPRESSIONDIALOG_H

#include <QDialog>
#include<string.h>
using namespace std;

namespace Ui {
class compressiondialog;
}

class compressiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit compressiondialog(QWidget *parent = nullptr,QString x = "hi");
    ~compressiondialog();
    void lzw_comp_algo(string x);
    void lzw_decomp_algo();

private:
    Ui::compressiondialog *ui;
    QString fpathprivate;
    string file_s;


};

#endif // COMPRESSIONDIALOG_H
