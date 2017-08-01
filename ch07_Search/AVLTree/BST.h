//原提供程序用两个模板参数，E代表data，K代表data.key，这样E类型受限，必须有一个key数据成员。
//实际只需E，并将E的比较重载为其关键字的比较，如需要则进一步对关键字进行重载。为与教材一致，未修改
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

class element{
public:
	string key;
	element(string st=""){
		key=st;
	}
	bool operator<(element el){//增加
		return key<el.key;
	}
	bool operator>(element el){//增加
		return key>el.key;
	}
	friend ostream& operator << (ostream &out, element &el){
	out << el.key;
	return out;
	}
};
template <typename E, typename K>struct BSTNode{
	E data;
	BSTNode<E,K> *left, *right;
	BSTNode(){
		left = NULL;
		right = NULL;
	}
	BSTNode(E &d, BSTNode<E,K> *L = NULL, BSTNode<E,K> *R = NULL){
		data = d;
		left = L;
		right = R;
	}
	~BSTNode(){}
	void setData(const E &d){
		data = d;
	}
	E getData(){
		return data;
	}
	bool operator < (const E &x){
		return data < x;
	}  
	bool operator > (const E &x){
		return data > x;
	}
	bool operator == (const E &x){
		return data == x;
	}
	bool operator <= (const E &x){
		return data <= x;
	}  
	bool operator >= (const E &x){
		return data >= x;
	}
	bool operator != (const E &x){
		return data != x;
	}
};

//二叉搜索树类定义
template <typename E, typename K>class BST{
public:
	BST(){
		root = NULL;
	}
	BST(K value);
//	BST(BSTNode<E,K> * temp):root(temp){}	//做了一个浅复制
	BST(BST & bst){
		if (this != & bst){					//非自我复制
			root=Copy(bst.root);	//复制树
		}
	}
	~BST(){
		makeEmpty();
	}
	BSTNode<E,K>* getRoot(){
		return root;
	}
	BSTNode<E,K> *getLeft(){
		return left;
	}
	BSTNode<E,K> *getRight(){
		return right;
	}
	void OpticBST(int p[], int q[], E a[], int n);
	BSTNode<E,K>* Search(const K x){
		return Search(x,root);
	}
	void CreatOpt(BSTNode<E, K> *&prt,int** &R,E a[],int i,int j);	//参数必须是引用，否则树链不起来
	BST<E,K>& operator = (/*const*/ BST<E,K> &R);
	void makeEmpty(){
		makeEmpty (root); root = NULL;
	}
	bool isEmpty(){
		return root == NULL;
	}
	void PrintTree(ostream &out = cout)const {   //广义表形式输出	
		PrintTree(root, out);
	}
	void PrintData(ostream &out = cout)const{    //输出数据
		PrintData(root, out);
	}
	bool DelMax();
	bool DelMin();
	E Min(){
		return Min(root)->data;
	}
	E Max(){
		return Max(root)->data;
	}
	bool Insert(E &e1){
		return Insert(e1, root);
	}
	bool Remove(K x){
		return Remove(x, root);
	}
	friend istream& operator >> (istream &in, BST<E,K> &R){
		while (!in.eof()){
			E elem;
			assert(in >> elem);
			R.Insert(elem);
		}
		return in;
	}
	friend ostream& operator << (ostream &out, BST<E,K> &R){
		out << "The structure of the Binary Search tree is: \n";
		R.PrintTree(out);
		out << "\n\nThe data printed by inorder in the tree is: \n";
		R.PrintData(out);
		out << endl;
		return out;
	}
protected:
	BSTNode<E, K> *root;
	K RefValue;		//输入停止标志
	BSTNode<E, K>* Search(K x, BSTNode<E,K> *ptr);	//递归：搜索
	void makeEmpty(BSTNode<E,K> *&ptr);				//递归：置空
	void PrintTree(BSTNode<E,K> *ptr, ostream &out)const;	//递归：打印搜索树结构
	void PrintData(BSTNode<E,K> *ptr, ostream &out)const;	//递归：打印各结点数据
	BSTNode<E,K>* Copy(/*const*/ BSTNode<E,K> *& ptr);	//递归：复制
	BSTNode<E,K>* Min(BSTNode<E,K> *ptr);			//递归：求最小
	BSTNode<E,K>* Max(BSTNode<E,K> *ptr);			//递归：求最大
	bool Insert(E &e1, BSTNode<E,K> *&ptr);	//递归：插入
	bool Remove(K x, BSTNode<E,K> *&ptr);			//递归：删除
};

