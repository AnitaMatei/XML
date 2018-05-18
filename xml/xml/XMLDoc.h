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
	char docReadName[100];
	char docSaveName[100];
	string version;
	XmlTree tree;
	bool firstNod = true;
	ifstream fin;
	ofstream fout;
	void skipChar(bool &nameEnded, char &c);
	void checkVer();
	void parse();
	void createLine();
public:
	XMLDoc(const char *docReadName=" ", const char *docSaveName=" ");
	void read();
	void save();
	
	char *getDocReadName();
	char *getDocSaveName();
	void setDocReadName(const char *s);
	void setDocSaveName(const char *s);
};










#endif  //XMLDoc.h