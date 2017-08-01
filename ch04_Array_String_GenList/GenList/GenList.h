#ifndef GENLIST_H
#define GENLIST_H

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "SeqList.h"

// 广义表结点的类结构定义
template <typename T>class GenListNode{
public:
	GenListNode(){
		mark = 0;
		utype = 0;
		tlink = NULL;
		info.ref = 0;
	}
	GenListNode(GenListNode<T> &RL)	{
		mark = RL.mark;
		utype = RL.utype;
		tlink = RL.tlink;
		info = RL.info;
	}

	int utype;					// =0/1/2
	int mark;					// 访问标记
	GenListNode<T> *tlink;		// 指向同一层下一个结点的指针
	union{
		int ref;				// utype=0: 表头，存放引用计数
		T value;				// utype=1: 元素，存放原子结点数值
		GenListNode<T> *hlink;	// utype=2: 子表，存放子表头指针
	}info;
};

// 广义表返回值的类结构定义
template <typename T>class Items{
public:
	int utype;					// =0/1/2
	int mark;					// 访问标记
	union{
		int ref;				// utype=0: 表头，存放引用计数
		T value;				// utype=1: 元素，存放数值
		GenListNode<T> *hlink;	// utype=2: 子表，存放子表头指针
	}info;
	Items(){
		utype = 0;
		mark = 0;
	}
	Items(Items<T> &RL){
		utype = RL.utype;
		mark = RL.mark;
		info = RL.info;
	}
};

// 广义表类的定义
template <typename T>class GenList{
public:
	GenList();
	~GenList();
	bool Head(Items<T> &x);
	bool Tail(GenList<T> &lt);
	GenListNode<T> *First();
	GenListNode<T> *Next(GenListNode<T> *elem);
	void Copy(const GenList<T> &R);
	int Length();
	int depth();
	void delvalue(const T &x);
	void Print(ostream &out = cout) {Print(first, out);}
	bool equal(GenList<T>& t){
		return equal(first,t.first);
	}
	friend istream& operator >> (istream &in, GenList<T> &L){
		SeqList<T> Ls1;
		SeqList<GenListNode<T> *> Ls2;
		L.CreateList (in, L.first, Ls1, Ls2);	//建立存储结构
		GenListNode<T> *p = L.first;            //删除广义表头部多出来的子表结点
		L.first = L.first->info.hlink;
		delete p;
		return in;
	}
	friend ostream& operator << (ostream &out, GenList<T> &L){
		L.Print(out);
		return out;
	}
private:
	GenListNode<T> *first;
	GenListNode<T> *Copy(GenListNode<T> *ls);
	int Length(GenListNode<T> *ls);
	int depth(GenListNode<T> *ls);
	bool equal(GenListNode<T> *s, GenListNode<T> *t);
	void delvalue(GenListNode<T> *ls, const T &x);
	void Remove(GenListNode<T> *ls);
	void Print(GenListNode<T>* p, ostream &out);
	void CreateList(istream &in, GenListNode<T> *& ls, 
			SeqList<T> &L1, SeqList <GenListNode<T> *> &L2);
};

template <typename T>GenList<T>::GenList(){
	first = new GenListNode<T>;
	assert(first);
}

template <typename T>GenList<T>::~GenList(){
	Remove(first);
}

template <typename T>bool GenList<T>::Head(Items<T> &x){//返回表头元素值
	if (first){
		x.utype = first->tlink->utype;
		x.info = first->tlink->info;
		return true;
	}
	else	return false;
}

template <typename T>bool GenList<T>::Tail(GenList<T> &lt){//返回表尾
	if (first->tlink){
		lt.first->utype = 0;
		lt.first->info.ref = 0;
		lt.first->tlink = Copy(first->tlink->tlink);
		return true;
	}
	else	return false;
}

template <typename T>GenListNode<T> *GenList<T>::First(){//返回表头
	return first->tlink;
}

template <typename T>GenListNode<T> *GenList<T>::Next(GenListNode<T> *elem){//返回直接后继
	return elem->tlink;
}

template <typename T>
void GenList<T>::Copy(const GenList<T> &R){//广义表复制
	first = Copy(R.first);
}

template <typename T>GenListNode<T>* GenList<T>::Copy(GenListNode<T> *ls){//副本实际未共享，但ref标识不变，equal()判相同，Remove()因ref>1漏删
	GenListNode<T> *q = NULL;
	if (ls){
		q = new GenListNode<T>;
		q->utype = ls->utype;
		switch (ls->utype){
		case 0:
			q->info.ref = ls->info.ref;
			break;
		case 1:
			q->info.value = ls->info.value;cout<<q->info.value<<endl;
			break;
		case 2:
			q->info.hlink = Copy(ls->info.hlink);
			break;
		}
		q->tlink = Copy(ls->tlink);
	}
	return q;
}

template <typename T>int GenList<T>::Length(){//广义表长度，同一层次元素数
	return Length(first)-1;
}

template <typename T>int GenList<T>::Length(GenListNode<T> *ls){
	return (ls == NULL)?0:(1+Length(ls->tlink));
}

template <typename T>int GenList<T>::depth(){
	return depth(first);
}

template <typename T>int GenList<T>::depth(GenListNode<T> *ls){//广义表深度
	if (!ls){
		return 1;
	}
	GenListNode<T> *temp = ls->tlink;
	int m = 0, n;
	while (temp){
		if (temp->utype == 2){
			n = depth(temp->info.hlink);
			if (m < n){
				m = n;
			}
		}
		temp = temp->tlink;
	}
	return m+1;
}

