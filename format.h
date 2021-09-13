#ifndef FORMAT_H
#define FORMAT_H

#include <QDialog>
#include <string.h>
using namespace std;

namespace Ui {
class format;
}

class format : public QDialog
{
    Q_OBJECT

public:
    explicit format(QWidget *parent = nullptr,QString x="hi");
    string get_line(string y);
    string get_line1(string y);
    void  get_vector(string y, int num_line );
    int  get_num_of_brackets(string y, int num_line );
    void  get_space(vector<string> v);
    string set_space (vector<int>space,string*temp,vector<string>v,int c, int b);
    string one_string (vector<string>v,string*temp,string yy,int i);
    string minifing (vector<string>v,string*temp,string yy,int i);

    string removeSpaces(string str);
    ~format();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::format *ui;
    QString fpathprivate;
    string file_s;
};

#endif // FORMAT_H
