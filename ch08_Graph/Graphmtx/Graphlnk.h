#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include "Graph.h"
#include <iostream>
#include <cassert>
using namespace std;

extern const int maxWeight;							//代表无穷大的值(=)

const int DefaultVertices = 30;						//默认最大顶点数(=n)

//邻接表实现的图类
template <typename T, typename E>struct Edge{		//边结点的定义
	int dest;										//边的另一顶点位置
	E cost;											//边上的权值
	Edge<T,E> *link;								//下一条边链指针
	Edge() {}										//构造函数
	Edge(int num, E weight){						//构造函数	
		dest = num;
		cost = weight;
		link = NULL;
	}
	bool operator != (Edge<T,E> &R)const{			//判边不等否。#只能用于同一行的单链表中
		return (dest != R.dest);
	}	
};

//顶点的定义
template <typename T, typename E>struct Vertex{
	T data;					//顶点的名字
	Edge<T,E> *adj;			//边链表的头指针
};

template <typename T, typename E>class Graphlnk : public Graph<T,E>{			//图的类定义
public:
	Graphlnk(int sz = DefaultVertices);	//构造函数
	~Graphlnk();						//析构函数
	T getValue(int i){	//返回该邻接顶点的编号，若不存在则返回0		//取位置为i的顶点中的值	
		return (i >= 0 && i < NumberOfVertices()) ? NodeTable[i].data : 0;
	}

	E getWeight(int v1, int v2);						//返回边(v1,v2)上的权值
	bool insertVertex(const T& vertex);					//在图中插入一个顶点vertex
	bool removeVertex(int v);							//在图中删除一个顶点v
	bool insertEdge(int v1, int v2, E weight);			//在图中插入一条边(v1,v2)
														//接受一个参数，表示插入顶点的值，返回true表示插入成功

	bool removeEdge(int v1, int v2);					//在图中删除一条边(v1,v2)
	int getFirstNeighbor(int v);						//取顶点v的第一个邻接顶点
														//返回第一个邻接定点的编号，若不存在或参数不合理则返回-1

	int getNextNeighbor(int v, int w);					//取v的邻接顶点w的下一邻接顶点

	int getVertexPos(const T &vertex){					//给出顶点vertex在图中的位置	
		for (int i = 0; i < numVertices; i++){
			if (NodeTable[i].data == vertex){
				return i;
			}
		}
		return -1; 
	}
private:
	Vertex<T,E> *NodeTable;								//顶点表 (各边链表的头结点)
};

//-----------------------------------------------------------------------------------------------------
//构造函数：建立一个空的邻接表
template <typename T, typename E>Graphlnk<T,E>::Graphlnk(int sz):Graph<T,E>(sz){
	NodeTable = new Vertex<T,E>[maxVertices];		//创建顶点表数组
	assert(NodeTable);
	for (int i = 0; i < maxVertices; i++){
		NodeTable[i].adj = NULL;
	}
}

