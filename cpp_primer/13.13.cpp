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
	destruct A("A");//构造函数构造
	destruct B("B");//构造函数构造
	destruct C("C");//构造函数构造
	destruct E(B);//利用拷贝构造函数构造
	auto D = new vector<destruct>;
	B = C;	//利用自定义的拷贝赋值运算符
	D->push_back(A);
	D->push_back(B);
	delete D;
	return 0;
}