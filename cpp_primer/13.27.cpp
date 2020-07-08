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
	HasPtr(const string &s = string()):
		ps(new string(s)),use(new int(1)),i(0){}
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

int main() {

	return 0;
}