#include "GenList.h"
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

int main(){
	ifstream fin1("data.txt");
	assert(fin1);
	string str;
	fin1 >> str;
	cout << "The genlist in the file is: \n" << str << endl;
	GenList<char> gl1;
	fin1.close();
	ifstream fin("data.txt");
	assert(fin);
	fin >> gl1;	
	cout << "\nSome information about Genlist gl1:\n";
	cout << "\nThe data of GenList is:" << endl;
	cout << gl1 << endl;

	cout << "\nThe depth of the GenList is: " << gl1.depth() << endl;
	cout << "The length of the GenList is: " << gl1.Length() << endl;

	cout << "The First Element is: ";
	int temp = 0;
	if (gl1.First()){
		temp = gl1.First()->utype;
		if (temp == 1){
			cout << "AtomNode: " << gl1.First()->info.value << endl;
		}
		else if (temp == 0){
			cout << "HeadNode." << endl;
		}
		else{
			cout << "SubListNode." << endl;
		}
	}
	else{
		cout << "NULL!" << endl;
	}

	cout << "The Second Element is: ";
	if (gl1.Next(gl1.First())){
		temp = gl1.Next(gl1.First())->utype;
		if (temp == 1){
			cout << "AtomNode: " << gl1.First()->info.value << endl;
		}
		else if (temp == 0){
			cout << "HeadNode! " << endl;
		}
		else{
			cout << "SubListNode!" << endl;
		}
	}
	else{
		cout << "NULL!" << endl;
	}

//	GenList<char> gl2(gl1);//Ç³¸´ÖÆ
	GenList<char> gl2;
	gl2.Copy(gl1);
	cout << "\ngl2 is a copy of gl1:\n";
	cout << "The data of gl2 is: " << endl;
	cout << gl2 << endl;

	if(gl1.equal(gl2)) cout<<"gl1 equals gl2.";
	else cout<<"gl1 do not equals gl2.";

	char rem;
	cout << "\nInput the data that you want to Remove: " << endl;
	cin >> rem;
	gl2.delvalue(rem);
	cout << "The current GenList gl2 is: " << endl;
	cout << gl2<< endl;

	cout << "\nInput the data that you want to Remove: " << endl;
	cin >> rem;
	gl1.delvalue(rem);
	cout << "The current GenList gl1 is: " << endl;
	cout << gl1<< endl;
	return 0;
}
