#include <cassert>
#include <iostream>
using namespace std;

const int stackIncreament = 20; //栈溢出时扩展空间的增量

template <typename T>class SeqStack{
public:
	SeqStack(int sz =50);
	~SeqStack(){
		delete []elements;
	}
	void Push(const T &x);
	bool Pop(T &x);
	bool getTop(T &x)const;
	bool IsEmpty()const{
		return top == -1;
	}
	bool IsFull()const{
		return top == maxSize-1;
	}
	int getSize()const{
		return top+1;
	}
	void MakeEmpty(){
		top = -1;
	}
	friend ostream& operator << (ostream &out, SeqStack<T> &s)	{
		out << "Index of top is: " << s.top << endl;
		for (int i = 0; i <= s.top; i ++)
			out << i << ": " << s.elements[i] << endl;
		return out;
	}
private:
	T *elements;
	int top;
	int maxSize;
	void overflowProcess();
};

template <typename T>SeqStack<T>::SeqStack(int sz){
	top = -1;
	maxSize = sz;
	elements = new T[maxSize];
	assert(elements); 
}

template <typename T>void SeqStack<T>::overflowProcess(){	//私有函数：扩充栈的存储空间。
	T *newArray = new T[maxSize + stackIncreament];
	assert(newArray);
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete []elements;
	elements = newArray;
}


template <typename T>void SeqStack<T>::Push(const T &x){
	if (IsFull())	overflowProcess();
	elements[++top] = x;  // top++; elements[top] = x;
}


template <typename T>bool SeqStack<T>::Pop(T &x){
	if (IsEmpty()){
		return false;
	}
	x = elements[top--]; // x = elements[top]; top--;
	return true; 
}


template <typename T>bool SeqStack<T>::getTop(T &x)const{
	if (IsEmpty()){
		return false;
	}
	x = elements[top];
	return true;
}
