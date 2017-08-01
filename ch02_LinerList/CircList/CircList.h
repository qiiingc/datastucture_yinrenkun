#ifndef CIRCLIST_H
#define CIRCLIST_H
#include <iostream>
#include <cassert>
#ifndef INSMOD_INF_INR
#define INSMOD_INF_INR
enum InsMod {INF, INR};//向前还是向后生成
#endif
using namespace std;

template <typename T>class CircLinkNode{
public:
	T data;
	CircLinkNode<T> *link;
	CircLinkNode(CircLinkNode<T> *ptr = NULL){//建立空结点
		link = ptr;
	}
	CircLinkNode(const T &item, CircLinkNode<T> *ptr = NULL){//建立非空结点
		data = item;
		link = ptr;
	}
};

template <typename T>class CircList{
public:
	CircList(){//建立有附加头结点的空环链表
		last = first = new CircLinkNode<T>;
		first->link = first;
	}
	CircList(const T &x){//头结点中可放特殊信息
		last = first = new CircLinkNode<T>(x);
		first->link = first;
	}
	CircList(CircList<T> &L);//复制一个环链表
	~CircList()	{//改
		makeEmpty();
		delete first;//释放附加头结点
	}
	void makeEmpty();
	int Length()const;
	CircLinkNode<T> *getHead()const{//本函数会破坏封装性
		return first;
	}
	CircLinkNode<T> *Search(T x);
	CircLinkNode<T> *Locate(int i);
	bool getData(int i,T&x)const;
	void setData(int i, T &x);
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool IsEmpty()const{
		return (first->link == first)?true:false;
	}
	bool IsFull()const{//链表不会满，仅仅为了与顺序表一致，保留本函数
		return false;
	}
	void Sort();
	void Inverse();//不要返回
	void input(T endTag, InsMod im = INR);
	void output();
	CircList<T> &operator = (CircList<T> &L);
	friend ostream& operator << (ostream &out, CircList<T> &L){
		CircLinkNode<T> *current = L.first->link;
		while (current != L.first){
			out << current->data <<'\t';
			current = current->link;
		}
		out<<endl;
		return out;
	}
	friend istream& operator >> (istream &in, CircList<T> &L){//重新输入数据，向后生成
		T val;
		L.makeEmpty();//先清空
		while (!in.eof()){
			in >> val;
			L.last->link = new CircLinkNode<T>(val);
			assert(L.last->link);
			L.last = L.last->link;
		}
		L.last->link = L.first;
		in.clear(0);//当以ctrl_Z结束，流关闭，必须重新打开
		return in;
	}
protected:
	CircLinkNode<T> *first, *last;
	void inputFront(T endTag);
	void inputRear(T endTag);
};

template <typename T>CircList<T>::CircList(CircList<T> &L){
	T value;
	CircLinkNode<T> *srcptr = L.first;
	CircLinkNode<T> *destptr = first = new CircLinkNode<T>;
	while (srcptr->link != L.first)
	{
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	last = destptr;
	last->link = first;
}

template <typename T>void CircList<T>::makeEmpty(){//改
	CircLinkNode<T> *q;
	while (first->link != first){//仅余附加头结点
		q = first->link;
		first->link = q->link;
		delete q;
	}
	last=first; //尾指针处理不可少，否则悬浮
}

template <typename T>int CircList<T>::Length()const{
	CircLinkNode<T> *p = first->link;
	int count = 0;
	while (p != first)
	{
		p = p->link;
		count++;
	}
	return count;
}

template <typename T>CircLinkNode<T> *CircList<T>::Search(T x){//改
	CircLinkNode<T> *current = first->link;
	while (current != first && current->data != x){
		current = current->link;
	}
	if(current==first) current=NULL;//未找到返回NULL，保持各函数一致
	return current;
}

template <typename T>CircLinkNode<T> *CircList<T>::Locate(int i){
	if (i < 0){
		return NULL;
	}
	if (i == 0){
		return first;
	}
	CircLinkNode<T> *current = first->link;
	int k = 1;
	while (current != first && k < i){
		current = current->link;
		k++;
	}
	return (k == i)?current:NULL;
}

template <typename T>bool CircList<T>::getData(int i,T&x)const{//改，与教材勘误一致
	if (i <= 0){
		return false;
	}
	CircLinkNode<T> *current = Locate(i);
	if (current == first || !current){
		return false;
	}
	else{
		x=current->data
		return true;
	}
}

template <typename T>void CircList<T>::setData(int i, T &x){//修改指定结点数据
	if (i <= 0)	return;
	CircLinkNode<T> *current = Locate(i);
	if (current == first || !current) return;
	else current->data = x;
}

template <typename T>bool CircList<T>::Insert(int i, T &x){//由新数据x建立的结点插入在第i号结点之后
	CircLinkNode<T> *current = Locate(i);
	if (current == NULL){
		return false;
	}
	CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
	if (!newNode)	{
		cerr << "Memory allocating error!" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	if (last->link != first){//新结点在链尾，链尾指针要移动
		last = last->link;
	}
	return true;
}

template <typename T>bool CircList<T>::Remove(int i, T &x){//删除结点，并提取数据
	CircLinkNode<T> *current = Locate(i-1);//定位在待删除结点的前一结点
	if (!current || current->link == first)	return false;
	CircLinkNode<T> *del = current->link;
	if (del == last) last = current;//被删结点为尾结点，重置尾指针
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template <typename T>void CircList<T>::output(){//可以代之以调用重载的<<运算符
	CircLinkNode<T> *current = first->link;
	while (current != first){
		cout << current->data << endl;
		current = current->link;
	}
}

template <typename T>CircList<T> &CircList<T>::operator = (CircList<T> &L){//改，原函数误认为原链表只有一个头指针
	T value;
	CircLinkNode<T> *srcptr = L.first;
	makeEmpty();//应该先清除，保留附加头结点，后赋值复制
	CircLinkNode<T> *destptr = first;
	while (srcptr->link != L.first)	{
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	last=destptr;//处理尾指针
	destptr->link = first;
	return *this;
}

template <typename T>void CircList<T>::input(T endTag, InsMod im){
	if (im == INF){
		inputFront(endTag);
	}
	else{
		inputRear(endTag);
	}
}

template <typename T>void CircList<T>::inputFront(T endTag){//向前生成
	CircLinkNode<T> *newNode;
	T val;
	cin >> val;//作为链表对象附加头结点已存在，并改为可在原链表中添加任意多个结点
	while ( val != endTag){//endTag结束标识
		newNode = new CircLinkNode<T>(val);
		if (!newNode){
			cerr << "Memory allocation error!" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		if (last== first)	last = last->link;//仅在原是空链表那一步要修改尾指针
		cin >> val;
	}
}

template <typename T>void CircList<T>::inputRear(T endTag){//向后生成，已改
	T val;	
	cin >> val;
	rear = first;
	while (val != endTag){
		last->link = new CircLinkNode<T>(val);
		if (!newNode)		{
			cerr << "Memory allocating error!" << endl;
			exit(1);
		}
		last = newNode;
		cin >> val;
	}
	last->link = first;
}

template <typename T>void CircList<T>::Sort()
{
}

template <typename T>void CircList<T>::Inverse(){//逆转本链表，无须返回
	CircLinkNode<T> *h, *p, *pr;
	h = first;//逆转应不包括附加头结点，但环表例外
	p = first->link;
	last = p;
	while (p != first){
		pr = h;
		h = p;
		p = h->link;
		h->link = pr;
	}
	first->link = h;
}
#endif
