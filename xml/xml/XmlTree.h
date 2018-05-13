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

	void recDeletion(nod* startingPoint);

public:
	void init();

	void insert();

	int goDown(int index);
	void goDownLast();
	int goUp();
	
	void deleteOnlyCurr();  //da delete doar la nodul actual, iar copii ii lipeste la parintele lui curr
	void deleteCurr(); //da delete la toate nodurile sub curr, inclusiv; grija la folosirea functiei !!!MIRCEA!!!
	
	void afisareCurr();
	
	void addAttrib(string name, string value);
	void deleteAttrib(string name);
	
	void addToValue(string value);
	int replaceValue(string value);     

	void replaceName(string value); //redenumeste nodul
};



#endif //XmlTree.h