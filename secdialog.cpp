#include "secdialog.h"
#include "ui_secdialog.h"
#include "mainwindow.h"
#include "QFile"
#include "QPlainTextEdit"
#include "QMessageBox"
#include "QDebug"
#include "iostream"
#include<string>
#include "node_xml.h"
#include <stack>
using namespace std;
secDialog::secDialog(QWidget *parent,QString x) :
    QDialog(parent),
    ui(new Ui::secDialog)


{
    fpathprivate = x;
    ui->setupUi(this);
    QFile xmlfile(fpathprivate);
   //  qInfo() << fpathprivate;
    if(!xmlfile.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        cout<<"cannot open file in secdialog"<<endl;
        return;
    }
    int counter = 0;
     cout<<"fisttimeeeeeeeeee"<<endl;
       string y;
     QTextStream in(&xmlfile);
     while (!in.atEnd()) {

         QString line = in.readAll();
         // do things
        ui->plainTextEdit->setPlainText(line);
        y =  line.toLocal8Bit().constData();
        //cout<<y;

     }

     xmlfile.close();
     node_xml* root = new node_xml();
      root = secDialog::xml_to_tree(y);
     /* cout<<root->elementname<<"+"<<root->attrval[0]<<endl;
      cout<<root->childern_nodes[0]->elementname<<endl;
      cout<<root->childern_nodes[2]->childern_nodes[0]->childern_nodes.size()<<endl;
      cout<<root->childern_nodes[2]->childern_nodes[0]->elementname<<endl;

      cout<<root->childern_nodes[2]->childern_nodes[1]->childern_nodes.size()<<endl;
      cout<<root->childern_nodes[2]->childern_nodes[1]->elementname<<endl;

      cout<<root->childern_nodes[2]->childern_nodes[2]->childern_nodes.size()<<endl;
      cout<<root->childern_nodes[2]->childern_nodes[2]->elementname<<endl;
      */

      int tempnum =1; int tempflag = 0; string* json_str;

    //  secDialog::xml_to_json(root,0, 0,0,0,root->childern_nodes.size(),json_str);
     // cout<<*json_str;






}

void secDialog::node_fill(string* xx,node_xml* node)
{
   string x = *xx;
    int newlpos = 0;
    int spacepos =0;
    int equalpos = 0;
    int quotespos = 0;
    int openbracketpos =0;
    int closebracketpos =0;
      if(x[0] == '<')
      {

          spacepos = x.find(' ');
          closebracketpos = x.find('>');
          //if tag has NOO attributes
          if(closebracketpos < spacepos)
          {
              node->elementname = x.substr(1,closebracketpos-1); //fill the element
              x = x.substr(closebracketpos+1);//updated
          }

          else if(closebracketpos > spacepos)
          {
              node->elementname = x.substr(1,spacepos-1); //fill the element
              x = x.substr(spacepos+1);

              //it may has more than one attr>>so loop till x[i] == '>'
              int i =0;
              while(x[0] != '>')
              {
                  equalpos = x.find('=');
                   //cout<<"equalpos:"<<equalpos<<endl;
                  node->attrname.push_back(x.substr(0,equalpos));

                  x = x.substr(equalpos+2); //i removed " before attr val
                  // cout<<"x after remoooving attr1->"<<x[0]<<endl;

                  quotespos = x.find('"');
                  node->attrval.push_back(x.substr(0,quotespos));
                  x = x.substr(quotespos+1);//done filling attr1
                  if(x[0] == '>')
                  {
                     x = x.substr(1);//remove >;
                     break;
                  }
                  else
                  {
                      x = x.substr(1);//remove space;
                  }



              }

          }







          //store text of the tag if exist!
          if(x[0] != '\n')
          {
              //tag has text
              //compare pos of first '\n' and '<'
              openbracketpos = x.find('<');
              newlpos = x.find('\n');
              if(openbracketpos > newlpos)
              {
              node->text = x.substr(0,newlpos+1);


              x = x.substr(newlpos+1);
              //now x after newline with embedded spaces


              }
              else
              {
                   node->text = x.substr(0,openbracketpos);
                    x = x.substr(newlpos+1);
                   //now x after newline with embedded spaces
              }
          }

      }


         *xx = x;

}


