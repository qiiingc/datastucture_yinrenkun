#ifndef BINARY_TREE
#define BINARY_TREE

#include <string>
#include <cassert>
#include <iostream>
using namespace std;
#include"LinkedStack.h"
#include"LinkedQueue.h"

template <typename T>struct BinTreeNode{
	T data;
	BinTreeNode<T> *leftChild;
	BinTreeNode<T> *rightChild;

	BinTreeNode():leftChild(NULL), rightChild(NULL){}
	BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
		:leftChild(l), rightChild(r){
		data = x;
	}
};

template <typename T>class BinaryTree{
public:
	BinaryTree():root(NULL){}
	BinaryTree(T value):root(NULL){
		RefValue = value;
	}
	BinaryTree(BinaryTree<T> &s){
		if (this != &s){
			root=Copy(s.root);
		}
	}
	~BinaryTree(){
		destroy(root);
	}
	bool IsEmpty(){
		return root == NULL;
	}
	bool Find(T &x){
		return Find(root,x);
	}
	int Height(){
		return Height(root);
	}
	int Size(){
		return Size(root);
	}
	BinTreeNode<T> *Parent(BinTreeNode <T> *t){
		return (root == NULL || root ==  t)?NULL:Parent(root, t);
	}
	BinTreeNode<T> *LeftChild(BinTreeNode<T> *t){
		return (t != NULL)?t->leftChild:NULL;
	}
	BinTreeNode<T> *RightChild(BinTreeNode<T> *t){
		return (t != NULL)?t->rightChild:NULL;
	}
	BinTreeNode<T> *getRoot()const{
		return root;
	}
	void PreOrder(void (*visit)(BinTreeNode<T> *t)){
		PreOrder(root, visit);
	}
	void InOrder(void (*visit)(BinTreeNode<T> *t)){
		InOrder (root, visit);
	}
	void PostOrder(void (*visit)(BinTreeNode<T> *t)){
		PostOrder(root, visit);
	}	
	bool Insert(T item){
		return Insert(root, item);
	}
	//for E524
	void CreateCompBinTree(T *CBT, int num){//建立完全二叉树
		CreateCompBinTree(CBT, num, 0, root);
	}
	//for E530
	void printBinTree(ostream &out = cout){//按广义表打印
		printBinTree(root, out);
	}	
	void Output(ostream &out = cout){//按缩格文本输出
		out << "The structure of the binary tree is:\n";
		Output(root, string(" "), out);
		out << endl;
	}
	void levelOrder(void (*visit)(BinTreeNode<T> *t));//层次序遍历
	void PreOrder1(void (*visit) (BinTreeNode<T> *t));//非递归前序遍历
	void InOrder1(void (*visit) (BinTreeNode<T> *t));//非递归中序遍历
	void PostOrder1(void (*visit) (BinTreeNode<T> *t));//非递归后序遍历
	friend istream& operator >> (istream &in, BinaryTree<T> &Tree){//输入二叉树
		Tree.CreateBinTree(in, Tree.root);
		return in;
	}
	// show bintree in the form of genlist
	friend ostream& operator << (ostream& out, BinaryTree<T>& Tree){//按广义表输出
		Tree.printBinTree(out);
		out << endl;
		return out;
	}
protected:
	BinTreeNode<T> *root;		//二叉树的根指针
	T RefValue;					//数据输入停止标志
	void CreateBinTree(istream &in, BinTreeNode<T> *& subTree);//递归建立二叉树
	void CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *& subTree);//建立完全二叉树
	void printBinTree(BinTreeNode<T> *subTree, ostream &out);//按广义表打印
	void Output(BinTreeNode<T> *subTree, string str, ostream &out);//按目录结构方式输出二叉树
	bool Insert(BinTreeNode<T> *& subTree, T &x);//在结点的某子树插入数据为x的结点
	void destroy(BinTreeNode<T> *& subTree) ;//清除子二叉树
	bool Find(BinTreeNode<T> *subTree, T &x)const;//在子树中寻找数据为x的结点
	BinTreeNode<T> *Copy(BinTreeNode<T> *r);//复制二叉树r
	int Height(BinTreeNode<T> *subTree)const ;//树高
	int Size(BinTreeNode<T> *subTree)const;//树的节点数
	BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *t) ;//在子树中找父结点
	void Traverse(BinTreeNode<T> *subTree, ostream &out);//遍历输出
	void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));//前序遍历
	void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));//中序遍历
	void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t));//后序遍历
};

