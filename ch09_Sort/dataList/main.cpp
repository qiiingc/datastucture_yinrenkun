#include "dataList.h"
#include "person.h"
#include <fstream>
using namespace std;

int main(){
	ifstream fin("persons.txt");
	assert(fin);
	dataList<person,long> sc;
	fin >> sc;
	cout << sc;
	return 0;
}
