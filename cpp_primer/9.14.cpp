#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main() {
	vector<string> str;
	
	list<char *> p = { "123456789" };
	str.assign(p.begin(), p.end());

	return 0;
}