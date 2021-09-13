#ifndef NODE_XML_H
#define NODE_XML_H
#include "string"
#include "vector"
using namespace std;

class node_xml
{
public:
    node_xml();


    string elementname;
    vector<string> attrname; //it may has more than one attribute
    vector<string> attrval;
    string text;
    vector<node_xml*>childern_nodes;
    int spacewidth;

};

#endif // NODE_XML_H
