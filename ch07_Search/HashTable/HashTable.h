#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <cassert>
using namespace std;

const int DefaultSize = 100;
enum KindOfStatus {Active,Empty,Deleted};			//元素分类 (活动/空/删)

//散列表类定义
template <typename E, typename K>class HashTable{
public:
	HashTable(const int d, int sz = DefaultSize); 	//构造函数
	~HashTable() {delete []ht; delete []info;}		//析构函数
	HashTable<E,K>& operator = (const HashTable<E,K> &ht2);
	bool Search(const K k1, E &e1);					//在散列表中搜索k1
	bool Insert(const E &e1);						//在散列表中插入e1
	bool Remove(const K k1, E &e1);					//在散列表中删除e1
	void makeEmpty();								//置散列表为空
	void output();  //输出
//	HashTable<E,K>& operator = (const HashTable<E,K> &ht2);
	friend ostream& operator << (ostream &out, HashTable<E,K> &ht2){
		for(int i = 0; i < ht2.TableSize; i++){
			if(ht2.info[i] == Active){
				out << "#" << i << ":\t"<< ht2.ht[i] << endl;
			}
			else if (ht2.info[i] == Empty){
					out << "#" << i << ":\tEmpty!" << endl;
				}
				else if (ht2.info[i] == Deleted){
					out << "#" << i << ":\tDeleted!" << endl;
					}
		}
		return out;
	}
	friend istream& operator >> (istream &in, HashTable<E,K> &ht2){
		E data;
		while (!in.eof()){
			assert(in >> data);
			ht2.Insert(data);
		}
		return in;
	}
private:
	int divitor;									//散列函数的除数
	int CurrentSize, TableSize;						//当前桶数及最大桶数
	E *ht;											//散列表存储数组
	KindOfStatus *info;								//状态数组
	int FindPos(const K k1) const;					//散列函数:计算初始桶号
/*	int operator == (E &e1) {return *this == e1;}	//#错！重载函数：元素判等。
	int operator != (E &e1) {return *this != e1;}	//重载函数：元素判不等*/
};

//构造函数
template <typename E, typename K>HashTable<E,K>::HashTable(int d, int sz){
	divitor = d;
	TableSize = sz;
	CurrentSize = 0;
	ht = new E[TableSize];
	info = new KindOfStatus[TableSize];
	for (int i = 0; i < TableSize; i++){
		info[i] = Empty;
	}
}

// 私有函数
// 搜索在一个散列表中关键码与k1匹配的元素，
// 搜索成功，则函数返回该元素的位置，
// 否则返回插入点（如果有足够的空间）
template <typename E, typename K>int HashTable<E,K>::FindPos(const K k1)const{
	int i = k1 % divitor;			//计算初始桶号
	int j = i;						//j是检测下一空桶下标
	do{
		if (info[j] == Empty || info[j] == Active && ht[j] == k1){
			return j;
		}
		j = (j+1) % TableSize;		//当做循环表处理, 找下一个空桶 
	} while (j != i);
	return j;						//转一圈回到开始点, 表已满, 失败
}

// 使用线性探查法在散列表ht(每个桶容纳一个元素)中搜索k1。
// 如果k1在表中存在, 则函数返回true,并用引用参数e1返回找到的元素；
// 如果k1不在表中, 则返回false。
template <typename E, typename K>bool HashTable<E,K>::Search(const K k1, E &e1){
	int i = FindPos(k1);  			//搜索
	if (info[i] != Active || ht[i] != k1){
		return false;
	}
	e1 = ht[i];
	return true;
}

//清空散列表
template <typename E, typename K>void HashTable<E,K>::makeEmpty(){
	for (int i = 0; i < TableSize; i++){
		info[i] = Empty;                 //只需将info表清空
	}
	CurrentSize = 0;
}

// 在ht表中搜索e1。
// 若找到则不再插入, 若未找到, 但表已满, 则不再插入, 返回false；
// 若找到位置的标志是Empty或Deleted, 不论表是否已满, x插入, 返回true。
template <typename E, typename K>bool HashTable<E,K>::Insert(const E &e1){
	K k1 = e1.key;					//重载函数：抽取关键码
	int i = FindPos(k1);			//用散列函数计算桶号
	if (info[i] != Active){			//该桶空,存放新元素	
		ht[i] = e1;
		info[i] = Active;
		CurrentSize++;
		return true;
	}
	if (info[i] == Active && ht[i] == e1){
		cout << "Element existed !"<< endl;
		return false;
	}
	cout << "Table is full !"<< endl;
	return false;
}

// 在ht表中删除元素k1。
// 若表中找不到k1, 或虽然找到k1, 但它已经逻辑删除过, 则返回false；
// 否则在表中删除元素k1, 返回true, 并在引用参数e1中得到它。
template <typename E, typename K>bool HashTable<E,K>::Remove(const K k1, E& e1){
	int i = FindPos(k1);
	if (info[i] == Active && ht[i]==k1){			//找到要删元素, 且是活动元素	
		e1 = ht[i];
		info[i] = Deleted;		 	//做逻辑删除标志, 并不真正物理删除
		CurrentSize--;
		return true;			  	//删除操作完成, 返回成功标志
	}
	else{						  	//表中无被删元素, 返回不成功标志	
		return false;
	}
}

template <typename E, typename K>HashTable<E,K>& HashTable<E,K>::operator = (const HashTable<E,K> &ht2){
	if (this != &ht2){
		delete []ht;               //先清后复制，因为大小可能不一样
		delete []info;
		TableSize = ht2.TableSize;
		ht = new E[TableSize];
		info = new E[TableSize];
		for (int i = 0; i < TableSize; i++){
			ht[i] = ht2.ht[i];
			info[i] = ht2.info[i];
		}
		CurrentSize = ht2.CurrentSize;
	}
	return *this;
}

template <typename E, typename K>void HashTable<E,K>::output(){
	for(int i = 0; i<TableSize; i++)	{
		if(info[i] == Active){
			cout << "#" << i << ":\t"<< ht[i] << endl;
		}
		else if (info[i] == Empty){
				cout << "#" << i << ":\tEmpty!" << endl;
			}
			else if (info[i] == Deleted){
					cout << "#" << i << ":\tDeleted!" << endl;
				}
	}
}

#endif
