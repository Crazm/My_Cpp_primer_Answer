#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <set>

using namespace std;

class Test {
public:
	Test() = default;
	Test(const Test & r) {
		cout << "¿½±´¹¹Ôìº¯Êý" << endl;
	}
};

Test& fun(Test a) {
	Test t;
	return t;
}

int main() {
	Test t;
	fun(t);
	return 0;
}