#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H
#include "LinkedQueue.h"
//Ë«¶Ë¶ÓÁÐ

template <typename T>
class LinkedDeque:public LinkedQueue<T>{
public:
	LinkedDeque(){};
	~LinkedDeque(){};
	bool getHead(T &x)const;
	bool getTail(T &x)const;
	bool EnQueue(const T &x){
		return EnQueueTail(x);
	}
	bool EnQueueHead(const T &x);
	bool EnQueueTail(const T &x);
	bool DeQueue(T &x){
		return DeQueueHead(x);
	}
	bool DeQueueHead(T &x);
	bool DeQueueTail(T &x);
};

template <typename T>bool LinkedDeque<T>::getHead(T &x)const{
	T temp;
	bool tag = LinkedQueue<T>::getFront(temp);
	x = temp;
	return tag;
}

template <typename T>bool LinkedDeque<T>::getTail(T &x)const{
	if (!front)
	{
		return false;
	}
	x = rear->data;
	return true;
}

template <typename T>bool LinkedDeque<T>::EnQueueHead(const T &x){
	LinkNode<T> *p = new LinkNode<T>(x);
	if (!p)	return false;
	p->link = front;
	front = p;
	if (!front->link)	rear = front;
	return true;
}

template <typename T>bool LinkedDeque<T>::EnQueueTail(const T &x){
	return LinkedQueue<T>::EnQueue(x);
}

template <typename T>bool LinkedDeque<T>::DeQueueHead(T &x){
	T temp;
	bool tag = LinkedQueue<T>::DeQueue(temp);
	x = temp;
	return tag;
}

template <typename T>bool LinkedDeque<T>::DeQueueTail(T &x){
	if (!front)	return false;
	if (front == rear){
		x = rear->data;
		front = rear = NULL;
		return true;
	}
	LinkNode<T> *p = front;
	while (p->link != rear)	p = p->link;
	x = rear->data;
	p->link = NULL;
	rear = p;
	return true;
}
#endif
