#include <iostream>
#include <cstdlib>
#include "StaticLinkedList.h"
using namespace std;

void genRand(int *A, int n){
	for (int i = 0; i < n; i++)	{
		A[i] = rand()%1000 /* *99/RAND_MAX*/;
	}
}

int main(){
	int n;
	cout << "Input the num of the list you want to generate: ";
	cin >> n;
	int *A = new int[n];
	genRand(A, n);
	StaticLinkedList<int> lst(n+1);
	lst.input(A, n);
	cout << "The list is:\n";
	lst.output();
	cout << endl;

	cout << "\nTest insertSort(staticLinkedList<T>& L)" << endl;
	insertSort(lst);
	cout << "The sorted list is: \n";
	lst.output();
	cout<<endl;

	cout<<"\n\nTest selectSort (staticLinkedList<T>& L)"<<endl;
	StaticLinkedList<int> lst1(n+1);
	genRand(A,n);
	lst1.input(A, n);
	cout<<"Generate a new list, the list is:\n";
	lst1.output();
	cout<<endl;
	selectSort(lst1);
	cout<<"The sorted list is: \n";
	lst1.output();
	cout<<endl;

	cout<<"\n\nTest rMergeSort (staticLinkedList<T>& L,const int left, const int right)"<<endl;
	StaticLinkedList<int> lst2(n+1);
	genRand(A,n);
	lst2.input(A, n);
	cout<<"Generate a new list, the list is:\n";
	lst2.output();
	cout<<endl;
//	rMergeSort(lst2, 0, n-1);
	rMergeSort(lst2, 1, n);	//#0号是附加表头元素
	cout<<"The sorted list is: \n";
	lst2.output();
	cout<<endl;
	ReArrange(lst2);
	cout<<"The rearranged list array is: \n";;
	lst2.aoutput();

	cout<<"\n\nTest radixSort(staticLinkedList<T>& L, int d)"<<endl;
	StaticLinkedList<int> lst3(n+1);
	genRand(A,n);
	lst3.input(A, n);
	cout<<"Generate a new list, the list is:\n";
	lst3.output();
	cout<<endl;
    int (*gd)(Element<int> &,int,int) = getDigit<int>;//#改
	radixSort(lst3, 4, gd);//#改。注意d的取值
	cout<<"The sorted list is: \n";
	lst3.output();
	cout<<endl;

	cout << "Press enter to exit!\n";
	cin.ignore(100,'\n');
	char ch;
	cin.get(ch);
	return 0;
}
