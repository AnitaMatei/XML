#include "XMLDoc.h"
#include "XmlTree.h"
#include <string>
using namespace std;
ifstream fin;
XmlTree tree;
bool firstNod = true;
void parse()
{
	char c='i';
	string nume;
	bool nameEnded = false;
	if (c == '/')
	{
		fin >> c;
		tree.goUp();
		while (c != '<')
		{
			fin >> c;
			if (c == '<')
			{
				tree.insert();
				tree.goDownLast();
			}
		}
	}
	while (fin >> c && c != '/')
	{
		if (c == ' ' || c == '>')
		{
			if (nameEnded == false)
			{
				tree.replaceName(nume);
				cout << nume << endl;
				nameEnded = true;
				nume.clear();
			}
		}
		if (nameEnded == false && c!='<')
			nume += c;
		if (c == '<')
		{
			if (firstNod == true)
			{
				tree.init();
				firstNod = false;
			}
			else
			{
				tree.insert();
				tree.goDownLast();
			}
			parse();
		}
	}
}

int main()
{
	char c;
	string nume;
	fin.open("GamerProfile.xml");
	if (!fin.is_open())
		cout << "Eroare la deschidere fisier";
	else
		parse();
	/*while (fin >> c)
	{
		if (c == '<')
		{
			if (firstNod)
			{
				tree.init();
				firstNod = false;
			}
			else
			{
				tree.insert();
				tree.goDownLast();
			}
			nameEnded = false; fin >> c;
		}
		if (c == ' ' || c == '>')
		{
			tree.replaceName(nume);
			nameEnded = true;
			nume.clear();
		}
		if (nameEnded == false)
			nume=nume+c;
	}
	cout << nume << endl;*/
	fin.close();
	system("pause");
}