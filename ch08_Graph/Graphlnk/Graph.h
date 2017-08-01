#ifndef GRAPH_H
#define GRAPH_H
#include "MinSpanTree.h"
#include "MinHeap.h"
#include "UFSets.h"
#include "SeqQueue.h"
#include "Tree.h"
const int maxWeight = 100000;

// 图的抽象基类定义#有权无向图
// T为顶点的类型；E为边权值的类型，一般应为某一整数类型。
template <typename T, typename E>class Graph{
public:
	Graph(int sz){
		maxVertices = sz;
		numVertices = 0;
		numEdges = 0;
	}
	virtual ~Graph(){};
	bool GraphEmpty() const{				//判图空否	
		return (numEdges == 0);
	}	
	bool GraphFull() const{					//判图满否 	
		return (numVertices == maxVertices || 
			numEdges == maxVertices*(maxVertices-1)/2);//无向图，有向图不除以2
	}
	int NumberOfVertices(){				//返回当前顶点数	
		return numVertices;
	}
	int NumberOfEdges(){					//返回当前边数	
		return numEdges;
	}
	void DFS();						    //深度优先遍历图，输出所有的连通分量
	void BFS();						    //广度优先遍历图，输出所有的连通分量
	void DFSTree(Tree<T> &tree);		//立以左子女-右兄弟链表表示的DFS生成森林。
	void Components();					//利用深度优先搜索求非连通图的连通分量的算法
	void Kruskal(MinSpanTree<T,E> &MST);//最小生成树
	void Prim(MinSpanTree<T,E> &MST);
	
	friend istream& operator >> (istream &in, Graph<T,E> &G){
		int i, j, k, n, m;
		T e1, e2;
		E weight;
		in >> n >> m;				//输入顶点数与边数
		for (i = 0; i < n; i++){	//依次输入顶点值
			in >> e1;
			G.insertVertex(e1);
		}
		i = 0;
		while (i < m){
			assert(in >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
			j = G.getVertexPos(e1);				//取对应顶点下标
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1){			//取对应顶点不存在
				cout << "Input error!\n";
			}
			else{
				G.insertEdge(j, k, weight);		//由顶点下标和权值插入边
				i++;
			}
		}
		return in;
	}
	friend ostream& operator << (ostream &out, Graph<T,E> &G){
		int i, j, n, m;
		T e1, e2;
		E weight;
		n = G.NumberOfVertices();		//顶点数与边数
		m = G.NumberOfEdges();
		out << "Number of Vertices: " << n << endl;
		out << "Number of Edges: " << m << endl;
		out << "The edges in the graph are:\n";
		for (i = 0; i < n; i++){
			for (j = i + 1; j < n; j++){
				weight = G.getWeight(i, j);
				if (weight > 0 && weight < maxWeight){
					e1 = G.getValue(i);	//由下标取得顶点值
					e2 = G.getValue(j);
					out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
				}
			}
		}
		return out;
	}

	// 图的子类必须实现的一些接口
	virtual T getValue(int i) = 0;							//取位置为i的顶点中的值
	virtual E getWeight(int v1, int v2) = 0;				//返回边(v1,v2)上的权值
	virtual bool insertVertex(const T &vertex) = 0;			//在图中插入一个顶点vertex
	virtual bool removeVertex(int v) = 0;					//在图中删除一个顶点v
	virtual bool insertEdge(int v1, int v2, E weight) = 0;	//插入权值为weight的边(v1,v2)
	virtual bool removeEdge(int v1, int v2) = 0;			//删除边(v1,v2)
	virtual int getFirstNeighbor(int v) = 0;				//取顶点v的第一个邻接顶点
	virtual int getNextNeighbor(int v, int w) = 0;			//取v的邻接顶点w的下一邻接顶点
	virtual int getVertexPos(const T &vertex) = 0;			//给出顶点vertex在图中的位置
protected:
	int maxVertices;			//图中最大顶点数
	int numEdges;				//当前边数
	int numVertices;			//当前顶点数
	void DFS(int v, bool visited[]);					   //深度优先遍历图，子过程
	void DFSTree(int v, bool visited[], TreeNode<T> *& subTree);
};


