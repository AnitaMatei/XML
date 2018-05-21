#ifndef __XMLDOC_H
#define __XMLDOC_H

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "XmlTree.h"

using namespace std;

class XMLDoc {
	string docReadName, docSaveName, version, format;
	XmlTree tree;
	bool firstNod = true;
	ifstream fin;
	ofstream fout;
	
	void skipChar(bool &nameEnded, char &c);
	void checkVer();
	void parse();
	void createLine(int depth);
public:
	XMLDoc(const string docReadName=" ", const string docSaveName=" ");
	void read();
	void save();
	string getDocReadName();
	string getDocSaveName();
	void setDocReadName(const string s);
	void setDocSaveName(const string s);
};
#endif  //XMLDoc.h