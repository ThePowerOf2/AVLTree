#include "pch.h"
#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	// Declaring variables.
	bool Exit = false;
	int choice = 0;
	string input;

	Tree<string> tree;

	while (!Exit) {
		cout << endl << "Please Choose an option" << endl;
		cout << "1 - Insert into the tree." << endl;
		cout << "2 - Delete from the tree." << endl;
		cout << "3 - Search for an item in the tree." << endl;
		cout << "4 - Print out the trees contents." << endl;
		cout << "0 - Exit the program." << endl;

		cout << "Choice: ";
		cin >> choice;

		switch (choice) {
		case 0:
			Exit = true;
			break;
		case 1:
			cout << "Please enter the item you want to enter into the tree: ";
			cin >> input;
			cout << endl;
			tree.insertItem(input);
			break;
		case 2:
			cout << "Please enter the item you want to delete from the tree: ";
			cin >> input;
			cout << endl;
			tree.deleteItem(input);
			break;
		case 3:
			cout << "Please enter the item you want to search for in the tree: ";
			cin >> input;
			cout << endl;
			tree.searchForItem(input);
			break;
		case 4:
			cout << endl;
			tree.printTree();
			break;
		default:
			cout << "Invalid Choice!";
		}
	}
}