template <typename T>void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *& subTree){//私有函数: 以递归方式建立二叉树。
	T item;
	if (in >> item){
		if (item != RefValue){
			subTree = new BinTreeNode<T>(item);		//Create Root
			assert(subTree);
			CreateBinTree(in, subTree->leftChild);	// Create left child tree
			CreateBinTree(in, subTree->rightChild);	// Create reght child tree
		}
		else
		{
			subTree = NULL;
		}
	}
}
// rt is the root of the subTree
template<typename T>void BinaryTree<T>::CreateCompBinTree(T *CBT, int num, int rt, BinTreeNode<T> *& subTree){//建立完全二叉树
	if (rt >= num)	{
		subTree = NULL;
	}
	else{
		subTree = new BinTreeNode<T>(CBT[rt]);
		if (subTree == NULL){
			cerr << "Memory Allocating error!" << endl;
			exit(1);
		}
		CreateCompBinTree(CBT, num, 2*rt+1, subTree->leftChild);
		CreateCompBinTree(CBT, num, 2*rt+2, subTree->rightChild);
	}
}
//E530
// print the binary tree in the form of genlist.
template <typename T>void BinaryTree<T>::printBinTree(BinTreeNode<T> *subTree, ostream &out){//按广义表打印
	if (subTree){
		out << subTree->data;
		if (subTree->leftChild || subTree->rightChild){
			out << "(";
			printBinTree(subTree->leftChild, out);
			if (subTree->rightChild){
				out << ",";
			}
			printBinTree(subTree->rightChild, out);
			out << ")";
		}
	}
}

// print the structure of the binary tree.
template <typename T>void BinaryTree<T>::Output(BinTreeNode<T> *subTree, string str, ostream &out){//按目录结构方式输出二叉树
	if (!subTree)	{
		return;
	}
	out << str << subTree->data;
	if (subTree->leftChild){
		out << "─┐" << endl;
		if (subTree->rightChild){
			Output(subTree->leftChild, str+"│　", out);
		}
		else{
			Output(subTree->leftChild, str+"　　", out);
		}
	}
	if (subTree->rightChild){
		out << endl << str << "└─┐" << endl;
		Output(subTree->rightChild, str+"　　", out);
	}
}

template<typename T>bool BinaryTree<T>::Insert(BinTreeNode<T> *& subTree, T& x){//在结点的某子树插入数据为x的结点
	if (!subTree){
		subTree=new BinTreeNode<T>(x);
		assert(subTree);
		return true;
	}
	else{
		return Insert(subTree->leftChild, x) || Insert(subTree->rightChild, x);//如果左子树插入成功，不会再去右子树
	}
}

template<typename T>bool BinaryTree<T>::Find(BinTreeNode<T> *subTree, T &x)const{//在子树中寻找数据为x的结点
	if (!subTree){
		return false;
	}
	if (subTree->data==x){
		return true;
	}
	bool p=false;
	p = Find(subTree->leftChild,x); 
	if (p)	{
		return true;
	}
	else{
		return Find(subTree->rightChild, x);
	}
}

template<typename T>BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *r){ //递归复制二叉树
	 if (!r){
		 return NULL;
	 }
	 BinTreeNode<T> *p=new BinTreeNode<T>(r->data);
	 p->leftChild = Copy(r->leftChild);
	 p->rightChild = Copy(r->rightChild);
	 return p;
}

template <typename T>void BinaryTree<T>::destroy(BinTreeNode<T> *& subTree){//清除子二叉树
	if (subTree != NULL)	{
		destroy (subTree->leftChild);
		destroy (subTree->rightChild);
		delete subTree;
	}
}

template <typename T>int BinaryTree<T>::Height(BinTreeNode<T> *subTree)const{//树高
	if (subTree == NULL){
		return 0;
	}
	else{
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i < j)?j+1:i+1;
	}
}

template <typename T>int BinaryTree<T>::Size(BinTreeNode<T> *subTree)const{//树的节点数
	if (subTree == NULL)	{
		return 0;
	}
	else{
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
	}
}


template <typename T> BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *t){//在子树中找父结点
	if (subTree == NULL){
		return NULL;
	}
	if (subTree->leftChild == t || subTree->rightChild == t ){
		return subTree;
	}
	BinTreeNode <T> *p;
	if ((p = Parent(subTree->leftChild, t)) != NULL){
		return p;
	}
	else{
		return Parent(subTree->rightChild, t);
	}
}

