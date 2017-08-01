#include "WinnerTree.h"
#include "TournamentSort.h"
#include <fstream>
#include <cassert>
using namespace std;

int main(){
	ifstream fin("data.txt");
	assert(fin);
	int n,i;
	assert(fin >> n);
	int * a = new int[n];
	cout << "There are " << n << " nodes in the file.\n";
	cout << "The value of each node is:\n";
	for( i = 0; i < n; i++){
		fin >> a[i];
		cout << "node[" << i << "]: " << a[i] << endl;
	}
	cout <<"+-------------------------------------------------+"<< endl;
    TournamentSort<int>(a, 0, n-1);
	cout << "The sorted result is : " << endl;
	for( i = 0; i < n; ++i){
		cout << a[i] << endl;
	}
	
	cout << "Press enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}