node_xml* secDialog:: xml_to_tree(string x)
{
    string originalx = x;
     node_xml* root =nullptr;
    //first remove <?xml> this line and comment line
    //i may append them later so i gonna save them in tempvars
    string first_comment;
    ///////CRITICALLLLLLLLL
   // x = x.substr(1);
    if(x[0] != '<')
    {
        x = x.substr(x.find('<'));
    }
    if(x[0] == '<' && x[1] == '?')
    {
      //substr until \n
        int newlinepos = x.find('\n');
        x = x.substr(newlinepos+1);

    }
    //handling first comment before root element
    if(x[0] == '<' && x[1] == '!')
    {
        //substr until \n
          int newlinepos = x.find('\n');
          first_comment = x.substr(0,newlinepos);
          x = x.substr(newlinepos+1);

     }
    if(x[0] != '<')
    {
        x = x.substr(x.find('<'));
    }
    cout<<"function output inside xmltreeeeee"<<endl;

    //parsing fucking code
    //first get the root element


    ////////////CODE NEWWWWWWWWWWWWWWWWWWWWWWWWWWW

   //////code to fill the whole tree

    stack<node_xml*> parents_stack;
    int currentspacewidth = 0;
    int lastspacewidth = 0;
    int openbracketpos = 0;
    node_xml* current_parent = nullptr;
    node_xml* tempnode = nullptr;
if(root == nullptr)
{
    root = new node_xml();
 cout<<"fill the root element"<<endl;
    //fill the root element
    node_fill(&x,root);
    root->spacewidth=0;

    // node_fill is supposed to fill node till 1 pos after '\n' if it has and new node to be filled

    x = x.substr(x.find(' '));
    currentspacewidth = x.find('<') - x.find(' ');///////////////////////////////////////////////////
    x = x.substr(x.find('<'));
    current_parent = root; //initially
    parents_stack.push(root);
}

int counter = 0;


while(x.length()>0 && root != nullptr)
{
   /* cout<<x;
    cout<<"counter"<<counter<<endl;
    cout<<"ffffffffffffffffffffffffffffffffffffffffffffffff"<<endl;  */
    counter++;

    ///New code after adding spacewidth to nodeclass


    tempnode = new node_xml();
    node_fill(&x,tempnode);
    tempnode->spacewidth = currentspacewidth;
    while(!parents_stack.empty())
    {
      int pw = parents_stack.top()->spacewidth;
      if(currentspacewidth > pw)
      {
          current_parent = parents_stack.top();
          parents_stack.top()->childern_nodes.push_back(tempnode);

          parents_stack.push(tempnode);
          break;


      }
      else
          parents_stack.pop();


    }

    // node_fill is supposed to fill node till 1 pos after '\n' if it has and new node to be filled
    //case </element>
    if((x.find('<') != std::string::npos) && x.length()>0)
    {
    while( x.length()>0 && x[x.find('<')+1] == '/')
    {
       x = x.substr(x.find('>')+1);/////////updated

    }
    }

    if(x.length()>0 || (x.find('<') != std::string::npos))
    {
    x = x.substr(x.find(' '));
    lastspacewidth = currentspacewidth;
    currentspacewidth = x.find('<') - x.find(' ');

    x = x.substr(x.find('<'));

     }
    else
    {
        break;
    }




}
   cout<<"mfr234 ;)"<<x<<"5raaa"<<endl;


   return root;


}



