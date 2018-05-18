#include "XMLDoc.h"


XMLDoc::XMLDoc(const char *docReadName, const char *docSaveName) {
	strcpy(this->docReadName,docReadName);
	strcpy(this->docSaveName, docSaveName);
}
void XMLDoc::skipChar(bool &nameEnded, char &c) //sare peste incheierea unui nod
{
	nameEnded = true;
	fin >> c;
	tree.goUp(1);
	while (c != '>')
	{
		fin >> c;
	}
}
void XMLDoc::parse()
{
	char c, curm;
	string nume, atrib, valatrib;
	bool nameEnded = false, atribEnded = false;
	while (fin >> c)
	{
		//conditii pt extragerea atributelor si valorilor lor
		if (nameEnded && c != '>' && c != '/')
		{
			if (c == '=')
			{
				atribEnded = true;
				fin >> c; fin >> c;
			}
			if (!atribEnded)
				atrib += c;
			else
			{
				curm = fin.peek();
				valatrib += c;
				if (curm == '"')
				{
					tree.addAttrib(atrib, valatrib);
					atribEnded = false;
					atrib.clear();
					valatrib.clear();
					fin >> c;
				}
			}
		}
		//daca s-a terminat numele nodului
		if (nameEnded == false)
		{
			if (c == ' ' || c == '>')
			{
				tree.replaceName(nume);
				nameEnded = true;
			}
		}
		//verifica daca s-a terminat nodul curent si in caz afirmativ citeste pana cand incep datele sibling-ului
		if (c == '/')
		{
			skipChar(nameEnded, c);
		}
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
				skipChar(nameEnded, curm);
				canInsert = false;
			}
			if (firstNod == true)
			{
				tree.init();
				firstNod = false;
			}
			else if (canInsert)
			{
				tree.insert();
				tree.goDownLast();
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
		parse();
	//tree.displayTree();
	fin.close();
}

char* XMLDoc::getDocReadName() {
	return docReadName;
}
char* XMLDoc::getDocSaveName() {
	return docSaveName;
}
void XMLDoc::setDocReadName(const char *s) {
	strcpy(docReadName, s);
}
void XMLDoc::setDocSaveName(const char *s) {
	strcpy(docSaveName, s);
}

void XMLDoc::createLine() {
	string line;
	line.clear();
	for (int i = 0; i < tree.getTag(); i++)
		line += '\t';

	line == "<" + tree.getName() + " ";
	for (int i = 0; i < tree.getAttribNr(); i++)
	{
		line += tree.getAttrib(i) + "=" + "\"" + tree.getAttribValue(i) + "\"";
		if (i < tree.getAttribNr() - 1)
			line += " ";
	}
	if (tree.getChildrenNr() == 0) {
		line += "/>";
		fout << line << endl;;
	}
	else {
		line += ">";
		fout << line<<endl;
		for (int i = 0; i < tree.getChildrenNr(); i++)
		{
			tree.goDown(i);
			createLine();
			tree.goUp(1);
			line.clear();
			for (int j = 0; j < tree.getChildrenNr(); j++)
				line += '\t';
			line += "</" + tree.getName() + ">";
			fout << line << endl;
		}
	}
	
	
}


void XMLDoc::save() {
	tree.goUpMax();
	fout.open(docSaveName);
	createLine();
}
