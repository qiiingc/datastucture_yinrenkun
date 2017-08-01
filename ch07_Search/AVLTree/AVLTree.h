#ifndef AVLTREE_H
#define AVLTREE_H
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
//#include "BST.h"
#include "SeqStack.h"

//AVL树结点的类定义  
template <typename E, typename K>struct AVLNode /*: public BSTNode<E,K>*/{
	int bf;
	E data;
	AVLNode<E,K> *left, *right;
	AVLNode(){
		left = NULL;
		right = NULL;
		bf = 0;
	}
	AVLNode(E d, AVLNode<E,K> *l = NULL, AVLNode<E,K> *r = NULL){
		data = d;
		left = l;
		right = r;
		bf = 0;
	}
};

//平衡的二叉搜索树（AVL）类定义
template <typename E, typename K>class AVLTree /*: public BST<E,K>*/{
public:
	AVLTree(){
		root = NULL;
	}
	AVLTree(K Ref){
		RefValue = Ref;
		root = NULL;
	}
	int Height()const{
		return Height(root);
	}
	bool Insert(E &e1){
		return Insert(root, e1);
	}
	bool Remove(K x, E &e1){
		return Remove(root, x, e1);
	}
	AVLNode<E,K> *Search(K x)const{
		return Search(x,root);
	}
	void PrintTree(ostream &out = cout)const{    //广义表形式输出	
		PrintTree(root, out);
	}
	void PrintData(ostream &out = cout)const{    //输出数据	
		PrintData(root, out);
	}
	friend istream& operator >> (istream& in,AVLTree<E,K>& Tree){
		E data;
		while (!in.eof()){
			assert(in >> data);
			Tree.Insert(data);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, AVLTree<E,K> &R){
		out << "The structure of the AVL tree is: \n";
		R.PrintTree(out);
		out << "\n\nInorder traversal of AVL tree: \n";	//提示：AVL树的中序遍历
		R.Traverse(R.root, out);				//以中序次序输出各结点的数据
		out << "\n\nThe datail of the tree is: \n";
		R.PrintData(out);
		return out;									//返回输出元素
	}
protected:
//	K RefValue;
	AVLNode<E,K> *root;
	int Height(AVLNode<E,K> *ptr)const; 
	bool Insert(AVLNode<E,K> *&ptr, E &e1);
	bool Remove(AVLNode<E,K> *&ptr, K x, E &e1);
	void RotateL(AVLNode<E,K> *&ptr);
	void RotateR(AVLNode<E,K> *&ptr);
	void RotateLR(AVLNode<E,K> *&ptr);
	void RotateRL(AVLNode<E,K> *&ptr);
	void Traverse(AVLNode<E,K> *ptr, ostream &out)const;
	void PrintTree(AVLNode<E,K> *ptr, ostream &out)const;
	void PrintData(AVLNode<E,K> *ptr, ostream &out)const;
	AVLNode<E,K> *Search(K x, AVLNode<E,K> *par)const;
};

template <typename E, typename K>AVLNode<E,K> *AVLTree<E,K>::Search(K x, AVLNode<E,K> *ptr)const{
	if (ptr == NULL){
		return NULL; 
	}
	AVLNode<E,K> *temp = ptr;
	while (temp){
		if (temp->data == x){
			return temp;
		}
		if (temp->data > x){
			temp = temp->left;
		}
		else{
			temp = temp->right;
		}
	}
	return NULL;
/*	if (!par)//未采用对半搜索
		return NULL;
	if (x == par->data)
		return par;
    AVLNode<E,K> *p;
	if ((p = Search(x,par->left))!=NULL)
		return p;
	else
		return Search(x,par->right);*/
}

template <typename E, typename K>int AVLTree<E,K>::Height(AVLNode<E,K> *ptr)const{
	if (!ptr){
		return 0;
	}
	int n=Height(ptr->left);
	int m=Height(ptr->right);
	return n<m ? m+1 : n+1;
}
//以下必须对应教材的图，而教材图缺了一些中间步骤，要补足才易于理解
//右子树比左子树高: 做左单旋转后新根在ptr
template <typename E, typename K>void AVLTree<E,K>::RotateL(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subL = ptr;			//保留原来的根结点
	ptr = subL->right;					//原根的右子女将成为新根
	subL->right = ptr->left;			//ptr成为新根前卸掉左子女，成为原根的右子女
	ptr->left = subL;					//左单旋，ptr成为新根，原根成为新根的右子女
	ptr->bf = subL->bf = 0;				//改写平衡度
}


//左子树比右子树高, 旋转后新根在ptr
template <typename E, typename K>void AVLTree<E,K>::RotateR(AVLNode<E,K> *& ptr){ 
	AVLNode<E,K> *subR = ptr;
	ptr = subR->left;					//原根的左子女成为新根
	subR->left = ptr->right;			//新根原右子女成为原根的左子女
	ptr->right = subR;					//原根成为新根的右子女
	ptr->bf = subR->bf = 0;				//改写平衡度
}

template <typename E, typename K>void AVLTree<E,K>::RotateLR(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subR = ptr;
	AVLNode<E,K> *subL = subR->left;
	ptr = subL->right;					//先左旋
	subL->right = ptr->left;			//ptr成为新根前卸掉左子女，成为原根的右子女
	ptr->left = subL;					//左单旋，ptr成为新根，原根成为新根的右子女
	if (ptr->bf <= 0){					//旋转前插入新结点后ptr左子树变高
		subL->bf = 0;
	}
	else{								//插入新结点后ptr右子树变高
		subL->bf = -1;
	}
	subR->left = ptr->right;
	ptr->right = subR;	
	if (ptr->bf == -1){					//旋转前插入新结点后ptr左子树变高
		subR->bf = 1;
	}
	else{								//插入新结点后ptr右子树变高
		subR->bf = 0;
	}
	ptr->bf = 0;
}

template <typename E, typename K>
void AVLTree<E,K>::RotateRL(AVLNode<E,K> *& ptr){
	AVLNode<E,K> *subL = ptr;
	AVLNode<E,K> *subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right; 
	ptr->right = subR;
	if (ptr->bf >= 0){
		subR->bf = 0;
	}
	else{
		subR->bf = 1;
	}
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf == 1){
		subL->bf = -1;
	}
	else{
		subL->bf = 0;
	}
	ptr->bf = 0;
}

