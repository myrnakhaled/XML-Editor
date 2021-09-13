#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"
#include "QString"
#include "jsonwindow.h"
#include "compressiondialog.h"
#include "sub_string.h"
#include "format.h"
#include "minify.h"



QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


    void on_pushButton_browsefile_clicked();

    void on_pushButton_check_clicked();

    void on_pushButton_format_clicked();

    void on_pushButton_converttojson_clicked();

    void on_pushButton_compress_clicked();
    void on_pushButton_minify_clicked();

private:
    Ui::MainWindow *ui;
    secDialog* sec;
    jsonwindow* jsonwindow1;
    compressiondialog* compdialog;
    sub_string* sub_string1;
    format* format1;
    minify* min1;


};
#endif // MAINWINDOW_H
