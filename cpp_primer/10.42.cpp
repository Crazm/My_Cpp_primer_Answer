#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	list<string> str{ "sgf","agsd","havyd","sgf","jghwug","wqeuguguwqe","agsd","hsadgweuw" };
	str.sort();
	str.unique();
	for (auto &i : str)
		cout << i << " ";
	cout << endl;
	return 0;
}