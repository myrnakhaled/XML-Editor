#include "format.h"
#include "ui_format.h"
#include "QString"
#include"QFile"
#include <string>
#include "iostream"
#include"qfiledialog.h"
#include"qmessagebox.h"
#include <stack>
#include <vector>

using namespace std;

format::format(QWidget *parent,QString x) :
    QDialog(parent),
    ui(new Ui::format)
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
        ui->plainTextEdit->setPlainText(line);
        y =  line.toLocal8Bit().constData();
     }

     xmlfile.close();
    file_s = y;
}
















stack<string> s1;

stack<string> s_name1;
vector<string>ms1;
vector<int>space(2000,0);
string header[10];
string format:: get_line(string y){
   string yy;
   string y2;
    string y3;
      string first_comment;
      int b=0;

   while( 1){

       if(!((y.find('<') == (y.find('!')-1 ) ) || (y.find('<') == (y.find('?')-1))))
        {
        //cout<<"bbbbbbbbbbbbbbbbbbbbbbbbbbrrrrrrrrrrrrrrrrrrrrrreeeeeeeeeeeeeeeeeeeeeeeeeaaaaaaaaaaaaaaaaaaaakkkkkkkk\n";
        break;
       }
      // cout<<"iiiiiiiiiiinnnnnnnnnnnnn  whiiiiiiile\n";
   if(y.find('<') == y.find('?')-1)
   {
     //substr until \n
       int newlinepos = y.find('\n');
      header[b]= y.substr(0,newlinepos);
      b++;
       y = y.substr(newlinepos+1);

   }
   //handling first comment before root element
   if((y.find('<') == y.find('!')-1  ))
   {
       //substr until \n
         int newlinepos = y.find('\n');
         first_comment = y.substr(0,newlinepos);
          header[b]= y.substr(0,newlinepos);
          b++;
         y = y.substr(newlinepos+1);

   }
      }

   string *s;
string temp[2000];
int i=0;
int j=0;
while(y.length()>3)
{

   temp[i]=y.substr(y.find('<'),y.find('\n')-y.find('<'));
   if(y.find('\n')<2000)
   y = y.substr(y.find('\n')+1);
   else
         y = y.substr(y.find('>')+1);

get_vector(temp[i], i );
i++;
//set_space(space[i]);
//cout<< temp[i]<<endl;

}
get_vector(temp[i], i );
get_space(ms1);
y2=set_space (space,temp,ms1,i,b);
//y3=minifing (ms1,temp,yy, i);
 one_string (ms1,temp,y,i);
 cout<<",,,,,,,,,,,,,,,,,,,,,,,,,,file,,,,,,,,,,,,,,,,,,,"<<endl;
  cout<<y2;
  cout<<",,,,,,,,,,,,,,,,,,,,,,,,,,file,,,,,,,,,,,,,,,,,,,"<<endl;
//cout<<",,,,,,,,,,,,,minify ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"<<endl;
  // cout<<y3;
//cout<<"\n,,,,,,,,,,,,,minify ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"<<endl;

return y2;
}
string format:: get_line1(string y){
   string yy;
   string y2;
    string y3;
      string first_comment;
      int b=0;

   while( 1){

       if(!((y.find('<') == (y.find('!')-1 ) ) || (y.find('<') == (y.find('?')-1))))
        {
        //cout<<"bbbbbbbbbbbbbbbbbbbbbbbbbbrrrrrrrrrrrrrrrrrrrrrreeeeeeeeeeeeeeeeeeeeeeeeeaaaaaaaaaaaaaaaaaaaakkkkkkkk\n";
        break;
       }
      // cout<<"iiiiiiiiiiinnnnnnnnnnnnn  whiiiiiiile\n";
   if(y.find('<') == y.find('?')-1)
   {
     //substr until \n
       int newlinepos = y.find('\n');
      header[b]= y.substr(0,newlinepos);
      b++;
       y = y.substr(newlinepos+1);

   }
   //handling first comment before root element
   if((y.find('<') == y.find('!')-1  ))
   {
       //substr until \n
         int newlinepos = y.find('\n');
         first_comment = y.substr(0,newlinepos);
          header[b]= y.substr(0,newlinepos);
          b++;
         y = y.substr(newlinepos+1);

   }
      }

   string *s;
string temp[2000];
int i=0;
int j=0;
while(y.length()>3)
{

   temp[i]=y.substr(y.find('<'),y.find('\n')-y.find('<'));
   if(y.find('\n')<2000)
   y = y.substr(y.find('\n')+1);
   else
         y = y.substr(y.find('>')+1);

get_vector(temp[i], i );
i++;
//set_space(space[i]);
//cout<< temp[i]<<endl;

}
get_vector(temp[i], i );
get_space(ms1);
//y2=set_space (space,temp,ms1,i,b);
y3=minifing (ms1,temp,yy, i);
 one_string (ms1,temp,y,i);
// cout<<",,,,,,,,,,,,,,,,,,,,,,,,,,file,,,,,,,,,,,,,,,,,,,"<<endl;
//  cout<<y2;
 // cout<<",,,,,,,,,,,,,,,,,,,,,,,,,,file,,,,,,,,,,,,,,,,,,,"<<endl;
cout<<",,,,,,,,,,,,,minify ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"<<endl;
   cout<<y3;
cout<<"\n,,,,,,,,,,,,,minify ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,"<<endl;

return y3;
}
int  format :: get_num_of_brackets(string y, int num_line ){
int i=0;

  for(int i1=0; i1<y.length(); i1++)
  {

  if(y[i1]=='<')
     { s1.push("<");
  i++;

  }
  if(y[i1]=='>')
     { s1.push(">");
  i++;

  }

  }
  //cout<<"iiiiiiiiiiii ............ "<<i<<endl;
  return i;
}
void  format :: get_vector(string y, int num_line ){
  string temp;
  int i=0;
  int num;
 // cout<<"my zeftttttttttttttt "<< y<<endl;
  num = get_num_of_brackets( y,  num_line );
 // cout<<"nummmmmmmmmmnnnnnnnnn  "<<num;
  if(num==2 ){
  if(y.find(' ')>y.find('>')){
      temp=y.substr(y.find('<')+1,y.find('>')-y.find('<')-1);

      if(temp[0]!='!' )
     {

     ms1.push_back(temp);
      //cout<<"my stack is "<<temp<<endl;

  }}else

  {
      temp=y.substr(y.find('<')+1,y.find(' ')-y.find('<')-1);
      if(temp[0]!='!')
     {
      ms1.push_back(temp);
      //cout<<"my stack is "<< temp<<endl;
      }


  }
  }
  int m=2;
  if(num==4  ){
      while(m>0){
           m--;
      if(y.find(' ')>y.find('>')){
          temp=y.substr(y.find('<')+1,y.find('>')-y.find('<')-1);
          y= y.substr(y.find('>')+1);
          y= y.substr(y.find('<')+1,y.find('>')-y.find('<')-1);
          if(temp[0]!='!' )
         {
         ms1.push_back(temp);
          //cout<<"my stack is "<< s_name.top()<<endl;
          // cout<<"my stack is "<<temp<<endl;
          }

      }
      else
      {
          temp=y.substr(y.find('<')+1,y.find(' ')-y.find('<')-1);
          y= y.substr(y.find('>')+1);
          y= y.substr(y.find('<')+1,y.find('>')-y.find('<')-1);
          if(temp[0]!='!' )
         {
         ms1.push_back(temp);
         // cout<<"my stack is "<< s_name.top()<<endl;
           //cout<<"my stack is "<<temp<<endl;
          }

      }


  }

  }
//cout<<"vector siiiiiiiiize "<< ms.size();

  }
