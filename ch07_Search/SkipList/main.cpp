#include <fstream>
#include <cassert>
#include "person.h"
#include "SkipList.h"
using namespace std;
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	SkipList<person,long> skp(99999);
	cout << "Load data from the file...\n";
	assert(fin >> skp);
	cout << "Completed!\n" << endl;
	cout << "The skip list is: \n" << skp << endl;

	cout << "\n1. Test Begin and Next: \n";
	cout << "Use the Begin and Next to print the skip list:\n";
	SkipNode<person,long> *node = skp.Begin();
	while (node){
		cout << node->data << endl;
		node = skp.Next(node);
	}
	
	cout << "\n2. Test the DelMin, DelMax, Insert, Search and Remove\n";
	long ID;
	person pr;
	char cmd;
	bool quit = false;
	cout << "\nCommands:\n";
	cout << "I: Insert\nS: Search\nR: Remove\n";
	cout << "F: Delete the minimal element\n";
	cout << "L: Delete the maximal element\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";
	while (!quit){
		cout << "Prease enter a command: ";
		cin >> cmd;
		cin.ignore(100, '\n');
		switch (cmd)
		{
		case 'I':
		case 'i':
			cout << "Insert, please enter the ID, Age and Name:\n";
			cin >> pr;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			skp.Insert(pr.getID(), pr);
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
			if (skp.Search(ID, pr)){
				cout << "The data is:\t" << pr << endl;
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
			if (skp.Remove(ID, pr)){
				cout << "This person has been removed: \n" << pr << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'F':
		case 'f':
			cout << "Delete the minimal element:\n";
			if (skp.DelMin(pr)){
				cout << "The minimal element of the list is:\t" << pr << endl;
				cout << "And this element has been removed.\n";
			}
			else{
				cout << "The skip list is empty!\n";
			}
			break;
		case 'L':
		case 'l':
			cout << "Delete the maximal element:\n";
			if (skp.DelMax(pr)){
				cout << "The maximal element of the list is:\t" << pr << endl;
				cout << "And this element has been removed.\n";
			}
			else{
				cout << "The skip list is empty!\n";
			}
			break;
		case 'p':
		case 'P':
			cout << "\nThe skip list is:\n" << skp << endl;
			break;
		case 'H':
		case 'h':
			cout << "Commands:\n";
			cout << "I: Insert\nS: Search\nR: Remove\n";
			cout << "F: Delete the minimal element\n";
			cout << "L: Delete the maximal element\n";
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
	
	cout << "\nPress enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