void secDialog::xml_to_json(node_xml * node,int flag,int identicalsiblingnow,int identicalnum,int childnumnow,int parentchildnum,vector<string> &json_str)
{

        if (node == nullptr)
            return;



       // cout<<"BEFORE EACH CALl flag+identicalnow"<<flag<<"+"<<identicalsiblingnow<<endl;
        string jtemp = "";

        /* first print data of node */
         if(flag==0)
        {
        cout <<'"'<< node->elementname <<'"'<<": ";
        jtemp = '"' +  node->elementname + '"' + ": ";
        json_str.push_back( jtemp);

        }

         if(flag==1 && identicalsiblingnow > 1)
         {
     // cout<<"yarreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeet"<<childnumnow<<endl;

         }
         else if(flag ==1 && identicalsiblingnow == 1)
         {
            // cout<<"DA5ALLLLLLL";
             cout <<'"'<< node->elementname <<'"'<<": ";
             jtemp = '"' + node->elementname + '"' + ": ";
             json_str.push_back( jtemp);


         }




        //if it has  (childern || attributes ) >>{}
        // else  >>>if node has text but no childern nor attributes no{}


        if(flag == 0)
        {
        if((node->childern_nodes.size()>0) || node->attrname.size()>0)
            for(int k=0;k<node->spacewidth;k++)
            {
                cout<<" ";
            }
            cout<<"{"<<endl; //EDited
         jtemp= "{\n";
        json_str.push_back( jtemp);

        }
        else if(flag==1 && identicalsiblingnow == 1)
        {
            cout<<"["<<endl;
            for(int k=0;k<node->spacewidth;k++)
            {
                cout<<" ";
            }

        cout<<"{"<<endl;
       jtemp = "[\n{\n";
        json_str.push_back( jtemp);

         }
        else if(flag==1 && identicalsiblingnow > 1)
        {
            for(int k=0;k<node->spacewidth;k++)
            {
                cout<<" ";
            }
            cout<<"{"<<endl;
            jtemp= "{";
            json_str.push_back( jtemp);
        }

        if((node->text != "") || (node->childern_nodes.size()>0))
        {

            //check if node has attributes
            if(node->attrname.size()>0)
            {
                int attrcounter = 0;
                while(attrcounter < node->attrname.size())
                {
                    cout<<'"'<<"@"<<node->attrname[attrcounter]<<'"'<<": "<<'"'<<node->attrval[attrcounter]<<'"';
                    jtemp= "\"@ " + node->attrname[attrcounter] + '"' + ": " + '"' + node->attrval[attrcounter] + '"';
                    json_str.push_back( jtemp);

                    if(attrcounter>0)
                    {
                        cout<<",";
                        jtemp= ",";
                        json_str.push_back( jtemp);


                    }

                }
            }

            //check if node has text
            if(node->text != "" && (node->childern_nodes.size()>0) || (node->attrname.size()>0) )
            {
                cout<<'"'<<"#text"<<'"'<<": "<<'"'<<node->text<<'"';
                jtemp = "\"#text\": \"" + node->text + '"';
                json_str.push_back( jtemp);
                if(childnumnow < parentchildnum-1)
                {
                     cout<<",";
                    jtemp= ",";
                    json_str.push_back( jtemp);

                }

            }
            else if(node->text != "" && (node->childern_nodes.size()==0) &&(node->attrname.size()==0) )
            {
                cout<<'"'<<node->text<<'"';
                 jtemp= '"' + node->text + '"';
                 json_str.push_back( jtemp);
                if(childnumnow < parentchildnum-1)
                {
                   cout<<",";
                   jtemp=",";
                   json_str.push_back( jtemp);

                }

            }


            //check if node has childern
            if(node->childern_nodes.size()>0)
            {
                //need to check if there is siblings with same element name!!!
               int childcounter = 0;
               int identical_siblings = 0;
               vector<int>identical_IDs ;



               while(childcounter < node->childern_nodes.size() )
               {
                   for(int i=childcounter+1 ; i<node->childern_nodes.size(); i++)
                   {
                       if(node->childern_nodes[childcounter]->elementname == node->childern_nodes[i]->elementname )
                       {
                           identical_siblings = 1; //flag
                           identical_IDs.push_back(childcounter);
                           identical_IDs.push_back(i);
                           /////////hgfuhygiku



                       }

                   }

                   //if child is unique among his fucking siblings
                   if(!identical_siblings)
                   {

                       xml_to_json(node->childern_nodes[childcounter],identical_siblings,0,0,childcounter,node->childern_nodes.size(),json_str);


                   }
                   else
                   {

                     xml_to_json(node->childern_nodes[childcounter],identical_siblings,++identicalsiblingnow,identical_IDs.size(),childcounter,node->childern_nodes.size(),json_str);


                   }

            childcounter++;

               }


            }


            if(flag && (identicalsiblingnow == identicalnum))
            {
                cout<<endl;
                cout<<"]"<<endl;
                 jtemp= "\n]\n";
                 json_str.push_back( jtemp);
            }

            if(childnumnow == parentchildnum-1)
            {
                cout<<endl;
                cout<<"},"<<endl;
                 jtemp= "\n}\n";
                 json_str.push_back( jtemp);
             }

        }

        if((flag==1) && (identicalsiblingnow == identicalnum))
        {

                identicalsiblingnow = 0;
                flag = 0;


        }






}




secDialog::~secDialog()
{
    delete ui;
}
void secDialog:: setfilepath(const QString &fpath)
{
    fpathprivate = fpath;
}
void secDialog::on_pushButton_clicked()
{


}

