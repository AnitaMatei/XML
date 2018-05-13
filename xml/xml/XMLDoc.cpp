#include "XMLDoc.h"


XMLDoc::XMLDoc(const char *docReadName, const char *docSaveName) {
	strcpy(this->docReadName,docReadName);
	strcpy(this->docSaveName, docSaveName);
	docTree.init();
}

void XMLDoc::read() {
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
