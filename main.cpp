// Challenge 06: Lowest Common Ancestor
#include "strTree.h"
using namespace std;

// Main Execution

int main(int argc, char *argv[]) {
	
	Node* test = new Node("hello");
	cout << test->value << endl;
	cout << test->length << endl;

	strTree tree("hello");
	cout << tree.root->value << endl;
	cout << tree.root->length << endl;

	cout << "TEST - against: hellooo (smaller)" << endl;
	tree.insert("helloo");

	cout << "TEST - against: hellx (smaller)" << endl;
	tree.insert("hellx");

	cout << "TEST - against: hez (smaller)" << endl;
	tree.insert("hez");

	cout << "TEST - against: hell (larger)" << endl;
	tree.insert("hell");

	cout << "TEST - against: hella (larger)" << endl;
	tree.insert("hella");

	cout << "TEST - against: hez (larger)" << endl;
	tree.insert("hek");


	return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
