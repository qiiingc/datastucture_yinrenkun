#ifndef SORTEDDBLCHAIN_H
#define SORTEDDBLCHAIN_H
#include <iostream>
#include <cassert>
using namespace std;


template <typename E, typename K>struct ChainDblNode{
	E data;
	ChainDblNode<E,K> *rLink, *lLink;
	ChainDblNode(ChainDblNode<E,K> *l = NULL, ChainDblNode<E,K> *r = NULL){
		lLink = l;
		rLink = r;
	}
	ChainDblNode(E &e1, ChainDblNode<E,K> *l = NULL, ChainDblNode<E,K> *r = NULL){
		data = e1;
		lLink = l;
		rLink = r;
	}
};

template <typename E, typename K>class SortedDblChain{
public:
	SortedDblChain(){
		first = new ChainDblNode<E,K>;//不可以用first作为构造函数的左右指针，那是无效的，因为它还未指向一个新分配的头结点
		assert(first);
		first->rLink = first->lLink = first;//这句绝不可少
		current = first;
	}
	~SortedDblChain(){
		delete first;
	}
	ChainDblNode<E,K> *Head(){
		if (first->rLink == first){
			return NULL;
		}
		return first->rLink;
	}
	ChainDblNode<E,K> *Rear(){
		if (first->lLink == first){
			return NULL;
		}
		return first->lLink;
	}
	ChainDblNode<E,K> *Current(){
		if (current == first){
			return NULL;
		}
		return current;
	}
	ChainDblNode<E,K> *Search(const K k1);
	void Insert(const K k1, E &e1);
	bool Remove(const K k1, E &e1);
	friend istream& operator >> (istream& in, SortedDblChain<E,K> &R){
		E data;
		while (!in.eof()){
			assert(in >> data);
			R.Insert(data.key, data);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, SortedDblChain<E,K> &R){
		ChainDblNode<E,K> *p = R.first->rLink;
		while (p != R.first){
			out << p->data << endl;
			p = p->rLink;
		}
		return out;
	}
private:
	ChainDblNode<E,K> *first;
	ChainDblNode<E,K> *current;
};


template <typename E, typename K>void SortedDblChain<E,K>::Insert(const K k1, E &e1){
	ChainDblNode<E,K> *p = first->rLink;
	while (p != first && p->data < k1){
		p = p->rLink;
	}
	if (p != first && p->data == k1){	//关键码已存在，则用新的数据覆盖	
		p->data = e1;
		return;
	}
	ChainDblNode<E,K> *newNode = new ChainDblNode<E,K>(e1);
	assert(newNode);
	current = newNode;					//current指向刚插入的结点
	newNode->rLink = p;
	p->lLink->rLink = newNode;
	newNode->lLink = p->lLink;
	p->lLink = newNode;
}

template <typename E, typename K>bool SortedDblChain<E,K>::Remove(const K k1, E &e1){
	ChainDblNode<E,K> *p = first->rLink;
	while (p != first && p->data < k1){
		p = p->rLink;
	}
	if (p != first && p->data == k1){
		if (p == current){
			if (p->lLink != first){
				current = p->lLink;
			}
			else{
				current = p->rLink;
			}
		}
		p->rLink->lLink = p->lLink;
		p->lLink->rLink = p->rLink;	
		e1 = p->data;
		delete p;
		return true;
	}
	return false;
}

template <typename E, typename K>ChainDblNode<E,K> *SortedDblChain<E,K>::Search(const K k1){
	int i = 0;
	ChainDblNode<E,K> *p = current;
	if (p == first){
		return NULL;
	}
	if (k1 < p->data){
		while (p != first && k1 < p->data){
			p = p->lLink;
			i++;
		}
	}
	else	{
		while (p != first && k1 > p->data){
			p = p->rLink;
			i++;
		}
	}
	cout << "Count: " << i << endl;
	if (p != first && p->data == k1){
		current = p;
		return p;
	}
	else{
		return NULL;
	}
}
#endif
