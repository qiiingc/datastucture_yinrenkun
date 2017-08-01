#ifndef MYSORT_H
#define MYSORT_H
#include "dataList.h"
#include "SeqStack.h"
#include "BST.h"
const int M = 8;
const int radix = 10;

// 冒泡排序
template <typename E, typename K> void BubbleSort(dataList<E,K> &L, int left, int right);
// 正反方向交替扫描的冒泡排序算法
template <typename E, typename K> void ShakerSort(dataList<E,K> &L, int left, int right);
// 直接选择排序的算法
template <typename E, typename K> void SelectSort(dataList<E,K>& L, int left, int right);
// 直接插入排序算法
template <typename E, typename K> void InsertSort(dataList<E,K> &L, int left, int right);
// 折半插入排序算法
template <typename E, typename K> void BinaryInsertSort(dataList<E,K> &L, int left, int right);
// 希尔排序
template <typename E, typename K> void ShellSort(dataList<E,K> &L, int left, int right);
// 快速排序算法
template <typename E, typename K> void QuickSort(dataList<E,K> &L, int left, int right);
// 改进的归并排序算法
template <typename E, typename K> void MergeSort(dataList<E,K> &L, int left, int right);
// 堆排序算法
template <typename E, typename K> void HeapSort(dataList<E,K> &L, int left, int right);
// MST排序算法（最高位优先的基数排序算法）
// getDigit函数各参数的意义
template <typename E, typename K> void RadixSort(dataList<E,K> &L, int left, int right,
					int d, int (*getDigit)(E&elem, int d, int Radix));
// BST排序
template <typename E, typename K> void BSTSort(dataList<E,K> &L, int left, int right);
// 计数排序
template <typename E, typename K> void CountSort(dataList<E,K> &L, int left, int right);

// 冒泡排序
template <typename E, typename K>void BubbleSort(dataList<E,K> &L, int left, int right){
    int pass = left + 1;
	bool exchange = true;
    while (pass <= right && exchange){
        exchange = false;
        for (int j = right;  j >= pass;  j--){
            if (L[j-1] > L[j]){
                L.Swap(j-1, j);
	            exchange = true;
            }
		}
        pass++;
    }
}

// E917
// 正反方向交替的冒泡排序算法
//奇数趟对表L从前向后, 比较相邻的排序码, 遇到逆序即交换, 
//直到把参加比较排序码序列中最大的排序码移到序列尾部；
//偶数趟从后向前, 比较相邻的排序码, 遇到逆序即交换, 
//直到把参加比较排序码序列中最小的排序码移到序列前端。
template <typename E, typename K>void ShakerSort(dataList<E,K> &L, int left, int right){
	int low = left, high = right, i, j;
	while (low < high){					//当比较范围多于一个对象时排序 	
		j = low;						//记忆元素交换位置
		for (i = low; i < high; i++){	//正向起泡
		
			if (L[i] > L[i+1]){			//发生逆序			
				L.Swap(i, i+1); 		//交换
				j = i;					//记忆右边最后发生交换的位置j
			}
		}
		high = j;						//比较范围上界缩小到j
		for (i = high; i > low; i--){	//反向起泡		
			if (L[i-1] > L[i]){			//发生逆序			
				L.Swap(i-1, i);  		//交换
				j = i;					//记忆左边最后发生交换的位置j
			}
		}
		low = j;						//比较范围下界缩小到j
	}
}

// 直接选择排序的算法
template <typename E, typename K>
void SelectSort(dataList<E,K> &L, int left, int right){
	for (int i = left; i < right; i++)	{
		int k = i;
		for (int j = i+1; j <= right; j++){
			if (L[j] < L[k]) k = j;
		}
		if (k != i){
			L.Swap(i, k);
		}
	}
}

// 直接插入排序算法
template <typename E, typename K>void InsertSort(dataList<E,K> &L, int left, int right){
	E temp;
	int i, j;
	for (i = left + 1; i <= right; i++){
		if (L[i] < L[i-1]){
			temp = L[i];
			j = i - 1;
			do{
				L[j+1] = L[j];
				j--;
			} while (j >= left && temp < L[j]);
			L[j+1] = temp;
		}
	}
}

// 折半插入排序算法
template <typename E, typename K>void BinaryInsertSort(dataList<E,K> &L, int left, int right){
	E temp;
	int low, high, mid;
	for (int i = left + 1; i <= right; i++){
		temp = L[i];
		low = left;
		high = i - 1;
		while (low <= high){
			mid = (low + high) / 2;
			if (temp < L[mid]){
				high = mid - 1;
			}
			else{
				low = mid + 1;
			}
		}
		for (int k = i - 1; k >= low; k--){
			L[k+1] = L[k];
		}
		L[low] = temp;
	}
}

// 希尔排序
template <typename E, typename K>void ShellSort(dataList<E,K> &L, int left, int right){
	int i, j, gap = right - left + 1;
	E temp;
    do{
        gap = gap/3 + 1;
        for (i = left + gap; i <= right; i++){
            if (L[i] < L[i-gap]){
                temp = L[i];  j = i-gap;
                do{
                    L[j+gap] = L[j];
					j = j-gap;
                } while (j >= left && temp < L[j]);
                L[j+gap] = temp;
            }
		}
    } while (gap > 1);
}

// 快速排序算法
template <typename E, typename K>void QuickSort(dataList<E,K> &L, int left, int right){
	if (right - left <= M){
		InsertSort(L, left, right);
	}
	else{
		int pivotpos = L.Partition(left, right);
		QuickSort(L, left, pivotpos-1);
		QuickSort(L, pivotpos+1, right);
	}
}

