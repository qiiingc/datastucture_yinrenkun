#include "UFSets.h"
#include <iostream>
using namespace std;

int main(){
	int i;
	UFSets ufs1(10);
	cout << "1. Test SimpleUnion(r1, r2): ";
	for (i = 8; i >=0; i--)	{
		ufs1.SimpleUnion(i, i+1);
	}
	cout << ufs1 << endl;
	UFSets ufs2(10);
	cout << "2. Test WeightedUnion(r1, r2): ";
	for (i = 8; i >=0; i--)	{
		ufs2.WeightedUnion(i, i+1);
	}
	cout << ufs2 << endl;
	cout << "Tips: 1 and 2 have the same Union order but different result!\n" << endl;

	UFSets ufs3(10);
	ufs3.SimpleUnion(1,2);
	ufs3.SimpleUnion(1,4);
	ufs3.SimpleUnion(9,3);
	ufs3.SimpleUnion(9,5);
	ufs3.SimpleUnion(7,9);
	ufs3.SimpleUnion(7,1);
	ufs3.SimpleUnion(0,6);
	ufs3.SimpleUnion(0,7);
	ufs3.SimpleUnion(0,8);
	cout << "A new UFSets for test: " << ufs3 << endl;

	cout << "3. Test Find(i): \n";
	for (i = 0; i < 10; i++){
		cout << "The root of Node " << i << " is: " << ufs3.Find(i) << endl;
	}
	cout << "\nAfter Find(i): " << ufs3 << endl;
	cout << "Tips: The UFSets is not changed!\n" << endl;

	cout << "4. Test CollapsingFind(i): \n";
	for (i = 0; i < 10; i++){
		cout << "The root of Node " << i << " is: " << ufs3.CollapsingFind(i) << endl;
	}
	cout << "\nAfter CollapsingFind(i): " << ufs3 << endl;
	cout << "Tips: The UFSets is changed!" << endl;

	cout << "Press enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
