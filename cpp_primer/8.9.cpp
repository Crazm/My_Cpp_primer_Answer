#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


istringstream &fun(istringstream &is) {
	string str;
	while (is >> str)
		cout << str << ' ';
	is.clear();
	return is;
}

int main() {
	istringstream ss("hello world!");
	fun(ss);
	return 0;
}
