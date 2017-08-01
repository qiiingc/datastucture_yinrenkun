#include "ThreadTree.h"

template <typename T>void ThreadTree<T>::createInThread(){
	ThreadNode<T> *pre = NULL;		//前驱结点指针
	if (/*!*/root){					//改
		createInThread(root, pre);	//中序遍历线索化二叉树
		pre->rightChild = NULL;		//后处理中序最后一个结点
		pre->rtag = 1;
	}
}

//通过中序遍历, 对二叉树进行线索化
template <typename T>void ThreadTree<T>::createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre){
	if (!current){
		return;
	}	
	createInThread(current->leftChild, pre); // 左子树线索化	
	if (current->leftChild == NULL){         //建立当前结点的前驱线索
	  current->leftChild = pre;
	  current->ltag = 1;
	}	
	if (pre != NULL && pre->rightChild == NULL){//建立前驱结点的后继线索
		pre->rightChild = current;
		pre->rtag = 1; 
	}
	pre = current;//前驱跟上,当前指针向前遍历	
	createInThread(current->rightChild, pre);//递归, 右子树线索化
}

template <typename T>ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T> *current){// 返回以current为根，中序遍历的第一个结点
    ThreadNode<T> *p = current;	
    while (p->ltag == 0){
		p = p->leftChild;//最左下结点（不一定是叶结点）
	}
    return p;
}

template <typename T>ThreadNode<T> * ThreadTree <T>::Next(ThreadNode<T> *current){// 返回结点current中序遍历的后继结点
    ThreadNode<T> *p = current->rightChild;
    if (current->rtag == 0){	//rtag == 0, 表示有右子女	
		return First (p);
	}
    else{	//rtag == 1, 直接返回后继线索	
		return p;
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current){// 返回以current为根，中序遍历的最后一个结点
	ThreadNode<T> *p = current;
	//最右下结点（不一定是叶结点）
	while (p->rtag == 0){
		p = p->rightChild;//最右下结点（不一定是叶结点）
	}
	return p;
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current){// 返回中序遍历的前驱结点
	//函数返回在中序线索二叉树中结点current在中序下的前驱结点。
	ThreadNode<T> *p = current->leftChild;
	if (current->ltag == 0){	//在左子树中找中序最后一个结点	
		return Last(p);
	}
	else{ //ltag==1, 直接返回前驱线索	
		return p;
	}
}
template<typename T>bool ThreadTree<T>::FindTh(const T &value){//线索二叉树中使用
	ThreadNode<T> *p;
    for (p = First(root); p != NULL; p = Next(p)){
		if(p->data==value){
			current=p;
			return true;
		}
	}
	return false;
}

template <typename T>void ThreadTree <T>::InOrder(void (*visit)(ThreadNode<T> *t)){//中序遍历
    ThreadNode<T> *p;
    for (p = First(root); p != NULL; p = Next(p)){
		visit (p);
	}
}

template <typename T>void ThreadTree<T>::PreOrder(void (*visit)(ThreadNode<T> *t)){// 前序遍历
	ThreadNode<T> *p = root;
	while (p){
		visit(p);				//访问根结点
		if (p->ltag == 0){		//有左子女,即为后继		
			p = p->leftChild;
		}
		else if (p->rtag == 0){	//有右子女,即为后继		
			p = p->rightChild;
		}
		else{
			while (p != NULL && p->rtag == 1){	//沿后继线索检测,直到有右子女的结点			
				p = p->rightChild;
			}
			if (p != NULL){	//右子女即为后继			
				p = p->rightChild;
			}
		}
	}
}

template <typename T>void ThreadTree<T>::PostOrder(void (*visit)(ThreadNode<T> *p)){
	ThreadNode<T> *t = root;
	//寻找后序第一个结点
	while (t->ltag == 0 || t->rtag == 0){
		if (t->ltag == 0){
			t = t->leftChild;
		}
		else if (t->rtag == 0){
			t = t->rightChild;
		}
	}
	visit(t);	//访问第一个结点
	ThreadNode<T> *p;
	while ((p = parent(t)) != NULL)	{
		if (p->rightChild == t || p->rtag == 1){	//*t是*p的后序后继		
			t = p;
		}
		else{	//否则，t移到*p的右子树		
			t = p->rightChild;
			while (t->ltag == 0 || t->rtag == 0){	
				if (t->ltag == 0){
					t = t->leftChild;
				}
				else if (t->rtag == 0){
					t = t->rightChild;
				}
			}
		}
		visit(t);
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::parent(ThreadNode<T> *t){
	ThreadNode<T> *p;
	if (t == root){
		return NULL;
	}
	for (p = t; p->ltag == 0; p = p->leftChild);//求*t为根子树第一个结点，其前驱是*t的祖先
	if (p->leftChild != NULL){//左指针是前驱，仅该结点是全树(t为root)中序第一结点才无前驱
		p=p->leftChild;//找到祖先
		if(p->rightChild != t/*&&p->leftChild != t*/)//如果不是父结点
			for(p = p->rightChild; //向右一步
			/*rightChild != t&&*/p->leftChild != t;//测t是否p的子女，并且一定会找到
			p = p->leftChild);//向左走到底
	}
	else{//该结点是全树(t为root)中序第一结点，无前驱，必须换一个方向，去右边找后继
		for (p = t; p->rtag == 0; p = p->rightChild);//求*t为根子树最后一个结点
		p=p->rightChild;//找到祖先
		if(p->leftChild != t/*&&p->rightChild != t*/)
		for (p = p->leftChild;//向左一步
			 /*p->leftChild != t&&*/p->rightChild != t;
			p = p->rightChild);//向右走到底,总能找到
	}
	return p;
}
