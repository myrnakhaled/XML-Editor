#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <string.h>
#include "node_xml.h"
using namespace std;

namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr,QString x="hi");
    ~secDialog();
    void setfilepath(const QString &fpath);
    node_xml* xml_to_tree(string x);
    void node_fill(string* xx,node_xml* node);
    void xml_to_json(node_xml * node,int flag,int identicalsiblingnow,int identicalnum,int childnumnow,int parentchildnum,vector<string> &json_str);



private slots:
    void on_pushButton_clicked();

private:
    Ui::secDialog *ui;
    QString fpathprivate;
    string * strarr;
};

#endif // SECDIALOG_H
