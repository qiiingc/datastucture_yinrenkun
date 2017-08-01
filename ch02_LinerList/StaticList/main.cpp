#include "StaticList.h"
#include <iostream>
using namespace std;

int main(){
	StaticList<int> list(10);
	list.Append(25);
	list.Append(92);
	list.Append(57);
	list.Append(36);
	list.Append(78);
	list.Insert(3, 11);
	list.Insert(1, 49);

	// Print the list
	list.output();
	list.output(1);

	cout << "search 36: " << list.Search(36) << endl;
	cout << "search 25: " << list.Search(25) << endl;
	cout << "search 78: " << list.Search(78) << endl;
	cout << "search 50: " << list.Search(50) << endl;
	cout << endl;

	if (list.Remove(5)){
		cout << "Remove the 5th data:\n";
		list.output();
		list.output(1);
	}

	list.Append(11);
	cout << "After Insert 11 in the rear:\n";
	list.output();
	list.output(1);
	return 0;
}
