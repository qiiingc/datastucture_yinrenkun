#ifndef LINKEDSET_H
#define LINKEDSET_H
#include <iostream>
using namespace std;
//集合的结点类定义
template <typename T>
struct SetNode{
	T data;
	SetNode<T> *link;
	SetNode(){
		link = NULL;
	}
	SetNode(const T &x, SetNode<T> *next = NULL){
		data = x;
		link = next;
	}
};

//集合的类定义
template <typename T>class LinkedSet{
private:
	SetNode<T> *first, *last;
public:
	LinkedSet(){
		first = last = new SetNode<T>;
	}
	LinkedSet(LinkedSet<T> &R);
	~LinkedSet(){
		makeEmpty();
		delete first;
	}
	void makeEmpty();
	bool addMember(const T &x);
	bool delMember(const T &x);
	LinkedSet<T>& operator = (const LinkedSet<T> &R);
	LinkedSet<T> operator + (const LinkedSet<T> &R);
	LinkedSet<T> operator * (const LinkedSet<T> &R);
	LinkedSet<T> operator - (const LinkedSet<T> &R);
	bool Contains(const T &x);
	bool subSet(const LinkedSet<T> &R);
	bool operator == (const LinkedSet<T> &R);
	friend istream& operator >> (istream &in, LinkedSet<T> &R){//输入集合
		T item;
		while (!in.eof()){
			in >> item;
			if (item < 0){
				break;
			}
			R.addMember(item);
		}
		in.clear();
		return in;
	}
	friend ostream& operator << (ostream &out, LinkedSet<T> &R){//输出
		cout << "{";
		if(R.first->link){
			cout << R.first->link->data;
			SetNode<T> *q = R.first->link->link;
			while (q){
				cout << ", " << q->data;
				q = q->link;
			}
		}
		cout << "}\n";
		return out;
	}
};

template <typename T>LinkedSet<T>::LinkedSet(LinkedSet<T> &R){//复制构造函数
	SetNode<T> *srcptr = R.first->link;
	first = last = new SetNode<T>;
	while (srcptr)
	{
		last->link = new SetNode<T>(srcptr->data);
		last = last->link;
		srcptr = srcptr->link;
	}
	last->link = NULL;
}

template <typename T>bool LinkedSet<T>::Contains(const T &x){//集合是否包含x
	SetNode<T> *temp = first->link;
	while (temp && temp->data < x){
		temp = temp->link;
	}
	return (temp && temp->data == x);
}

template <typename T>bool LinkedSet<T>::subSet(const LinkedSet<T> &R){//this是否是r的子集
	SetNode<T> *pr = R.first->link;
	SetNode<T> *pt = first->link;
	while (pt && pr){
		if (pt->data == pr->data){
			pt = pt->link;
			pr = pr->link;
		}
		else if (pt->data > pr->data){
			pr = pr->link;
		}
		else		{
			return false;
		}
	}
	return pt?false:true;
}

template <typename T>bool LinkedSet<T>::addMember(const T &x){//添加值为x的元素
	SetNode<T> *p = first->link, *pre = first;
	while (p && p->data < x){
		pre = p;
		p = p->link;
	}		
	if (p && p->data == x){
		return false;
	}
	SetNode<T> *s = new SetNode<T>(x);
	s->link = p;
	pre->link = s;
	if (p == NULL){
		last = s;
	}
	return true;
}

template <typename T>bool LinkedSet<T>::delMember(const T &x){//删除值为x的元素
	SetNode<T> *p = first->link, *pre = first;
	while (p && p->data < x)	{
		pre = p;
		p = p->link;
	}		
	if (p && p->data == x)	{
		pre->link = p->link;
		if (p == last){
			last = pre;
		}
		delete p;
		return true;
	}
	else{
		return false;
	}
}

template <typename T>void LinkedSet<T>::makeEmpty(){//清空集合
	SetNode<T> *q;
	while (first->link){
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

template <typename T>LinkedSet<T>& LinkedSet<T>::operator = (const LinkedSet<T> &R){
	SetNode<T> *srcptr = R.first->link;
	first = last = new SetNode<T>;
	while (srcptr){
		last->link = new SetNode<T>(srcptr->data);
		last = last->link;
		srcptr = srcptr->link;
	}
	last->link = NULL;
	return *this;
}

template <typename T>LinkedSet<T> LinkedSet<T>::operator + (const LinkedSet<T> &R){//并
	SetNode<T> *pb = R.first->link;
	SetNode<T> *pa = first->link;
	LinkedSet<T> temp;
	SetNode<T> *p, *pc = temp.first;
	while (pa && pb)	{
		if (pa->data == pb->data){
			pc->link = new SetNode<T>(pa->data);
			pa = pa->link;  pb = pb->link;
		}
		else if (pa->data < pb->data){
			pc->link = new SetNode<T>(pa->data);
			pa = pa->link;
		}
		else{
			pc->link = new SetNode<T>(pb->data);
			pb = pb->link;
		}
		pc = pc->link;
	}
	p = (pa?pa:pb);
	while (p){
		pc->link = new SetNode<T>(p->data);
		pc = pc->link;
		p = p->link;
	}
	pc->link = NULL;
	temp.last = pc;
	return temp;
}

template <typename T>LinkedSet<T> LinkedSet<T>::operator * (const LinkedSet<T> &R){//交
	SetNode<T> *pb = R.first->link;
	SetNode<T> *pa = first->link;
	LinkedSet<T> temp;
	SetNode<T> *pc = temp.first;
	while (pa && pb){
		if (pa->data == pb->data){
			pc->link = new SetNode<T>(pa->data);
			pc = pc->link;
			pa = pa->link;  pb = pb->link;
		}
		else if (pa->data < pb->data){
			pa = pa->link;
		}
		else{
			pb = pb->link;
		}
	}
	pc->link = NULL;
	temp.last = pc;
	return temp;								
}

template <typename T>LinkedSet<T> LinkedSet<T>::operator - (const LinkedSet<T> &R){//差
	SetNode<T> *pb = R.first->link;
	SetNode<T> *pa = first->link;
	LinkedSet<T> temp;
	SetNode<T> *pc = temp.first;
	while (pa && pb){
		if (pa->data == pb->data){
			pa = pa->link;
			pb = pb->link;
		}
		else if (pa->data < pb->data){
			pc->link = new SetNode<T>(pa->data);
			pc = pc->link;  pa = pa->link;
		}
		else{
			pb = pb->link;
		}
	}
	while (pa){
		pc->link = new SetNode<T>(pa->data);
		pc = pc->link;
		pa = pa->link;
	}
	pc->link = NULL;
	temp.last = pc;
	return temp;
}

template <typename T>bool LinkedSet<T>::operator == (const LinkedSet<T>& R){
	SetNode<T> *pb = R.first->link;
	SetNode<T> *pa = first->link;
	while (pa && pb){
		if (pa->data == pb->data){
			pa = pa->link;
			pb = pb->link;
		}
		else{
			return false;
		}
	}
	return (pa||pb)?false:true;
}
#endif
