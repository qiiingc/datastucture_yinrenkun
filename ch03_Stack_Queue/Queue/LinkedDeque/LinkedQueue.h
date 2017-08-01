#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>struct LinkNode{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = NULL){
		link = ptr;
	}
	LinkNode(const T &item, LinkNode<T> *ptr = NULL){
		data = item;
		link = ptr;
	}
};

template <typename T>class LinkedQueue{//无头结点
public:
	LinkedQueue(){
		rear = NULL;
		front = NULL;
	}
	~LinkedQueue(){
		makeEmpty();
	}
	bool EnQueue(const T &x);
	bool DeQueue(T &x);
	bool getFront(T &x)const;
	void makeEmpty();
	bool IsEmpty()const{
		return front == NULL;
	}
	int getSize()const;
	friend ostream& operator << (ostream &os, LinkedQueue<T> &Q){
		LinkNode<T> *p = Q.front;
		int i = 0;
		while (p){
			os << "#" << ++i << ": " << p->data << endl;
			p = p->link;
		}
		os << "Queue Size: " << Q.getSize() << endl;
		return os;
	}
	void output();
protected:
	LinkNode<T> *front, *rear;
};

template <typename T>void LinkedQueue<T>::makeEmpty(){
	LinkNode<T> *p;
	while (front){
		p = front;
		front = front->link;
		delete p;
	}
}

template <typename T>bool LinkedQueue<T>::EnQueue(const T &x){
	if (!front){
		front = rear = new LinkNode<T>(x);
		if (!front)	return false;
	}
	else{
		rear->link = new LinkNode<T>(x);
		if (!(rear->link))	return false;
		rear = rear->link;
	}
	return true;
}

template <typename T>bool LinkedQueue<T>::DeQueue(T &x){
	if (IsEmpty())	return false;
	LinkNode<T> *p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <typename T>bool LinkedQueue<T>::getFront(T &x)const{
	if (IsEmpty())	return false;
	x = front->data;
	return true;
}

template <typename T>int LinkedQueue<T>::getSize()const{
	LinkNode<T> *p = front;
	int k = 0;
	while (p){
		p = p->link;
		k++;
	}
	return k;
}

template <typename T>void LinkedQueue<T>::output(){
	LinkNode<T> *p = front; int i = 1;
	while (i <= getSize())	{
		cout << p->data << "  "<<endl;
		p = p->link;
        i++;
	}
}
#endif
