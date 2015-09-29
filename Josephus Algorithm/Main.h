#ifndef MAIN_CPP
#define MAIN_CPP

////////////////////////////////////////////////////////////////////////////
// Thomas Freeman
// Josephus Problem using Circular Linked List
////////////////////////////////////////////////////////////////////////////

#include "circularLinkedList.h"

#include <iostream>
#include <string>

using namespace std;


void testJosephusAlgorithm() {

	//Testing the Josephus Algorithm
	//When inputs at (7, 3) the nodes should be removed in the order (4, 1, 6, 5, 7, 3) and the survivor node should be 2.
	List<int> list;
	list.runJosephusAlgorithm();
}

int main() {

	cout << "//////////////////////////////////////////////////////////" << endl;
	cout << "// Thomas Freeman" << endl;
	cout << "// Josephus Problem using Circular Linked List" << endl;
	cout << "//////////////////////////////////////////////////////////" << endl << endl << endl;

	testJosephusAlgorithm();

	cin.ignore();


	return 0;
}



#endif