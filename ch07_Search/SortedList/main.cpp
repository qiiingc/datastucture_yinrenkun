#include "SortedList.h"
#include "person.h"
#include <fstream>
#include <cassert>
using namespace std;

int main(){
	ifstream fin("persons.txt");
	assert(fin);
	cout << "Load data from the file...\n";
	SortedList<person,long> sc;
	while (!fin.eof()){
		person pr;
		assert(fin >> pr);
		sc.Insert(pr.getID(), pr);
	}
	cout << "Completed!\n" << endl;
	cout << "The sorted list is: \n" << sc << endl;

	cout << "\nCommands:\n";
	cout << "I: Insert\nR: Remove\n";
	cout << "1: Sequence Search\n";
	cout << "2: Iterative BinarySearch\n";
	cout << "3: Recursive BinarySearch\n";
	cout << "4: FibonacciSearch\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";

	long ID;
	person pr;
	char cmd;
	int rst;
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
		case '1':
			cout << "Sequence Search, please enter an ID to search: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			rst = sc.Search(ID);
			if (rst != 0){
				cout << "The data is:\t" << *(sc.getData(rst)) << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case '2':
			cout << "Iterative BinarySearch, please enter an ID to search: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			if (ID < 0){
				break;
			}
			rst = sc.BinarySearch(ID);
			if (rst != 0){
				cout << "The data is:\t" << *(sc.getData(rst)) << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case '3':
			cout << "Recursive BinarySearch, please enter an ID to search: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			rst = sc.BinarySearch(ID, 1, sc.Length());
			if (rst != 0){
				cout << "The data is:\t" << *(sc.getData(rst)) << endl;
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case '4':
			cout << "FibonacciSearch, please enter an ID to search: ";
			cin >> ID;
			if (!cin){
				cin.clear();
				cin.ignore(100,'\n');
				break;
			}
			if (ID < 0){
				break;
			}
			rst = sc.FibonacciSearch(ID);
			if (rst != 0){
				cout << "The data is:\t" << *(sc.getData(rst)) << endl;
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
			cout << "\nThe sorted list is:\n" << sc << endl;
			break;
		case 'H':
		case 'h':
			cout << "\nCommands:\n";
			cout << "I: Insert\nR: Remove\n";
			cout << "1: Sequence Search\n";
			cout << "2: Iterative BinarySearch\n";
			cout << "3: Recursive BinarySearch\n";
			cout << "4: FibonacciSearch\n";
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
	return 0;
}
