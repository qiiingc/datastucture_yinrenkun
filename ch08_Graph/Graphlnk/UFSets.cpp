#include "UFSets.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//构造函数
UFSets::UFSets(int sz){
	size = sz;
	parent = new int[size];  //创建双亲数组
	for (int i = 0; i < size; i++){
		parent[i] = -1;
	}
}

UFSets::UFSets(UFSets &R){
	size = R.size;
	parent = new int[size];
	for (int i = 0; i < size; i++){
		parent[i] = R.parent[i];
	}
}

UFSets& UFSets::operator = (UFSets &R){
	size = R.size;
	parent = new int[size];
	for (int i = 0; i < size; i++){
		parent[i] = R.parent[i];
	}
	return *this;
}

//函数搜索并返回包含元素x的树的根。
int UFSets::Find(int x){
	while (parent[x] >= 0){
		x = parent[x];
	}
	return x;
}

//求两个不相交集合Root1与Root2的并(将Root2连接到Root1下面)
void UFSets::SimpleUnion(int Root1, int Root2){
	int r1 = Find(Root1), r2 = Find(Root2);
	if (r1 != r2){
		parent[r1] += parent[r2];
		parent[r2] = r1;
	}
}

//按Union的加权规则改进的算法
void UFSets::WeightedUnion(int Root1, int Root2){
	int r1 = Find(Root1), r2 = Find(Root2), temp;
	if (r1 != r2){
		temp = parent[r1] + parent[r2];
		if (parent[r2] < parent[r1]){
			parent[r1] = r2;
			parent[r2] = temp;
		}
		else{
			parent[r2] = r1;
			parent[r1] = temp;
		}
	}
}

//使用折叠规则的搜索算法
int UFSets::CollapsingFind(int i){
	int j = i;
	for (; parent[j] >= 0; j = parent[j]);
	while (i != j){
		int temp = parent[i];  
		parent[i] = j; 
		i = temp; 
	}
    return j;
}

void UFSets::output(ostream &out){
	int i;
	out << "\n" << string(70, '=');
	for (int j = 0; j <= (size-1)/10; j++){
		out << "\nNode:\t";
		for(i = 10*j; i < 10*(j+1) && i < size; i++){
			out << setw(6) << i;
		}
		out << "\nParent:\t";
		for(i = 10*j; i < 10*(j+1) && i < size; i++){
			out << setw(6) << parent[i];
		}
		if (i < size){
			out << "\n" << string(70, '-');
		}
	}
	cout << "\n" << string(70, '=') << "\n";
}
