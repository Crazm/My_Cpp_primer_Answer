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

class HasPtr {
public:
	HasPtr(const string &s = string()) :
		ps(new string(s)), i(0) {}
	HasPtr(const HasPtr &sou) :
		ps(new string(*sou.ps)), i(sou.i) {}
	HasPtr& operator=(const HasPtr &rhs) {
		string *p = new string(*rhs.ps);
		delete ps;
		ps = p;
		i = rhs.i;
		return *this;
	}
private:
	string *ps;
	int i;
};

int main() {

	return 0;
}