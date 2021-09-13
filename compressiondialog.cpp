
#include "compressiondialog.h"
#include "ui_compressiondialog.h"
#include"QFile"
#include <string>
#include "iostream"
#include"vector"
#include <unordered_map>
#include <bitset>
#include "QMessageBox"
#include "qdatastream.h"

using namespace std;

compressiondialog::compressiondialog(QWidget *parent,QString x) :
    QDialog(parent),
    ui(new Ui::compressiondialog)
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
       // ui->plainTextEdit_xml->setPlainText(line);
        y =  line.toLocal8Bit().constData();
     }

     cout<<"the uncomp file size:"<<xmlfile.size();
     xmlfile.close();
    file_s = y;
     compressiondialog::lzw_comp_algo(file_s);

     compressiondialog::lzw_decomp_algo();
     string t = "The file size before compression:";


   //"BABAABAAA"
   //"WYS*WYGWYS*WYSWYSG"

}




void compressiondialog:: lzw_comp_algo(string x)
{

    unordered_map<string, int> table;
    //filling table with ASCII code
       for (int i = 0; i <= 255; i++) {
           string ch = "";
           ch += char(i);
           table[ch] = i;
       }

       string p = "", c = "";
          p += x[0];
          int code = 256;
          vector<int> output_code;




          for(int i=0;i<x.length();i++)
          {

              if (i != x.length() - 1)
                 c += x[i + 1];
              if (table.find(p + c) != table.end()) {
                        p = p + c;
                    }
                    else {
                       /* cout << p << "\t" << table[p] << "\t\t"
                             << p + c << "\t" << code << endl;*/

                        output_code.push_back(table[p]);
                        table[p + c] = code;
                        code++;
                        p = c;
                    }
                    c = "";

          }


          string t ="";
          t = t+ x[x.length()-1];
          output_code.push_back(table[t]);


         /*
          1-each encoded vector element max is 12 bit!! so convert each element to 12-bit Binary
          2-append all of them in one string
          2-to store in file using UTF-8 >>convert each 8bits -> the * corresponding ASCII char
          3-store this fucking chars into the fucking file.binary
          */


         QString binary_encoded_str;
         string tempstr = "";
        for(int i=0;i<output_code.size();i++)
        {
            tempstr += bitset<12>(output_code[i]).to_string();

        }
         binary_encoded_str = QString::fromStdString(tempstr);

   // cout<<"the encoded str is:"<<tempstr<<"G"<<endl;
     // cout<<tempstr.length(); tmam the \n is not counted though
    ///making a file (compressed to be:) using qdatastream
    QFile comfile("E:/com.txt");
   if(!comfile.open(QFile::WriteOnly)) cout<<"couldnottttttttttttttttt";
   QDataStream out(&comfile);
   out << binary_encoded_str.toUtf8().constData();


    comfile.flush();
    comfile.close();



}

void compressiondialog:: lzw_decomp_algo()
{

    ////check  by reading the compressed file

    QFile comfile("E:/com.txt");
    //print its size
    cout<<"the compressed file size is:";
    cout<<comfile.size()<<endl;
    string message ="The size after compression = ";
    message += to_string(comfile.size());



    QMessageBox::information(this,"",QString::fromStdString(message));




    QTextStream in(&comfile);
     if(!comfile.open(QFile::ReadOnly)) cout<<"couldnottttttttttttttttt222222";
     QString str;
     qint32 a;
     in >> str;
     comfile.close();
     cout<<endl;


   //qDebug() << str;
   string y = str.toStdString();
     // cout<<y<<endl;
      y = y.substr(6);
     // cout<<y;

///if the is the file is too big i ginna print only part of it

      if(y.length()>6000)
      {
          y = y.substr(0,6000);
          cout<<"after substr"<<endl;
          cout<<y;
      }



   ///substr y to 12 chars each then convert to int
    vector<int> x;
   int counter =0;
   int th = y.length()/12;
    while(counter<th)
    {
        string temp = y.substr(0,12);
      //  cout<<temp<<endl;
      //  long t1 = bitset<12>(temp).to_ulong();
       // x.push_back((int)t1);
       x.push_back(stoi(temp, 0, 2));
       y = y.substr(12);
       counter++;

    }


    //done ;)
    cout<<"decoded int vector"<<endl;
   /* for(int i=0;i<x.size();i++)
    {
        cout<<x[i]<<" ";
    }
*/
    string decomp_str ="";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = x[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
     decomp_str +=s;          //cout << s;
    int count = 256;
    for (int i = 0; i < x.size() - 1; i++) {
        n = x[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        decomp_str +=s;  // cout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }

   // cout<<"decomp "<<decomp_str<<endl;//done:)
     ui->plainTextEdit->setPlainText(QString::fromStdString(decomp_str));




}

compressiondialog::~compressiondialog()
{
    delete ui;
}
