#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename E, typename K>struct ChainNode{
	E data;
	ChainNode<E,K> *link;
	ChainNode()	{
		link = NULL;
	}
	ChainNode(E &e1, ChainNode<E,K> *next = NULL)	{
		data = e1;
		link = next;
	}
};

template <typename E, typename K>class SortedChain{
public:
	SortedChain(){
		first = new ChainNode<E,K>;
		assert(first);
	}
	~SortedChain(){
		delete first;
	}
	ChainNode<E,K> *Search(const K k1)const;
	void Insert(const K k1, E &e1);
	bool Remove(const K k1, E &e1);
	ChainNode<E,K> *Begin(){
		return first->link;
	}
	ChainNode<E,K> *Next(ChainNode<E,K> *current)const{
		return (current)?current->link:NULL;
	}
	friend ostream& operator << (ostream &out, SortedChain<E,K> &R){
		ChainNode<E,K> *p = R.first->link;
		while (p){
			out << p->data << endl;
			p = p->link;
		}
		return out;
	}
	friend istream& operator >> (istream &in, SortedChain<E,K> &R){
		E data;
		while (!in.eof()){
			assert(in >> data);
			R.Insert(data.key, data);
		}
		return in;
	}
private:
	ChainNode<E,K> *first;
};

template <typename E, typename K>ChainNode<E,K> *SortedChain<E,K>::Search(const K k1)const{
	ChainNode<E,K> *p = first->link;
	while (p && p->data < k1)	{
		p = p->link;
	}
	return (p && p->data == k1)?p:NULL;
}

template <typename E, typename K>void SortedChain<E,K>::Insert(const K k1, E &e1){
	ChainNode<E,K> *p = first->link;
	ChainNode<E,K> *pre = first;
	while (p && p->data < k1){
		pre = p;
		p = p->link;
	}
	if (p && p->data == k1){	//关键码已存在，则用新的数据覆盖	
		p->data = e1;
		return;
	}
	ChainNode<E,K> *newNode = new ChainNode<E,K>(e1);
	assert(newNode);
	newNode->link = p;
	pre->link = newNode;
}

template <typename E, typename K>bool SortedChain<E,K>::Remove(const K k1, E &e1){
	ChainNode<E,K> *p = first->link;
	ChainNode<E,K> *pre = first;
	while (p && p->data < k1){
		pre = p;
		p = p->link;
	}
	if (p && p->data == k1){
		pre->link = p->link;
		e1 = p->data;
		delete p;
		return true;
	}
	return false;
}
#endif
