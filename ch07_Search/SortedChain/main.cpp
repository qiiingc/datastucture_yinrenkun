#include "SortedChain.h"
#include "person.h"
#include <fstream>

using namespace std;
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	SortedChain<person,long> sc;
	cout << "Load data from the file...\n";
	assert(fin >> sc);
	cout << "Completed!\n" << endl;
	cout << "The sorted chain is: \n" << sc << endl;

	cout << "\n1. Test Begin and Next: \n";
	cout << "Use the Begin and Next to print the Sorted Chain:\n";
	ChainNode<person,long> *node = sc.Begin();
	while (node){
		cout << node->data << endl;
		node = sc.Next(node);
	}

	cout << "\n2. Test the Insert, Search and Remove\n";
	long ID;
	person pr;
	char cmd;
	bool quit = false;
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
			sc.Insert(pr.getID(), pr);
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
			node = sc.Search(ID);
			if (node){
				cout << "The data is:\t" << node->data << endl;
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
			if (sc.Remove(ID, pr)){
				cout << "This person has been removed: \n" << pr << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'p':
		case 'P':
			cout << "\nThe Sorted chain is:\n" << sc << endl;
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