template <typename T>void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out){//前序遍历输出结点数据
	if (subTree){
		out << subTree->data << ' ';
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
}

template <typename T>void BinaryTree<T>::PreOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL){
		visit(subTree);
		PreOrder(subTree->leftChild, visit);
		PreOrder(subTree->rightChild, visit);
	}
}

template <typename T>void BinaryTree<T>::InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL){
		InOrder(subTree->leftChild, visit); 
		visit(subTree);
		InOrder(subTree->rightChild, visit);
	}
}

template <typename T>void BinaryTree<T>::PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *t)){
	if (subTree != NULL ){
		PostOrder(subTree->leftChild, visit);	
		PostOrder(subTree->rightChild, visit);
		visit (subTree);
	}
}

template <typename T>void BinaryTree<T>::PreOrder1(void (*visit) (BinTreeNode<T> *t) ) {//非递归前序遍历
     LinkedStack<BinTreeNode<T>*> S;
     BinTreeNode<T> *p = root; 
     S.Push (NULL);
	 while (p != NULL) {
          	visit(p);			   //访问结点
 	      if (p->rightChild != NULL)
               S.Push (p->rightChild);  //预留右指针在栈中
		  if (p->leftChild != NULL) 
               p = p->leftChild;	//进左子树
 	      else S.Pop(p);		//左子树为空，由堆栈弹出
     }
}

template <typename T> void BinaryTree<T>::InOrder1(void (*visit) (BinTreeNode<T> *t)) {//非递归中序遍历
     LinkedStack<BinTreeNode<T>*> S;  
	 BinTreeNode<T> *p = root; 
     do {
          while (p != NULL) {	//遍历指针向左下移动
               S.Push (p); 		//该子树沿途结点进栈
               p = p->leftChild;
          }
          if (!S.IsEmpty()) {		//栈不空时退栈
               S.Pop (p);  visit (p);	//退栈, 访问
               p = p->rightChild;	//遍历指针进到右子女
          }
     } while (p != NULL || !S.IsEmpty ());
}

template <typename T>struct stkNode {
	BinTreeNode<T> *ptr;      //树结点指针	        
	enum{L, R}tag;               //退栈标记，必须说明为枚举变量，tag移到最右边。这里最好用bool量
	stkNode (BinTreeNode<T> *N = NULL){
		ptr=N;
		tag=L;
	}	           //构造函数
};

template <typename T>void BinaryTree<T>::PostOrder1(void (*visit) (BinTreeNode<T> *t)){//非递归后序遍历
     LinkedStack<stkNode<T> > S;
	 stkNode<T> w; 
     BinTreeNode<T> * p = root;     //p是遍历指针
	 do {
		while (p != NULL) {	
		     w.ptr = p;
			 w.tag = stkNode<T>::L;//枚举类型定义在struct stkNode中，如定义为全局性就简单了
			 S.Push (w);   
		     p = p->leftChild;					}
	 	int continue1 = 1;	    //继续循环标记, 用于R
		while (continue1 && !S.IsEmpty ()) {
		     S.Pop (w);  p = w.ptr;
		     switch (w.tag) {   	//判断栈顶的tag标记
			 case stkNode<T>::L:  w.tag = stkNode<T>::R;
				 S.Push (w);
				 continue1 = 0;
				 p = p->rightChild;  break;
			 case stkNode<T>::R:  visit (p);   break;
			 }
	 	}
     } while (!S.IsEmpty ());	//继续遍历其他结点
     cout << endl;
}

template <typename T>void BinaryTree<T>::levelOrder (void (*visit) (BinTreeNode<T> *t)) {//层次序遍历
     if (root == NULL) return;
     LinkedQueue<BinTreeNode<T> * > Q;
     BinTreeNode<T> *p = root;   
     visit (p);   Q.EnQueue (p); 	
     while (!Q.IsEmpty ()) {
          Q.DeQueue (p);
          if (p->leftChild != NULL) {
			  visit (p->leftChild);
			  Q.EnQueue (p->leftChild);
          }
          if (p->rightChild != NULL) {
			  visit (p->rightChild);
			  Q.EnQueue (p->rightChild);
          }
     }
}

#endif
