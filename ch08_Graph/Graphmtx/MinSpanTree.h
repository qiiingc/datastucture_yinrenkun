#ifndef MINSPANTREE_H
#define MINSPANTREE_H
#include <iostream>
#include <cassert>
using namespace std;

const double maxValue = 99999999.0;  	//机器可表示的、问题中不可能出现的大数
const int DefaultSize2=50;

//最小生成树边结点的类声明
template <typename T, typename E>struct MSTEdgeNode{//T为顶点类型，其实在生成树中未用
	int tail, head;					//两顶点位置
	E key;							//边上的权值,为结点关键码
	MSTEdgeNode(){					//构造函数	
		tail = -1;
		head = -1;
		key = 0;
	}		
/*	MSTEdgeNode<T,E>& operator = (const MSTEdgeNode<T,E> &x){//可以用默认
		tail=x.tail;
		head=x.head;
		key=x.key;
		return *this;
	}*/
	friend bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);//类模板的友元函数必须是函数模板
	friend bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);//所以必须在这里声明，在类外定义
	friend bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
	friend bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
};
template <typename T, typename E> bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){//只有在类外才能定义为函数模板
	return n1.key < n2.key;
}
template <typename T, typename E> bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key > n2.key;
}
template <typename T, typename E> bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key == n2.key;
}
template <typename T, typename E> bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2){
	return n1.key <= n2.key;
}

//最小生成树的类定义
template <typename T, typename E>class MinSpanTree{
protected:
	MSTEdgeNode<T,E> *edgevalue;			//用边值数组表示树
	int maxSize, n;							//数组的最大元素个数和当前个数
public:
	MinSpanTree(int sz = DefaultSize2 /*- 1*/){
		maxSize = sz;
		n = 0;
		edgevalue = new MSTEdgeNode<T,E>[sz];
		assert(edgevalue);
	}
	bool Insert(MSTEdgeNode<T,E> &item);	//将边item插入到树中，若树中节点已满，则返回false;
	void output();							//自定义函数，顺序输出所有边
};


template<class T,class E>bool MinSpanTree<T,E>::Insert(MSTEdgeNode<T,E> &item){	
	if(n == maxSize){
		return false;
	}
	edgevalue[n] = item;
	n++;
	return true;
}

template<class T,class E>void MinSpanTree<T,E>::output(){
	for(int i=1; i<=n; i++){
		cout<<"Edge "<<i<<" : "<<"head = "<<edgevalue[i-1].head<<" ; tail = "<<edgevalue[i-1].tail<<" ; key = "<<edgevalue[i-1].key<<endl;
	}
}

#endif
