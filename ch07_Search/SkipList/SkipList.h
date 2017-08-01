#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <iostream>
#include <cassert>
using namespace std;
const int DefaultSize = 100;

//跳表结点类定义
template <typename E, typename K>struct SkipNode{
	E data;								//数据域
	SkipNode<E,K> **link;				//指针数组域
	SkipNode(int size = DefaultSize){
		link = new SkipNode<E,K> *[size];
		assert(link);
	}
	~SkipNode(){
		delete []link;
	}
};

//跳表类定义
template <typename E, typename K>class SkipList{
public:
	SkipList(K large, int maxLev = DefaultSize);//构造函数
	~SkipList();								//析构函数
	bool Search(const K k1, E &e1)const;		//搜索函数
	E& getData(SkipNode<E,K> *current){
		return current?(&current->data):NULL;
	}
	bool Insert(const K k1, E &e1);		//插入函数
	bool Remove(const K k1, E &e1);	    //删除函数
	bool DelMin(E &e1);
	bool DelMax(E &e1);
	SkipNode<E,K>* Begin(){
		return (head->link[0] == tail)?NULL:head->link[0];
	}
	SkipNode<E,K>* Next(SkipNode<E,K> *p){
		return (p == NULL || p == tail || p->link[0] == tail)?NULL:p->link[0];
	}
	friend istream& operator >> (istream &in, SkipList<E,K> &R){
		while (!in.eof()){
			E elem;
			assert(in >> elem);
			R.Insert(elem.key, elem);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, SkipList<E,K> &R){
		SkipNode<E,K> *p = R.head->link[0];
		if (p == R.tail){
			out << "The skip list is empty!\n";
		}
		while (p != R.tail){
			out << p->data << endl;
			p = p->link[0];
		}
		return out;
	}						//输出各链的值
private:
	int maxLevel;						//所允许的最大级数
	int Levels;							//当前非空链的级数
	K TailKey;							//在TailKey中存有一个大值
	SkipNode<E,K> *head;				//附加头结点
	SkipNode<E,K> *tail;				//附加尾结点
	SkipNode<E,K> **last;				//指针数组
	int Level();
	SkipNode<E,K> *SaveSearch(const K k1);
};

//构造函数：建立空的多级链
template <typename E, typename K>SkipList<E,K>::SkipList(K large, int maxLev){
	maxLevel = maxLev;	//最大级链数目
	TailKey = large;	//控制扫描的最大关键码
	Levels = 0;
	head = new SkipNode<E,K>(maxLevel+1);	//附加头结点,有maxLevel+1指针
	tail = new SkipNode<E,K>(0);			//附加尾结点,有0个指针
	last = new SkipNode<E,K> *[maxLevel+1];	//跳表的辅助多级链指针
	tail->data = large;
	for (int i = 0; i <= maxLevel; i++){
		head->link[i] = tail;
	}
}


//析构函数：释放链表所有元素结点
template <typename E, typename K>SkipList<E,K>::~SkipList(){
	SkipNode<E,K> *next;
	while (head != tail){
		next = head->link[0];	//第0级链包含所有函数
		delete head;
		head = next;
	}
	delete tail;
	delete []last;
}

//搜索算法
template <typename E, typename K>bool SkipList<E,K>::Search(const K k1, E& e1)const{
	if (k1 > TailKey){
		return false;
	}
	SkipNode<E,K> *p = head;
	for (int i = Levels; i >= 0; i--){ //逐级向下搜索	
		while (p->link[i]->data < k1){ //重载：元素关键码判小于
			p = p->link[i];
		}
	}
	e1 = p->link[0]->data;	// p处于要找的元素的左边!
	return e1 == k1; //重载：元素关键码判等于
}


template <typename E, typename K>SkipNode<E,K> *SkipList<E,K>::SaveSearch(const K k1){
	if (k1 > TailKey)	{
		return NULL;
	}
	SkipNode<E,K> *p = head;
	for (int i = Levels; i >= 0; i--){ //逐级向下搜索	
		while (p->link[i]->data < k1) //重载：元素关键码判小于
		p = p->link[i];
		last[i] = p;	//记下每一级的最后比较结点, p处于要找的元素的左边!
	}
	return p->link[0];	//返回找到的结点地址
}


//产生一个随机的级别，该级别 < maxLevel
template <typename E, typename K>int SkipList<E,K>::Level(){
	int lev = 0;
	while (rand() <= RAND_MAX/2){//不理想的方法，但0级概率为0.5,1级0.25,2级0.125等等
		lev++;
	}
	return (lev < maxLevel)?lev:maxLevel;
}

//插入算法
template <typename E, typename K>bool SkipList<E,K>::Insert(const K k1, E& e1){
	if (k1 >= TailKey){
		return false;
	}
	SkipNode<E,K> *p = SaveSearch(k1); //检查是否重复，并设置Last的值
	if (p->data == k1){ //重载：元素间判等于	
		return false;
	}
	int lev = Level(); //随机产生一个级别
	if (lev > Levels){ //调整级别	
		lev = ++Levels;
		last[lev] = head;
	}
	SkipNode<E,K> *newNode = new SkipNode<E,K>(lev+1);
	newNode->data = e1;  //重载：元素赋值
	for (int i = 0; i <= lev; i++){	//各级链入	
		newNode->link[i] = last[i]->link[i]; //第i级链入
		last[i]->link[i] = newNode;
	}
	return true;
}


template <typename E, typename K>bool SkipList<E,K>::Remove(const K k1, E &e1){
	if (k1 > TailKey){ //关键码太大	
		return false;
	}
	SkipNode<E,K> *p = SaveSearch(k1); //搜索与k1匹配的元素->pF
	if (p->data != k1){ //重载：元素关键码判不等	
		return false;
	}
	for (int i = 0; i <= Levels && last[i]->link[i] == p; i++){
		last[i]->link[i] = p->link[i]; //逐级链摘下该结点
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //修改级数
	}
	e1 = p->data;
	delete p;
	return true;
}

template <typename E, typename K>bool SkipList<E,K>::DelMin(E &e1){
	SkipNode<E,K> *p = head->link[0];
	if (p == tail){
		return false;
	}
	for (int i = 0; i <= Levels && head->link[i] == p; i++){
		head->link[i] = p->link[i]; //逐级链摘下该结点
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //修改级数
	}
	e1 = p->data;
	delete p;
	return true;
}

template <typename E, typename K>bool SkipList<E,K>::DelMax(E &e1){
	int i;
	if (head->link[0] == tail){
		return false;
	}
	SkipNode<E,K> *p = head;
	for (i = Levels; i >=0; i--){
		if (p->link[0] == tail){ //当i=Levels时,该条件肯定不成立		
			last[i] = last[i+1];//故该语句不会溢出
			while (last[i]->link[i] != p){
				last[i] = last[i]->link[i];
			}
		}
		else{
			while (p->link[i]->data < TailKey){
				last[i] = p;
				p = p->link[i];
			}
		}
	}
	for (i = 0; i <= Levels && last[i]->link[i] == p; i++){
		last[i]->link[i] = tail; //逐级链摘下该结点
	}
	while (Levels > 0 && head->link[Levels] == tail){
		Levels--; //修改级数
	}
	e1 = p->data;
	delete p;
	return true;
}
#endif