//深度优先遍历图，输出所有的连通分量
template<typename T, typename E> void Graph<T,E>::DFS(){
	int i, n = NumberOfVertices();		//取图中顶点个数
	bool *visited = new bool[n]; 		//创建辅助数组
	for (i = 0; i < n; i++){			//辅助数组visited初始化	
		visited[i] = false;
	}
	for(i=0;i<n;i++){					//#从每个顶点开始，各做一次遍历。
		if(!visited[i]){				//#借助辅助数组，上一趟遍历已访问过的各顶点不会作为新起点。所以输出了所有连通分量，不会重复。
			DFS(i, visited); 			//从顶点0开始深度优先搜索
			cout<<endl;
		}
	}
	delete [] visited;					//释放visited
}

//从顶点位置v出发, 以深度优先的次序访问所有可读入的尚未访问过的顶点。
//算法中用到一个辅助数组visited, 对已访问过的顶点作访问标记。
template<typename T, typename E>void Graph<T,E>::DFS(int v, bool visited[]){
	cout << getValue(v) << ' ';			//访问顶点v
	visited[v] = true;	 				//顶点v作访问标记
	int w = getFirstNeighbor(v); 		//找顶点v的第一个邻接顶点w
	while (w != -1){					//若邻接顶点w存在。#注意因为邻接顶点数目不定，使用循环语句，与树相同，与二叉树不同	
		if (visited[w] == false){		//若w未访问过, 递归访问顶点w		
			DFS(w, visited);
		}
		w = getNextNeighbor(v, w);		//取v排在w后的下一个邻接顶点
	}
}

//广度优先遍历图，输出所有的连通分量
template <typename T, typename E>void Graph<T,E>::BFS(){
	int i,v, w, n = NumberOfVertices();		//图中顶点个数
	bool *visited = new bool[n];	
	for (i = 0; i < n; i++){
		visited[i] = false;
	}
	SeqQueue<int> Q;
	for (i = 0; i < n; i++){	//#从每个顶点开始，各做一次遍历。
		if (visited[i] == true){//#借助辅助数组，上一趟遍历已访问过的各顶点不会作为新起点。所以输出了所有连通分量，不会重复。
			continue;
		}
		cout << getValue(i) << ' ';				//访问顶点v
		visited[i] = true;						//做已访问标记
		Q.EnQueue(i);							//顶点进队列, 实现分层访问
		while (!Q.IsEmpty()){					//循环, 访问所有结点		
			Q.DeQueue(v/*i*/);					//不能随意改变控制变量i
			w = getFirstNeighbor(v/*i*/);			//第一个邻接顶点
			while (w != -1){						//若邻接顶点w存在			
				if (!visited[w]){				//若未访问过				
					cout << getValue(w) << ' ';	//访问
					visited[w] = true; 		
					Q.EnQueue(w);				//顶点w进队列
				}
				w = getNextNeighbor(v/*i*/, w);		//找顶点i的下一个邻接顶点
			}
		}//外层循环，判队列空否
		cout << endl;
	}
    delete [] visited;
}

//利用深度优先搜索求非连通图的连通分量的算法
template<typename T, typename E> void Graph<T,E>::Components(){
	int i, n = NumberOfVertices();		//取图中顶点个数
	bool *visited = new bool[n]; 		//创建辅助数组
	for (i = 0; i < n; i++){				//辅助数组visited初始化	
		visited[i] = false;
	}
	int j=1;
	for(i=0;i<n;i++){
		if(!visited[i]){
			cout << "Component " << j << ":" << endl;
			DFS(i, visited); 			//从顶点0开始深度优先搜索
			j++;
			cout << endl;
		}
	}
	delete [] visited;					//释放visited
}

