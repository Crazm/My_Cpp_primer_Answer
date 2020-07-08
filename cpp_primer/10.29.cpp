#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	vector<string> str;
	ifstream in("fstest.txt");
	istream_iterator<string> string_it(in);
	istream_iterator<string> string_end;
	while (string_it != string_end)
		str.push_back(*string_it++);
	for (auto &i : str)
		cout << i << " ";
	return 0;
}