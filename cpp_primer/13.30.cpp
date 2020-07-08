#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class HasPtr {
	friend inline void swap(HasPtr &lhs, HasPtr &rhs);
public:
	//构造函数分配新的string和新的计数器，并将计数器初始化为1
	HasPtr(const string &s = string()) :
		ps(new string(s)), use(new int(1)), i(0) {}
	//拷贝构造函数拷贝所有三个数据成员，并递增计数器
	HasPtr(const HasPtr &rhs) :ps(rhs.ps), use(rhs.use), i(rhs.i) {
		++*use;
	}
	//拷贝运算符，右边的计数++，左边的计数--，若减到零，则把左边的内存释放，在把右边的值赋给左边
	HasPtr& operator=(HasPtr &rhs) {
		++*rhs.use;
		if (--*use == 0) {
			delete use;
			delete ps;
		}
		ps = rhs.ps;
		use = rhs.use;
		i = rhs.i;
		return *this;
	}
	~HasPtr() {
		if (--*use == 0) {	//若引用计数为0，则释放相应的内存
			delete use;
			delete ps;
		}
	}

private:
	string *ps;
	int *use;
	int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
	cout << "void swap(HasPtr &lhs, HasPtr &rhs)" << endl;
	//using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.use, rhs.use);
	swap(lhs.i, rhs.i);
}

int main() {
	HasPtr h1("hello"), h2("world");
	swap(h1, h2);

	return 0;
}