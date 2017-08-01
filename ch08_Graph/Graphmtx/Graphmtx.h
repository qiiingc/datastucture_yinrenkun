#ifndef Graphmtx_H
#define Graphmtx_H
#include "Graph.h"
#include <iostream>
using namespace std;

extern const int maxWeight;
const int maxSize = 100;

//邻接矩阵存储的图的类定义（无向图）
template <class T, class E>
class Graphmtx : public Graph<T,E>					//图的邻接矩阵类定义
{
public:
	Graphmtx(int sz = maxSize);						//构造函数
	~Graphmtx()										//析构函数
	{
		delete []VertexList;
		delete []Edge;
	}

	T getValue(int i)								//取顶点i的值, i不合理返回0
	{
		return i >= 0 && i < numVertices ? VertexList[i] : 0;
	}

	E getWeight(int v1, int v2) 					//取边(v1,v2)上的权值，若边不合理，则返回0
	{
		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}

	int getFirstNeighbor(int v);					//取顶点v的第一个邻接顶点
													//返回该邻接顶点的编号，若不存在则返回-1

	int getNextNeighbor(int v, int w);				//取v的邻接顶点w的下一邻接顶点
													//返回下一个邻接定点的编号，若不存在或参数不合理则返回-1

	bool insertVertex(const T &vertex);				//插入顶点vertex
													//接受一个参数，表示插入顶点的值，返回true表示插入成功

	bool insertEdge(int v1, int v2, E cost);		//插入边(v1, v2),权值为cost
													//返回true表示插入成功

	bool removeVertex(int v);						//删去顶点v和所有与它相关联的边
													//返回true表示删除成功

	bool removeEdge(int v1, int v2);				//在图中删去边(v1,v2)
													//返回true表示删除成功

	int getVertexPos(const T &vertex)				//给出顶点vertex在图中的位置，若不存在则返回-1
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (VertexList[i] == vertex)
			{
				return i;
			}
		}
		return -1;
	}

private:
	T *VertexList; 								   //顶点表
	E **Edge;									   //邻接矩阵
};

//构造函数
template <class T, class E>
Graphmtx<T,E>::Graphmtx(int sz):Graph<T,E>(sz)
{
	int i, j;
	VertexList = new T[maxVertices];			//创建顶点表数组
	Edge = (int **) new int *[maxVertices];		//创建邻接矩阵数组
	for (i = 0; i < maxVertices; i++)
	{
		Edge[i] = new int[maxVertices];
	}
	for (i = 0; i < maxVertices; i++)			//邻接矩阵初始化
	{
		for (j = 0; j < maxVertices; j++)
		{
			Edge[i][j] = maxWeight;
		}
	}
}

//给出顶点位置为v的第一个邻接顶点的位置, 如果找不到, 则函数返回-1。
template <class T, class E>
int Graphmtx<T,E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
			{
				return col;
			}
		}
	}
	return -1;
}

//给出顶点v的某邻接顶点w的下一个邻接顶点
template <class T, class E>
int Graphmtx<T,E>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w+1; col < numVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
			{
				return col;
			}
		}
	}
	return -1;
}

//插入顶点vertex：
//若顶点表满, 则不插入，返回false；若成功插入，则返回true。
template <class T, class E>
bool Graphmtx<T,E>::insertVertex(const T &vertex)
{
	if (numVertices == maxVertices)
	{
		return false;
	}
	VertexList[numVertices++] = vertex;
	return true;
}

//插入边(v1, v2), 权值为cost
template <class T, class E>
bool Graphmtx<T,E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1 < numVertices && v2 > -1 &&
		v2 < numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost; // 若为有向图，则去掉另一条边
		numEdges++;
		return true;
	}
	else
	{
		return false;
	}
}

//删去顶点v和所有与它相关联的边
template <class T, class E>
bool Graphmtx<T,E>::removeVertex(int v)
{
	if (v < 0 && v >= numVertices)				//v不在图中,不删除
	{
		return false;
	}
	if (numVertices == 1)						//只剩一个顶点,不删除
	{
		return false;
	}
	int i, j;
	VertexList[v] = VertexList[numVertices-1];	//顶点表中删除该结点
	for (i = 0; i < numVertices; i++)			//减去与v相关联边数
	{
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
		{
			numEdges--;
		}
	}
	for (i = 0; i < numVertices; i++)			//用最后一列填补第v列
	{
		Edge[i][v] = Edge[i][numVertices-1];
	}
	numVertices--;								//顶点数减一
	for (j = 0; j < numVertices; j++)			//用最后一行填补第v行
	{
		Edge[v][j] = Edge[numVertices][j];
	}
	return true;
}

//在图中删去边(v1,v2)
template <class T, class E>
bool Graphmtx<T,E>::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && 
		Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else
	{
		return false;
	}
}

#endif
