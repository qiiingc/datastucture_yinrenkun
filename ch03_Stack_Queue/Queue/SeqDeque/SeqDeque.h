#ifndef SEQDEQUE_H
#define SEQDEQUE_H
#include "SeqQueue.h"

template <typename T>class SeqDeque:public SeqQueue<T>{
public:
	SeqDeque(int sz = 50):SeqQueue<T>(sz){};
	~SeqDeque(){};//动态建立的数组，调用基类的析构函数释放
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

template <typename T>bool SeqDeque<T>::getHead(T &x)const{
	T temp;
	bool tag = SeqQueue<T>::getFront(temp);
	x = temp;
	return tag;
}

template <typename T>bool SeqDeque<T>::getTail(T &x)const{
	if (front == rear)	return false;
	x = elements[(rear-1+maxSize)%maxSize];
	return true;
}

template <typename T>bool SeqDeque<T>::EnQueueHead(const T &x){
	if ((rear+1)%maxSize == front)	return false;
	front = (front-1+maxSize)%maxSize;//因为front指向队首元素，所以先移后入队
	elements[front] = x;
	return true;
}

template <typename T>bool SeqDeque<T>::EnQueueTail(const T &x){
	return SeqQueue<T>::EnQueue(x);
}

template <typename T>bool SeqDeque<T>::DeQueueTail(T &x){
	if (front == rear)	return false;
	rear = (rear-1+maxSize)%maxSize;
	return true;
}

template <typename T>bool SeqDeque<T>::DeQueueHead(T &x){
	T temp;
	bool tag = SeqQueue<T>::DeQueue(temp);
	x = temp;
	return tag;
}
#endif