void format:: get_space(vector<string> v){

   int s=1;
   space[0] = 0;
   space[1] = 1;

 for(int i=2;i<v.size();i++){

    if((space[i]<space[i-1]||space[i-1]==-5) &&  v[i][0] != '/' ){

        s++;
       space[i]= s ;

    }
    if( v[i][0] == '/'){
        if(v[i]=="/"+v[i-1])
        {space[i]=-5;

        }
        else
          {

            space[i]=s ;

        }
           s--;
    }

 }

}
string format::set_space (vector<int>space,string*temp,vector<string>v,int c,int b){
string s;
   int count ;
   int j=-1;
   //cout<<"bbbbbbbbbbbb  "<<b;
   for(int i1=0;i1<b;i1++){

       cout<<header[i1]<<endl;

     s+=header[i1];
    s+="\n";
    s=s.substr('\0');
   }


 for(int i=0; i<c;i++){
     j++;
     if(space[j]<0) j++;

     count=space[j]*2;
     while (count>0) {
         cout<<" ";
         s+=" ";
          s=s.substr('\0');
         count--;

     }
    cout<<temp[i]<<endl;
     //s+=one_string(v,temp,s,c );
    s+=temp[i];
     s+="\n";
     s=s.substr('\0');

 }

  return s;
}
string format ::removeSpaces(string str)
{
   bool flag=true;
   int count = 0;
   int sub=0;
//int l=str.find('\0');
cout<<" element length "<<str.length();
   for (int i2 = 0; i2<str.length(); i2++){
       if(flag)
        { count=i2;}

       //cout<<"iiiiiiiiiiiiiii"<<i<<endl;
       cout<<"nnnnn...."<<str<<"find element...\n";

        cout <<i2<<"...find >..."<<str.find('>');

       if(i2>str.find('>'))
       {
           flag=false;
       if (str[i2] != ' ' )
           str[count++] = str[i2];

  // str[count] = '\0';
   //str=str.substr(0,str.find('\0'));
       }

   }
   cout<<"...my string before "<<str<<endl<<endl;
   if(flag)
    sub = str.length()-(count+1) ;
   else{
     //  cout<<"flllllllllllllllllaaaaaaagggggggggg\n";
       str=str.substr(0,count);
   }

 cout<<"..count" <<count<<endl;
   cout<<"...my string after "<<str<<endl<<endl;
   return str;
}
string format::minifing (vector<string>v,string*temp,string yy,int i){
   string temp1[1000];

   for(int i11=0;i11<i;i11++){
      temp1[i11]=removeSpaces(temp[i11]) ;
   }
    for(int j=0;j<i;j++){
       yy+=temp1[j];
    }
   return yy;
    }

string format::one_string (vector<string>v,string*temp,string y2,int i){
for(int i11=0;i11<i;i11++){
   y2+=temp[i11];
}
return y2;
}










format::~format()
{
    delete ui;
}

void format::on_pushButton_2_clicked()
{

    string temp = get_line(file_s);
    ui->plainTextEdit_2->setPlainText(QString::fromStdString(temp));
}


void format::on_pushButton_clicked()
{
    //save file

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save file"), "",
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
              QString text = ui->plainTextEdit_2->toPlainText();
              out << text;
              file.flush();
              file.close();

          }
          }
}

