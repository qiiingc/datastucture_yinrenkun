#include <fstream>
#include <cassert>
#include <string>
#include "BST.h"
#include "person.h"
using namespace std;

int main(){
	ifstream fin("persons.txt");
	assert(fin);
	BST<person,long> bst,bst1;
	cout << "Load data from the file...\n";
	assert(fin >> bst);
	fin.close();
	cout << "Completed!\n" << endl;
	cout << bst << endl;
	bst1=bst;
	cout<<bst1<<endl;
	cout << "\nThe commands are listed here:\n";
	cout << "I: Insert\nS: Search\nR: Remove\n";
	cout << "F: Delete the minimal element\n";
	cout << "L: Delete the maximal element\n";
	cout << "P: Print the list\nQ: Quit\nH: Help\n";

	long ID;
	person pr;
	char cmd;
	bool quit = false;
	BSTNode<person,long> *bn;
	while (!quit)	{
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
			if (bst.Remove(ID)){
				cout << "Remove succeed!\n";
			}
			else{
				cout << "The ID is not exist!\n";
			}
			break;
		case 'F':
		case 'f':
			cout << "Delete the minimal element in the BST tree:\n";
			if (bst.DelMin()){
				cout << "Succeed!\n";
			}
			else{
				cout << "The BST tree is empty!\n";
			}
			break;
		case 'L':
		case 'l':
			cout << "Delete the maximal element in the BST tree:\n";
			if (bst.DelMax()){
				cout << "Succeed!\n";
			}
			else{
				cout << "The BST tree is empty!\n";
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

	BST<element,string> bst2;
	element a[]={"","do","if","to"};
	int p[]={0,50,10,5},q[]={15,10,5,5};
	bst2.OpticBST(p,q,a,3);
	cout << bst2 << endl;
	BST<element,string> bst3;
	element a1[]={"","B","D","F","H"};
	int p1[]={0,1,5,4,3},q1[]={5,4,3,2,1};
	bst3.OpticBST(p1,q1,a1,4);
	cout << bst3 << endl;

	cout << "\n\nPress enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}

