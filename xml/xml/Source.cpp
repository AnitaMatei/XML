#include <iostream>
#include <Windows.h>
#include "XMLDoc.h"

using namespace std;

int main() {
	XMLDoc q("XMLin.xml","caine.xml");
	q.read();
	q.deleteNode("RenderProfile", "Current");
	q.save();

	system("pause");
}