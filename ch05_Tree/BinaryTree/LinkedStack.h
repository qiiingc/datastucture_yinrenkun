#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>struct StackNode{
	T data;
	StackNode<T> *link;
	StackNode(T d = 0, StackNode<T> *next = NULL):link(next),data(d){}
};

template <typename T>class LinkedStack{
private:
	StackNode<T> *top;
public:
	LinkedStack():top(NULL){}//无头结点
	~LinkedStack(){
		makeEmpty();
	}
	void Push(const T &x);
	bool Pop(T &x);
	bool getTop(T &x)const;	
	int getSize()const;
	bool IsEmpty()const{
		return top == NULL;
	}
	bool IsFull()const{
		return false;
	}
	void makeEmpty();
	friend ostream& operator << (ostream &os, LinkedStack<T> &s)	{
		os << "Stack Size: " << s.getSize() << endl;
		StackNode<T> *p = s.top;
		int i = 0;
		while (p){
			os << ++i << ": " << p->data << endl;
			p = p->link;
		}
		return os;
	}
};

template <typename T>void LinkedStack<T>::makeEmpty(){
	StackNode<T> *p;
	while (top){//最后top为NULL
		p = top;
		top = top->link;
		delete p;
	}
}

template <typename T>void LinkedStack<T>::Push(const T &x){
	top = new StackNode<T>(x, top);
	assert(top);
}

template <typename T>bool LinkedStack<T>::Pop(T &x){
	if (IsEmpty()){
		return false;
	}
	StackNode<T> *p = top;
	top = top->link;
	x = p->data;
	delete p;
	return true;	
}

template <typename T>bool LinkedStack<T>::getTop(T &x)const{	
	if (IsEmpty())	return false;
	x = top->data; 
	return true;
}

template <typename T>int LinkedStack<T>::getSize()const{
	StackNode<T> *p = top;
	int k = 0;
	while (p){
		p = p->link;
		k++;
	}
	return k;
}
#endif
