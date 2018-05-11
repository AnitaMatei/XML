#ifndef __XMLTREE_H
#define __XMLTREE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class XmlTree {
	struct nod {
		string name;
		vector<string> attrib;
		vector<string> attribValues;
		string value;

		int tag;

		vector<nod*> adr;
		nod *parent;
	}*curr;
	int tag = 1;

public:
	void init();

	void insert();

	int goDown(int index);
	void goDownLast();
	int goUp();
	
	void deleteOnlyCurr();
	
	void afisareCurr();
	
	void addAttrib(string name, string value);
	void deleteAttrib(string name);
	
	void addToValue(string value);
	int replaceValue(string value);
};



#endif //XmlTree.h