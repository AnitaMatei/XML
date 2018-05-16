#include <iostream>
#include "XMLDoc.h"

using namespace std;

int main() {
	XMLDoc doc("C:\\Users\\chido\\Documents\\Battlefield 1\\settings");
	doc.read();
	system("pause");
	return 0;
}