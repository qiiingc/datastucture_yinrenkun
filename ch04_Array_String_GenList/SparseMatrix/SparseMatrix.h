#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include <cassert>
using namespace std;

const int drows = 6,  dcols = 7, dterms = 9;

template<typename E>
struct Triple		//三元组
{
    int row, col;	//非零元素行号/列号
    E value;		//非零元素的值
    void operator = (Triple<E> &R){
		row = R.row;
		col = R.col;
		value = R.value;
	}
	Triple(int r=-1, int c=-1, E v=0){
		row = r;
		col = c;
		value = v;
	}
};		

template <typename E>class SparseMatrix{//稀疏矩阵定义与教材略有不同
public: 
    SparseMatrix( int mT = dterms, int Rw = drows, int Cl = dcols);
	SparseMatrix(SparseMatrix<E>& x);//有动态分配，必须定义复制构造函数和析构函数
	~SparseMatrix(){
		delete []smArray;
	}
    SparseMatrix<E> Transpose();
    SparseMatrix<E> FastTranspos();
    SparseMatrix<E> Add(SparseMatrix<E> &b);
    SparseMatrix<E> Multiply(SparseMatrix<E> &b);
	int getRows(){
		return Rows;
	}
	int getCols(){
		return Cols;
	}
	friend ostream& operator << (ostream &out, SparseMatrix<E> &M){
		out << "rows = " << M.Rows << endl;
		out << "cols = " << M.Cols << endl;
		out << "Nonzero terms = " << M.Terms << endl;
		for (int i = 0; i < M.Terms; i++)		{
			out << "M[" << M.smArray[i].row << "][" << M.smArray[i].col
				<< "]=" << M.smArray[i].value << endl;
		}
		return out;
	}
	friend istream& operator >> (istream &in, SparseMatrix<E> &M){
		cout<<"pleae input the number of nonzero nodes :";
		cin>>M.Terms;
		cout<<endl;
		for (int i = 0; i < M.Terms; i++){
			cout << "Enter row, column, and value of term:" << i+1 << endl;
			in >> M.smArray[i].row >> M.smArray[i].col>> M.smArray[i].value;
		}
		return in;
	}
	SparseMatrix<E> & operator = (SparseMatrix<E> &x){ //改
		Rows = x.Rows;
		Cols = x.Cols;
		Terms=x.Terms;
		maxTerms =x.maxTerms;
		delete []smArray;                  //先清后建再复制
		smArray = new Triple<E>[maxTerms];
		assert(smArray);
		for(int i = 0; i < x.Terms; i++){
			smArray[i] = x.smArray[i];
		}
		return /*des*/*this;
	}
private:
    int Rows, Cols, Terms;
    Triple<E> *smArray;
	int maxTerms;
};
#endif
