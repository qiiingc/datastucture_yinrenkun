#include <fstream>
#include "MaxHeap.h"
using namespace std;
int main(){
	ifstream fin("data.txt");
	assert(fin);
	int n;
	assert(fin >> n);
	int * a = new int[n];
	cout << "There are " << n << " nodes in the file.\n";
	cout << "The value of each node is:\n";
	for(int i = 0; i < n; i++){
		fin >> a[i];
		cout << "node[" << i << "]: " << a[i] << endl;
	}

	MaxHeap<int/*,int*/> h(a,n);
	cout<<"The MaxHeap is: \n";
	h.output();
	cout<<"+-----------------------------------------------------+"<<endl;
	cout<<"Test bool Insert(const Item& x)"<<endl;
	cout<<"Please input a value to insert : ";
	int t;
	cin>>t;
	h.Insert(t);
	cout<<"The new Maxheap is : ";
	h.output();
	cout<<"+-----------------------------------------------------+"<<endl;
	cout<<"Test bool RemoveMax(Item& x);"<<endl;
	h.RemoveMax(t);
	cout<<"The new heap is : ";
	h.output();
	cout<<"The max removed is : "<<t<<endl;

	cout << "Press enter to exit!\n";
	cin.ignore(100, '\n');
	char ch;
	cin.get(ch);
	return 0;
}