//在以ptr为根的AVL树中插入新元素e1,
//如果插入成功,函数返回true,否则返回false。
template <typename E, typename K>bool AVLTree<E,K>::Insert(AVLNode<E,K> *& ptr, E &e1){
	AVLNode<E,K> *pr = NULL, *p = ptr, *q;
	int d;
	SeqStack<AVLNode<E,K>*> st;
	while (p != NULL){					//寻找插入位置	
		if (e1 == p->data) return false;//找到等于e1的结点,不插入
		pr = p;  st.Push(pr);			//否则用栈记忆查找路径
		if (e1 < p->data) p = p->left;
		else p = p->right;
	}
	p = new AVLNode<E,K>(e1);			//创建新结点,data=e1,bf=0
	assert(p);
	if (pr == NULL){						//空树,新结点成为根结点	
		ptr = p;
		return true;
	}
	if (e1 < pr->data){					//新结点插入	
		pr->left = p;
	}
	else{
		pr->right = p;
	}
	//重新平衡化
	while (st.IsEmpty() == false){
		st.Pop(pr);						//从栈中退出父结点
		if (p == pr->left){				//调整父结点的平衡因子		
			pr->bf--;
		}
		else{
			pr->bf++;
		}
		if (pr->bf == 0){				//第1种情况,|bf|=0,平衡退出		
			break;
		}
		if (pr->bf == 1 || pr->bf == -1){//第2种情况,|bf|=1		
			p = pr;
		}
		else{							//第3种情况,|bf|=2		
			d = (pr->bf < 0) ? -1 : 1;	//区别单双旋转标志
			if (p->bf == d){				//两结点平衡因子同号,单旋转			
				if (d == -1)				{
					RotateR(pr);		//右单旋转
				}
				else{
					RotateL(pr);		//左单旋转
				}
			}
			else{							//两结点平衡因子反号,双旋转
				if (d == -1){
					RotateLR(pr);		//先左后右双旋转,”<”型 
				}
				else{
					RotateRL(pr);		//先右后左双旋转,”>”型
				}
			}
			break;						//不再向上调整
		}//第三种情况结束
	}
	// 对于第二种情况需要继续从结点向根的方向回溯调整
	if (st.IsEmpty() == true){			//调整到树的根结点	
		ptr = pr;
	}
	else{								//中间重新链接	
		st.getTop(q);
		if (q->data > pr->data){		
			q->left = pr;
		}
		else{
			q->right = pr;
		}
	}
	return true;
}

