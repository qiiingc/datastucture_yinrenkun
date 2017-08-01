#include "bitSet.h"
#include <fstream>
#include <cassert>
using namespace std;
int main(){
	const int len = 30;
	bitSet<int> s1(len), s2(len), s3(len), s4(len), s5(len), s6(len);
	ifstream fin("input.txt");
	assert(fin);
	fin >> s1;
	cout << "s1: " << s1;
	fin >> s2;
	cout << "s2: " << s2;
	fin.close();
	s3 = s1 + s2;
	cout << "s1+s2=>s3, then s3 is:\n";
	cout << "s3: " << s3;
	s4 = s1 * s2;
	cout << "s1*s2=>s4, then s4 is:\n";
	cout << "s4: " << s4;
	s5 = s1 - s2;
	cout << "s1-s2=>s5, then s5 is:\n";
	cout << "s5: " << s5;
	s6 = s1;
	cout << "s1=>s6, then s6 is:\n";
	cout << "s6: " << s6;
	cout << endl;

	cout << ((s1 == s2)?"s1 == s2":"s1 != s2") << endl;
	cout << ((s1 == s6)?"s1 == s6":"s1 != s6") << endl;
	cout << "s4 " << (s4.subSet(s2)?"is":"is not") << " a subset of s2. \n";
	cout << "s5 " << (s5.subSet(s2)?"is":"is not") << " a subset of s2. \n";
	cout << endl;

	int x;
	cout << "Input a element to continue the following test: ";
	cin >> x;
	cout <<"The elememt " << x 
		<< (s6.Contains(x)?" is":" is not") 
		<< " contained in s6. \n";
	if (s6.Contains(x)){
		cout << "Delete element " << x << endl;
		s6.delMember(x);
	}
	else{
		cout << "Add element " << x << endl;
		s6.addMember(x);
	}
	cout <<"The elememt " << x 
		<< (s6.Contains(x)?" is":" is not") 
		<< " contained in s6. \n" << endl;
	if (!s6.Contains(x)){
		cout << "Add element " << x << endl;
		s6.addMember(x);
	}
	cout << "Delete element " << x 
		<< (s6.delMember(x)?": Successful!":": Failed!") << endl;
	cout << "Delete element " << x 
		<< (s6.delMember(x)?": Successful!":": Failed!") << endl << endl;

	cout << "s6: " << s6 << endl;
	cout << "Make s6 empty:\n";
	s6.makeEmpty();
	cout << "s6: " << s6 << endl;

	cout << "Press enter to exit!\n";
	cin.ignore(100,'\n');
	char ch;
	cin.get(ch);
	return 0;
}
