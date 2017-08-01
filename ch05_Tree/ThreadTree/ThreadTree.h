#ifndef THREADTREE
#define THREADTREE

// 线索二叉树的结点类
template <typename T>struct ThreadNode{
	int ltag, rtag;	//线索标志
	ThreadNode<T> *leftChild, *rightChild; //线索或子女指针
	T data;			//结点数据
	ThreadNode(const T item){
		data = item;
		leftChild = NULL;
		rightChild = NULL;
		ltag = 0;
		rtag = 0;
	}
};

// 线索二叉树类
template <typename T>class ThreadTree{
protected:
	ThreadNode<T> *root;
	void createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre);
	ThreadNode<T> *parent(ThreadNode<T> *t);
public:
	ThreadTree(){
		root = NULL;
	}
	~ThreadTree(){
		destroy(root);
	}
	void InitThreadTree();
	void createInThread(); //建立中序线索二叉树
	bool FindTh (const T &value);	//在线索二叉树中找value,成功返true,并置current为此结点;否则返false
	ThreadNode<T> *First(ThreadNode<T> *current);	//寻找中序下第一个结点
	ThreadNode<T> *Last(ThreadNode<T> *current);	//寻找中序下最后一个结点
	ThreadNode<T> *Next(ThreadNode<T> *current);	//寻找结点在中序下的后继结点
	ThreadNode<T> *Prior(ThreadNode<T> *current);	//寻找结点在中序下的前驱结点
	void InOrder(void (*visit)(ThreadNode<T> *t));	//线索化二叉树的中序遍历
	void PreOrder(void (*visit)(ThreadNode<T> *t));	//线索化二叉树的前序遍历
	void PostOrder(void (*visit)(ThreadNode<T> *t));	//线索化二叉树的后序遍历	
	bool Find (const T &value);	//在常规二叉树中找value,成功返true,并置current为此结点;否则返false
	ThreadNode<T>* /*&*/ getCurrent(){//返回current,最好是副本
		return current;
	}
	void destroy(ThreadNode<T> *& subTree);
private:
	ThreadNode<T> *current;
	bool Find(ThreadNode<T> *p, const T &value);			//在以p为根的常规二叉树中搜索value
	bool setRoot(const T &rt){                              //设置根值为rt
		root = new ThreadNode<T>(rt);
		if(root) return true;
		else return false;
	}
	static ThreadNode<T>* &leftChild (ThreadNode<T> *t){//返回左子女
		return t->leftChild;
	}
	static ThreadNode<T>* &rightChild (ThreadNode<T> *t){
		return t->rightChild;                //返回右子女
	}
	bool MakeLink(const T ex, const T ap, char linkmark); 
	void Print(ThreadNode<T>* /*&*/p, int i);//p不可以为引用，否则实参指针root被移动。尽管本例中会移回来
};
//-----------------------------------------------------------------------------------------------------------------
template <typename T>void ThreadTree<T>::destroy(ThreadNode<T> *& subTree){//清除子二叉树
	if (subTree != NULL){
		destroy (subTree->leftChild);
		destroy (subTree->rightChild);
		delete subTree;
	}
}

template<typename T>bool ThreadTree<T>::Find(const T &value){//建立常规二叉树过程中使用
	if(!root){
		return 0;
	}
	else{
		return Find(root, value);
	}
}

template<typename T>bool ThreadTree<T>::Find(ThreadNode<T> *p, const T &value){//在以p为根的树中搜索value
	if (!p)	{
		return false;
	}
	if(p->data == value){
		current = p;                 //找到，current指向该结点
		return true;
	}
	else{
		return Find(p->leftChild,value) || Find(p->rightChild, value);//左边找到后不会再去右边
	}
}


template<typename T>bool ThreadTree<T>::MakeLink(const T ex, const T ap, char linkmark){//将数据ap连接为数据域为ex结点的子女
	if(linkmark != eptmark) {//结束标志		
		ThreadNode<T> *p = new ThreadNode<T>(ap);//将ap转化为结点
		if(Find(ex))                             //找ex,置为current
		cout << "cu " << current -> data << endl;
		if(current) {
			switch(linkmark) {
                case 'l': current -> leftChild = p; 
					cout << "input success!" << endl;break;//建立左子女关系
                case 'r': current -> rightChild = p; 
					cout << "input success!" << endl;break;//建立右子女关系
				default: cout << "error! please reinput again!" << endl;
			}
			return false;//返回假，继续
		}
		else {
			cout << "error! please reinput again!" << endl;
			return false;
		}
	}
	else return true;//返回真，结束
}

template<typename T>void ThreadTree<T>::InitThreadTree(){
	cout << "please input the root node" << endl;//输入根结点
	char elem1, elem2, elem3;
	cin >> elem1;
	while(1){
		if(setRoot(elem1)) {
			cout << "input success!" << endl;
			break;
		}
		else cout << "error! please reinput again!"  << endl;
	}
	cout << "please enter link between nodes, one existed and one to be inserted" << endl;
    cout << "e.g (Parent) (leftChild) l or (Parent) (rightChild) r" << endl;
	//输入除根外的所有结点，要求elem1为已加入的结点
	//elem2为新建结点，且二者子女关系
	while(1){
        cin >> elem1 >> elem2 >> elem3;//按格式输入
		if(MakeLink(elem1, elem2, elem3)) break;//建立关联
	}
	cout << "treeview" << endl;
	Print(root,0);
	return;
}

template<typename T>
void ThreadTree<T>::Print(ThreadNode<T>* /*&*/p, int i) {//前序遍历打印
	if(p) {
		for(int j = 0; j < i; ++j) cout << '\t';	//i为制表符计数
		cout << p->data << endl;//输出当前结点	    
		if(ThreadTree<T>::leftChild(p) || ThreadTree<T>::rightChild(p)){//先左，后右一步，然后又向左，到树叶终止
			++i;//层次
			Print(ThreadTree<T>::leftChild(p), i);//递归输出左子树
			Print(ThreadTree<T>::rightChild(p), i);//递归输出右子树
		}
	}
	return;
}

#endif
