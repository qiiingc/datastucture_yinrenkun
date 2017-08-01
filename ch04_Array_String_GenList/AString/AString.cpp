#include "AString.h"
#include <cstring>
#include <cassert>
#include <iostream>
using namespace std;

AString::AString(int sz){
	maxSize = sz;             //maxsize是可容纳串的最大长度
	ch = new char[maxSize+1]; //为串结束符留1个字节
	assert(ch);
	curLength = 0;            //串当前长度，不含串结束符
	ch[0] = '\0';
}

AString::AString(const char *init){
	int len = strlen(init);
	maxSize = (len > defaultSize)?len:defaultSize;
	ch = new char[maxSize+1];
	assert(ch);
	curLength = len;
	strcpy(ch,init);          //数据结构教学以写程序段为好
}

AString::AString(const AString &ob){
	maxSize = ob.maxSize;
	ch = new char[maxSize+1];
	assert(ch);
	curLength = ob.curLength;
	strcpy(ch, ob.ch);
}

AString AString::substr(int pos, int len){
	//从串中第 pos 个位置起连续提取 len 个字符形成子串返回
	AString temp(maxSize);
	if (pos >= 0 && pos+len-1 < maxSize && len > 0){
		if (pos+len-1 >= curLength){
			len = curLength - pos; //改为子串可能达到的最大串长
		}
		temp.curLength = len;
		for (int i = 0, j = pos; i < len; i++, j++){
			temp.ch[i] = ch[j];
		}
		temp.ch[len] = '\0';
	}
	return temp;
}

AString AString::operator () (int pos, int len){
	//从串中第 pos 个位置起连续提取 len 个字符形成子串返回
	AString temp(maxSize);
	if (pos >= 0 && pos+len-1 < maxSize && len > 0){
		if (pos+len-1 >= curLength){
			len = curLength - pos;
		}
		temp.curLength = len;
		for (int i = 0, j = pos; i < len; i++, j++){
			temp.ch[i] = ch[j];
		}
		temp.ch[len] = '\0';
	}
	return temp;
}

AString& AString::operator = (const AString &ob){
	if (&ob != this){
		delete []ch;              //先清后建
		maxSize=ob.maxSize;
		ch = new char[maxSize+1];
		assert(ch);
		curLength = ob.curLength;
		strcpy(ch,ob.ch);
	}
	else	cout << "字符串自身赋值出错!\n";		
	return *this;
}

char& AString::operator [] (int i){	//下标运算符重载：取当前串*this的第i个字符
	assert(i >= 0 && i < curLength);
	return ch[i];
}

AString AString::operator + (const AString& ob){
	int n = curLength + ob.curLength;
	int m = (maxSize >= n) ? maxSize : n;
	AString temp(m);

	temp.curLength = n;
	strcpy(temp.ch, ch);
	strcat(temp.ch, ob.ch);
	return temp;
}

AString& AString::operator += (const AString& ob){
	char *temp = ch;             //*this字符串由temp保留
	int n = curLength + ob.curLength;
	int m = (maxSize >= n) ? maxSize : n;
	
	ch = new char[m+1];
	assert(ch);
	maxSize = m;
	curLength = n;
	strcpy(ch, temp);
	strcat(ch, ob.ch);
	delete []temp;
	return *this;
}

int AString::Find(AString &pat, int k)const{//从第K个（下标）字符开始
	int i, j, n = curLength, m = pat.curLength;
	for (i = k; i <= n-m; i++){ 
		for (j = 0; j < m; j++){
			if (ch[i+j] != pat.ch[j]) break;   //本次失配			
		}
		if (j == m)	return i;	//pat为空或pat扫描完, 匹配成功
	}	
	return -1;	 //在*this中找不到它
}

int AString::fastFind(AString &pat, int k, int next[])const{
	int posP = 0, posT = k;
	int lengthP = pat.curLength;	//模式串长度
	int lengthT = curLength;		//目标串长度
	while (posP < lengthP && posT < lengthT){	//对两串扫描	
		if (posP == -1 || pat.ch[posP] == ch[posT]){//对应字符匹配
			posP++;
			posT++;
		}
		else	posP = next[posP];   //求pat下趟比较位置
	}		
	if (posP < lengthP) return -1;	//匹配失败	
	else  return posT-lengthP;	//匹配成功
}

void AString::getNext(int next[]){
	int j = 0, k = -1, lengthP = curLength;
	next[0] = -1;
	while (j < lengthP){
		if ( k == -1 || ch[j] == ch[k])	{
			j++;
			k++;
			next[j] = k;
		}
		else	k = next[k];
	}
}

// 字符串替换函数：
// 若t是当前串的子串，则用v替换t在当前串中的所有出现；
// 若t不是当前串的子串，则当前串保持不变。
// 该函数返回当前串的引用。
AString& AString::replace(AString &t, AString &v){
	int *next = new int[t.Length()+1];//没有+1使用中出界，析构时有问题
	t.getNext(next);
	int k = 0, j = 0;
	AString s2;
	while (k <= curLength - t.Length())	{
		j = fastFind(t, k, next);
		if ( j == -1 )	break;
		s2 = s2 + (*this)(k, j-k) + v;
		k = j + t.Length();
	}
	s2 += (*this)(k, curLength-k);
	*this = s2;
	delete []next;
	return *this;
}
