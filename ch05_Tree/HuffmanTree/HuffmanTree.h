#ifndef HAFFMANTREE_H
#define HAFFMANTREE_H
#include "MinHeap.h"
#include<iostream>
#include<string>
using namespace std;

//Huffman树结点的类定义
template <typename T, typename E>struct HuffmanNode{
	E data;
	HuffmanNode<T,E> *leftChild, *rightChild, *parent;
	HuffmanNode():leftChild(NULL), rightChild(NULL), parent(NULL){}//构造函数
	HuffmanNode(E elem, HuffmanNode<T,E> * pr,HuffmanNode<T,E> *left,HuffmanNode<T,E>*right) 
		:data(elem), parent(pr), leftChild(left), rightChild(right){}
	//重载操作符：
	bool operator > (HuffmanNode<T,E> right){
		return data>right.data;
	}
	bool operator >= (HuffmanNode<T,E> right){
		return (data>right.data) || (data==right.data);
	}
	bool operator < (HuffmanNode<T,E> right){
		return data<right.data;
	}
	bool operator <= (HuffmanNode<T,E> right){
		return (data<right.data) || (data==right.data);
	}
	bool operator == (HuffmanNode<T,E> right){
		return data==right.data;
	}
};

//Huffman树类定义
template <typename T, typename E>class HuffmanTree{
public:
	HuffmanTree(E w[], int n);
	~HuffmanTree(){
		deleteTree(root);
	}
	HuffmanNode<T,E>* getRoot(){
		return root;
	}
	void output(HuffmanNode<T,E> * t, string str, ostream &out);
protected:
	HuffmanNode<T, E> *root;
	void deleteTree(HuffmanNode<T, E> * t);
	void mergeTree(HuffmanNode<T, E> *ht1,HuffmanNode<T, E> *ht2,   
		HuffmanNode<T, E> *& parent);
};


//--------------------------------------------------------------------------------------------------
template <typename T, typename E>void HuffmanTree<T,E>::deleteTree(HuffmanNode<T,E> * t){//清除子二叉树，添加
	if (t != NULL){
		deleteTree (t->leftChild);
		deleteTree (t->rightChild);
		delete t;
	}
}

template <typename T, typename E>void HuffmanTree<T,E>::output(HuffmanNode<T,E> * t, string str, ostream &out){//按目录结构方式输出二叉树，添加
	if (!t){
		return;
	}
	out << str << t->data;
	if (t->leftChild){
		out << "─┐" << endl;
		if (t->rightChild){
			output(t->leftChild, str+"│　", out);
		}
		else{
			output(t->leftChild, str+"　　", out);
		}
	}
	if (t->rightChild){
		out << endl << str << "└─┐" << endl;
		output(t->rightChild, str+"　　", out);
	}
}

template <typename T, typename E>HuffmanTree<T,E>::HuffmanTree(E w[], int n){
	//给出n个权值w[1]～w[n], 构造Huffman树
	MinHeap<T, HuffmanNode<T,E> > hp;	//使用最小堆存放森林的结点
	HuffmanNode<T, E> *parent, *first, *second,temp;
	HuffmanNode<T, E> *NodeList/* = new HuffmanNode<T,E>[n]*/; //不宜一次性建立森林，否则析构函数一个一个删结点时操作系统断言出错
	int i;
	for (i = 0; i < n; i++){//按棵逐步建立森林中的树木，并作为Huffman树的叶结点。数据放入森林
		NodeList = new HuffmanNode<T,E>;
		NodeList->data = w[i+1];
		NodeList->leftChild = NULL;
		NodeList->rightChild = NULL;
		NodeList->parent = NodeList;//父指针指向自己，信息入堆后，出堆时可以找到对应结点
		hp.Insert(*NodeList);	//森林信息插入最小堆中
	}
	for (i = 0; i < n-1; i++){	//n-1趟, 建Huffman树	
		hp.RemoveMin(temp); 		//根权值最小的树
		first=temp.parent;			//first指向对应的最小结点
		hp.RemoveMin(temp);	        //根权值次小的树
		second=temp.parent;			//second指向对应的次小结点
		mergeTree(first, second, parent);	//合并
		hp.Insert(*parent);		//新结点插入堆中
	}
	root = parent;		//建立根结点
	cout<<"       root = "<<root->data<<endl;
	output(root,string(),cout);
}

template <typename T, typename E>void HuffmanTree<T, E>::mergeTree(HuffmanNode<T, E> *bt1, 
		HuffmanNode<T, E> *bt2, HuffmanNode<T, E> *& parent){//pasent必须为引用，它作为返回量
	parent = new HuffmanNode<T,E>;
	parent->leftChild = bt1;
	parent->rightChild = bt2;
	parent->parent=parent;//归并后的根结点的父指针指向新子树，在信息入堆后，出堆时可以找到对应子树
	parent->data = bt1->data + bt2->data;		//数据为左右子树数据之和
	bt1->parent = bt2->parent = parent;		//处理两子树根结点的父指针
	cout<<bt1->data<<" and "<<bt2->data<<" union to："<<parent->data<<endl;
}

#endif
