#ifndef DATALIST_H
#define DATALIST_H
#include <iostream>
#include <cassert>
using namespace std;

const int defaultSize = 100;

template <typename E, typename K>class dataList{
public:
    dataList(int sz = defaultSize){
		maxSize = sz;
		currentSize = 0;
        Element = new E[sz];
        assert(Element);
    }
    dataList(dataList<E,K> &R){
		maxSize = R.maxSize;
		currentSize = R.currentSize;
		Element = new E[maxSize];
		assert(Element);
		for (int i = 0; i < currentSize; i++){
			Element[i] = R.Element[i];
		}
	}
    virtual ~dataList(){
		delete []Element;
	}
    virtual int Length(){
		return currentSize;
	}
	virtual int SeqSearch(const K k1)const;
    virtual bool Insert(E &e1);
    virtual bool Remove(K k1, E &e1);
	void Swap(E &x, E &y){
		E temp = x;
		x = y;
		y = temp;
	}
	void Swap(int x, int y){//#重载
		E temp = Element[x];
		Element[x] = Element[y];
		Element[y] = temp;
	}
	dataList<E,K>& operator = (dataList<E,K> &R){
		maxSize = R.maxSize;
		currentSize = R.currentSize;
		Element = new E[maxSize];
		assert(Element);
		for (int i = 0; i < currentSize; i++){
			Element[i] = R.Element[i];
		}
		return *this;
	}
	E& operator [] (int i){
		return Element[i];
	}
	int Partition(const int low, const int high);
	friend ostream& operator << (ostream &out, dataList<E,K> &R){
		for (int i = 0; i < R.currentSize; i++){
			out << R.Element[i] << endl;
		}
		return out;
	}
	friend istream& operator >> (istream &in, dataList<E,K> &R){
		E data;
		while (!in.eof()){
			assert(in >> data);
			R.Insert(data);
		}
		return in;
	}
protected:
	E *Element;
	int maxSize, currentSize;
};

template <typename E, typename K >bool dataList<E,K>::Insert(E &e1){
    if (currentSize == maxSize){
		return false;
	}
    Element[currentSize] = e1;
    currentSize++;
	return true;
}

template <typename E, typename K>bool dataList<E,K>::Remove(K k1, E &e1){
	if (currentSize == 0){
		return false;
	}
	int i;
	for (i = 0; i < currentSize && Element[i] != k1; i++);
	if (i == currentSize){
		return false;
	}
	e1 = Element[i];
	Element[i] = Element[currentSize-1];
	currentSize--;
	return true;
}

template <typename E, typename K>int dataList<E,K>::SeqSearch(const K k1)const{
	int i;
	for (i = 0; i < currentSize; i++){
		if (Element[i] == k1){
			break;
		}
	}
	return (i == currentSize)?0:(i+1);
}

template <typename E, typename K>int dataList<E,K>::Partition(const int low, const int high){
	//数据表类的共有函数
	int pivotpos = low;
	E pivot = Element[low];	  //基准元素
	for (int i = low+1; i <= high; i++){
		//检测整个序列, 进行划分
		if (Element[i] < pivot){
			pivotpos++;
			if (pivotpos != i){
				Swap(Element[pivotpos], Element[i]);
			}
		}//小于基准的交换到左侧去
	}
	Element[low] = Element[pivotpos];
	Element[pivotpos] = pivot;	//将基准元素就位	
	return pivotpos;			//返回基准元素位置
}
#endif
