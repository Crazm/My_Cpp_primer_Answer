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
	HasPtr(const string &s = string()):
		ps(new string(s)),i(0){}
	HasPtr(const HasPtr &sou):
		ps(new string(*sou.ps)),i(sou.i){}
private:
	string *ps;
	int i;
};