//从图的第一个顶点出发，深度优先遍历图，
//建立以左子女-右兄弟链表表示的DFS生成森林。
template<typename T, typename E> void Graph<T,E>::DFSTree(Tree<T> &tree){
	TreeNode<T> *p, *q;
	int v, n = NumberOfVertices();		//取图中顶点个数
	bool *visited = new bool[n]; 		//创建辅助数组
	for (v = 0; v < n; v++){			//辅助数组visited初始化	
		visited[v] = false;
	}
	for(v = 0; v < n; v++){				//#从每个顶点开始，各做一次遍历。
		if(!visited[v]){				//#借助辅助数组，上一趟遍历已访问过的各顶点不会作为新起点。所以输出了所有连通分量，不会重复。
			p = new TreeNode<T>(getValue(v));
			if (!tree.getRoot()){
				tree.setRoot(p);
			}
			else{
				q->nextSibling = p;
			}
			q = p;
			DFSTree(v, visited, p); 	//从顶点0开始深度优先搜索
		}
	}
	delete [] visited;					//释放visited
}

//从图的顶点v出发，以深度优先次序遍历图，建立以subTree为根的生成树；
//根结点subTree已在上层算法中创建。
//算法中用到一个辅助数组visited, 对已访问过的顶点作访问标记。
template<typename T, typename E>void Graph<T,E>::DFSTree(int v, bool visited[], TreeNode<T> *& subTree){
	bool first = true;
	visited[v] = true;	 				//顶点v作访问标记
	TreeNode<T> *p, *q;
	int w = getFirstNeighbor(v); 		//找顶点v的第一个邻接顶点w
	while (w != -1){						//若邻接顶点w存在	
		if (visited[w] == false){		//若w未访问过, 递归访问顶点w		
			p = new TreeNode<T>(getValue(w));
			if (first){
				subTree->firstChild = p;//第一个邻接顶点作为左长子女
				first = false;
			}
			else{
				q->nextSibling = p;//其余邻接顶点作为右兄弟
			}
			q = p;
			DFSTree(w, visited, q);
		}
		w = getNextNeighbor(v, w);		//取v排在w后的下一个邻接顶点
	}
}

// 求最小生成树
template <typename T, typename E>void Graph<T,E>::Kruskal(MinSpanTree<T,E> &MST){
	MSTEdgeNode<T,E> ed;				//边结点辅助单元
	int u, v, count;
	int n = NumberOfVertices();			//顶点数
	int m = NumberOfEdges();			//边数
	MinHeap<E,MSTEdgeNode<T,E> > H(m);	//最小堆,关键码类型为E
	UFSets F(n);						//并查集
	for (u = 0; u < n; u++){
		for (v = u+1; v < n; v++){
			if (getWeight(u,v) != 0){//#对应边存在
				ed.tail = u;
				ed.head = v;
				ed.key = getWeight(u, v);
				H.Insert(ed);			//插入堆
			}
		}
	}
	count = 1;							//最小生成树加入边数计数
	while (count < n){					//反复执行, 取n-1条边	
		H.RemoveMin(ed);				//从最小堆中退出具最小权值的边ed
		u = F.Find(ed.tail);
		v = F.Find(ed.head);			//取两顶点所在集合的根u与v
		if (u != v){						//不是同一集合, 说明不连通		
			F.SimpleUnion(u, v);		//合并, 连通它们
			MST.Insert(ed);				//该边存入最小生成树
			count++;
		}
	} 
}

template <typename T, typename E>void Graph<T,E>::Prim(MinSpanTree<T, E> &MST){
	MSTEdgeNode<T, E> ed; //边结点辅助单元
	int i, u, v, count;				
	int n = NumberOfVertices();	  //顶点数	
	int m = NumberOfEdges();	  //边数
//	int u = getVertexPos(u0);		  //起始顶点号
	u = 0;
	MinHeap <E,MSTEdgeNode<T, E> > H(m);  //最小堆
	bool *Vmst = new bool[n];   //最小生成树顶点集合
	for (i = 0; i < n; i++) Vmst[i] = false;	
	Vmst[u] = true;		        //u 加入生成树
	count = 1;
	do{			        //迭代	
		v = getFirstNeighbor(u); 
		while (v != -1){	 //检测u所有邻接顶点		
			if (!Vmst[v]){	        //v不在mst中			
				ed.tail = u;  ed.head = v;
				ed.key = getWeight(u, v);
				H.Insert(ed);	        //(u,v)加入堆
			}     //堆中存所有u在mst中, v不在mst中的边
			v = getNextNeighbor(u, v); 
		} 
		while (!H.IsEmpty() && count < n)		{ 
			H.RemoveMin(ed);	         //选堆中具最小权的边
			if (!Vmst[ed.head])			{
				MST.Insert(ed);       //加入最小生成树
				u = ed.head;
				Vmst[u] = true;//u加入生成树顶点集合
				count++;  
				break;
			}
		}
	} while (count < n);
}


