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
		int nivel;
		int tag;

		vector<nod*> adr;
		nod *parent;
	}*curr;
	int tag = 1;

	void recDeletion(nod* startingPoint);
	void recDisplay(nod* startingPoint, int depth);


public:
	void init();

	void insert();
	int getNivel();
	int goDown(int index);         //coboara jos pe copilul precizat
	int goDownLast();          //coboara jos pe ultimul copil adaugat
	int goUp(int times);         //se urca sus de cate ori ii zici
	int goUpMax();          //se urca sus pana la root
	
	void deleteOnlyCurr();  //da delete doar la nodul actual, iar copii ii lipeste la parintele lui curr
	void deleteCurr(); //da delete la toate nodurile sub curr, inclusiv; grija la folosirea functiei !!!MIRCEA!!!
	
	void afisareCurr();
	
	void addAttrib(string name, string value);
	void deleteAttrib(string name);
	
	void addToValue(string value);
	int replaceValue(string value);     

	void replaceName(string value); //redenumeste nodul

	void displayTree();     //afiseaza tot arborele
	int showAttrib(int howMany = 1);  

	int getTag();
	string getName();
	string getAttrib(int index);
	string getAttribValue(int index);
	int getAttribNr();
	int getChildrenNr();
	string getLastAttrib();
	string getLastAttribValue();
};



#endif //XmlTree.h