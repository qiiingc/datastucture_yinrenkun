#include "AString.h"
#include <iostream>
using namespace std;

int main(){
	cout << "Please input a string : ";
	AString str;
	cin >> str;
	cout << "The length of the string is: " << str.Length() << endl;

	cout << "\n1. Test the substr(int pos, int len): \n";
	int pos, len;
	cout << "Input the pos and the len: ";
	cin >> pos >> len;
	AString sub = str.substr(pos, len);
	cout << "The substring is: " << sub << endl;

	cout << "\n2. Test the operator()(int pos, int len): \n";
	cout << "Input the pos and the len: ";
	cin >> pos >> len;
	sub = str(pos, len);
	cout << "The substring is: " << sub << endl;
	
	cout << "\n3. Test the operator[](int i): \n";
	cout << "Input the positon i:";
	int i;
	cin >> i;
	cout << "The char in position " << i << " is: " << str[i] << endl;

	AString str2;
	cout << "Input a new string:\n";
	cin >> str2;

	cout << "\n4. Test the operator ==\n";
	cout << "The two strings " << "\"" << str << "\" and \"" << str2 << "\"";
	if (str == str2)  cout << " is Equal!\n";
	else	cout << " is not Equal!\n";

	cout << "\n5. Test the operator !=\n";
	cout << "The two strings " << "\"" << str << "\" and \"" << str2 << "\"";
	if (str != str2)	cout << " is not Equal!\n";
	else	cout << " is Equal!\n";
	
	cout << "\n6. Test the operator +\n";
	AString tmp = str + str2;
	cout << "\"" << str << "\" + \"" << str2 
		<< "\" = \"" << tmp << "\"\n";
	
	cout << "\n7. Test the operator +=\n";
	cout << "\"" << str << "\" += \"" << str2 
		<< "\", then the result is: \n";
	str += str2;
	cout << str << endl;

	cout << "\n8. Test int fastFind(AString& pat, int k, int *next):\n";
	cout << "Input a string and a substring: " << endl;
	cin >> str >> str2;
	int *next = new int[str2.Length()+1];//没有+1使用中出界，析构时有问题
	str2.getNext(next);
	int f = str.fastFind(str2, 0, next);
	delete [] next;
	if(f == -1)	cout << "Not Find!" << endl;
	else	cout << "Find,the position is : " << f << endl;
	
	cout << "\n9. Test the replace(AString &t, AString &v):\n";
	AString s("aabbabcbaabaaacbab");
	AString t("bab");
	AString v("abdc");
	cout << "The initial string is: " << s << endl;
	cout << "The string t is: " << t << endl;
	cout << "The string v is: " << v << endl;
	s.replace(t, v);
	cout << "After s.replace(t, v), the string is: " << s << endl;

	return 0;
}
