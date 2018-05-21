#include <iostream>
#include <Windows.h>
#include "XMLDoc.h"

using namespace std;

int main() {
	////Soruce.cpp folosit pt debug
	XMLDoc q("XMLin.xml", "XMLout.xml");
	q.read();
	q.save();
	system("pause");
}