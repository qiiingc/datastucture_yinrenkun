#include "Graph.h"

extern const int maxWeight;
template <class T, class E>
int Centre(Graph<T,E> &G, E &biasDist){
	int i, j, k, n = G.NumberOfVertices();
	E **a = new E*[n];
	for(i = 0 ; i < n; i ++)	{
		a[i] = new E[n];
	}

    for (i = 0; i < n; i++){    	//矩阵a与path初始化	
        for (j = 0; j < n; j++)		{
            a[i][j] = G.getWeight (i,j);
        }
	}
    for (k = 0; k < n; k++){   //针对每一个k, 产生a(k)及path(k)			
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
				if (a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    //缩短路径长度, 绕过 k 到 j
                }
			}
		}
	}

	E *bias = new E[n];
	for (j = 0; j < n; j++){
		bias[j] = 0;
		for (i = 0; i < n; i++){
			if (a[i][j] > bias[j] && a[i][j] < maxWeight){
				bias[j] = a[i][j];
			}
		}
	}
	int tmp = 0;
	biasDist = bias[0];
	for (j = 0; j < n; j++){
		if (bias[j] < biasDist){
			biasDist = bias[j];
			tmp = j;
		}
	}
	return tmp;
}
