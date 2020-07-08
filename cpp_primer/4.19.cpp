#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using namespace std;

int main() {
	list<string> str;
	string temp;
	while (cin >> temp) {
		str.push_back(temp);
	}
	for (auto i = str.begin(); i != str.end(); ++i) {
		cout << *i << " ";
	}
	return 0;
}