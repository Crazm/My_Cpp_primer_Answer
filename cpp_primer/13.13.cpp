#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>

using namespace std;

class destruct{
public:
	destruct(const string nam):name(nam) {
		cout << name << ":destruct()" << endl;
	}
	destruct(const destruct & rhs) {
		name = rhs.name;
		cout << name << ":destruct(const destruct & rhs)" << endl;
	}
	destruct& operator=(destruct &rhs) {
		cout << name << ":destruct& operator=(destruct &rhs)" << endl;
		name = rhs.name;
		return *this;
	}
	~destruct() {
		cout << name << ":~destruct()" << endl;
	}
private:
	string name;
};

int main() {
	destruct A("A");//���캯������
	destruct B("B");//���캯������
	destruct C("C");//���캯������
	destruct E(B);//���ÿ������캯������
	auto D = new vector<destruct>;
	B = C;	//�����Զ���Ŀ�����ֵ�����
	D->push_back(A);
	D->push_back(B);
	delete D;
	return 0;
}