#include <iostream>
#include "SparseMatrix.h"
#include "SparseMatrix.cpp"
using namespace std;

int main(){
	cout<<"+---------------------------------------------------------------+"<<endl;
	cout<<"#1 Construct the sparseMatrix :"<<endl;
	cout<<"pleae input the number of rows , columns and maxnonzero nodes : "<<endl;
	int r,c,t;
	cin>>r>>c>>t;
	SparseMatrix<int> m(t,r,c);
	cin>>m;
	cout<<"Construct Succeed!"<<endl;
	cout<<"The SparseMatrix you input is :"<<endl;
	cout<<m;
	cout<<"+---------------------------------------------------------------+"<<endl;
	cout<<"#2 Test void Transpose(SparseMatrix<E>& b)"<<endl;
	SparseMatrix<int> m1=m.Transpose();
	cout<<"New matrix is : "<<endl;
	cout<<m1<<endl;
	cout<<"+---------------------------------------------------------------+"<<endl;
	cout<<"#3 Test void FastTranspos(SparseMatrix<E>& b)"<<endl;
	SparseMatrix<int> m2=m.FastTranspos();
	cout<<"New matrix is : "<<endl;
	cout<<m2<<endl;
	cout<<"+---------------------------------------------------------------+"<<endl;
	cout<<"#4 Test SparseMatrix<E> Add(SparseMatrix<E>& b)"<<endl;
	cout<<"Input another matrix :"<<endl;
	cout<<"Rows = "<<m.getRows()<<" , Cols = "<<m.getCols()<<" Input the maxTerms : ";
	cin>>t;
	SparseMatrix<int> m3(t,r,c);
	cin>>m3;
	cout<<"The SparseMatrix you input is :"<<endl;
	cout<<m3;
	SparseMatrix<int> m4=m.Add(m3);
	cout<<"The Result is :"<<endl;
	cout<<m4;
	cout<<"+---------------------------------------------------------------+"<<endl;
	cout<<"#5 Test SparseMatrix<E> Multiply(SparseMatrix<E>& b)"<<endl;
	cout<<"Input another matrix :"<<endl;
	cout<<"Rows = "<<m.getCols()<<" , Cols = "<<m.getRows()<<" Input the maxTerms : ";
	cin>>t;
	SparseMatrix<int> m5(t,c,r);
	cin>>m5;
	cout<<"The SparseMatrix you input is :"<<endl;
	cout<<m5;
	SparseMatrix<int> m6=m.Multiply(m5);
	cout<<"The Result is :"<<endl;
	cout<<m6;
	return 0;
}
