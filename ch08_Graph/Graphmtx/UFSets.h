#ifndef UFSETS
#define UFSETS
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
const int DefaultSize1 = 30;

//集合中的各个子集合互不相交
class UFSets{
public:
    UFSets(int sz = DefaultSize1);
	UFSets(UFSets &R);
	~UFSets(){
		delete []parent;
	}
    UFSets& operator = (UFSets &R);		//操作符重载，实现集合赋值
    void SimpleUnion(int Root1, int Root2);//子集合并
    int Find(int x);					//查找x的根
    void WeightedUnion(int Root1, int Root2);//压缩高度的合并算法
	int CollapsingFind(int i);			//使用折叠规则的搜索算法
	void output(ostream &out = cout);
	friend ostream& operator << (ostream &out, UFSets &R){
		int i;
		out << "\n" << string(70, '=');
		for (int j = 0; j <= (R.size-1)/10; j++){
			out << "\nNode:\t";
			for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
				out << setw(6) << i;
			}
			cout << "\nParent:\t";
			for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
				out << setw(6) << R.parent[i];
			}
			if (i < R.size){
				out << "\n" << string(70, '-');
			}
		}
		out << "\n" << string(70, '=') << "\n";
		return out;
	}
private:
    int *parent;						//集合元素数组(双亲表示)
    int size;							//集合元素的数目
};
#endif
