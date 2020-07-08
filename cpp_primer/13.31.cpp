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
	void swap( HasPtr &rhs) {
		cout << "void swap(HasPtr &lhs, HasPtr &rhs)" << endl;
		using std::swap;
		swap(ps, rhs.ps);
		swap(use, rhs.use);
		swap(i, rhs.i);
	}
	void swap(HasPtr &lhs, HasPtr &rhs) {
		lhs.swap(rhs);
	}
	bool operator<(HasPtr &p1) {
		//cout << *ps<< "<" << *p1.ps <<"	bool operator<(HasPtr &p1)" << endl;
		return *ps < *p1.ps;
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

 

int main() {
	vector<HasPtr> Has;
	Has.push_back(HasPtr("world"));
	Has.push_back(HasPtr("sgllo"));
	Has.push_back(HasPtr("hsfglo"));
	Has.push_back(HasPtr("jgf"));
	Has.push_back(HasPtr("zello"));
	sort(Has.begin(), Has.end());
	return 0;
}