//////////////////////////////////////////////////////////////////

//Dijkstra
//Graph是一个带权有向图。
//dist[j], 0≤j<n, 是当前求到的从顶点v到顶点j的最短路径长度,
//path[j], 0≤j<n, 存放求到的最短路径。
template <typename T, typename E>void ShortestPath(Graph<T,E> &G, T v, E dist[], int path[]){
    int n = G.NumberOfVertices();
    bool *S = new bool[n]; 	   //最短路径顶点集
    int i, j, k;  E w, min;
    for (i = 0; i < n; i++)	{
	    dist[i] = G.getWeight(v, i);
        S[i] = false;
        if (i != v && dist[i] < maxValue) path[i] = v;
        else path[i] = -1;
    }
    S[v] = true;  dist[v] = 0;     	//顶点v加入顶点集合
    for (i = 0; i < n-1; i++){       //求解各顶点最短路径	
        min = maxValue;
		int u = v; 					//选不在S中具有最短路径的顶点u
        for (j = 0; j < n; j++){			
            if (!S[j] && dist[j] < min){
				u = j;
				min = dist[j];
			}
		}
        S[u] = true;	               	//将顶点u加入集合S
        for (k = 0; k < n; k++){       	//修改		
            w = G.GetWeight(u, k);
            if (!S[k] && w < maxValue && dist[u]+w < dist[k]){ //顶点k未加入S   			            
                dist[k] = dist[u]+w; 
                path[k] = u;     		//修改到k的最短路径
            }    
        }
    }
}

//在有向带权图中有的边具有负的权值。
//从顶点v找到所有其他顶点的最短路径。 
template <typename T, typename E>void Bellman_Ford(Graph<T, E>& G, int v, E dist[], int path[]){
    E w;  int i, k, u, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){        //计算dist1[i]	
        dist[i] = G.getWeight(v, i);
        if (i != v && dist[i] < maxValue){
			path[i] = v;
		}
        else{
			path[i] = -1;
		}
    }
    for (k = 2; k < n; k++){     //计算dist2[i]到distn-1[i]	
        for (u = 0; u < n; u++){
            if (u != v){
                for (i = 0; i < n; i++){
                    w = G.getWeight(i, u);
					if (w > 0 && w < maxValue && dist[u] > dist[i]+w){
                        dist[u] = dist[i]+w;
                        path[u] = i;
                    }
                }
			}
		}
	}
}

//a[i][j]是顶点i和j之间的最短路径长度。
//path[i][j]是相应路径上顶点j的前一顶点的顶点号。
template <typename T, typename E>void Floyd(Graph<T,E> &G, E **a, int **path){
	int i, j, k, n = G.NumberOfVertices();
    for (i = 0; i < n; i++){    	//矩阵a与path初始化	
        for (j = 0; j < n; j++){
            a[i][j] = G.getWeight (i,j);
			if (i != j && a[i][j] < maxValue){
				path[i][j] = i;
			}
			else{
				path[i][j] = 0;
			}
        }
	}
    for (k = 0; k < n; k++){   //针对每一个k, 产生a(k)及path(k)			
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
				if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = path[k][j]; 
                    //缩短路径长度, 绕过 k 到 j
                }
			}
		}
	}
}

// 通过path数组求最短路径的函数
#endif
