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
void XmlTree::goDownLast() {
	curr = curr->adr[curr->adr.size() - 1];
}
int XmlTree::goUp() {
	if (curr->parent != NULL)
	{
		curr = curr->parent;
		return 1;
	}
	else return 0;
}
void XmlTree::deleteOnlyCurr() {   
	for (int i = 0; i < curr->adr.size(); i++)
	{
		curr->adr[i]->parent = curr->parent;
		curr->parent->adr.push_back(curr->adr[i]);
	}
	nod *ccurr = curr;  //copie curr folosita pt a sterge pointerul
	curr = curr->parent;
	delete ccurr;
}
void XmlTree::afisareCurr() {
	cout << curr->tag << '\n';
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
		if (startingPoint->adr[i]->adr.size()>0)
			recDeletion(startingPoint->adr[i]);   //daca are copii urmatorul nod, avansezi pe el

		delete startingPoint->adr[i];  //altfel, delete direct
	}
}

void XmlTree::deleteCurr() {
	nod* ccurr = curr;   //copie a lui curr pt a nu ramane cu pointeri pe care nu ii putem accesa
	recDeletion(ccurr);
}