template <typename T>bool GenList<T>:: equal(GenListNode<T> *s, GenListNode<T> *t){//广义表是否相等，不适用共享表副本
	bool x;
	if (s->tlink == NULL && t->tlink == NULL)	return true;
	if (s->tlink && t->tlink && s->tlink->utype == t->tlink->utype)	{
		if (s->tlink->utype == 1){
			x = (s->tlink->info.value == t->tlink->info.value)?true:false;
		}
		if (s->tlink->utype == 2){
			x = equal(s->tlink->info.hlink, t->tlink->info.hlink);
		}
		if (s->tlink->utype == 0){
			if(s->tlink->info.ref== t->tlink->info.ref) x=true;
			else x=false;
		}
		if (x)	{
			return equal(s->tlink, t->tlink);
		}
	}
	return false;
}

template <typename T>void GenList<T>::delvalue(const T &x){//删除含定值结点
	delvalue(first, x);
}
template <typename T>void GenList<T>::delvalue(GenListNode<T> *ls, const T &x){
	if (ls->tlink)	{
		GenListNode<T> *p = ls->tlink;
		while (p && (p->utype == 1 && p->info.value == x)){
			cout<<p->info.value;
			ls->tlink = p->tlink;
			delete p;
			p = ls->tlink;
		}
		if (p){
			if (p->utype == 2){
				cout<<'#'<<endl;
				delvalue(p->info.hlink, x);//进入下一层次
			}
			delvalue(p, x);//由本结点开始
		}
	}
}

template <typename T>void GenList<T>::Remove(GenListNode<T> *ls){//删除指定子表，不适用共享表副本
	ls->info.ref--;
	if (ls->info.ref <= 0){
		GenListNode<T> *q;
		while (ls->tlink){
			q = ls->tlink;
			if (q->utype == 2){
				Remove(q->info.hlink);
				if (q->info.hlink->info.ref <= 0){
					delete q->info.hlink;
				}
			}
			ls->tlink = q->tlink;
			delete q;
		}
	}
}


// 从广义表的字符串描述s出发, 建立一个带头结点的广义表，要求T为char型。
// 在表L1存储大写字母的表名, 在表L2存储表名对应子表结点的地址。
template <typename T>void GenList<T>::CreateList(istream& in, GenListNode<T> *& ls, 
			SeqList<T> &L1, SeqList <GenListNode<T> *> &L2){
	T chr; 
	in >> chr;
	cout<<chr; 
	//读入一个字符，只可能读入#、左括号和字母
	if (isalpha(chr) && isupper(chr) || chr == '('){ //大写字母或'('	
		bool b=true;
		ls = new GenListNode<T>;          //建子表结点
		cout<<'&';
		ls->utype = 2;		
		if (isalpha(chr) && isupper(chr)){ //表名处理,有名子表		
			int n = L1.Length();
			int m = L1.Search(chr);
			if (m != 0){                  //该表已建立
				b=false;                  //共享
				ls->info.hlink = *L2.getData(m);//查子表地址
				ls->info.hlink->info.ref++;		//引用计数加1
				cout<<'@';
				in >> chr;
				if (chr != '('&&chr!=','&&chr != ')') exit(1);	//表名后必跟'('或','或')'
				if(chr=='(')
					do{
						in>>chr; //共享表可以只输入表名，其它内容程序忽略
					}while(chr!=')');
				else if(chr==','||chr == ')') in.putback(chr);//逗号或')'送回缓冲区
			} 	
			else{       //该表未建立
				ls->info.hlink = new GenListNode<T>;         //建附加头结点
				L1.Insert(n, chr);                           //保存表名及地址
				L2.Insert(n, ls->info.hlink);
				in >> chr;
				cout<<chr; 
				cout<<'%';  
				ls->info.hlink->utype = 0;
				ls->info.hlink->info.ref = 1;
				if (chr != '(') exit(1);	//表名后必跟'('
				CreateList(in, ls->info.hlink->tlink, L1, L2);//递归建子表
			}
		}
		else{//无名子表
			ls->info.hlink = new GenListNode<T>;
			cout<<'%';  
			ls->info.hlink->utype = 0;         //建头结点
			ls->info.hlink->info.ref = 1;
			CreateList(in, ls->info.hlink->tlink, L1, L2);//递归建子表
		}
		CreateList(in, ls, L1, L2);                   //递归建后继表
	}
	else if (isalpha(chr) && islower(chr)){	//建原子结点。本程序现在仅在T为char时有效
			ls = new GenListNode<T>;
			cout<<'*'; 
			ls->utype = 1;
			ls->info.value = chr;//这里应该有将字符与T类型具体数据一一对应的表，最终把具体数据存入info.value
			CreateList(in, ls, L1, L2);
		}
		else if (chr == ','){ 		//建后继结点	
				if (ls->tlink) delete ls->tlink;
				ls->tlink = new GenListNode<T>;
				CreateList(in, ls->tlink, L1, L2); 
			}
			else if (chr == ')')	ls->tlink = NULL;  //链收尾
				else if (chr == '#')	ls = NULL; //空表, 链收尾
}

//打印数据
template<typename T>
void GenList<T>::Print(GenListNode<T>* p, ostream &out){
	if (!p)
		return;                           //p为NULL结束
	if (p->utype==1)                      //原子结点
		out << (p->info).value << "   ";
	else if (p->utype == 0)               //附加表头结点
			while (p->tlink){			  //关注此句,因为无返回指针，必须由while显式循环
				Print(p->tlink, out);
				p=p->tlink;               //返回后右移
			}
		else	Print(p->info.hlink, out);//子表结点
}

#endif
