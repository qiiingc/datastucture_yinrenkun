#include "SparseMatrix.h"
#include <iostream>
#include <cassert>
using namespace std;

template <typename E>SparseMatrix<E>::SparseMatrix(int mT, int Rw, int Cl){
    Rows = Rw;
	Cols = Cl;
	Terms=0;         //添加
	maxTerms = mT;   //修改
    smArray = new Triple<E>[maxTerms];//修改
	assert(smArray);
}

template <typename E>SparseMatrix<E>::SparseMatrix(SparseMatrix<E>& x){
    Rows = x.Rows;
	Cols = x.Cols;
	Terms=x.Terms;         //添加
	maxTerms =x.maxTerms;   //修改
    smArray = new Triple<E>[maxTerms];//修改
	assert(smArray);
	int i;
	for(i=0;i<=Terms;i++) smArray[i]=x.smArray[i];
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::Transpose(){
	SparseMatrix<E> B(maxTerms,Cols,Rows);                    //修改
	if (Terms > 0){
		int CurrentB = 0;
		int i, k;
		for (k = 0; k < Cols; k++){       //按列号扫描
			for (i = 0; i < Terms; i++){  //在数组中找列号为k的三元组
				if (smArray[i].col == k){ //这样所得转置矩阵三元组有序
					B.smArray[CurrentB].row = k;	
	                B.smArray[CurrentB].col = smArray[i].row;
	                B.smArray[CurrentB].value=smArray[i].value;	
 	                CurrentB++;
				}
			}
		}
	}
	B.Terms=Terms;
	return B;
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::FastTranspos(){//快速转置
    int *rowSize = new int[Cols];       //行元素数量数组
    int *rowStart = new int[Cols];      //行起始位置数组
	SparseMatrix<E> /*B(Rows,Cols,Terms)*/B(maxTerms,Cols,Rows);
	B.Terms=Terms;
    if (Terms > 0)	{
        int i, j;
        for (i = 0; i < Cols; i++){
			rowSize[i] = 0;
		}
	    for (i = 0; i < Terms; i++){//建立行元素数量数组
			rowSize[smArray[i].col]++; 
		}
        rowStart[0] = 0;	
        for (i = 1; i < Cols; i++){//导出行起始位置数组
			rowStart[i] = rowStart[i-1]+rowSize[i-1];
		}
	    for (i = 0; i < Terms; i++)		{			
			j = rowStart [smArray[i].col];
			B.smArray[j].row = smArray[i].col;
			B.smArray[j].col = smArray[i].row;
			B.smArray[j].value = smArray[i].value;
			rowStart [smArray[i].col]++;//放置一个元素后，对应行起始位置项++，指出该行下一个元素位置		
		}
	}
	B.Terms=Terms;
    delete []rowSize;
	delete []rowStart;
	return B;
}

template <typename E>SparseMatrix<E> SparseMatrix<E>::Add(SparseMatrix<E> &b){
	SparseMatrix<E> result(Terms+b.Terms,Rows,Cols);
	if ( Rows != b.Rows || Cols != b.Cols){//两矩阵规格不一致，不能相加
		cout << "Incompatible matrices" << endl;
		return result;
	}
	int i = 0, j = 0, index_a, index_b; result.Terms = 0;
	while (i < Terms && j < b.Terms){                        //归并算法
		index_a = Cols*smArray[i].row+smArray[i].col;        //等效一维数组下标
		index_b = Cols*b.smArray[j].row+b.smArray[j].col;
		if (index_a < index_b){
			result.smArray[result.Terms] = smArray[i];
			i++;
		}
		else if (index_a > index_b){
			result.smArray[result.Terms] = b.smArray[j];
			j++;
		}
		else{
			result.smArray[result.Terms] = smArray[i];
			result.smArray[result.Terms].value= smArray[i].value + b.smArray[j].value;
			i++; j++;
		}
		result.Terms++;
	}

	for ( ; i < Terms; i ++){
		result.smArray[result.Terms] = smArray[i];
		result.Terms++;
	}
	for ( ; j < b.Terms; j++){
		result.smArray[result.Terms] = b.smArray[j];
		result.Terms++;
	}
	return result;
}

template <typename E> SparseMatrix<E> SparseMatrix<E>::Multiply(SparseMatrix<E> &b){
	SparseMatrix<E> result(Rows*b.Cols/2,Rows, b.Cols);//实用程序可以先分配比较小的空间，以后安需重新分配
	if (Cols != b.Rows)	{
		cout << "Incompatible matrices" << endl;
		return result; 
	}
	int *rowSize = new int[b.Rows];		//矩阵B 各行非零元素个数
	int *rowStart = new int[b.Rows+1];	//矩阵B 各行在三元组开始位置
	E *temp = new E[b.Cols];			//暂存每一行计算结果
	int i, Current, lastInResult, RowA, ColA, ColB;
	for (i = 0; i < b.Rows; i++) rowSize[i] = 0;
	for (i = 0; i < b.Terms; i++) rowSize[b.smArray[i].row]++;
	rowStart[0] = 0;					//B第i 行非零元素开始位置
	for (i = 1; i <= b.Rows; i++)
		rowStart[i] = rowStart[i-1]+rowSize[i-1];
	Current = 0; lastInResult = -1;		//a 扫描指针及result 存指针
	while (Current < Terms){				//生成result 的当前行temp	
		RowA = smArray[Current].row;	//当前行的行号
		for (i = 0; i < b.Cols; i++) temp[i] = 0;
		while (Current < Terms && smArray[Current].row == RowA){//处理该行各元素
			ColA = smArray[Current].col; //矩阵A 当前扫描到元素的列号
			for (i = rowStart[ColA]; i < rowStart[ColA+1]; i++){
				ColB = b.smArray[i].col; //矩阵B 中相乘元素的列号
				temp[ColB] += smArray[Current].value*b.smArray[i].value;
			} //A的RowA 行与B 的ColB 列相乘
			Current++;
		}
		for (i = 0; i < b.Cols; i++){
			if (temp[i] != 0){			//将temp 中的非零元素压缩到result 中去			
				lastInResult++;
				result.smArray[lastInResult].row = RowA;//行号固定
				result.smArray[lastInResult].col = i;//列号对应temp下标
				result.smArray[lastInResult].value = temp[i];//temp元素对应稀疏矩阵元素值
			}
		}
	}
	result.Rows = Rows;
	result.Cols = b.Cols;
	result.Terms = lastInResult+1;
	delete []rowSize;
	delete []rowStart;
	delete []temp;
	return result;
}