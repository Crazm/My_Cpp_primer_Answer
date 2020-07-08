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
	//���캯�������µ�string���µļ�������������������ʼ��Ϊ1
	HasPtr(const string &s = string()) :
		ps(new string(s)), use(new int(1)), i(0) {}
	//�������캯�����������������ݳ�Ա��������������
	HasPtr(const HasPtr &rhs) :ps(rhs.ps), use(rhs.use), i(rhs.i) {
		++*use;
	}
	//������������ұߵļ���++����ߵļ���--���������㣬�����ߵ��ڴ��ͷţ��ڰ��ұߵ�ֵ�������
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
		if (--*use == 0) {	//�����ü���Ϊ0�����ͷ���Ӧ���ڴ�
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