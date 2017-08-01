#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include "SeqQueue.h"
using namespace std;

template <typename T>struct TreeNode{
	T data;
	TreeNode<T> *firstChild, *nextSibling;
	TreeNode(T value = 0, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
		:firstChild(fc), nextSibling(ns){
		data = value;
	}
};

template <typename T>class Tree{
public:
	Tree(){
		root = current = NULL;
	}
	Tree(T value){
		root = current = NULL;
		RefValue = value;
	}
	bool Root(); 			//置根结点为当前结点
	TreeNode<T> *getRoot(){
		return root;
	}
	void setRoot(TreeNode<T> *rt){
		root = rt;
	}
	bool IsEmpty(){
		return root == NULL;
	}
	bool FirstChild();		//将当前结点的第一个子女置为当前结点
	bool NextSibling();		//将当前结点的下一个兄弟置为当前结点
	bool Parent();			//将当前结点的双亲置为当前结点
	bool Find(T value);		//搜索含value的结点, 使之成为当前结点

	void PreOrder(void (*visit)(TreeNode<T> *t)){//前序
		TreeNode<T> *p = root;
		while (p){
			PreOrder(p, visit);
			p = p->nextSibling;
		}
	}
	void PostOrder(void (*visit)(TreeNode<T> *t)){//后序
		TreeNode<T> *p = root;
		while (p){
			PostOrder(p, visit);
			p = p->nextSibling;
		}
	}
	void LevelOrder(void (*visit)(TreeNode<T> *t)){//层次
		LevelOrder(root, visit);
	}

	//以先根次序输入树;以RefValue表示某节点没有子女或不再有兄弟
	void CreateTree(istream &in = cin){
		CreateTree(in, root);
	}
	void Output(ostream &out = cout){		//树状格式输出	
		Output(root, string(), out);
	}
	void IntendedText(ostream &out = cout){	//将树用缩格文本形式输出	
		IntendedText(root, string(), out);//string()是构造函数
	}
	void ShowTree(ostream &out = cout){
		ShowTree(root, out);
	}
	void reSetCurrent(){		//将current重新指向根节点	
		current = root;
	}
	friend istream& operator >> (istream &in, Tree<T> &tree); //tree不可误作Tree
	friend ostream& operator << (ostream &out, Tree<T> &tree);//因为类模板的友元函数是函数模板，必须在此声明，在类外定义
private:
	TreeNode<T> *root, *current;
	bool Find(TreeNode<T> *p, T value);		//在以p为根的树中搜索value
	void RemovesubTree(TreeNode<T> *p);		//删除以p为根的子树
	bool FindParent(TreeNode<T> *t, TreeNode<T> *p);
	void PreOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void PostOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void LevelOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t));
	void Output(TreeNode<T> *subTree, string str, ostream &out);
	void IntendedText(TreeNode<T> *subTree, string str, ostream &out);
	void ShowTree(TreeNode<T> *t, ostream &out);
	void CreateTree(istream& in, TreeNode<T> *& subTree);//以先根次序输入树;以RefValue表示某节点没有子女或不再有兄弟
	T RefValue;					//数据输入停止标志
};

template <typename T>  istream& operator >> (istream &in, Tree<T> &tree){
	tree.CreateTree(in,tree.root);
	return in;
}

template <typename T>  ostream& operator << (ostream &out, Tree<T> &tree){
	tree.IntendedText(out);
	return out;
}

template <typename T> bool Tree<T>::Root(){		//让树的根结点成为树的当前结点
	if (root == NULL){
		current = NULL;
		return false;
	}
	else{
		current = root;
		return true;
	}
}

template <typename T>bool Tree<T>::Parent(){		//置当前结点的双亲结点为当前结点
	TreeNode<T> *p = current;
	if (current == NULL || current == root){	// 空树或根无双亲
		current = NULL;
		return false;
	}
	return FindParent (root, p);	//从根开始找*p的双亲结点
}

template <typename T>bool Tree<T>::FindParent(TreeNode<T> *t, TreeNode<T> *p){	//在根为*t的树中找*p的双亲, 并置为当前结点
	TreeNode<T> *q = t->firstChild;     //*q是*t长子
	while (q != NULL && q != p){	//扫描兄弟链
		if (FindParent(q, p)){
		   return true;
		}
		q = q->nextSibling;
	}
	if (q != NULL && q == p){
		current = t;
		return true;
	}
	else{
		current = NULL;
		return false;
	}
}

