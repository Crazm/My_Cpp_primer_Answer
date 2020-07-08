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

class HasPtr {		//类的行为像一个值
public:
	HasPtr(const string &s = string()) :id(0), name(new string(s)) {}
	HasPtr(const HasPtr &hp) :id(hp.id), name(new string(*hp.name)) {}
	HasPtr(HasPtr &&rhs) :name(rhs.name), id(rhs.id) {
		rhs.name = nullptr;
		rhs.id = 0;
	}
	HasPtr& operator=(const HasPtr &rhs) {
		auto ptr = new string(*rhs.name);
		delete name;
		id = rhs.id;
		name = ptr;
		return *this;
	}
	HasPtr& operator=(HasPtr rhs) {
		swap(*this, rhs);
		return rhs;
		return *this;
	}
	~HasPtr() { delete name; }
private:
	int id;
	string *name;
};

int main() {

	return 0;
}
