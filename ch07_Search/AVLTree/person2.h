#include <string>
#include <cassert>
#include <iomanip>
#include <iostream>
using namespace std;

// person必须包含几个最基本的元素：

class person
{
public:
	long key;
	person(long id = 0, int age = 0, string name = string())
	{
		ID = id;
		Age = age;
		Name = name;
		key = ID;
	}
	person(person &pr)
	{
		ID = pr.ID;
		Age = pr.Age;
		Name = pr.Name;
		key = ID;
	}
	long getKey()
	{
		return key;
	}
	void setKey(long k1)
	{
		key = k1;
	}
	long getID()
	{
		return ID;
	}
	void setID(long id)
	{
		ID = id;
	}
	int getAge()
	{
		return Age;
	}
	void setAge(int age)
	{
		if (age < 0 || age > 150)
		{
			return;
		}
		Age = age;
	}
	string getName()
	{
		return Name;
	}
	void setName(string name)
	{
		Name = name;
	}
	person& operator = (person &pr)
	{
		ID = pr.ID;
		Age = pr.Age;
		Name = pr.Name;
		key = ID;
		return *this;
	}
	person& operator = (long k1)
	{
		ID = k1;
		key = ID;
		return *this;
	}
	person& operator + (long k1)
	{
		ID = ID + k1;
		key = ID;
		return *this;
	}
	friend bool operator < (person &pr, long k1)
	{
		return (pr.ID < k1);
	}
	friend bool operator <= (person &pr, long k1)
	{
		return (pr.ID <= k1);
	}
	friend bool operator > (person &pr, long k1)
	{
		return (pr.ID > k1);
	}
	friend bool operator >= (person &pr, long k1)
	{
		return (pr.ID >= k1);
	}
	friend bool operator == (person &pr, long k1)
	{
		return (pr.ID == k1);
	}
	friend bool operator != (person &pr, long k1)
	{
		return (pr.ID != k1);
	}

	friend bool operator < (long k1, person &pr)
	{
		return (k1 < pr.ID);
	}
	friend bool operator <= (long k1, person &pr)
	{
		return (k1 <= pr.ID);
	}
	friend bool operator > (long k1, person &pr)
	{
		return (k1 > pr.ID);
	}
	friend bool operator >= (long k1, person &pr)
	{
		return (k1 >= pr.ID);
	}
	friend bool operator == (long k1, person &pr)
	{
		return (k1 == pr.ID);
	}
	friend bool operator != (long k1, person &pr)
	{
		return (k1 != pr.ID);
	}

	friend bool operator < (person &pr1, person &pr2)
	{
		return (pr1.ID < pr2.ID);
	}
	friend bool operator <= (person &pr1, person &pr2)
	{
		return (pr1.ID < pr2.ID);
	}
	friend bool operator > (person &pr1, person &pr2)
	{
		return (pr1.ID > pr2.ID);
	}
	friend bool operator >= (person &pr1, person &pr2)
	{
		return (pr1.ID >= pr2.ID);
	}
	friend bool operator == (person &pr1, person &pr2)
	{
		return (pr1.ID == pr2.ID);
	}
	friend bool operator != (person &pr1, person &pr2)
	{
		return (pr1.ID != pr2.ID);
	}
	friend ostream& operator << (ostream &out, person &pr)
	{
//		out << "\nID:\t" << pr.ID;
//		out << "\nAge:\t" << pr.Age;
//		out << "\nName:\t" << pr.Name;
		out << setw(4) << pr.ID << '\t' << pr.Age << "    " << pr.Name;
		return out;
	}
	friend istream& operator >> (istream &in, person &pr)
	{
		in >> pr.ID >> pr.Age >> pr.Name;
		pr.key = pr.ID;
		return in;
	}
private:
	long ID;
	int Age;
	string Name;
};
