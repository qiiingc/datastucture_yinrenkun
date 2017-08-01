#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream>
#include <cassert>
using namespace std;
const int DefaultSize=50;

template <typename T,typename Item> class MinHeap{// T为关键码的数据类型，Item为记录的结构类型
public:
	MinHeap(int sz = DefaultSize);//构造函数：建立空堆
	MinHeap(Item arr[], int n);	//构造函数：通过一个数组建堆
	~MinHeap(){
		delete []heap;
	}
	bool Insert(const Item &x);
	bool RemoveMin(Item &x);
	bool IsEmpty()const{
		return currentSize == 0;
	}
	bool IsFull()const{
		return currentSize == maxHeapSize;
	}	
	void MakeEmpty(){
		currentSize = 0;
	}

	void output(){//自定义函数，顺序输出最小堆元素	
		for(int i = 0; i<currentSize; i++)
			cout<<heap[i]<<" ";
		cout<<endl;
	}

private: 
	Item *heap;						//存放最小堆中元素的数组
	int currentSize;				//最小堆中当前元素个数
	int maxHeapSize;				//最小堆最多允许元素个数
	void siftDown(int start, int m);//从start到m下滑调整成为最小堆
	void siftUp(int start);			//从start到0上滑调整成为最小堆
};

// 构造函数：建立空堆
template <typename T,typename Item>MinHeap<T,Item>::MinHeap(int sz){
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new Item[maxHeapSize];
	assert(heap);
	currentSize = 0;
}

// 构造函数：通过一个数组建堆
template <typename T,typename Item> MinHeap<T,Item>::MinHeap(Item arr[], int n)
{
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;	
	heap = new Item[maxHeapSize]; 
	assert(heap);
	for (int i = 0; i < n; i++ )
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize-2)/2;		//找最初调整位置:最后分支结点
	while (currentPos >= 0)					//自底向上逐步扩大形成堆
	{
		siftDown(currentPos, currentSize -1);	//局部自上向下下滑调整
		currentPos--;							//再向前换一个分支结点
	}
}

//私有函数：最小堆的下滑调整算法
template <typename T,typename Item>void MinHeap<T,Item>::siftDown(int start, int m){
	int i = start, j = 2*i+1;//j是i的左子女位置
	Item temp = heap[i]; 			
	while (j <= m){//检查是否到最后位置	
		//让j指向两子女中的小者
		if (j < m && heap[j] > heap[j+1]){
			j++;
		}
		if (temp <= heap[j]){
			break;
		}
		else{
			heap[i] = heap[j];
			i = j;
			j = 2*j+1;
		}
	}
	heap[i] = temp;	//回放temp中暂存的元素
}

// 私有函数：最小堆的上滑调整算法
template <typename T,typename Item>void MinHeap<T,Item>::siftUp(int start){
	int j = start, i = (j-1)/2;
	Item temp = heap[j];
	while (j > 0){ //沿父结点路径向上直达根	
		if (heap[i] <= temp){
			break;
		}
		else{
			heap[j] = heap[i];
			j = i;
			i = (i-1)/2;
		}
	}
	heap[j] = temp;	//回放temp中暂存的元素
}

// 公共函数: 将x插入到最小堆中
template <typename T,typename Item>bool MinHeap<T,Item>::Insert(const Item &x){
	if (currentSize == maxHeapSize){	//堆满	
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;	//插入
	siftUp(currentSize);	//向上调整
	currentSize++;			//堆计数加1
	return true;
}

// 公共函数：最小堆的删除算法
template <typename T,typename Item>bool MinHeap<T,Item>::RemoveMin(Item &x){
	if (!currentSize){	//堆空, 返回false	
		cout << "Heap empty" << endl;
		return false;
	}
	x = heap[0];		// 返回最小元素
	heap[0] = heap[currentSize-1];	//最后元素填补到根结点
	currentSize--;
	siftDown(0, currentSize-1);		//自上向下调整为堆
	return true;
}

#endif
