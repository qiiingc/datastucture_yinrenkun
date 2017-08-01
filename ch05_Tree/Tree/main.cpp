#include "Tree.h"
#include <fstream>
#include <cassert>
#include <iomanip>
using namespace std;

void visit(TreeNode<int> * n){
	cout << setw(4) << n->data;
}

int main(){
	Tree<int> tree(0);                   //ÊäÈë½áÊø·ûÎª0
	cout << "The Intended text of the tree is:\n";
	ifstream fin("data.txt");
	assert(fin);
	fin >> tree;
	fin.close();
	cout << tree;
	tree.Output();
	cout << "\nThe preorder of the tree is:\n";
	tree.PreOrder(visit);
	cout << "\nThe levelorder of the tree is:\n";
	tree.LevelOrder(visit);
	cout << "\nThe postorder of the tree is:\n";
	tree.PostOrder(visit);

	cout << "\n\nPress enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