//析构函数：删除一个邻接表
template <typename T, typename E>Graphlnk<T,E>::~Graphlnk(){				
	for (int i = 0; i < numVertices; i++ ){		//删除各边链表中的结点	
		Edge<T,E> *p = NodeTable[i].adj; 		//找到其对应边链表的首结点
		while (p != NULL){						//不断地删除第一个结点		
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	} 
	delete []NodeTable;  			//删除顶点表数组
}

//函数返回边(v1,v2)上的权值, 若该边不在图中, 则函数返回权值0。
template <typename T, typename E>E Graphlnk<T,E>::getWeight(int v1, int v2){
	if (v1 != -1 && v2 != -1){
		Edge<T,E> *p = NodeTable[v1].adj;			//V1的第一条关联的边
		while (p != NULL && p->dest != v2){			//寻找邻接顶点v2		
			p = p->link;
		}
		if (p != NULL){
			return p->cost;				//找到此边, 返回权值
		}
	}
	return 0;										//边(v1,v2)不存在
}

template <typename T, typename E>bool Graphlnk<T,E>::insertVertex(const T& vertex){
	//在图的顶点表中插入一个新顶点vertex。若插入成功，函数返回true, 否则返回false。
	if (numVertices == maxVertices){	//顶点表满, 不能插入	
		return false;
	}
	NodeTable[numVertices].data = vertex;			//插入在表的最后
	numVertices++;
	return true;
}

//在带权图中插入一条边(v1,v2), 
//若此边存在或参数不合理，函数返回false, 否则返回true。
template <typename T, typename E>bool Graphlnk<T,E>::insertEdge(int v1, int v2, E weight){
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices){
		Edge<T,E> *q, *p = NodeTable[v1].adj;		//v1对应的边链表头指针
		while (p != NULL && p->dest != v2){ 		//寻找邻接顶点v2		
			p = p->link;
		}
		if (p != NULL){				//找到此边, 不插入		
			return false;
		}
		p = new Edge<T,E>;			//否则, 创建新结点
		q = new Edge<T,E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj; 				//链入v1边链表
		NodeTable[v1].adj = p;
		
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj; 				//链入v2边链表
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
template <typename T, typename E>int Graphlnk<T,E>::getFirstNeighbor(int v){
	if (v != -1){									//顶点v存在	
		Edge<T,E> *p = NodeTable[v].adj;			//对应边链表第一个边结点
		if (p != NULL){								//存在, 返回第一个邻接顶点		
			return p->dest;
		}
	}
	return -1;										//第一个邻接顶点不存在
}

//给出顶点v的邻接顶点w的下一个邻接顶点的位置, 
//若没有下一个邻接顶点, 则函数返回-1。
template <class T,class E>int Graphlnk<T,E>::getNextNeighbor(int v, int w){
	if (v != -1){									//顶点v存在	
		Edge<T,E> *p = NodeTable[v].adj;			//对应边链表第一个边结点
		while (p != NULL && p->dest != w){			//寻找邻接顶点w		
			p = p->link;
		}
		if (p != NULL && p->link != NULL){
			return p->link->dest; 					//返回下一个邻接顶点
		}
	}
	return -1; 										//下一邻接顶点不存在
}

//在图中删除一条边(v1, v2)
template <typename T, typename E>bool Graphlnk<T,E>::removeEdge(int v1, int v2){
	if (v1!= -1 && v2 != -1){
		Edge<T,E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while (p != NULL && p->dest != v2){	 			//v1对应边链表中找被删边		
			q = p;
			p = p->link;
		}
		if (p != NULL){									//找到被删边结点		
			if (p == s){
				NodeTable[v1].adj = p->link;			//该结点是边链表首结点
			}
			else{										//不是, 重新链接			
				q->link = p->link;
			}
			delete p;
		}
		else{											//没有找到被删边结点		
			return false;
		}
		p = NodeTable[v2].adj;							//v2对应边链表中删除
		q = NULL, s = p;
		while (p->dest != v1){							//寻找被删边结点		
			q = p;
			p = p->link;
		}
		if (p == s){									//该结点是边链表首结点
		
			NodeTable[v2].adj = p->link;
		}
		else{
			q->link = p->link;							//不是, 重新链接
		}
		delete p; 
		numEdges--;
		return true;
	}
	return false;										//没有找到结点
}

template <typename T, typename E>bool Graphlnk<T,E>::removeVertex(int v){
	//在图中删除一个指定顶点v, v是顶点号。若删除成功, 函数返回true, 否则返回false。
	if (numVertices == 1 || v < 0 || v >= numVertices){
		return false;
	}
	//表空或顶点号超出范围
	Edge<T,E> *p, *s,*t;  int k;
	while (NodeTable[v].adj != NULL){				//删除第v个边链表中所有结点
		p = NodeTable[v].adj;  k = p->dest;			//取邻接顶点k
		s = NodeTable[k].adj;  t = NULL;			//找对称存放的边结点
		while (s != NULL && s->dest != v){
			t = s;  s = s->link;
		}
		if (s != NULL){								//删除对称存放的边结点		
			if (t == NULL){
				NodeTable[k].adj = s->link;
			}
			else{
				t->link = s->link;
			}
			delete s;
		}
		NodeTable[v].adj = p->link;					//清除顶点v的边链表结点
		delete p;
		numEdges--;									//与顶点v相关联的边数减一
	}
	numVertices--;									//图的顶点个数减1
	NodeTable[v].data = NodeTable[numVertices].data;//填补#用最后一个顶点来代替
	NodeTable[v].adj = NodeTable[numVertices].adj;
	p = NodeTable[v].adj;
	while (p != NULL){								//用来顶替的顶点下标变了，对应边的表达要改变
		s = NodeTable[p->dest].adj;
		while (s!= NULL){
			if (s->dest == numVertices){
				s->dest = v;//修改对应边顶点的下标
				break;
			}
			else{
				s = s->link;
			}
		}
	}
	return true;
}
#endif