template <typename T>bool Tree<T>::FirstChild(){	//在树中找当前结点的长子, 并置为当前结点
	if (current && current->firstChild){
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return f!lse;
}

template <typename T> bool Tree<T>::NextSibling(){	//在树中找当前结点的兄弟, 并置为当前结点
	if (current && current->nextSibling){
	  current = current->nextSibling;
	  return true;
	}
	current = NULL;
	return false;
}

template <typename T> void Tree<T>::PreOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){
	if (subTree){
		visit(subTree);
		subTree = subTree->firstChild; 
		while (subTree){
			PreOrder(subTree, visit);
			subTree = subTree->nextSibling;
		}
	}
}

template <typename T>void Tree<T>::PostOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){
	if (subTree){
		TreeNode<T> *p = subTree;
		p = p->firstChild; 
		while (p){
			PostOrder(p, visit);
			p = p->nextSibling;
		}
		visit(subTree);
	}
}

template <typename T>void Tree<T>::LevelOrder(TreeNode<T> *subTree, void (*visit)(TreeNode<T> *t)){	//按广度优先次序分层遍历树, 树的根结点是当前指针current。
	SeqQueue<TreeNode<T>*> Q;
	if (subTree){
		while (subTree){
			Q.EnQueue(subTree);
			subTree = subTree->nextSibling;
		}
		while (!Q.IsEmpty()){
			Q.DeQueue(subTree);
			visit(subTree);
			subTree = subTree->firstChild;
			while (subTree){
				Q.EnQueue(subTree);
				subTree = subTree->nextSibling;
			}
		}
	}
}

template <typename T>bool Tree<T>::Find(T value){
	if (IsEmpty()){
		return false;
	}
	return Find(root, value);
}

template <typename T>bool Tree<T>::Find(TreeNode <T> *p, T value){
	bool result = false;
	if (p->data == value){
		result = true;
		current = p;
	}
	else{
		TreeNode<T> *q = p->firstChild;
		while (q != NULL && !(result = Find(q, value))){
			q = q->nextSibling;
		}
	}
	return result;
}

template<typename T>void Tree<T>::RemovesubTree(TreeNode<T> *p){	//私有函数: 若指针subTree不为空, 则删除根为subTree的子树
	if (subTree){
		RemovesubTree(subTree->firstChild); 
 	    RemovesubTree(subTree->nextSibling);
 	    delete subTree;
	}
}

template <typename T>void Tree<T>::IntendedText(TreeNode<T> *subTree, string str, ostream &out){
	TreeNode<T> *p = subTree;
	while (p){//深度优先
		cout << str << p->data << endl;
		string temp = str + string("\t");//注意表达式最后一项构造无名标准串
		if (p->firstChild){
			IntendedText(p->firstChild, temp, out);//深度递归
		}
		p = p->nextSibling;//广度循环
	}
}

template <typename T>void Tree<T>::Output(TreeNode<T> *subTree, string str, ostream &out){
	if (subTree == root){
		current = root;
	}
	string temp;
	TreeNode<T> *p = subTree;
	while (p){//深度优先
		out << str << p->data << endl;//str开始是空串
		if (p == current && p->firstChild){
//			str = str + "└──";
//			temp = str;
			temp= str + "└──";
		}
		else if (p == current && p->nextSibling){
				current = current->nextSibling;
			}
			else if (p->firstChild && p->firstChild->nextSibling){
				temp = string("│　　") + str;
				}
				else{
					temp = string("　　　") + str;
				}
		Output(p->firstChild, temp, out);//深度递归
		p = p->nextSibling;//广度循环
	}
}

template <typename T>void Tree<T>::ShowTree(TreeNode<T> *t, ostream &out){
	if (!t){
		return;
	}
	out << '(';
	out << t->data;
	for (TreeNode<T> *p = t->firstChild; p; p = p->nextSibling){
		ShowTree(p, out);
	}
	out << ')';
}

template <typename T>void Tree<T>::CreateTree(istream& in, TreeNode<T> *& subTree){
	T item;
	if (in >> item){                                //流正常执行以下程序
		if (item != RefValue){
			subTree = new TreeNode<T>(item);		//Create Root
			assert(subTree);
			CreateTree(in, subTree->firstChild);	// Create first child tree
			CreateTree(in, subTree->nextSibling);	// Create nextSibling tree
		}
		else{
			subTree = NULL;
		}
	}
}

#endif
