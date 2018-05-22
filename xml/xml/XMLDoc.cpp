#include "XMLDoc.h"


XMLDoc::XMLDoc(const string docReadName, const string docSaveName) {
	this->docReadName = docReadName;
	this->docSaveName = docSaveName;
}
void XMLDoc::skipChar(bool &nameEnded, char &c) //sare peste incheierea unui nod
{
	nameEnded = true;
	fin >> c; tree.goUp(1);
	while (c != '>')
	{
		fin >> c;
	}
}
void XMLDoc::checkVer()  //verifica daca exista date despre versiune
{
	char c;
	fin.seekg(1); fin >> c;
	if (c == '?')
	{
		fin.seekg(0); getline(fin, version);
	}
	else
		fin.seekg(0);
}
void XMLDoc::parse()
{
	char c, curm;
	string nume, atrib, valatrib;
	bool nameEnded = false, atribEnded = false, valueEnded = true;
	while (fin >> c)
	{
		//conditii pt extragerea atributelor si valorilor lor
		if (nameEnded && c!='>')
		{
			if (atribEnded==false)
				atrib += c;
			curm = fin.peek();
			if (curm == '=')
			{
				atribEnded = true; valueEnded = false;
				fin >> c; fin >> c;
			}
			if (valueEnded==false)
			{
				fin >> c;
				if (c != '"')
				{
					valatrib += c; fin >> c;
				}
				while (c != '"')
				{
					valatrib += c; fin >> c;
				}
				tree.addAttrib(atrib, valatrib);
				atrib.clear(); valatrib = "";
				valueEnded = true; atribEnded = false;
			}
		}
		//daca s-a terminat numele nodului
		if (nameEnded == false)
			if (c == ' ' || c == '>' || c == '/')
			{
				tree.replaceName(nume); nameEnded = true;
			}
		//verifica daca s-a terminat nodul curent si in caz afirmativ citeste pana cand incep datele sibling-ului
		if (c == '/')
			skipChar(nameEnded, c);
		//se formeaza numele nodului
		if (nameEnded == false && c != '<')
			nume += c;
		//cand se gaseste un nou nod, se insereaza si devine nodul curent
		if (c == '<')
		{
			bool canInsert = true;
			curm = fin.peek();
			if (curm == '/' && !firstNod)
			{
				skipChar(nameEnded, curm); canInsert = false;
			}
			if (firstNod == true)
			{
				tree.init(); firstNod = false;
			}
			else if (canInsert)
			{
				tree.insert(); tree.goDownLast();
			}
			parse();
		}
	}
}
void XMLDoc::read() {
	fin.open(docReadName);
	fin >> noskipws;
	if (!fin.is_open())
		cout << "Eroare la deschidere fisier";
	else
	{
		checkVer();
		parse();
	}
	fin.close();
}

string XMLDoc::getDocReadName() {
	return docReadName;
}
string XMLDoc::getDocSaveName() {
	return docSaveName;
}
void XMLDoc::setDocReadName(const string s) {
	docReadName = s;
}
void XMLDoc::setDocSaveName(const string s) {
	docSaveName = s;
}

/////
//creez fiecare linie in parte
//daca nu are copii nodul actual, creez linia, o inchid si o afisez
//daca are copii, atunci creez linia si o afisez, ma duc recursiv pe copii si la intoarcere il inchid
///////
void XMLDoc::createLine(int depth) {
	string line;
	line.clear();
	for (int i = 0; i <depth; i++)
		line += "\t";

	line += "<" + tree.getName();
	for (int i = 0; i < tree.getAttribNr(); i++)
	{
		if (i == 0)
			line += " ";
		line += tree.getAttrib(i) + "=" + "\"" + tree.getAttribValue(i) + "\"";
	}
	if (tree.getChildrenNr() == 0) {
		line += " />";
		fout << line << endl;;
	}
	else {
		line += ">";
		fout << line << endl;
		for (int i = 0; i < tree.getChildrenNr(); i++)
		{
			tree.goDown(i);
			createLine(depth + 1);
			tree.goUp(1);
		}
		line.clear();
		for (int j = 0; j < depth ; j++)
			line += "\t";
		line += "</" + tree.getName() + ">";
		fout << line << endl;
	}

}

void XMLDoc::save() {
	tree.goUpMax();
	fout.open(docSaveName);
	fout << version<<endl;
	createLine(0);
	fout.close();
}

void XMLDoc::recsearch(string x, bool & p)
{
	int i;
	if (p == true)
	{
		if (tree.getName() == x)
		{
			p = false;
			return;
		}
		for (i=0;i<tree.getChildrenNr();i++)
		{
		    tree.goDown(i);
		    recsearch(x,p);
			if(p==true)
			tree.goUp(1);
		}
	}
	
}

void XMLDoc::gotonode(string x)
{
	bool c = true;
    tree.goUpMax();
    recsearch(x, c);
}

void XMLDoc::addNode(string nod, string name)
{
	gotonode(nod);
	tree.insert();
	tree.goDownLast();
	tree.replaceName(name);
}

void XMLDoc::addAtribut(string nod, string atribut, string valatribut)
{
	gotonode(nod);
	tree.addAttrib(atribut, valatribut);
}

void XMLDoc::deleteNode(string nod, string All_or_Current)
{
	gotonode(nod);
	if (All_or_Current == "All")
	{
		tree.deleteCurr();
	}
	else if (All_or_Current == "Current")
	{
			tree.deleteOnlyCurr();
	}
}

void XMLDoc::gotoRoot()
{
	tree.goUpMax();
}

void XMLDoc::delAtribut(string x)
{
	tree.deleteAttrib(x);
}


string XMLDoc::ShowName()
{
	cout<<tree.getName()<<endl;
	return tree.getName();

}