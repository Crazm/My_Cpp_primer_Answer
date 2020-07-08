#include <iostream>
#include <string>
#include <vector>
using namespace std;


istream &fun(istream &is) {
	string str;
	while (is >> str)
		cout << str <<' ';
	is.clear();
	return is;
}

int main() {
	fun(cin);
	return 0;
}
