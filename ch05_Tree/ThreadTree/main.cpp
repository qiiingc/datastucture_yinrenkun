#include <iostream>
using namespace std;
#define eptmark '$'
#include "ThreadTree.h"
#include "ThreadTree.cpp"
template<class T>
void visit(ThreadNode<T> *p) {
	cout << p -> data << ' ';
}

int main(){
	ThreadNode<char> *p;
	cout<<"+--------------------------------------------------+"<<endl;
	cout<<"#1 Input the binarytree : "<<endl;
	ThreadTree<char> tree;
	tree.InitThreadTree();
	cout <<"+-------------------------------------------------+" << endl;
	cout << "#2 Create the ThreadTree :" << endl;
	tree.createInThread();
	cout << "#3 Test the PreOrder funcion : " << endl;
	tree.PreOrder(visit);
	cout << endl;
	cout <<"+-------------------------------------------------+" << endl;
	cout << "#4 Test the PostOrder funcion : " << endl;
	tree.PostOrder(visit);
	cout << endl;
	cout <<"+-------------------------------------------------+" << endl;
	cout << "#6 Test the InOrder funcion : " << endl;
	tree.InOrder(visit);
	cout << endl;
	cout <<"+-------------------------------------------------+" << endl;
	cout << "#6 Test the Search function : " << endl;
	cout<<"Please input a char to search : "<<endl;
	char ch;
	cin >> ch;
	if(tree.FindTh(ch)) cout<<tree.getCurrent()->data<<endl;
	else cout<<'!'<<endl;
	cout << "search the first node in inorder sequence according to the selected root" << endl;
	cout << tree.First(tree.getCurrent())->data << endl;
	cout << "search the last node in inorder sequence according to the selected root" << endl;
	cout << tree.Last(tree.getCurrent())->data << endl;
	cout << "search the next node in inorder sequence according to the selected root" << endl;
	p=tree.Next(tree.getCurrent());
	if(p) cout <<p->data << endl;
	else cout<<'!'<<endl;
	cout << "search the Prior node in inorder sequence according to the selected root" << endl;
	p=tree.Prior(tree.getCurrent());
	if(p) cout <<p->data << endl;
	else cout<<'!'<<endl;
	return 0;
}