//在以ptr为根的AVL树中删除关键码为x的结点。
//如果删除成功,函数返回true,同时通过参数e1返回被删结点元素；
//如果删除失败则函数返回false。 
template <typename E, typename K>bool AVLTree<E,K>::Remove(AVLNode<E,K> *& ptr, K x, E &e1){
	AVLNode<E,K> *pr = NULL, *p = ptr, *q, *ppr;
	int d, dd = 0;
	SeqStack<AVLNode<E,K>*> st;
	while (p != NULL){					//寻找删除位置	
		if (x == p->data.key){			//找到等于x的结点,停止搜索		
			break;
		}
		pr = p;  st.Push(pr);			//否则用栈记忆查找路径
		if (x < p->data.key){
			p = p->left;
		}
		else{
			p = p->right;
		}
	}

	if (p == NULL){						//未找到被删结点,删除失败	
		return false;
	}
	e1 = p->data;

	if (p->left && p->right){			//被删结点有两个子女	
		pr = p;  st.Push(pr);
		q = p->left;					//在p左子树找p的直接前驱
		while (q->right){
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->data = q->data;				//用q的值填补p
		p = q;							//被删结点转化为q
	}
	//以下包括由双子女转换后的和原来就非双子女的。
	//同时以下也包括单子女和无子女
	if (p->left){						//被删结点p最多只有一个子女q	
		q = p->left;
	}
	else{
		q = p->right;					//无子女时，q为NULL
	}
	if (pr == NULL){					//被删结点为根结点,其父结点为空
		ptr = q;
	}
	else{								//被删结点不是根结点	
		if (pr->left == p){				//链接		
			pr->left = q;
		}
		else{
			pr->right = q;
		}
		while (st.IsEmpty() == false){	//重新平衡化		
			st.Pop(pr);					//从栈中退出父结点
			if(q==NULL){				//调整父结点的平衡因子。无子女
				pr->bf=0;
			}
			else{						//单子女
				if (pr->right == q){
					pr->bf--;			//删在右边
				}
				else{
					pr->bf++;			//删在左边
				}
			}
			if (st.IsEmpty() == false){
				st.getTop(ppr);			//从栈中取出祖父结点
				dd = (ppr->left == pr) ?-1 : 1;	//旋转后与上层链接方向
			}
			else{						//栈空,旋转后不与上层链接			
				dd = 0;
			}
			if (pr->bf == 1 || pr->bf == -1){ 	//图7.20,|bf|=1			
				break;
			}
			if (pr->bf != 0){			//|bf|=2			
				if (pr->bf < 0) {d = -1;  q = pr->left;}
				else{					//用q指示较高的子树				
					d = 1;
					q = pr->right;
				}
				if (q->bf == 0){			//图7.22				
					if (d == -1){
						RotateR(pr);		//再参见图7.15
						pr->bf = 1;
						pr->right->bf = -1;	//#改
					}
					else{
						RotateL(pr);
						pr->bf = -1;
						pr->left->bf = 1;	//#改
					}
					//旋转后新根与上层链接
					if (dd == -1){
						ppr->left = pr;
					}
					else if (dd == 1){
						ppr->right = pr;
					}
					break;
				}
				if (q->bf == d){			//两结点平衡因子同号,图7.23				
					if (d == -1){		//右单旋转					
						RotateR(pr);
					}
					else{				//左单旋转					
						RotateL(pr);
					}
				}
				else{					//两结点平衡因子反号,图7.24				
					if (d == -1){		//先左后右双旋转,”<”型 					
						RotateLR(pr);
					}
					else{				//先右后左双旋转,”>”型					
						RotateRL(pr);
					}
				}
				//旋转后新根与上层链接
				if (dd == -1){
					ppr->left = pr;
				}
				else if (dd == 1){
					ppr->right = pr;
				}
			}
			q = pr;						//图7.21,|bf|=0
		}
		if (st.IsEmpty() == true){		//调整到树的根结点		
			ptr = pr;
		}
	}
	delete p;
	return true;
}


template <typename E, typename K>void AVLTree<E,K>::Traverse(AVLNode<E,K> *ptr, ostream &out)const{
	if (ptr != NULL){					//树非空	
		Traverse(ptr->left, out);		//中序遍历左子树
		out << ptr->data.key << ' ';	//输出根的数据
		Traverse(ptr->right, out);		//中序遍历右子树
	}
}

template<typename E, typename K>void AVLTree<E,K>::PrintTree(AVLNode<E,K> *ptr, ostream &out)const{
	if (!ptr){
		return;
	}
	out << ptr->data.key;
	if (ptr->left == NULL && ptr->right == NULL){
		return;
	}
	out << "(";
	PrintTree(ptr->left, out);
	out << ',';
	PrintTree(ptr->right, out);
	out << ")";
}

template<typename E, typename K>void AVLTree<E,K>::PrintData(AVLNode<E,K> *ptr, ostream &out)const{
	if (ptr){
		PrintData(ptr->left, out);
		out << ptr->data <<'\t'<< ptr->bf << endl;
		PrintData(ptr->right, out);
	}
}
#endif
