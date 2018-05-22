#include "XmlTree.h"

void XmlTree::init() {
	curr = new nod;
	curr->parent = NULL;
	curr->tag = tag;
	tag++;
}

void XmlTree::insert() {
	curr->adr.push_back(new nod());
	curr->adr[curr->adr.size() - 1]->parent = curr;
	curr->adr[curr->adr.size() - 1]->tag = tag;
	tag++;
}
int XmlTree::goDown(int index) {
	if (index < curr->adr.size()) {
		curr = curr->adr[index];
		return 1;
	}
	else return 0;
}
int XmlTree::goDownLast() {
	if (curr->adr.size() > 0) {
		curr = curr->adr[curr->adr.size() - 1];
		return 1;
	}
	else return 0;
}
int XmlTree::goUp(int times) {
	if (curr->parent != NULL && times>=1)
	{
		while (times > 0) {
			curr = curr->parent;
			times--;
		}
		return 1;
	}
	else return 0;
}

int XmlTree::goUpMax() {
	if (curr->parent != NULL)
	{
		while (curr->parent != NULL)
			curr = curr->parent;
		return 1;
	}
	return 0;
}

void XmlTree::deleteOnlyCurr() {   
	for (int i = 0; i < curr->adr.size(); i++)
	{
		curr->adr[i]->parent = curr->parent;
		curr->parent->adr.push_back(curr->adr[i]);
		curr->adr.erase(curr->adr.begin() + i);
	}
	nod *ccurr = curr;  //copie curr folosita pt a sterge pointerul
	curr = curr->parent; 
	for (int i = 0; i<curr->adr.size(); i++)                    
		if (curr->adr[i]->tag == ccurr->tag)
		{
			curr->adr.erase(curr->adr.begin() + i);
			break;
		}
	delete ccurr;
}
void XmlTree::afisareCurr() {
	cout << curr->name << '\n';
}
void XmlTree::addAttrib(string name, string value) {  //adauga un atribut si valoarea lui 
	curr->attrib.push_back(name);
	curr->attribValues.push_back(value);
}
void XmlTree::deleteAttrib(string name) {
	for (int i = 0; i<curr->attrib.size(); i++)
		if (curr->attrib[i] == name)
		{
			curr->attrib.erase(curr->attrib.begin() + i);
			curr->attribValues.erase(curr->attrib.begin() + i);
		}
}
void XmlTree::addToValue(string value) {
	curr->value += value;
}
int XmlTree::replaceValue(string value) {  //daca nu are copii, atunci dau replace la valoare 
	if (curr->adr.size() == 0)
	{
		curr->value = value;
		return 1;
	}
	else return 0;
}
void XmlTree::replaceName(string value) {
	curr->name = value;
}

void XmlTree::recDeletion(nod* startingPoint) {
	for (int i = 0; i < startingPoint->adr.size(); i++) {
		if (startingPoint->adr[i]->adr.size() > 0)
			recDeletion(startingPoint->adr[i]);   //daca are copii urmatorul nod, avansezi pe el
		delete startingPoint->adr[i];
		startingPoint->adr.erase(startingPoint->adr.begin() + i);
	}
}

void XmlTree::deleteCurr() {
	nod* ccurr = curr;   //copie a lui curr pt a nu ramane cu pointeri pe care nu ii putem accesa
	curr = curr->parent;
	recDeletion(ccurr);
	for(int i=0;i<curr->adr.size();i++)                     //cauti unde se afla nodul curent in vectorul de adrese al parintelui si ii dai erase din vector
		if (curr->adr[i]->tag == ccurr->tag)
		{
			curr->adr.erase(curr->adr.begin() + i);
			break;
		}
	delete ccurr;              //dupa care delete
}


void XmlTree::recDisplay(nod* startingPoint, int depth) {         //depth ca sa stiu la ce nivel ma aflu in tree
	for (int i = 0; i < startingPoint->adr.size(); i++)
	{
		int cdepth=depth;
		while (cdepth > 0)
		{
			cout << '\t';
			cdepth--;
		}
		cout << startingPoint->adr[i]->name << endl;
		if (startingPoint->adr[i]->adr.size() > 0)
			recDisplay(startingPoint->adr[i],depth+1);
	}
}

void XmlTree::displayTree() {
	
	nod* ccurr = curr;  
	while (ccurr->parent != NULL)       //ne intoarcem mai intai la radacina cu copia
		ccurr = ccurr->parent;
	cout << ccurr->name << endl;
	recDisplay(ccurr,1);
}

int XmlTree::showAttrib(int howMany ) {
	if (howMany > curr->attrib.size())
		return 0;
	for (int i = 0; i < howMany; i++)
		cout << curr->attrib[i] << "=\"" << curr->attribValues[i] << "\"";
	return 1;

}

int XmlTree::getTag() {
	return curr->tag;
}
string XmlTree::getName() {
	return curr->name;
}
string XmlTree::getAttrib(int index) {
	return curr->attrib[index];
}
string XmlTree::getAttribValue(int index) {
	return curr->attribValues[index];
}

int XmlTree::getAttribNr() {
	return curr->attrib.size();
}
int XmlTree::getChildrenNr() {
	return curr->adr.size();
}

string XmlTree::getLastAttrib() {
	return curr->attrib[curr->attrib.size() - 1];
}
string XmlTree::getLastAttribValue() {
	return curr->attribValues[curr->attribValues.size() - 1];
}