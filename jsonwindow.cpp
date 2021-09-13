#include "jsonwindow.h"
#include "ui_jsonwindow.h"
#include "QString"
#include"QFile"
#include <string>
#include "iostream"
#include "node_xml.h"
#include"secdialog.h"
#include"qfiledialog.h"
#include"qmessagebox.h"
using namespace std;

jsonwindow::jsonwindow(QWidget *parent,QString x) :
    QDialog(parent),
    ui(new Ui::jsonwindow)
{
    fpathprivate = x;
    ui->setupUi(this);
    QFile xmlfile(fpathprivate);

    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
        return;

       string y;
     QTextStream in(&xmlfile);
     while (!in.atEnd())
     {

         QString line = in.readAll();
        ui->plainTextEdit_xml->setPlainText(line);
        y =  line.toLocal8Bit().constData();
     }

     xmlfile.close();
    file_s = y;


}

jsonwindow::~jsonwindow()
{
    delete ui;
}

void jsonwindow::on_convert_button_clicked()
{
    //to do
    secDialog sec1;
    node_xml* root = new node_xml();
     root = sec1.xml_to_tree(file_s);

     vector<string> json_str;
     json_str.push_back("{\n");

     sec1.xml_to_json(root,0, 0,0,0,root->childern_nodes.size(),json_str);
     json_str.push_back("}");
    \
     string js;
     cout<<"yadi nilaaaaaa"<<endl;
     for(int i=0;i<json_str.size();i++)
     {
        cout<< json_str[i];
        js += json_str[i];
     }

    ///out to plain txt

   ui->plainTextEdit_json->setPlainText(QString::fromStdString(js));



}


void jsonwindow::on_save_button_clicked()
{
    //fn to save jsontxt file on pc


        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save json file"), "",
            tr("filename (*.txt);;All Files (*)"));
        if (fileName.isEmpty())
              return;
          else {
              QFile file(fileName);
              if (!file.open(QIODevice::WriteOnly)) {
                  QMessageBox::information(this, tr("Unable to open file"),
                      file.errorString());
                  return;
              }
              else
              {
                  //write js string to file specified here
                  QTextStream out(&file);
                  QString text = ui->plainTextEdit_json->toPlainText();
                  out << text;
                  file.flush();
                  file.close();

              }
              }
}
