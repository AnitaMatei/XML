#ifndef __XMLDOC_H
#define __XMLDOC_H

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

class XMLDoc {
	char docReadName[100];
	char docSaveName[100];
	string docText[1000];

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