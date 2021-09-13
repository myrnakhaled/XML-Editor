#ifndef JSONWINDOW_H
#define JSONWINDOW_H

#include <QDialog>
#include <string.h>
using namespace std;

namespace Ui {
class jsonwindow;
}

class jsonwindow : public QDialog
{
    Q_OBJECT

public:
    explicit jsonwindow(QWidget *parent = nullptr,QString x="hi");
    ~jsonwindow();



private slots:
    void on_convert_button_clicked();

    void on_save_button_clicked();

private:
    Ui::jsonwindow *ui;
     QString fpathprivate;
     string file_s;

};

#endif // JSONWINDOW_H
