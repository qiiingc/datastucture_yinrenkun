#include "SortedDblChain.h"
#include "person.h"
#include <fstream>
#include <cassert>

using namespace std;
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	SortedDblChain<person,long> sc;
	cout << "Load data from the file...\n";
	assert(fin >> sc);
	cout << "Completed!\n" << endl;
	cout << "The sorted dblchain is: \n" << sc << endl;
	
	cout << "\nThe commands are listed here:\n";
	cout << "I: Insert\nS: Search\nR: Remove\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";
	long ID;
	person pr;
	char cmd;
	bool quit = false;
	ChainDblNode<person,long> *node;
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
			cout << "The current node is:\t" << sc.Current()->data << endl;
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
				cout << "This person has been removed: \n" << pr;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			cout << "\nThe current node is:\t" << sc.Current()->data << endl;
			break;
		case 'p':
		case 'P':
			cout << "\nThe sorted dbl chain is:\n" << sc << endl;
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
