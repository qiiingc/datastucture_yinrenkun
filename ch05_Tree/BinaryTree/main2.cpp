#include "BinaryTree.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

void visit(BinTreeNode<int> *t)
{
	cout << t->data << "\t";
}

int main()
{
	cout << "Create a complete Binary tree from an array:\n";
	cout << "Input the nodes num in the binary tree: ";
	unsigned num;
	assert(cin >> num);
	int *CBT = new int[num];
	cout << "\nThe data in the array is:\n";
	for (unsigned i = 0; i < num; i++)
	{
		CBT[i] = i+1;
		cout << setw(4) << i+1;
	}
	cout << endl;
	BinaryTree<int> binTree;
	binTree.CreateCompBinTree(CBT, num, binTree);
	binTree.Output();
//	cout<<"The content in test.txt is : "<<"1 2 3 0 0 4 5 0 6 0 0 7 0 0 8 0 9 0 0"<<endl;
	cout<<"Read the txt and create the BinaryTree..."<<endl;
	void (* v)(BinTreeNode<int> *) = visit;
	BinaryTree<int> tree(0);
	ifstream fin("test.txt");
	if (!fin) {
		cerr<<"Can't open!"<<endl;
		exit(1);
	}
	fin>>tree;
	cout<<"Create Succeed!"<<endl;
	ofstream fout("out2.txt");
	if (!fout)
	{
		cerr<<"Can't open!"<<endl;
		exit(1);
	}
	tree.Output(fout);
	/*
	cout << "Create a complete binary tree\n" << endl;
	unsigned int num;
	cout << "Please enter the number of the nodes: ";
	assert(cin >> num);
	int *CBT = new int[num];
	cout << "Please enter the nodes:\n";
	for (unsigned int i = 0; i < num; i++)
	{
		assert(cin >> CBT[i]);
	}
	BinaryTree<int> tree;
	tree.CreateCompBinTree(CBT, num, tree);
	delete []CBT;
	cout << "Create succeed!" << endl;

	void (*v)(BinTreeNode<int> *) = visit;
	cout << "#1 Test the PreOrder,InOrder,PostOrder,levelOredr funcion:"<<endl;
	cout << "\nPreOrder:\t";
	tree.PreOrder(v);
	cout<< "\nInOrder:\t";
	tree.InOrder(v);
	cout<< "\nPostOrder:\t";
	tree.PostOrder(v);

	ofstream fout("out.txt");
	if (!fout)
	{
		cerr<<"Can't open!"<<endl;
		exit(1);
	}
	fout << tree;
	fout << endl;
	tree.printBinTree(fout);
	fout.close();*/
	return 0;
}