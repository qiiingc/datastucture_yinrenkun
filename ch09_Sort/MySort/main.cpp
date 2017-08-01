#include "dataList.h"
#include "MySort.h"
#include "person.h"
#include <fstream>
using namespace std;

// 用于做RadixSort算法函数参数
// 取person类元素p的关键码的第d位数字的值，radix为基数。
int getDigit(person &p, int d, int R = radix){
	long key = p.getID();
	key = key<0?(-key):key;
	for (int i = 1; i < d; i++){
		key = key/R;
	}
	return key%R;
}

// MySort.h中的各排序算法使用示例：
// 由于各排序算法中，除了RadixSort外，其他各程序的输入参数都一样，
// 因此，这里只给出RadixSort和其它排序函数中的某一个来示范排序算法的使用。
int main(){
	ifstream fin("persons.txt");
	assert(fin);
	dataList<person,long> sc1, sc2;
	assert(fin >> sc1);
	sc2 = sc1;

	cout << "The origin datalist is:\n" << sc1 << endl;
	int (*gd)(person &,int,int) = getDigit;
	RadixSort<person,long>(sc1, 0, sc1.Length()-1, 3, gd);//#模板实参推演出现歧义，必须显式指定
	cout << "Use RadixSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BubbleSort(sc1, 0, sc1.Length()-1);
	cout << "Use BubbleSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	ShakerSort(sc1, 0, sc1.Length()-1);
	cout << "Use ShakerSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	SelectSort(sc1, 0, sc1.Length()-1);
	cout << "Use SelectSort( to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to continue!\n";
	char ch;
	cin.get(ch);

	cout << "====================================================\n";
	sc1=sc2;
	InsertSort(sc1, 0, sc1.Length()-1);
	cout << "Use InsertSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BinaryInsertSort(sc1, 0, sc1.Length()-1);
	cout << "Use BinaryInsertSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	ShellSort(sc1, 0, sc1.Length()-1);
	cout << "Use ShellSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	QuickSort(sc1, 0, sc1.Length()-1);
	cout << "Use QuickSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to continue!\n";
	cin.get(ch);

	cout << "====================================================\n";
	sc1=sc2;
	MergeSort(sc1, 0, sc1.Length()-1);
	cout << "Use MergeSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	HeapSort(sc1, 0, sc1.Length()-1);
	cout << "Use HeapSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	BSTSort(sc1, 0, sc1.Length()-1);
	cout << "Use BSTSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "====================================================\n";
	sc1=sc2;
	CountSort(sc1, 0, sc1.Length()-1);
	cout << "Use CountSort to sort the datalist, then the list is:\n" << sc1 << endl;

	cout << "Press enter to exit!\n";
	cin.get(ch);

	return 0;
}

