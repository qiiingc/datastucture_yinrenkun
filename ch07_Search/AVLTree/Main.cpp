#include "AVLTree.h"
#include "person.h"
#include <fstream>
using namespace std;

int main(){
	ifstream fin("persons.txt");
	assert(fin);
	BST<person,long> bst1;
	cout << "Load data from the file...\n";
	assert(fin >> bst1);
	fin.close();
	cout << "Completed!\n" << endl;
	cout << bst1 << endl;
	fin.clear(0);
	fin.open("persons.txt");
	AVLTree<person,long> bst;
	cout << "Load data from the file...\n";
	assert(fin >> bst);
	fin.close();
	cout << "Completed!\n" << endl;
	cout << bst << endl;
	cout << "\nThe commands are listed here:\n";
	cout << "I: Insert\nS: Search\nR: Remove\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";

	long ID;
	person pr;
	char cmd;
	bool quit = false;
	AVLNode<person,long> *bn;
	while (!quit){
		cout << "Prease enter a command: ";
		cin >> cmd;
		cin.ignore(100, '\n');
		switch (cmd){
		case 'I':
		case 'i':
			cout << "Insert, please enter the ID, Age and Name:\n";
			cin >> pr;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			if(!bst.Insert(pr)){
				cout << "Insert Failed!\n";
			}
			break;
		case 'S':
		case 's':
			cout << "Search, please enter an ID to search: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			bn = bst.Search(ID);
			if(bn){
				cout << "The data is:\t" << bn->data << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'R':
		case 'r':
			cout << "Remove, Enter an ID to delete: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			if (bst.Remove(ID, pr)){
				cout << "Remove succeed!\n";
				cout << "The removed element is:\t" << pr << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'p':
		case 'P':
			cout << bst << endl;
			break;
		case 'H':
		case 'h':
			cout << "Commands:\n";
			cout << "I: Insert\nS: Search\nR: Remove\n";
			cout << "P: Print the list\nQ: Quit\nH: Help\n";
			break;
		case 'Q':
		case 'q':
			quit = true;
			break;
		default:
			break;
		}
	}

	cout << "\n\nPress enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
