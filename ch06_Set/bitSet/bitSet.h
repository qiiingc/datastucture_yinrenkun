#ifndef BITSET_H
#define BITSET_H

#include <cassert>
#include <iostream>
using namespace std;
const int DefaultSize = 50;

// T 应该为整数类型
template<typename T>class bitSet{
//用位向量来存储集合元素, 集合元素的范围在0到
//setSize-1之间。数组采用16位无符号短整数实现
public:
	bitSet(int sz = DefaultSize);
	bitSet(const bitSet<T> &R);
	~bitSet();
	bool getMember(const T &x);				//取集合元素x
	void putMember(const T &x, int v);			//用v值修改集合元素x
	void makeEmpty();
	bool addMember(const T &x);					//加入新成员x
	bool delMember(const T &x);					//删除老成员x
	bitSet<T>& operator = (const bitSet<T> &R);	
	bitSet<T> operator + (const bitSet<T> &R);
	bitSet<T> operator * (const bitSet<T> &R);
	bitSet<T> operator - (const bitSet<T> &R);
	bool Contains(const T &x);                  //判x是否集合this的成员
	bool subSet(bitSet<T> &R);					//判this是否R的子集
	bool operator == (bitSet<T> &R);		    //判集合this与R相等

	friend istream& operator >> (istream &in, bitSet<T> &R){
		T item;
		while (!in.eof()){
			in >> item;
			if (item < 0){
				break;
			}
			R.addMember(item);
		}
		in.clear();
		return in;
	}
	friend ostream& operator << (ostream &out, bitSet<T> &R)	{
		out << "{";
		int i = 0;
		while (i < R.setSize){
			if (R.getMember(i)){
				out << i++;
				break;
			}
			i++;
		}
		for (; i < R.setSize; ++i){
			if (R.getMember(i)){
				out << ", " << i;
			}
		}
		out << "}" << endl;
		return out;
	}

private:
	int setSize;				//集合大小
	int vectorSize;				//位数组大小
	unsigned short *bitVector;	//存储集合元素的位数组
};

template <typename T>bitSet<T>::bitSet(int sz){
	setSize = sz;
	assert(setSize > 0);
	vectorSize = (setSize+15)>>4;//缩为16分之1，并避免截尾
	bitVector = new unsigned short [vectorSize];
	assert(bitVector);
	for (int i = 0; i < vectorSize; i++){
		bitVector[i] = 0;
	}
}

//复制构造函数
template <typename T>bitSet<T>::bitSet(const bitSet<T> &R){
	setSize = R.setSize;
	vectorSize = R.vectorSize;
	bitVector = new unsigned short [vectorSize];
	assert(bitVector);
	for (int i = 0; i < vectorSize; i++)	{
		bitVector[i] = R.bitVector[i];
	}
}

template <typename T>bitSet<T>::~bitSet(){
	delete []bitVector;
}

template <typename T>void bitSet<T>::makeEmpty(){//清空集合
	for (int i = 0; i < vectorSize; i++)	{
		bitVector[i] = 0;
	}
}

template <typename T>bool bitSet<T>::Contains(const T &x){//集合是否包含x
	return getMember(x);
}

//读取集合元素x
template <typename T>bool bitSet<T>::getMember(const T &x){
	int ad = x/16, id = x%16;
	unsigned short elem = bitVector[ad];
	return ((elem >> (15-id)) & 1);
}

//将值v送入集合元素x
template <typename T>void bitSet<T>::putMember(const T &x, int v){
	int ad = x/16, id = x%16;
	unsigned short elem = bitVector[ad];
	int temp = elem >> (15-id);
	if (temp%2 == 0 && v == 1){
		temp = temp+1;
	}
	else if (temp%2 == 1 && v == 0){
			temp = temp-1;
		}
	bitVector[ad] = (temp<<(15-id)) | (((1<<(15-id)) - 1) & elem);		//送回
}

template <typename T>bool bitSet<T>::addMember(const T &x){
	assert (x >= 0 && x < setSize);
	if (getMember(x) == 0){//x对应位是0，不在，添进去
		putMember(x, 1);
		return true;
	}
	return false;
}

template <typename T>bool bitSet<T>::delMember(const T &x){
	assert(x >= 0 && x < setSize);
	if (getMember(x) == 1){//x对应位是1，在，删除
		putMember(x, 0);
		return true;
	}
	return false;
}

template<typename T>bitSet<T>& bitSet<T>::operator = (const bitSet<T> &R){
	if (this != &R){
		setSize = R.setSize;
		vectorSize = R.vectorSize;
		delete []bitVector;
		bitVector = new unsigned short [vectorSize];
		assert(bitVector);
		for (int i = 0; i < vectorSize; i++){//操作仅可以按数组元素，不可也不必按位进行
			bitVector[i] = R.bitVector[i];
		}
	}
	return *this;
}

//求集合this与R的并
template<typename T>bitSet<T> bitSet<T>::operator + (const bitSet<T> &R){//并用按位或计算
	assert(vectorSize == R.vectorSize); //拟用setSize更准确
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] = bitVector[i] | R.bitVector[i];
	}
	return temp;
}

//求集合this与R的交
template <typename T>bitSet<T> bitSet<T>::operator * (const bitSet<T> &R){	//交用按位与计算
	assert (vectorSize == R.vectorSize);
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] = bitVector[i] & R.bitVector[i];
	}
	return temp;
}

//求集合this与R的差
template <typename T>bitSet<T> bitSet<T>::operator - (const bitSet<T> &R){	//*this和R的按位反进行按位与计算
	assert(vectorSize == R.vectorSize); 
	bitSet<T> temp(setSize);
	for (int i = 0; i < vectorSize; i++){
		temp.bitVector[i] =	bitVector[i] & ~R.bitVector[i];
	}
	return temp;
}

//判this是否R的子集
template <typename T>bool bitSet<T>::subSet(bitSet<T> &R){
	assert (setSize == R.setSize);
	for (int i = 0; i < vectorSize; i++){
		if (bitVector[i] & ~R.bitVector[i]){//*this与R的差为0
			return false;
		}
	}
	return true;	
}

//判集合this与R相等
template <typename T>
bool bitSet<T>::operator == (bitSet<T> &R){
	if (vectorSize != R.vectorSize)	{
		return false;
	}
	for (int i = 0; i < vectorSize; i++){
		if (bitVector[i] != R.bitVector[i]){//每一个数组元素都相同，注意最后一个数组元素未用的位，也应该相同，通常全为0
			return false;
		}
	}
	return true;
}
#endif
