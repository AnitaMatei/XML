#include "XMLDoc.h"


XMLDoc::XMLDoc(const char *docReadName = " ", const char *docSaveName = " ") {
	strcpy(this->docReadName,docReadName);
	strcpy(this->docSaveName, docSaveName);

}

void XMLDoc::read() {
	while (strcmp(docReadName, " ") == 0) {      //wait for a string different from " "
		printf("Please enter a valid file path for your XML document\n>>");
		scanf("%s", &docReadName);
		system("CLS");
	}
	ifstream fin(docReadName);  
	if (!fin) {														//if the file wasnt opened, throw error
		throw runtime_error("There is no such file there...");
	}
	int line = 0;
	while (!fin.eof) {                                         //while the end of the file wasnt reached, read the file line by line
		getline(fin, docText[line]);
		docText[line].erase(0, 1);								//delete the characters '<' '>'
		docText[line].erase(docText[line].length() - 2, docText[line].length() - 1);
		line++;
	}
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
