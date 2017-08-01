#include "SeqStack.h"
#include <fstream>
#include <cassert>
using namespace std;
int main(){
	SeqStack<int> sta;
	ifstream fin("data.txt");
	assert(fin);
	int data;
	while (!fin.eof()){
		assert(fin >> data);
		sta.Push(data);		
	}
	cout << "The initial Stack in the file is:\n" << sta;
	cout << "The current size of the Stack is: " << sta.getSize() << endl;
	sta.getTop(data);
	cout << "The current Top of the Stack is : " << data << endl;
	sta.Pop(data);
	cout << "\nDo a Pop operation, then the stack is:\n" << sta << endl;
	cout << "The data popped is: " << data << endl;
	sta.getTop(data);
	cout << "The current Top of the Stack is : " << data << endl;

	cout << "\nTest the state of the stack:\n";
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";
	cout << "Now make the stack empty, then the state of the stack is:\n";
	sta.MakeEmpty();
	if (sta.IsEmpty())	cout << "The stack is empty now!\n";
	else if (sta.IsFull())	cout << "The stack is full now!\n";
		else	cout << "The stack is not empty and not full now!\n";
	return 0;
}