// 改进的归并排序算法
template <typename E, typename K>void MergeSort(dataList<E,K> &L, int left, int right){
	dataList<E,K> L2;
	improvedMergeSort(L, L2, left, right);
	InsertSort(L, left, right);
}
template <typename E, typename K>void improvedMergeSort(dataList<E,K> &L1, dataList<E,K> &L2, int left, int right){
	if (left >= right || right - left + 1 < M){
		return;
	}
	int mid = (left + right)/2;
	improvedMergeSort(L1, L2, left, mid);
	improvedMergeSort(L1, L2, mid + 1, right);
	improvedMerge(L1, L2, left, mid, right);
}
template <typename E, typename K>void improvedMerge(dataList<E,K> &L1, dataList<E,K> &L2, int left, int mid, int right){
	int s1 = left, s2 = right, t = left, k;
	for (k = left; k <= mid; k++){
		L2[k] = L1[k];
	}
	for (k = mid + 1; k <= right; k++){
		L2[right + mid + 1 - k] = L1[k];
	}
	while (t <= right){
		(L2[s1] <= L2[s2])?L1[t++] = L2[s1++]:L1[t++] = L2[s2--];
	}
}

// 堆排序算法
template <typename E, typename K>void HeapSort(dataList<E,K> &L, int left, int right){
    int i, n = right - left + 1;
    for (i = (n-2)/2; i >= 0; i--){ 	//将表转换为堆	
        siftDown(L, i, n-1);
	}
    for (i = n-1; i >= 0; i--){		//对表排序	
        L.Swap(0, i);
		siftDown(L, 0, i-1);
    }
}

//私有函数: 从结点start开始到m自上向下比较, 
//如果子女的值大于双亲的值, 则相互交换, 将一
//个集合局部调整为最大堆。
template <typename E, typename K>void siftDown(dataList<E,K> &L, const int start, const int m){
    int i = start;
	int j = 2*i+1;	 //j是i的左子女
	E temp = L[i];	 //暂存子树根结点
    while (j <= m){	 //逐层比较	
        if (j < m && L[j] < L[j+1]){	//让j指向两子女中的大者		
			j++;
		}
	    if (temp >= L[j]){	 //temp排序码大不调整		
			break;
		}
        else{			    //否则子女中的大者上移		
            L[i] = L[j];
			i = j;
			j = 2*j+1;  	    //i下降到子女位置
        }
    }
	L[i] = temp;		    //temp放到合适位置
}

// MSD排序算法
template <typename E, typename K>void RadixSort(dataList<E,K> &L, int left, int right, int d, int (*getDigit)(E&,int,int)){
	int i, j, count[radix], p1, p2;
	E* auxArray=new E [right - left + 1];//#必须动态分配
	if (d <= 0){
		return;
	}
/*	if (right - left + 1 <= M){					//当小序列时调用直接插入排序更快
		InsertSort(L, left, right);
		return;
	}*/
	for (j = 0; j < radix; j++){				//计数数组清0
		count[j] = 0;
	}
	for (i = left; i <= right; i++){			//统计各桶元素数量
		count[getDigit(L[i],d,radix)]++;
	}
	for (j = 1; j < radix; j++){				//转换为各桶元素终止位置+1，注意从1开始到倒数第1桶结束
		count[j] = count[j] + count[j-1];
	}
	for (i = left; i <= right; i++){
		j = getDigit(L[i],d,radix);
		auxArray[count[j]-1] = L[i];			//分配到辅助数组
		count[j]--;								//注意--，最后成为各桶起始位置
	}
	for (i = left, j = 0; i <= right; i++, j++){//回放到原数组
		L[i] = auxArray[j];
	}
	delete[] auxArray;
	for (j = 0; j < radix-1; j++){
		p1 = left+count[j];
		p2 = left+count[j+1]-1;
		RadixSort<E,K>(L, p1, p2, d-1, getDigit);//#模板实参推演出现歧义，必须显式指定
	}
	p1 = left+count[j];							//最后一桶特殊
	p2 = right;
	RadixSort<E,K>(L, p1, p2, d-1, getDigit);	//#模板实参推演出现歧义，必须显式指定
}

// 基于二叉搜索树的排序算法
template <typename E, typename K>void BSTSort(dataList<E,K> &L, int left, int right){
	SeqStack<BSTNode<E,K>*> S;
	BST<E,K> bst;
	for(int i = left; i <= right; i++){
		bst.Insert(L[i]);
	}
	BSTNode<E,K> *p = bst.getRoot();
	int j = left;
	do{
		while (p){
			S.Push(p);
			p = p->left;
		}
		if (!S.IsEmpty()){
			S.Pop(p);
			L[j] = p->data;
			j++;
			p = p->right;
		}
	}while (p || !S.IsEmpty());
}

// E925计数排序
// 计数排序
template <typename E, typename K>void CountSort(dataList<E,K> &L, int left, int right){
	int i, j;
	int *count = new int[right-left+1];
	dataList<E,K> tmp(right-left+1);
	for (i = left; i <= right; i++){
		count[i-left] = 0;
	}
	for (i = left; i < right; i++){
		for (j = i+1; j <= right; j++){
			if (L[j] < L[i]){
				count[i-left]++;
			}
			else{
				count[j-left]++;
			}
		}
	}
	for (i = left; i <= right; i++){
		tmp[count[i-left]] = L[i];
	}
	for (i = left; i <= right; i++){
		L[i] = tmp[i-left];
	}
}
#endif