//私有函数：在当前以ptr为根的二叉搜索树中搜索含x的结点。
//若找到，则函数返回该结点的地址，否则函数返回NULL值。
template <typename E, typename K>BSTNode<E,K>* BST<E,K>::Search(K x, BSTNode<E,K> *ptr){
	if (ptr == NULL){
		return NULL; 
	}
	BSTNode<E,K> *temp = ptr;
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
}

//私有函数：在以ptr为根的二叉搜索树中插入值为e1的结点。
//若在树中已有含e1的结点则不插入，返回false；若成功插入，返回true.
template <typename E, typename K>bool BST<E,K>::Insert(E &e1, BSTNode<E,K> *&ptr){	  
	if (ptr == NULL){   //新结点作为叶结点插入	
		ptr = new BSTNode<E,K>(e1);
		assert(ptr);
		return true;
	}
	if (e1 < ptr->data){			//左子树插入
	
		return Insert(e1, ptr->left);
	}
	if (e1 > ptr->data){	//右子树插入
		return Insert(e1, ptr->right);
	}
	return false;			//x已在树中,不再插入
}

//输入一个元素序列, 建立一棵二叉搜索树
template <typename E, typename K>BST<E,K>::BST(K value){
	E x;
	root = NULL;		//置空树
	RefValue = value;
	cout << "Please input the value of each node,end input with "<<value<<" : "<<endl;
	cin >> x;				//输入数据
	while ( x != RefValue){	//RefValue是一个输入结束标志	
		Insert(x, root);
		cin >> x;			//插入，再输入数据
	}
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Copy(/*const*/ BSTNode<E,K> *& ptr){//复制以ptr为根的子树
	if (!ptr){			//空树
		return NULL;
	}
	/*if (!root){//？
		delete[] root;
	}*/
	BSTNode<E,K>* p/*root*/ = new BSTNode<E,K>(ptr->data);
	p->left=Copy(ptr->left);//改
	p->right=Copy(ptr->right);//改
	return /*this->root*/ p;
}

template<typename E, typename K>void BST<E,K>::makeEmpty(BSTNode<E, K> *& ptr){
	if (!ptr){
		return;
	}
	makeEmpty(ptr->left);
	makeEmpty(ptr->right);
	delete ptr;
}

template<typename E, typename K>bool BST<E,K>::DelMax(){
	if (!root){
		return false;
	}
	BSTNode<E,K> *pre = root, *cur = pre->right;
	if (!root->right){//只有左子树，根结点最大，删除原根结点
		root = pre->left;
		delete pre;
		return true;
	}
	while (cur->right){//否则，最右边最大
		pre = cur;
		cur = cur->right;
	}
	pre->right = cur->left;
	delete cur;
	return true;
}

template<typename E, typename K>bool BST<E,K>::DelMin(){
	if (!root){
		return false;
	}
	BSTNode<E,K> *pre = root, *cur = pre->left;
	if (!root->left){//只有右子树，根结点最小，删除原根结点
		root = pre->right;
		delete pre;
		return true;
	}
	while (cur->left){//否则，最左边最小
		pre = cur;
		cur = cur->left;
	}
	pre->left = cur->right;
	delete cur;
	return true;
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Min(BSTNode<E,K> *ptr){
	if (!ptr){
		return NULL;
	}
	BSTNode<E,K> *temp = ptr;
	while (temp->left){
		temp=temp->left;
	}
	return temp;
}

template<typename E, typename K>BSTNode<E,K>* BST<E,K>::Max(BSTNode<E,K> *ptr){
	if (!ptr){
		return NULL;
	}
	BSTNode<E,K> *temp=ptr;
	while (temp->right){
		temp=temp->right;
	}
	return temp;
}

template<typename E, typename K>BST<E,K>& BST<E,K>::operator = (/*const*/ BST<E, K> &R){
	if (this != & R){					//非自我复制
		root=/*return BST<E,K>(*/Copy(R.root)/*)*/;	//复制树
	}
	return *this;
}


//在以 ptr 为根的二叉搜索树中删除含 x 的结点
template <typename E, typename K>bool BST<E,K>::Remove(K x, BSTNode<E,K> *& ptr){
	if (!ptr){
		return false;
	}

	BSTNode<E,K> *temp;
	if (x < ptr->data.key){ //在左子树中执行删除
		return Remove(x, ptr->left);
	}
	else if (x > ptr->data.key){//在右子树中执行删除
			return Remove(x, ptr->right);
		}
		else if (ptr->left != NULL && ptr->right != NULL){//ptr指示关键码为x的结点，它有两个子女
				temp = ptr->right;		//到右子树搜寻中序下第一个结点
				while (temp->left != NULL){
					temp = temp->left;
				}
		ptr->data = temp->data;	//用该结点数据代替根结点数据，这样存在两个值为取代x的结点（temp结点和根结点）
		return Remove(temp->data.key, ptr->right);//删除temp结点
	}
	else{//ptr指示关键码为x的结点有一个子女
		temp = ptr;
		if (ptr->left == NULL){
			ptr = ptr->right;
		}
		else{
			ptr = ptr->left;
		}
		delete temp;
		return true;
	}
}

template<typename E, typename K>void BST<E,K>::PrintTree(BSTNode<E,K> *ptr, ostream &out)const{
	if (!ptr){
		return;
	}
	out << ptr->data/*.key*/;
	if (ptr->left == NULL && ptr->right == NULL){
		return;
	}
	out << "(";
	PrintTree(ptr->left, out);
	out << ',';
	PrintTree(ptr->right, out);
	out << ")";
}

template<typename E, typename K>void BST<E,K>::PrintData(BSTNode<E,K> *ptr, ostream &out)const{
	if (ptr){
		PrintData(ptr->left, out);
		out << ptr->data << endl;
		PrintData(ptr->right, out);
	}
}

template <typename E, typename K>void BST<E,K>::OpticBST(int p[], int q[], E a[], int n){//#修改
	//给定n个不同的数据a[1]<a[2]<...<a[n],以及它们的权值p[j],1<=j<=n,另外落在它们之间外部结点的权值分别为q[i],
	//0<=i<=n。本算法计算a[i+1],...,a[j]的最优二叉搜索树T[i][j]的代价C[i][j],T[i][j]的根R[i][j]和权W[i][j]
	int **R,**C,**W;
	int i, j, k, m, min, u;
	R=new int*[n+1];
	for(i=0;i<=n;i++) R[i]=new int[n+1];
	C=new int*[n+1];
	for(i=0;i<=n;i++) C[i]=new int[n+1];
	W=new int*[n+1];
	for(i=0;i<=n;i++) W[i]=new int[n+1];

	cout<<"\n输出有序关键码集合："<<endl;
	for(i=0;i<=n;i++) cout<<a[i]<<'\t';
	cout<<"\n输出内部结点权值："<<endl;
	for(i=0;i<=n;i++) cout<<p[i]<<'\t';
	cout<<"\n输出外部结点权值："<<endl;
	for(i=0;i<=n;i++) cout<<q[i]<<'\t';

	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++){						//将矩阵清零
			W[j][i]=0;
			C[j][i]=0;
			R[j][i]=0;
		}

	for (i = 0; i < n; i++){
		W[i][i] = q[i];
		C[i][i] = R[i][i] = 0;					//初始化
		W[i][i+1] = W[i][i] + p[i+1] + q[i+1];	//构造只有一个内部结点，两个外部结点的最优二叉搜索树
		R[i][i+1] = i + 1;						//这些树的根在i+1
		C[i][i+1] = W[i][i+1];					//这些树的总带权路径长度（代价）
	}
	W[n][n] = q[n];
	R[n][n] = C[n][n] = 0;
	for (m = 2; m <= n; m++){					//构造具有m个内部结点的最优二叉搜索树
		for (i = 0; i <= n - m; i++){
			j = i + m;							//在前一棵树基础上加一内部结点和一外部结点
			W[i][j] = W[i][j-1] + p[j] + q[j];

			min = C[i+1][j];
			u = i + 1;							//假定i+1为根，计算代价
			for (k = i + 2; k <= j; k++){
				if (C[i][k-1] + C[k][j] < min){
					min = C[i][k-1] + C[k][j];
					u = k;						//轮流以i+2,...,j为根，选代价最小的送min，其根为u
				}
			}
			C[i][j] = W[i][j] + min;
			R[i][j] = u;
		}
	}
	cout<<"\n输出累计权值和数组："<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<W[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"\n输出树代价数组："<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<C[i][j]<<'\t';
		cout<<endl;
	}
	cout<<"\n输出树根数组："<<endl;
	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++) cout<<R[i][j]<<'\t';
		cout<<endl;
	}

	CreatOpt(root,R,a,0,n);

	for(i=0;i<=n;i++){
		delete[] R[i];
		delete[] C[i];
		delete[] W[i];
	}
	delete []R;
	delete []C;
	delete []W;
}
	
template <typename E, typename K>void BST<E,K>::CreatOpt(BSTNode<E, K> *&prt,int** &R,E a[],int i,int j){	//#增加。参数必须是引用，否则树链不起来
	int k=R[i][j];
	Insert(a[k],prt);
	if(i!=(k-1)) CreatOpt(prt,R,a,i,k-1);	//取R的对角线元素则停止
	if(k!=j) CreatOpt(prt,R,a,k,j);			//取R的对角线元素则停止
}
#endif
