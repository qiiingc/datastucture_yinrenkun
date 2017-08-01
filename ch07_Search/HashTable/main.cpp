#include <fstream>
#include "HashTable.h"
#include "person.h"
using namespace std;
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	HashTable<person, long> ht(37, 40);
	cout << "Load data from the file...\n";
	assert(fin >> ht);
	fin.close();
	cout << "Completed!\n" << endl;
	cout << "The hash table is: \n" << ht << endl;

	cout << "\nThe commands are listed here:\n";
	cout << "I: Insert\nS: Search\nR: Remove\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";

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
			ht.Insert(pr);
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
			if (ht.Search(ID, pr)){
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
			if (ht.Remove(ID, pr)){
				cout << "This person has been removed: \n" << pr << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'p':
		case 'P':
			cout << "\nThe hash table is: \n" << ht << endl;
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
