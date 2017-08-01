#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include <iostream>
#include "SeqList.h"
using namespace std;

extern const int defaultSize;

long Fib(int n){
	int i;
	if (n == 0 || n == 1){
		return n;
	}
	int twoback = 0, oneback = 1, current;
	for ( i = 2; i <= n; i++){
		current = twoback + oneback;
		twoback = oneback;
		oneback = current;
	}
	return current;
}

template <typename E, typename K>class SortedList:public SeqList<E>{
public:
	void Insert(const K k1, E &e1);
	bool Remove(const K k1, E &e1);
	int Search(K k1)const;
	int BinarySearch(K k1)const;
	int BinarySearch(K k1, int low, int high)const;
	int FibonacciSearch(K k1)const;
};

template <typename E, typename K>void SortedList<E,K>::Insert(const K k1, E &e1){//生成有序表
	int i,j;
	for (i = 0; i <= last; i++)	{	//可以改进为比较与移动一次完成
		if (data[i] == k1){			//找到是更换
			data[i] = e1;
			return;
		}
		if (data[i] > k1){			//未找到是插入
			break;
		}
	}
	for (j = last; j >= i; j--){	//后移后插入
		data[j+1] = data[j];
	}
	data[i] = e1;
	last++;
}

template <typename E, typename K>bool SortedList<E,K>::Remove(const K k1, E &e1){
	if (last == -1){
		return false;
	}
	int i,j;
	for (i = 0; i <= last; i++){
		if (data[i] > k1){
			return false;
		}
		if (data[i] == k1){
			e1 = data[i];
			break;
		}
	}
	for (j = i; j <= last; j++){
		data[j] = data[j+1];
	}
	last--;
	return true;
}

template <typename E, typename K>int SortedList<E,K>::Search(K k1)const{//顺序查找
	int i;
	for ( i = 0; i <= last; i++){
		if (data[i] == k1){
			return i+1;
		}
		if (data[i] > k1){
			break;
		}
	}
	return 0;
}

template <typename E, typename K>int SortedList<E, K>::BinarySearch(K k1, int low, int high)const{//递归对半查找
	int mid = 0;
	if (low <= high){
		mid = (low + high) / 2;
		if (data[mid-1] < k1){
		   mid = BinarySearch(k1, mid +1, high);
		}
		else if (data[mid-1] > k1){
		   mid = BinarySearch(k1, low, mid-1);
		}
	}
	return mid;
}

template <typename E, typename K> int SortedList<E,K>::BinarySearch(K k1)const{//迭代对半查找
	int high = last + 1, low = 1, mid;
	while (low <= high){		 
		mid = (low + high) / 2;
		if (data[mid-1] < k1){
			low = mid+1;
		}			
		else if (data[mid-1] > k1){
				high = mid-1;
			}
			else{
				return mid;
			}
	}
    return 0;
}

template <typename E, typename K>	int SortedList<E,K>::FibonacciSearch(K k1)const{//斐波那契查找
	int i = 1,j;
	while (Fib(i) < last+1){	//Fib也要计算，不比*0.618快多少;最好按需制一个映射表，查Fib值
		i++;
	}
	if (i < 3){
		return BinarySearch(k1);
	}
	if (Fib(i) > last+1){
		for ( j = last+1; j < Fib(i)-1; j++){	//添加虚元素，黄金分割的优势减弱
			data[j] = data[j-1] + 1;
		}
	}
	int d1 = Fib(i-2), d2 = Fib(i-3), mid = Fib(i-1);
	while (d2 >= 0 && d1 >= 0){
		if (data[mid-1] < k1){
			mid = mid + d2;
			d1 = d1 - d2;
			d2 = d2 - d1;
		}
		else if (data[mid-1] > k1){
				mid = mid - d2;
				int tmp = d1;
				d1 = d2;
				d2 = tmp - d2;
			}
			else{
				return (mid-1 > last)?0:mid;
			}
	}
    return 0;
}
#endif
