#ifndef DBLLIST_H
#define DBLLIST_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>struct DblNode{
	T data;
	DblNode<T> *rLink, *lLink;
	DblNode(DblNode<T> *l = NULL, DblNode<T> *r = NULL){
		lLink = l;
		rLink = r;
	}
	DblNode(T value, DblNode<T> *l = NULL, DblNode<T> *r = NULL){
		data = value;
		lLink = l;
		rLink = r;
	}
};

template <typename T>class DblList{
public:
	DblList(T uniqueVal){
		first = new DblNode<T>(uniqueVal);
		assert(first);
		first->rLink = first->lLink = first;
	}
	~DblList()	{//析构函数不可少
		makeEmpty();
		delete first;//释放附加头结点
	}
	void makeEmpty(){//添
		DblNode<T> *q;
		while (first->rLink != first){//仅余附加头结点
			q = first->rLink;//先不管左指针
			first->rLink = q->rLink;
			delete q;
		}
		first->lLink=first;//最后处理
	}
	DblNode<T> *getFirst()const{
		return first;
	}
	DblNode<T> *Search(const T &x, int d = 1);
	DblNode<T> *Locate(int i, int d = 1);
	//在链表中定位序号为i(≥0)的结点, d=0按前驱方
	//向,d≠0按后继方向
	bool Insert(int i, const T &x, int d = 1);
	//在第i个结点后插入一个包含有值x的新结点,d=0
	//按前驱方向,d≠0按后继方向
	bool Remove(int i, T &x, int d);
	bool IsEmpty(){
		return first->rlink == first;
	}
	bool IsFull(){
		return false;
	}
	friend istream& operator >> (istream& in, DblList<T> &dbl){//改
		int i = 0;
		T data;
		dbl.makeEmpty();
		while (!in.eof()){
			in >> data;
			dbl.Insert(i, data, 1);
			i++;
		}
		return in;
	}

	friend ostream & operator << (ostream &out, DblList <T> &dbl)	{
		DblNode <T> *p= dbl.first->rLink;
		while ( p!=dbl.first ){
			out << p->data <<'\t';
			p = p->rLink;
		}
		cout << endl;
		return out;
	}
private:
	DblNode<T> *first;
};

template <typename T>DblNode<T> *DblList<T>::Locate(int i, int d){//d==1向右
	if (first->rLink == first || i==0){
		return first;
	}
	DblNode<T> *current = (d == 0)?first->lLink:first->rLink;
	while (current != first && --i > 0){
		current = (d == 0)?current->lLink:current->rLink;
	}
	return (current == first)?NULL:current;
}

template <typename T>DblNode<T> *DblList<T>::Search(const T &x, int d){//此函数向左向右无所谓
	DblNode<T> *current = (d == 0)?first->lLink:first->rLink;
	while (current != first && current->data != x)	{
		current = (d == 0)?current->lLink:current->rLink;
	}
	return (current == first)?NULL:current;
}

template <typename T>bool DblList<T>::Insert(int i, const T &x, int d){
	//建立一个包含有值x的新结点, 并将其按 d 指定的方向插入到第i个结点之后。
	DblNode<T> *current = Locate(i, d);
	if (current == NULL){
		return false;    //插入失败
	}
	DblNode<T> *newNode = new DblNode<T>(x);
	assert(newNode);
	if (d == 0){		//前驱方向:插在第i个结点左侧	
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else{			//后继方向:插在第i个结点后面	
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;
}

template <typename T>
bool DblList<T>::Remove(int i, T &x, int d){
	//在双向循环链表中按d所指方向删除第i个结点。
	DblNode<T> *current = Locate(i, d);
	if (current == NULL)
	{
		return false; 	      //删除失败
	}
	current->rLink->lLink = current->lLink;
	current->lLink->rLink = current->rLink;	
	x = current->data;
	delete current;
	return true;
}
#endif
