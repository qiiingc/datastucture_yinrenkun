#include "SeqDeque.h"
#include <fstream>
#include <cassert>
using namespace std;

int main(){
	int i,data, len;
	cout << "1. EnQueueTail and DeQueueHead:\n" << endl;
	cout << "The data in the file is: \n";
	ifstream fin1("data.txt");
	assert(fin1);
	SeqDeque<int> que1;
	while (!fin1.eof()){
		assert(fin1 >> data);
		cout << data << "  ";
		que1.EnQueue(data);
	}
	cout << endl;
	fin1.close();
	cout << "\nUse EnQueueTail for each data in the file, \nthen the queue is:\n";
	cout << que1 << endl;
	cout << "\nUse DeQueueHead in turn, the result is:"<<endl;
	len = que1.getSize();
	for(i = 0; i < len; i++){
		que1.DeQueue(data);
		cout << "Delete " << data << ", then the queue is:\n";
		cout << que1 << endl;
	}

	cout << "\n==================================================\n"; 

	cout << "2. EnQueueHead and DeQueueTail:" << endl;
	cout << "The data in the file is: \n";
	ifstream fin2("data.txt");
	assert(fin2);
	SeqDeque<int> que2;
	while (!fin2.eof()){
		assert(fin2 >> data);
		cout << data << "  ";
		que2.EnQueueHead(data);
	}
	cout << endl;
	fin2.close();
	cout << "\nUse EnQueueHead for each data in the file, \nthen the queue is:\n";
	cout << que2 << endl;
	cout << "\nUse DeQueueTail in turn, the result is:"<<endl;
	len = que2.getSize();
	for(i = 0; i < len; i++){
		que2.DeQueueTail(data);
		cout << que2.getSize();
		cout << "Delete " << data << ", then the queue is:\n";
		cout << que2 << endl;
	}
	return 0;
}
