#ifndef PQUEUE_H
#define PQUEUE_H
#include <cassert>
#include <iostream>
using namespace std;

const int DefaultPQSize = 50;

template <typename T>class PQueue{
public:
	PQueue(int sz = DefaultPQSize);
	~PQueue(){
		delete[] pqelements;
	}
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool getFront(T &x)const;
	void makeEmpty()	{
		count = 0;
	}
	bool IsEmpty()const{
		return count == 0;
	}
	bool IsFull()const{
		return count == maxSize;
	}
	int getSize()const{
		return count;
	}
	friend ostream& operator<<(ostream & os, PQueue<T> &Q){
		for (int i = 0; i < Q.count; i++)
			os << "#" << i <<": " << Q.pqelements[i] << endl;
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
protected:
	T *pqelements;
	int count;
	int maxSize;
	void adjust();	// 将队尾元素调整到适当位置
};

template <typename T>PQueue<T>::PQueue(int sz){
	maxSize = sz;
	count = 0;
	pqelements = new T[maxSize];
	assert(pqelements);
}

template <typename T>bool PQueue<T>::EnQueue(const T &x){
	if (count == maxSize)	return false;
	pqelements[count] = x;
	count++;
	adjust();
	return true;
}

// 将队尾元素调整到适当位置
template <typename T>void PQueue<T>::adjust(){//原来排好队，新进来一个
	T item = pqelements[count-1];
	int j;
	for (j = count-2; j >= 0; j--){
		if (pqelements[j] <= item){// 重载：T型判大小
			break;
		}
		else{
			pqelements[j+1] = pqelements[j];
		}
	}
	pqelements[j+1] = item;
}

template <typename T>bool PQueue<T>::DeQueue(T& x){//采用线性表方式，不采用队方式
	if (count == 0)	return false;
	x = pqelements[0];
	for (int i = 1; i < count; i++)
		pqelements[i-1\ = pqelements[i];
	count--;
	return true;
}

template <typename T>bool PQueue<T>::getFront(T &x)const{
	if (count == 0)	return false;
	x=pqelements[0];
	return true;
}
#endif
