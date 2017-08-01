#ifndef STATICLIST_H
#define STATICLIST_H
#include <cassert>
#include <iostream>
using namespace std;

const int defaultSize = 100;
template <typename T>struct SLinkNode{
	T data;
	int link;
};

template <typename T>class StaticList{
	SLinkNode<T> *elem;
	int maxSize;
	int avil;//可用结点链链首下标
public:
	StaticList(int sz = defaultSize);
	~StaticList();
	int Length();
	int Search(T x);
	int Locate(int i);
	bool getData(int i, T &x);
	bool Append(T x);          //在表尾添加新结点
	bool Insert(int i, T x);   //在第i个结点后插入一个结点
	bool Remove(int i);
	bool IsEmpty();
	void output(int type = 0);
	friend istream& operator >> (istream& in, StaticList<T> &stl){
		T data;
		while (!in.eof()){//在原链表后添加，与其他线性表不同
			in >> data;
			stl.Append(data);
		}
		return in;
	}
	friend ostream & operator<<(ostream &out, StaticList <T> &stl){
		int p = stl.elem[0].link;//elem[0]为附加头结点
		while(p != -1){
			cout << stl.elem[p].data << endl;
			p = stl.elem[p].link;
		}
		cout << endl;
		return out;
	}
};

template <typename T>StaticList<T>::StaticList(int sz){
	maxSize = sz;
	elem = new SLinkNode<T>[maxSize];
	assert(elem);
	elem[0].link = -1;//-1代表链尾
	avil = 1;//可用结点链链首下标
	for (int i = 1; i < maxSize - 1; i++)	elem[i].link = i + 1;//建立可用结点链
	elem[maxSize - 1].link = -1;
}

template <typename T>StaticList<T>::~StaticList(){
	delete []elem;
}

template <typename T>int StaticList<T>::Length(){
	int p = elem[0].link;
	int i = 0;
	while (p != -1){
		p = elem[p].link;
		i++;
	}
	return i;
}

template <typename T>bool StaticList<T>::IsEmpty(){
	return (elem[0].link == -1)?true:false;
}

template <typename T>int StaticList<T>::Search(T x){
	int p = elem[0].link;
	while (p != -1)	{
		if (elem[p].data == x)	break;
		else	p = elem[p].link;
	}
	return p;//未找到返回的是-1
}

template <typename T>int StaticList<T>::Locate(int i){//位置由下标给出
	if (i < 0)	return -1;
	if (i == 0)	return 0;
	int j = 1, p = elem[0].link;
	while (p != -1 && j < i){
		p = elem[p].link;
		j++;
	}
	return p;//未找到返回的是-1
}

template <typename T>bool StaticList<T>::getData(int i, T &x){
	int p = Locate(i);
	if (p == -1)	return -1;
	x = elem[p].data;
	return true;
}

template <typename T>bool StaticList<T>::Append(T x){
	if (avil == -1)	return false;
	int q = avil;
	avil = elem[avil].link;//更新可用结点链链首下标
	elem[q].data = x;      //建立q结点
	elem[q].link = -1;
	int p = 0;
	while (elem[p].link != -1)	p = elem[p].link;
	elem[p].link = q;      //链入q结点
	return true;
}

template <typename T>bool StaticList<T>::Insert(int i, T x){
	int p = Locate(i);
	if (p == -1)	return false;
	int q = avil;          //取可用结点
	avil = elem[avil].link;//更新可用结点链链首下标
	elem[q].data = x;      //建立新结点
	elem[q].link = elem[p].link;//链入
	elem[p].link = q;
	return true;
}

template <typename T>bool StaticList<T>::Remove(int i){
	int p = Locate(i - 1);
	if (p == -1) return false;
	int q = elem[p].link;
	if (q == -1) return false;//改。如果第i项不存在，返回失败，否则后继语句出错
	elem[p].link = elem[q].link;
	elem[q].link = avil;//移出的结点放入可用结点链
	avil = q;           //并在链首
	return true;
}

template <typename T>void StaticList<T>::output(int type){
	if (IsEmpty()){
		cout << "The static list is empty!\n";
		return;
	}
	if (type == 0){//按链表输出
		cout << "Index\tData" << endl;
		cout << "0\thead" << endl;
		int p = elem[0].link;
		while(p != -1){
			cout<< p << "\t" << elem[p].data << endl;
			p = elem[p].link;
		}
		cout << "Static List length: " << Length() << endl;
	}
	else{//按顺序表输出
		cout << "Index\tData\tLink" << endl;
		cout << "0\thead\t" << elem[0].link << endl;
		int avl = avil;
		for (int i = 1, len = Length(); len > 0; i++){//用链长控制输出
			if (i == avl){
				cout << i << "\t\t" << elem[i].link << endl;//待用结点不输出值
				avl = elem[avl].link;
			}
			else{//链表中的结点
				cout << i << "\t" << elem[i].data << "\t" << elem[i].link << endl;
				len--;
			}
		}
		cout << "First available position: " << avil << endl;
	}
	cout << endl;
}
#endif
